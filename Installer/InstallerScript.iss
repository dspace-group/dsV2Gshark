// DO NOT CHANGE VERSION HERE! Run update_version.bat
#define AppVer "2.0.0"
#define AppId "dsV2Gshark"
#define Timestamp GetDateTimeString('yymmdd_hhnnss', '', '')

// plugin uninstaller is started if installed version is below this
#define MinUpdateVersion '1.5.0'  

[Setup]
AppId={#AppId}
AppName=dSPACE V2Gshark Wireshark Plugin
DefaultGroupName=dSPACE V2Gshark Wireshark Plugin
AppVersion={#AppVer}
VersionInfoVersion={#AppVer}
AppPublisher=dSPACE GmbH
AppCopyright=Copyright 2024, dSPACE GmbH. All rights reserved.
WizardStyle=modern
WizardSizePercent=135
DefaultDirName={code:GetDefaultDirName}
Compression=lzma2
SolidCompression=yes
ChangesEnvironment=no
DisableDirPage=no
PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=dialog
UsePreviousPrivileges=no
OutputBaseFilename=dsV2Gshark_{#AppVer}_Win64_Setup
DirExistsWarning=no
DisableWelcomePage=no
LanguageDetectionMethod=none
AppendDefaultDirName=no
UsePreviousAppDir=no
UsedUserAreasWarning=no

[Languages]
Name: "dsV2Gshark_strings"; MessagesFile: "strings.isl"

[Types]
Name: "full"; Description: "Full installation"
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[CustomMessages]
Linebreak=%n

[Components]
Name: "plugin"; Description: "Plugin files"; Types: full custom; Flags: fixed
Name: "plugin/dissectors"; Description: "V2G dissectors"; Types: full custom; Flags: fixed
Name: "plugin/decoder"; Description: "EXI decoder (powered by chargebyte cbexigen)"; Types: full custom; Flags: fixed
Name: "plugin/decoder/din"; Description: "DIN 70121 support"; Types: full custom; Flags: fixed
Name: "plugin/decoder/iso2"; Description: "ISO 15118-2 support"; Types: full custom; Flags: fixed
Name: "plugin/decoder/iso20"; Description: "ISO 15118-20 support (experimental)"; Types: full custom; Flags: fixed
Name: "plugin/autoschema"; Description: "Automatic schema detection"; Types: full custom; Flags: fixed
Name: "plugin/battery_data_exchange"; Description: "Dissector for Battery Data Exchange Protocol"; Types: full custom; Flags: fixed
Name: "plugin/autodecrypt"; Description: "Live TLS decryption with disclosed master secret from UDP packet"; Types: full custom;
Name: "plugin/hpav_v2g_diagnostic"; Description: "Additional dissector for V2G related Homeplug AV packets"; Types: full custom;
Name: "examples"; Description: "Example PCAPs of CCS charging sessions"; Types: full custom;
Name: "profile"; Description: "Add dsV2Gshark profile to Wireshark"; Types: full
Name: "profile/activate"; Description: "Activate dsV2Gshark profile after installation"; Types: full
Name: "profile/buttons"; Description: "Add filter buttons"; Types: full
Name: "profile/colorfilters"; Description: "Coloring rules for V2G messages"; Types: full
Name: "profile/iograph"; Description: "Wireshark I/O Graphs for V2G messages"; Types: full

[Files]
Source: "..\Wireshark\plugins\v2gcommon.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/dissectors
Source: "..\Wireshark\plugins\v2gmsg.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/dissectors
Source: "..\Wireshark\plugins\v2gtp.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/dissectors
Source: "..\Wireshark\plugins\v2gsdp.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/dissectors
Source: "..\Wireshark\plugins\v2gtlssecret.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/autodecrypt
Source: "..\Wireshark\plugins\v2ghpscs.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/hpav_v2g_diagnostic
Source: "..\Wireshark\v2gLib*.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs; Components: plugin/decoder
Source: "..\Wireshark\plugins\v2gvasbatterydata.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/battery_data_exchange
Source: "..\Wireshark\battery_data_exchange.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs; Components: plugin/battery_data_exchange
Source: "..\Wireshark\plugins\v2gexamples.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: examples
Source: "..\Wireshark\dsV2Gshark_examples\*.pcap"; DestDir: "{app}\dsV2Gshark_examples"; Flags: ignoreversion recursesubdirs skipifsourcedoesntexist; Components: examples
Source: "..\Wireshark\dsV2Gshark_examples\*.pcapng"; DestDir: "{app}\dsV2Gshark_examples"; Flags: ignoreversion recursesubdirs skipifsourcedoesntexist; Components: examples
Source: "..\Wireshark\dsV2Gshark_examples\README.md"; DestDir: "{app}\dsV2Gshark_examples"; Flags: ignoreversion recursesubdirs; Components: examples
Source: "..\Wireshark\profiles\dsV2Gshark\preferences"; DestDir: "{app}\profiles\dsV2Gshark\"; Flags: ignoreversion; Components: profile
Source: "..\Wireshark\profiles\dsV2Gshark\recent"; DestDir: "{app}\profiles\dsV2Gshark\"; Flags: ignoreversion; Components: profile
Source: "..\Wireshark\profiles\dsV2Gshark\dfilter_buttons"; DestDir: "{app}\profiles\dsV2Gshark\"; Flags: ignoreversion; Components: profile/buttons
Source: "..\Wireshark\profiles\dsV2Gshark\io_graphs"; DestDir: "{app}\profiles\dsV2Gshark\"; Flags: ignoreversion; Components: profile/iograph
Source: "..\Wireshark\profiles\dsV2Gshark\colorfilters"; DestDir: "{app}\profiles\dsV2Gshark\"; Flags: ignoreversion; Components: profile/colorfilters
Source: "..\LICENSE"; DestDir: "{app}"; DestName: "dsV2Gshark_LICENSE.txt"; Flags: ignoreversion;
Source: "..\OSSAcknowledgements.txt"; DestDir: "{app}"; DestName: "dsV2Gshark_OSSAcknowledgements.txt"; Flags: ignoreversion recursesubdirs;
Source: "dsV2Gshark_README.txt"; DestDir: "{app}"; DestName: "dsV2Gshark_README.txt"; Flags: ignoreversion;

[InstallDelete]
Type: filesandordirs; Name: "{app}\v2gLuaDecoder.dll"
Type: filesandordirs; Name: "{app}\v2gX509CertInfos.dll"
Type: filesandordirs; Name: "{app}\luaV2Gdecoder.dll"
Type: filesandordirs; Name: "{app}\X509CertInfos.dll"
Type: filesandordirs; Name: "{app}\plugins\v2gmsg_generic.lua"
Type: filesandordirs; Name: "{app}\plugins\v2gshared.lua"
Type: filesandordirs; Name: "{app}\plugins\v2gllc.lua"

[Code]
const
  RegistryPath1 = 'Software\Microsoft\Windows\CurrentVersion\Uninstall\dsV2Gshark_is1';
  RegistryPath2 = 'Software\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\dsV2Gshark_is1';

function GetDefaultDirName(Param: String): String;
begin
  if IsAdmin then
    Result := 'C:\Program Files\Wireshark'
  else
    Result := ExpandConstant('{userappdata}\Wireshark');
end;

function EndsWith(const Str, SubStr: string): Boolean;
begin
  Result := (Length(Str) >= Length(SubStr)) and
            (Copy(Str, Length(Str) - Length(SubStr) + 1, Length(SubStr)) = SubStr);
end;

function InstallInAppData: Boolean;
begin
  Result := EndsWith(ExpandConstant('{app}'), '\AppData\Roaming\Wireshark');
end;

function GetInstalledVersion: String;
var
  InstalledVersion: String;
begin
  if RegQueryStringValue(HKLM, RegistryPath1, 'DisplayVersion', InstalledVersion) then
    Result := InstalledVersion
  else if RegQueryStringValue(HKLM, RegistryPath2, 'DisplayVersion', InstalledVersion) then
    Result := InstalledVersion
  else if RegQueryStringValue(HKCU, RegistryPath1, 'DisplayVersion', InstalledVersion) then
    Result := InstalledVersion
  else if RegQueryStringValue(HKCU, RegistryPath2, 'DisplayVersion', InstalledVersion) then
    Result := InstalledVersion
  else
    Result := '';
end;

procedure RunUninstaller;
var
  UninstallString: String;
  ResultCode: Integer;
begin
  if not RegQueryStringValue(HKLM, RegistryPath1, 'UninstallString', UninstallString) then
    if not RegQueryStringValue(HKLM, RegistryPath2, 'UninstallString', UninstallString) then
      if not RegQueryStringValue(HKCU, RegistryPath1, 'UninstallString', UninstallString) then
        if not RegQueryStringValue(HKCU, RegistryPath2, 'UninstallString', UninstallString) then
        begin
          MsgBox('Uninstaller not found! Please uninstall the plugin manually before continuing.', mbError, MB_OK);
          Exit
        end;
  
    ShellExec('', UninstallString, '/SILENT', '', SW_SHOWNORMAL, ewWaitUntilTerminated, ResultCode);
    if ResultCode <> 0 then
      MsgBox('Failed to uninstall old version! Please uninstall the plugin manually before continuing.' + #13#10#13#10 + 'Note: This may happen if Wireshark has been updated automatically. In this case, simply continue with this installer.', mbError, MB_OK);
end;

function HasWriteAccessToApp: Boolean;
var
  FileName: string;
begin
  FileName := AddBackslash(WizardDirValue) + 'writetest.tmp';
  Result := SaveStringToFile(FileName, 'test', False);
  if Result then
  begin
    Log(Format(
      'Have write access to the last installation path [%s]', [WizardDirValue]));
    DeleteFile(FileName);
  end
  else
  begin
    Log(Format('Does not have write access to the last installation path [%s]', [
      WizardDirValue]));
  end;
end;

function GetWiresharkConfigPath: string;
begin
  if FileExists(ExpandConstant('{app}\..\..\WiresharkPortable64.exe')) then
    Result := ExpandConstant('{app}\..\..\Data\')
  else
    Result := ExpandConstant('{userappdata}\Wireshark\');

  if not DirExists(Result) then
    CreateDir(Result);
end;

procedure CopyDirectory(SourceDir, DestDir: string);
var
  FindRec: TFindRec;
begin
  if FindFirst(SourceDir + '\*', FindRec) then
  begin
    try
      repeat
        if (FindRec.Name <> '.') and (FindRec.Name <> '..') then
        begin
          if FindRec.Attributes and FILE_ATTRIBUTE_DIRECTORY <> 0 then
          begin
            if not DirExists(DestDir + '\' + FindRec.Name) then
              CreateDir(DestDir + '\' + FindRec.Name);
            CopyDirectory(SourceDir + '\' + FindRec.Name, DestDir + '\' + FindRec.Name);
          end
          else
          begin
            FileCopy(SourceDir + '\' + FindRec.Name, DestDir + '\' + FindRec.Name, False);
          end;
        end;
      until not FindNext(FindRec);
    finally
      FindClose(FindRec);
    end;
  end;
end;

function NextButtonClick(PageId: Integer): Boolean;
begin
  Result := True;
  if (PageId = wpSelectDir) then
  begin
    if InstallInAppData then
    begin
      // no more checks needed
      exit;
    end;
  
    if not HasWriteAccessToApp then
    begin
      MsgBox('You do not have write access to this directory. Please run the installer as admin or select another directory!', mbError, MB_OK);
      Result := False;
      exit;
    end;

    if not DirExists(ExpandConstant('{app}')) then
    begin
      MsgBox('The selected directory does not exist!', mbError, MB_OK);
      Result := False;
      exit;
    end;

    if not FileExists(ExpandConstant('{app}\Wireshark.exe')) then
    begin
        MsgBox('Wireshark does not seem to be installed in the selected folder. Note: For Wireshark Portable, select (...)\WiresharkPortable64\App\Wireshark\', mbError, MB_OK);
        Result := False;
        exit;
    end;
  end
end;

function InitializeSetup(): boolean;
var
  StringVersionPrefix, stringVersionSuffix: string;
  VersionOfPlugin: string;
  StartPos, endPos: Integer;
  Lines: TArrayOfString;
  i: Integer;
  InstalledVersion: String;
  ResultCode: Integer;
begin
  // check for previously installed version
  InstalledVersion := GetInstalledVersion;
  if (InstalledVersion <> '') and (CompareStr(InstalledVersion, ExpandConstant('{#MinUpdateVersion}')) < 0) then
  begin
    ResultCode := MsgBox('To update the plugin, the previous version needs to be uninstalled. Should the uninstaller be started now?', mbInformation, MB_YESNOCANCEL);
    case ResultCode of
      IDYES:
        begin
          RunUninstaller;
        end;
      IDCANCEL:
        begin
          Result := False;
          Exit;
        end;
    end;
  end;

  // check version of lua files
  StringVersionPrefix := 'v2gcommon.DS_V2GSHARK_VERSION = "';
  stringVersionSuffix := '" -- DO NOT CHANGE';
  ExtractTemporaryFile('v2gcommon.lua');
  if LoadStringsFromFile(ExpandConstant('{tmp}\v2gcommon.lua'), Lines) then
  begin
    for i := 0 to GetArrayLength(Lines) - 1 do
    begin
      if (Copy(Lines[i], 1, Length(StringVersionPrefix)) = StringVersionPrefix) then
      begin
        StartPos := Length(StringVersionPrefix) + 1;
        endPos := Pos(stringVersionSuffix, Lines[i]);
        VersionOfPlugin := Copy(Lines[i], StartPos, endPos - StartPos);       
        Log('Version found in v2gmsg.lua is: ' + VersionOfPlugin);
        Break; 
      end;
    end;
  end;
  
  if CompareText(VersionOfPlugin, '{#AppVer}') <> 0 then
  begin
    MsgBox('This setup seems to be faulty! Plugin version (' + VersionOfPlugin +') mismatch installer version ('+'{#AppVer}' +')!', mbError, MB_OK);
  end;
  Result := True;
end;

procedure CurStepChanged(CurStep: TSetupStep); 
var
  FileName: string;
  ProfilePath: string;
begin
  if (CurStep = ssInstall) and WizardIsComponentSelected('profile') then
  begin
    // create backup of old profile
    ProfilePath := GetWiresharkConfigPath + 'profiles\dsV2Gshark'
    if DirExists(ProfilePath) then
    begin
      RenameFile(ProfilePath, ProfilePath + ExpandConstant('_backup_{#Timestamp}'))
    end;
  end
  else if (CurStep = ssPostInstall) and WizardIsComponentSelected('profile/activate') then               
  begin
    // set active profile to dsV2Gshark
    FileName := GetWiresharkConfigPath + 'recent_common'
    if not SaveStringToFile(FileName, #13#10 + 'gui.last_used_profile: dsV2Gshark', True) then
    begin
      MsgBox('Failed to activate dsV2Gshark profile. You may have to switch the profile manually!', mbError, MB_OK);
    end
    else if not InstallInAppData then
    begin
      // The dsV2Gshark profile must be located in %appdata% in order to get activated this way
      // Otherwise, Wireshark would (re-)set the active profile to 'default' first and copy our profile afterwards
      CreateDir(GetWiresharkConfigPath + 'profiles');
      CreateDir(GetWiresharkConfigPath + 'profiles\dsV2Gshark');
      CopyDirectory(ExpandConstant('{app}\profiles\dsV2Gshark'), GetWiresharkConfigPath + 'profiles\dsV2Gshark');
    end;
  end
end;
