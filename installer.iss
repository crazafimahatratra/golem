; Script generated by the Inno Script Studio Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Golem"
#define MyAppPublisher "Chraz"
#define MyAppURL "https://github.com/crazafimahatratra"
#define MyAppExeName "Golem.exe"
#define MyAppVersion "1.0.0.1"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{6050B22E-FD3C-43C7-8CCB-F68119710D1A}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
LicenseFile=D:\Utilisateurs\fanambinantsoa\Documents\gpl-3.0.txt
InfoBeforeFile=D:\Utilisateurs\fanambinantsoa\Documents\gpl-3.0.txt
OutputDir=D:\Utilisateurs\fanambinantsoa\Documents\QtProjects\Golem\output
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes
VersionInfoVersion={#MyAppVersion}
VersionInfoCompany={#MyAppPublisher}
VersionInfoDescription=Light project and tasks manager.
VersionInfoCopyright=chraz - 2019
VersionInfoProductName={#MyAppName}
VersionInfoProductVersion={#MyAppVersion}
VersionInfoProductTextVersion={#MyAppVersion}

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\build-Golem-Desktop_Qt_5_11_1_MinGW_32bit-Release\release\Golem.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\plugins\sqldrivers\qsqlite.dll"; DestDir: "{app}\sqldrivers"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\plugins\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\plugins\printsupport\windowsprintersupport.dll"; DestDir: "{app}\printsupport"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\plugins\styles\qwindowsvistastyle.dll"; DestDir: "{app}\styles"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\bin\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\bin\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\bin\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\bin\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\bin\Qt5PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\bin\Qt5Sql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\bin\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\bin\Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\5.11.1\mingw53_32\bin\Qt5Multimedia.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\Tools\mingw530_32\opt\bin\libeay32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt\Qt5.11.1\Tools\mingw530_32\opt\bin\ssleay32.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
