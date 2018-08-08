set QT_TOOLS_MINGW_PATH=C:\Qt\Qt5.8.0\Tools\mingw530_32\bin
set QT_TOOLS_PATH=C:\Qt\Qt5.8.0\5.8\mingw53_32\bin

set PORGRAMNAME=pivmake-gui

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------
set PATH=%PATH%;%QT_TOOLS_MINGW_PATH%

rmdir /S /Q build
mkdir build

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------
rmdir /S /Q libpdsdatafunc
bzr branch http://bzr.savannah.nongnu.org/r/pdsplibrary/libpdsdatafunc
cd libpdsdatafunc\extras\qtcreator
timeout 3 > NUL

:hito1
if EXIST "..\\..\\..\\build\\extras\\lib\\libpdsdatafunc.a" (
    dir ..\..\..\build\extras\lib\
    echo The lib files were installed 

) else (
    dir ..\..\..\build\extras\lib\
    timeout 3 > NUL
    echo The lib files were not installed trying newly

    "%QT_TOOLS_PATH%\qmake.exe" libpdsdatafunc.pro -spec win32-g++ PREFIX=..\..\..\build\extras
    "%QT_TOOLS_MINGW_PATH%\mingw32-make.exe"
    "%QT_TOOLS_MINGW_PATH%\mingw32-make.exe" install


    goto :hito1
)
cd ..\..\..\

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------
rmdir /S /Q libpdsra
bzr branch http://bzr.savannah.nongnu.org/r/pdsplibrary/libpdsra
cd libpdsra\extras\qtcreator
timeout 3 > NUL

:hito2
if EXIST "..\\..\\..\\build\\extras\\lib\\libpdsra.a" (
    dir ..\..\..\build\extras\lib\
    echo The lib files were installed 

) else (
    dir ..\..\..\build\extras\lib\
    timeout 3 > NUL
    echo The lib files were not installed trying newly

    "%QT_TOOLS_PATH%\qmake.exe" libpdsra.pro -spec win32-g++ PREFIX=..\..\..\build\extras
    "%QT_TOOLS_MINGW_PATH%\mingw32-make.exe"
    "%QT_TOOLS_MINGW_PATH%\mingw32-make.exe" install


    goto :hito2
)
cd ..\..\..\

rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------
rmdir /S /Q libpdsdic
bzr branch http://bzr.savannah.nongnu.org/r/pdsplibrary/libpdsdic
cd libpdsdic\extras\qtcreator
timeout 3 > NUL

:hito3
if EXIST "..\\..\\..\\build\\extras\\lib\\libpdsdic.a" (
    dir ..\..\..\build\extras\lib\
    echo The lib files were installed 

) else (
    dir ..\..\..\build\extras\lib\
    timeout 3 > NUL
    echo The lib files were not installed trying newly

    "%QT_TOOLS_PATH%\qmake.exe" libpdsdic.pro -spec win32-g++ PREFIX=..\..\..\build\extras
    "%QT_TOOLS_MINGW_PATH%\mingw32-make.exe"
    "%QT_TOOLS_MINGW_PATH%\mingw32-make.exe" install

    goto :hito3
)
cd ..\..\..\
rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------
mkdir output
mkdir output\win
mkdir output\bin\platforms
cd build
"%QT_TOOLS_PATH%\qmake.exe" ..\..\%PORGRAMNAME%.pro -spec win32-g++ PREFIX=win\output
"%QT_TOOLS_MINGW_PATH%\mingw32-make.exe"
"%QT_TOOLS_MINGW_PATH%\mingw32-make.exe" install
"%QT_TOOLS_PATH%\qmake.exe" ..\..\%PORGRAMNAME%.pro -spec win32-g++ PREFIX=win\output
"%QT_TOOLS_MINGW_PATH%\mingw32-make.exe"
"%QT_TOOLS_MINGW_PATH%\mingw32-make.exe" install
"%QT_TOOLS_PATH%\qmake.exe" ..\..\%PORGRAMNAME%.pro -spec win32-g++ PREFIX=win\output
"%QT_TOOLS_MINGW_PATH%\mingw32-make.exe"
"%QT_TOOLS_MINGW_PATH%\mingw32-make.exe" install
cd ..

copy /Y "%QT_TOOLS_PATH%\libgcc_s_dw2-1.dll" output\bin\
copy /Y "%QT_TOOLS_PATH%\libstdc++-6.dll" output\bin\
copy /Y "%QT_TOOLS_PATH%\libwinpthread-1.dll" output\bin\
copy /Y "%QT_TOOLS_PATH%\Qt5Widgets.dll" output\bin\
copy /Y "%QT_TOOLS_PATH%\Qt5Core.dll" output\bin\
copy /Y "%QT_TOOLS_PATH%\Qt5Gui.dll" output\bin\

copy /Y "%QT_TOOLS_PATH%\..\plugins\platforms\qwindows.dll" output\bin\platforms
copy /Y %PORGRAMNAME%.nsi output\win
rem ----------------------------------------------------------------------------
rem ----------------------------------------------------------------------------

rem rmdir /S /Q build


