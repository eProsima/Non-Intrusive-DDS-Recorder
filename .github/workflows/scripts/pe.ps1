# PE inspection helpers shared by the Windows CI steps.
#
# Installing the pcap runtime and reporting the recorder's dependency chain both come down to
# reading a PE header: one to pick the right architecture and the loadable build out of an
# installer that ships several, the other to walk the import chain. One copy, so a correction to
# the parsing serves both.

function Get-PEMachine([string] $path) {
    # The IMAGE_FILE_HEADER Machine field, or 0 for anything that is not a PE.
    try {
        $bytes = [System.IO.File]::ReadAllBytes($path)
    } catch { return 0 }
    if ($bytes.Length -lt 0x40) { return 0 }
    if ([BitConverter]::ToUInt16($bytes, 0) -ne 0x5A4D) { return 0 }          # MZ
    $pe = [BitConverter]::ToInt32($bytes, 0x3C)
    if ($pe -le 0 -or $pe + 6 -gt $bytes.Length) { return 0 }
    if ([BitConverter]::ToUInt32($bytes, $pe) -ne 0x00004550) { return 0 }    # PE\0\0
    return [BitConverter]::ToUInt16($bytes, $pe + 4)
}

function Get-PEArchName([int] $machine) {
    switch ($machine) {
        0x8664  { 'x64' }
        0x014C  { 'x86' }
        0xAA64  { 'arm64' }
        0       { '-' }
        default { ('0x{0:X4}' -f $machine) }
    }
}

function Get-PEImports([string] $path) {
    # The names in the import directory: the modules the loader must find before this image can
    # start. Delay loaded imports live in a different directory and are deliberately not read,
    # because their absence is not a load failure.
    try {
        $bytes = [System.IO.File]::ReadAllBytes($path)
    } catch { return @() }
    if ($bytes.Length -lt 0x40) { return @() }
    if ([BitConverter]::ToUInt16($bytes, 0) -ne 0x5A4D) { return @() }
    $pe = [BitConverter]::ToInt32($bytes, 0x3C)
    if ($pe -le 0 -or $pe + 0x18 -gt $bytes.Length) { return @() }
    if ([BitConverter]::ToUInt32($bytes, $pe) -ne 0x00004550) { return @() }

    $sectionCount = [BitConverter]::ToUInt16($bytes, $pe + 6)
    $optionalSize = [BitConverter]::ToUInt16($bytes, $pe + 20)
    $optional     = $pe + 24
    $magic        = [BitConverter]::ToUInt16($bytes, $optional)
    # The data directory follows the optional header's fixed part, whose size differs between
    # PE32 (0x60) and PE32+ (0x70).
    $dataDir = if ($magic -eq 0x20B) { $optional + 0x70 } else { $optional + 0x60 }
    if ($dataDir + 16 -gt $bytes.Length) { return @() }
    $importRva = [BitConverter]::ToUInt32($bytes, $dataDir + 8)
    if ($importRva -eq 0) { return @() }

    $sections = @()
    $base = $optional + $optionalSize
    for ($i = 0; $i -lt $sectionCount; $i++) {
        $s = $base + ($i * 40)
        if ($s + 40 -gt $bytes.Length) { break }
        $sections += [pscustomobject]@{
            Virtual = [BitConverter]::ToUInt32($bytes, $s + 12)
            Size    = [Math]::Max([BitConverter]::ToUInt32($bytes, $s + 8),
                                  [BitConverter]::ToUInt32($bytes, $s + 16))
            Raw     = [BitConverter]::ToUInt32($bytes, $s + 20)
        }
    }
    function Convert-Rva([uint32] $rva) {
        foreach ($s in $sections) {
            if ($rva -ge $s.Virtual -and $rva -lt ($s.Virtual + $s.Size)) {
                return [int]($rva - $s.Virtual + $s.Raw)
            }
        }
        return -1
    }

    $names = @()
    $entry = Convert-Rva $importRva
    if ($entry -lt 0) { return @() }
    while ($entry + 20 -le $bytes.Length) {
        $nameRva = [BitConverter]::ToUInt32($bytes, $entry + 12)
        if ($nameRva -eq 0) { break }
        $at = Convert-Rva $nameRva
        if ($at -lt 0) { break }
        $end = $at
        while ($end -lt $bytes.Length -and $bytes[$end] -ne 0) { $end++ }
        $names += [System.Text.Encoding]::ASCII.GetString($bytes, $at, $end - $at)
        $entry += 20
    }
    return $names
}

function Resolve-Module([string] $name, [string[]] $searchDirs = @()) {
    # Where the loader would find this module: a path, the string 'apiset' for the api-ms-win-*
    # and ext-ms-* names that come from the API set schema rather than from disk, or $null when
    # nothing provides it.
    if ($name -match '^(api-ms-win|ext-ms-)') { return 'apiset' }
    $dirs = @($searchDirs) + @("$env:WINDIR\System32", "$env:WINDIR") + ($env:PATH -split ';')
    foreach ($dir in $dirs) {
        if ([string]::IsNullOrWhiteSpace($dir)) { continue }
        $candidate = Join-Path $dir $name
        if (Test-Path $candidate -PathType Leaf) { return (Resolve-Path $candidate).Path }
    }
    return $null
}
