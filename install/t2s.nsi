;///////////////////////////////////////////////////////////////////////////
;//

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

	;!insertmacro MUI_DEFAULT MUI_UNWELCOMEFINISHPAGE_BITMAP "setup.bmp"
	;!insertmacro MUI_DEFAULT MUI_WELCOMEFINISHPAGE_BITMAP "setup.bmp"

;--------------------------------
;Name and file

  Name "Text To Speech"
  outfile "bin\ts-setup.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\Clipboard Text To Speech"

  BrandingText " Text to Speech "

  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\T2S" ""

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "License.txt"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !define 	 	MUI_FINISHPAGE_RUN "$PROGRAMFILES\Clipboard Text To Speech\t2s.exe"
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"

    icon t2s.ico
    uninstallicon t2s.ico

;--------------------------------
;Installer Sections

Section "Install"

    SetShellVarContext all
	
    SetOutPath "$INSTDIR"

    ; Add your own files here...
    File  /oname=t2s.exe ..\release\t2s.exe
    File  readme.txt

    ; ---------------------------------------------------------------------
    SetOutPath "$INSTDIR"

    CreateDirectory "$SMPROGRAMS\Clipboard Text to Speech"
	
    CreateShortCut "$SMPROGRAMS\Clipboard Text to Speech\T2S.lnk" "$INSTDIR\T2S.exe" "" \
                    "$INSTDIR\T2S.exe" 0  SW_SHOWNORMAL

    CreateShortCut "$SMPROGRAMS\Clipboard Text to Speech\Readme.lnk"      "$INSTDIR\readme.txt"

    ;CreateShortCut "$QUICKLAUNCH\T2S.lnk" "$INSTDIR\T2S.exe"

    ;CreateShortCut "$SMPROGRAMS\Text to Speech\HTML Documentation.lnk" "$INSTDIR\html\index.html"

    CreateDirectory "$SMPROGRAMS\Clipboard Text to Speech\Tools"
    CreateShortCut "$SMPROGRAMS\Clipboard Text to Speech\Tools\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
    ;CreateShortCut "$SMPROGRAMS\Clipboard Text to Speech\Tools\License.lnk" "$INSTDIR\License.txt"
	
    ;CreateShortCut "$DESKTOP\T2S.lnk" "$INSTDIR\T2S.exe"

	;GetFileTime    "$DESKTOP\T2S.lnk" $R0 $R1

    ;Store installation folder
    ;WriteRegStr HKCU "Software\Clipboard Text to Speech" "" $INSTDIR
    ;Store installation timestamp
    ;WriteRegStr HKCU "Software\Text to Speech" "FirstRun1" $R0
    ;WriteRegStr HKCU "Software\Text to Speech" "FirstRun2" $R1

    ;Create uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"

    ; Create control panel unistaller
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\T2S"  "DisplayName" "T2S "
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\T2S"  "UninstallString" $INSTDIR\Uninstall.exe
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\T2S"  "DisplayIcon" $INSTDIR\T2S.exe,0"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\T2S"  "DisplayVersion" "Version 2.0"
    ;WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\T2S"  "HelpLink" "http://www.T2S.com"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\T2S"  "NoModify" 1
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\T2S"  "NoRepair" 1

SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

    SetShellVarContext all

    ;Delete "$QUICKLAUNCH\T2S.lnk"
    ;Delete "$DESKTOP\T2S.lnk"

	;DeleteRegValue	HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "T2S"
    ;DeleteRegKey 	HKCU "Software\T2S"
    ;DeleteRegKey 	HKCR ".T2S"
    ;DeleteRegKey 	HKCR "T2S.FileHandler"
	
    DeleteRegKey 	HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\T2S"

    RMDir /r "$SMPROGRAMS\Clipboard Text to Speech\"
    RMDir /r "$INSTDIR"


SectionEnd

