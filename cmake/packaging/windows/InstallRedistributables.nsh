!include LogicLib.nsh
!include x64.nsh

!macro InstallRedistributables ARCH
    push ${ARCH}
    call InstallRedistributables_
!macroend

Function InstallRedistributables_
    exch $R0

    StrCmp $R0 "1" 0 CALL_REDIST
        !define VS2019Installer64 "vc_redist.x64.exe"
        File /oname=$TEMP\${VS2019Installer64} "${REDIS_DIR}\${VS2019Installer64}"
        ExecWait '"$TEMP\${VS2019Installer64}" /quiet /norestart'
        goto finish
    CALL_REDIST:
        !define VS2019Installer86 "vc_redist.x86.exe"
        File /oname=$TEMP\${VS2019Installer86} "${REDIS_DIR}\${VS2019Installer86}"
        ExecWait '"$TEMP\${VS2019Installer86}" /quiet /norestart'

    finish:

FunctionEnd
