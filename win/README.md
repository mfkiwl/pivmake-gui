#Installation Process

## Dependencies of the program

* **Qt5** developer files.

## Building the project in Windows

For compile the program in windows we need:

1. Download **qtcreator** (qt-opensource-windows-x86-mingw530-5.8.0.exe) from https://www.qt.io/download-open-source/ and install in `C:\`.
2. Open **qtcreator** select the `pivmake-gui.pro` file and **Build all**. Or:

    ./makewin.bat


## Directory hierarchy

For the program works correctly, only are necessary the **pivmake-gui** program file and the **shared** directory, so that these fulfill the next directory hierarchy:

    ./win/  pivmake-gui.nsi

    ./bin/  pivmake-gui.exe
            libgcc_s_dw2-1.dll
            libstdc++-6.dll
            libwinpthread-1.dll
            Qt5Widgets.dll
            Qt5Core.dll
            Qt5Gui.dll

            
    ./bin/platforms/qwindows.dll
    
    ./share/doc/pivmake-gui/    pivmake-gui.pdf
    
    ./share/pivmake-gui/icons/  pivmake-gui.png

    ./share/applications/           pivmake-gui.desktop


The `*.dll` files in `bin` can be found in `C:\Qt\Qt5.8.0\5.8\mingw53_32\bin` or `C:\Qt\Qt5.8.0\5.8\mingw53_32\plugins\`


