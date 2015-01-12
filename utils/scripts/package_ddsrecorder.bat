:: This script pack DDSRecorder library for any platform in Windows.
::
:: This script needs the next environment variables to be run.
:: - SVN_BIN_DIR: Directory with the subversion binaries.
:: - LIBREOFFICE_BIN_DIR: Directory with the LibreOffice binaries.
:: - NSIS_BIN_DIR: Directory with the NSIS installer libraries.
:: - EPROSIMADIR: URL to the directory with common sources of eProsima.
:: Also this script needs the eProsima.documentation.changeVersion macro installed in the system.

setlocal EnableDelayedExpansion
setlocal EnableExpansion
@echo off

:: Initialize the returned value to 0 (all succesfully)
set errorstatus=0

if "%EPROSIMADIR%"=="" (
    echo "EPROSIMADIR environment variable has to be set"
    set errorstatus=-1
    goto :exit
)

:: Go to root directory
cd "..\.."

:: Update and compile CDR library.
cd "thirdparty\fastcdr"
:: Update CDR library.
rmdir /S /Q lib\i86Win32VS2010
rmdir /S /Q lib\x64Win64VS2010
:: Compile CDR library.
cd "utils\scripts"
call build_cdr.bat
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
cd "..\..\..\.."

:: Get the current vesion of DDSRecorder
call thirdparty\dev-env\scripts\common_pack_functions.bat :getVersionFromCPP VERSION src\version.cpp
if not %errorstatus%==0 goto :exit

:: Compile DDSRecoder application.
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
rmdir /S /Q lib\i86Win32VS2010
rmdir /S /Q lib\x64Win64VS2010
:: Compile DDSRecorder application.
cd "utils\scripts"
call build_ddsrecorder.bat
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
cd "..\.."

:: Create PDFS from documentation.
cd "doc"
:: Installation manual
soffice.exe --headless "macro:///eProsima.documentation.changeVersion(%CD%\Installation Manual.odt,%VERSION%)"
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
:: User manual
soffice.exe --headless "macro:///eProsima.documentation.changeVersion(%CD%\User Manual.odt,%VERSION%)"
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
:: Release notes
soffice.exe --headless "macro:///eProsima.documentation.changeVersion(%CD%\Release Notes.odt,%VERSION%)"
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
cd ".."

:: Create README
soffice.exe --headless "macro:///eProsima.documentation.changeVersionToHTML(%CD%\README.odt,%VERSION%)"
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit

:: Create installers.
cd "utils\installers\windows"
:: Win32 installer.
makensis.exe /DVERSION="%VERSION%" Setup_Win32.nsi
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
:: Win64 installer.
makensis.exe /DVERSION="%VERSION%" Setup_Win64.nsi
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
cd "..\..\.."

goto :exit

:: Function exit ::
:exit
if %errorstatus%==0 (echo "PACKAGING SUCCESSFULLY") else (echo "PACKAGING FAILED")
exit /b %errorstatus%
goto :EOF
