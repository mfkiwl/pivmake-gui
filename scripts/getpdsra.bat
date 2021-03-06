set QT_TOOLS_MINGW_PATH=C:\Qt\Qt5.8.0\Tools\mingw530_32\bin
set QT_TOOLS_PATH=C:\Qt\Qt5.8.0\5.8\mingw53_32\bin
set MYLIBRARY=libpdsra

SET BATCHDIR=%~dp0

SET INSTALLDIR=%~1

IF "%INSTALLDIR%"=="" (
    SET "INSTALLDIR=%BATCHDIR%..\extras"
)

mkdir "%INSTALLDIR%"

if EXIST "%MYLIBRARY%\README.md" (
    @echo .
) else (
    @echo .
    @echo Trying download %MYLIBRARY% from bazaar repository
    bzr branch http://bzr.savannah.nongnu.org/r/pdsplibrary/%MYLIBRARY%
)

cd %MYLIBRARY%\extras\qtcreator
timeout 3 > NUL

if EXIST "%QT_TOOLS_PATH%\qmake.exe" (


:hito1
    if EXIST "%INSTALLDIR%\\lib\\%MYLIBRARY%.a" (

        echo The lib files were installed

    ) else (
        timeout 3 > NUL
        echo The lib files were not installed trying newly

        "%QT_TOOLS_PATH%\qmake.exe" %MYLIBRARY%.pro -spec win32-g++ PREFIX="%INSTALLDIR%"
        "%QT_TOOLS_MINGW_PATH%\mingw32-make.exe"
        "%QT_TOOLS_MINGW_PATH%\mingw32-make.exe" install
        "%QT_TOOLS_MINGW_PATH%\mingw32-make.exe" clean

        goto :hito1
    )



)

cd ..\..\..\
