;NSIS Modern User Interface
;Welcome/Finish Page Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

!define APPNAME     "${APPFILENAME}"
!define APPFILENAME "pivmake-gui"
!define APPVERSION  "0.0.1"
!define APPARCH     "i386"

  ;Name and file
  Name "${APPNAME}"
  OutFile "${APPFILENAME}_${APPVERSION}_${APPARCH}_install.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\${APPNAME}"

  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\${APPNAME}" ""

  ;Request application privileges for Windows 7 (dejalo desabilitado da problemas)
  ;RequestExecutionLevel user

;--------------------------------
;Variables

  Var StartMenuFolder

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

  !define WELCOME_TITLE '${APPNAME}'
  !define WELCOME_TEXT 'Welcome to the install setup of ${APPNAME} program.'


  !define FINISH_TITLE 'Thanks for installing ${APPNAME}'

;--------------------------------
;Pages
  !define MUI_WELCOMEPAGE_TITLE '${WELCOME_TITLE}'
  !define MUI_WELCOMEPAGE_TEXT '${WELCOME_TEXT}'
  !insertmacro MUI_PAGE_WELCOME
  ;!insertmacro MUI_PAGE_LICENSE "share\doc\${APPFILENAME}\COPYING"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  
  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\${APPNAME}" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
  !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder

  !define MUI_FINISHPAGE_TITLE '${FINISH_TITLE}'    
  !insertmacro MUI_PAGE_INSTFILES

  !define MUI_FINISHPAGE_RUN
  !define MUI_FINISHPAGE_RUN_TEXT "Start a shortcut"
  !define MUI_FINISHPAGE_RUN_FUNCTION "LaunchLink"
  !insertmacro MUI_PAGE_FINISH

Function LaunchLink
  ExecShell "" "$INSTDIR\bin\${APPFILENAME}.exe"
FunctionEnd

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections


Section "${APPNAME}" SecDummy
  SetOverwrite on

  CreateDirectory "$INSTDIR"
  CreateDirectory "$INSTDIR\bin"
  CreateDirectory "$INSTDIR\share"
  CreateDirectory "$INSTDIR\share\doc"
  CreateDirectory "$INSTDIR\share\doc\${APPFILENAME}"
  CreateDirectory "$INSTDIR\share\${APPFILENAME}"
  CreateDirectory "$INSTDIR\share\${APPFILENAME}\icons"
  CreateDirectory "$INSTDIR\share\applications"


  SetOutPath "$INSTDIR\share\doc\${APPFILENAME}"
  File /r "..\share\doc\${APPFILENAME}\*"

  SetOutPath "$INSTDIR\share\${APPFILENAME}\icons"
  File /r "..\share\${APPFILENAME}\icons\*"

  SetOutPath "$INSTDIR\share\applications"
  File /r "..\share\applications\*"

  SetOutPath "$INSTDIR\bin"
  File /r "..\bin\*"


  ;Store installation folder
  WriteRegStr HKCU "Software\${APPNAME}" "" "$INSTDIR"

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
    CreateShortCut  "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"  "$INSTDIR\Uninstall.exe"
	CreateShortCut  "$SMPROGRAMS\$StartMenuFolder\${APPNAME}.lnk" "$INSTDIR\bin\${APPFILENAME}.exe"
	CreateShortCut  "$DESKTOP\${APPNAME}.lnk"                     "$INSTDIR\bin\${APPFILENAME}.exe"
	
  
  !insertmacro MUI_STARTMENU_WRITE_END
  
SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecDummy ${LANG_ENGLISH} "${APPNAME} program"

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecDummy} $(DESC_SecDummy)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...
  
  Delete "$INSTDIR\Uninstall.exe"

  RMDir /r "$INSTDIR"
  
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
    
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\${APPNAME}.lnk"
  Delete "$DESKTOP\${APPNAME}.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"
  
  DeleteRegKey /ifempty HKCU "Software\${APPNAME}"

SectionEnd

