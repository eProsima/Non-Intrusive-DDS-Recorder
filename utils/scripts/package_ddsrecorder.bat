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

:: Update and compile CDR library.
cd "..\..\..\CDR"
:: Update CDR library.
svn update
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
:: Compile CDR library.
cd "utils\scripts"
call build_cdr.bat
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit

cd "..\..\..\DDSRecorder"

:: Get the current vesion of DDSRecorder
call :getVersion

:: Update and compile DDSRecoder application.
:: Update DDSRecorder application.
svn update
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
:: Compile DDSRecorder application.
cd "utils\scripts"
call build_ddsrecorder.bat
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit

:: Create PDFS from documentation.
cd "..\..\doc"
:: Installation manual
soffice.exe --headless "macro:///eProsima.documentation.changeVersion(%CD%\\Installation Manual.odt,%VERSION%)"
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
:: User manual
soffice.exe --headless "macro:///eProsima.documentation.changeVersion(%CD%\\User Manual.odt,%VERSION%)"
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit

:: Create installers.
cd "..\utils\installers\windows"
:: Win32 installer.
makensis.exe /DVERSION="%VERSION%" Setup_Win32.nsi
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
:: Win64 installer.
makensis.exe /DVERSION="%VERSION%" Setup_Win64.nsi
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit

goto :exit

:: Function to get the current version of the product ::
:getVersion
echo Getting version
set /p "VERSION="<"src\version.cpp"
set errorstatus=%ERRORLEVEL%
if not %errorstatus%==0 goto :exit
set VERSION=%VERSION:~21,-1%
echo Current version %VERSION%
goto :EOF

:: Function exit ::
:exit
if %errorstatus%==0 (echo "PACKAGING SUCCESSFULLY") else (echo "PACKAGING FAILED")
exit /b %errorstatus%
goto :EOF
