set QT_TOOLS_MINGW_PATH=C:\Qt\Qt5.8.0\Tools\mingw530_32\bin
set QT_TOOLS_PATH=C:\Qt\Qt5.8.0\5.8\mingw53_32\bin


set PATH=%PATH%;%QT_TOOLS_MINGW_PATH%
REM echo %PATH%
mkdir build
mkdir output
mkdir output\win
mkdir output\bin\platforms
cd build
"%QT_TOOLS_PATH%\qmake.exe" ..\..\pivmake-gui.pro -spec win32-g++ PREFIX=win\output
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
copy /Y pivmake-gui.nsi output\win

rmdir /S /Q build

