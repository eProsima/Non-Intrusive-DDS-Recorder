# Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

!include x64.nsh

Var X64VS2015Needed
Var I86VS2015Needed

Function InstallRedistributables

    StrCpy $X64VS2015Needed "1"
    StrCpy $I86VS2015Needed "1"

    # Check if it is necessary to install to x64VS2015
    ${If} ${RunningX64}
	    ClearErrors
            SetRegView 64
            ReadRegStr $0 HKLM "SOFTWARE\Classes\Installer\Dependencies\{3ee5e5bb-b7cc-4556-8861-a00a82977d6c}" "Version"
            IfErrors 0 VC2015RedistInstalled
            StrCpy $X64VS2015Needed "0"
    ${Else}
	    ClearErrors
            ReadRegStr $0 HKLM "SOFTWARE\Classes\Installer\Dependencies\{23daf363-3020-4059-b3ae-dc4ad39fed19}" "Version"
            IfErrors 0 VC2015RedistInstalled
            StrCpy $I86VS2015Needed "0"
    ${EndIf}

    VC2015RedistInstalled:

    ${If} ${RunningX64}
        StrCmp $X64VS2015Needed "1" notinstall2015 install2015
    ${Else}
        StrCmp $I86VS2015Needed "1" notinstall2015 install2015
    ${EndIf}

    install2015:
    messageBox MB_YESNO|MB_ICONQUESTION "$(^Name) needs Visual Studio 2015 Redistributable packages.$\nDo you want to download and install them?" IDNO notinstall2015

    ${If} ${RunningX64}
        NSISdl::download http://download.microsoft.com/download/C/E/5/CE514EAE-78A8-4381-86E8-29108D78DBD4/VC_redist.x64.exe $TEMP\vcredist_x64.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x64.exe"
        Goto +2
        MessageBox MB_OK "vcredist_x64.exe download failed: $R0"
    ${Else}
        NSISdl::download http://download.microsoft.com/download/C/E/5/CE514EAE-78A8-4381-86E8-29108D78DBD4/VC_redist.x86.exe $TEMP\vcredist_x86.exe
        Pop $R0 ; Get the return value
        StrCmp $R0 "success" 0 +3
        ExecWait "$TEMP\vcredist_x86.exe"
        Goto +2
        MessageBox MB_OK "vcredist_x86.exe download failed: $R0"
    ${EndIf}

    notinstall2015:

FunctionEnd
