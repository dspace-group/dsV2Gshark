// DO NOT CHANGE VERSION HERE! Run update_version.bat
#define AppVer "1.0.0"
#define AppId "dsV2Gshark"

[Setup]
AppId={#AppId}
AppName=dSPACE V2Gshark Wireshark Plugin
DefaultGroupName=dSPACE V2Gshark Wireshark Plugin
AppVersion={#AppVer}
VersionInfoVersion={#AppVer}
AppPublisher=dSPACE GmbH
AppCopyright=Copyright 2024, dSPACE GmbH. All rights reserved.
WizardStyle=modern
DefaultDirName=C:\Program Files\Wireshark
Compression=lzma2
SolidCompression=yes
ChangesEnvironment=no  
DisableDirPage=no
PrivilegesRequiredOverridesAllowed=dialog
UsePreviousPrivileges=no
OutputBaseFilename=dsV2Gshark_{#AppVer}_Setup
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

[Components]
Name: "plugin"; Description: "Plugin files"; Types: full custom; Flags: fixed
Name: "plugin/dissectors"; Description: "V2G dissectors"; Types: full custom; Flags: fixed
Name: "plugin/decoder"; Description: "EXI decoder (powered by chargebyte cbexigen)"; Types: full custom; Flags: fixed
Name: "plugin/decoder/din"; Description: "DIN 70121 support"; Types: full custom; Flags: fixed
Name: "plugin/decoder/iso2"; Description: "ISO 15118-2 support"; Types: full custom; Flags: fixed
Name: "plugin/decoder/iso20"; Description: "ISO 15118-20 support (experimental)"; Types: full custom; Flags: fixed
Name: "plugin/autoschema"; Description: "Automatic schema detection"; Types: full custom; Flags: fixed    
Name: "plugin/autodecrypt"; Description: "Live TLS decryption with disclosed master secret from UDP packet"; Types: full custom;
Name: "buttons"; Description: "Add filter buttons to Wireshark"; Types: full
Name: "colorfilters"; Description: "Highlight V2G messages in Wireshark"; Types: full

[Files]
Source: "..\Wireshark\plugins\v2gmsg.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/dissectors
Source: "..\Wireshark\plugins\v2gtp.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/dissectors
Source: "..\Wireshark\plugins\v2gsdp.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/dissectors
Source: "..\Wireshark\plugins\v2gtlssecret.lua"; DestDir: "{app}\plugins"; Flags: ignoreversion recursesubdirs; Components: plugin/autodecrypt
Source: "..\Wireshark\*.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs; Components: plugin/decoder
Source: "..\LICENSE"; DestDir: "{app}"; DestName: "dsV2Gshark_LICENSE.txt"; Flags: ignoreversion recursesubdirs;
Source: "..\OSSAcknowledgements.txt"; DestDir: "{app}"; DestName: "dsV2Gshark_OSSAcknowledgements.txt"; Flags: ignoreversion recursesubdirs;
Source: "dsV2Gshark_README.txt"; DestDir: "{app}"; DestName: "dsV2Gshark_README.txt"; Flags: skipifsourcedoesntexist;

[InstallDelete]
Type: filesandordirs; Name: "{app}\luaV2Gdecoder.dll"
Type: filesandordirs; Name: "{app}\X509CertInfos.dll"
Type: filesandordirs; Name: "{app}\plugins\v2gmsg_generic.lua"

[Code]
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

function RemoveFromFile(FileName: string; LinesToRemove: array of string): Boolean;
var
  LinesFile: TArrayOfString;
  i, j: Integer;
begin
  if LoadStringsFromFile(FileName, LinesFile) then
  begin
    for i := GetArrayLength(LinesFile) -  1 downto  0 do
    begin
      for j := GetArrayLength(LinesToRemove) -  1 downto  0 do
      begin
        if Pos(LinesToRemove[j], LinesFile[i]) >  0 then
          LinesFile[i] := '';
      end;
    end;
     
    if SaveStringsToFile(FileName, LinesFile, False) then
    begin
      Result := True;
    end
    else
      Result := False;
  end
  else
  begin
    Result := False;
  end;
end;

function PrependStringsToFile(const FileName: string; const Strings: TArrayOfString): boolean;
var
  Lines: TArrayOfString;
  Count, NewLinesCount, i: Integer;
begin
  Result := True;
  if LoadStringsFromFile(FileName, Lines) then
  begin
    Count := GetArrayLength(Lines);
    NewLinesCount := GetArrayLength(Strings);
    SetArrayLength(Lines, Count + NewLinesCount);
    for i := Count -  1 downto  0 do
      Lines[i + NewLinesCount] := Lines[i];
    for i :=  0 to NewLinesCount -  1 do
      Lines[i] := Strings[i];
    if not SaveStringsToFile(FileName, Lines, False) then
      Result := False;
  end
  else
    Result := False;
end;

function CheckLines(const FileName: string; const LinesToCheck: TArrayOfString): TArrayOfString;
var
  FileLines: TStringList;
  MissingLines: TStringList;
  i: Integer;
begin
  if not FileExists(FileName) then
  begin
    Result := LinesToCheck;
  end
  else
  begin
    FileLines := TStringList.Create;
    MissingLines := TStringList.Create;
    try
      FileLines.LoadFromFile(FileName);

      for i :=  0 to High(LinesToCheck) do
      begin
        if not FileLines.IndexOf(LinesToCheck[i]) >=  0 then
          MissingLines.Add(LinesToCheck[i]);
      end;

      SetLength(Result, MissingLines.Count);
      for i :=  0 to MissingLines.Count -  1 do
        Result[i] := MissingLines[i];
    finally
      FileLines.Free;
      MissingLines.Free;
    end;
  end;
end;

function NextButtonClick(PageId: Integer): Boolean;
begin
  Result := True;
  if (PageId = wpSelectDir) and not DirExists(ExpandConstant('{app}')) then
    begin
      MsgBox('The selected directory does not exist!', mbError, MB_OK);
      Result := False;
      exit;
    end;
  if (PageId = wpSelectDir) and not HasWriteAccessToApp then
    begin
      MsgBox('You do not have write access to this directory. Please run the installer as admin or select another directory!', mbError, MB_OK);
      Result := False;
      exit;
    end;
  if (PageId = wpSelectDir) and not FileExists(ExpandConstant('{app}\Wireshark.exe')) then
  begin
      MsgBox('Wireshark does not seem to be installed in the selected folder. Note: For Wireshark Portable, select (...)\WiresharkPortable64\App\Wireshark\', mbError, MB_OK);
      Result := False;
      exit;
  end;
end;

function InitializeSetup(): boolean;
var
  StringVersionPrefix, stringVersionSuffix: string;
  VersionOfPlugin: string;
  StartPos, endPos: Integer;
  Lines: TArrayOfString;
  i: Integer;
begin
  // check version of lua files
  StringVersionPrefix := 'DS_V2GSHARK_VERSION = "';
  stringVersionSuffix := '" -- DO NOT CHANGE';
  ExtractTemporaryFile('v2gmsg.lua');
  if LoadStringsFromFile(ExpandConstant('{tmp}\v2gmsg.lua'), Lines) then
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
  Lines: TArrayOfString;
  StringsToCheck, StringsToAdd: TArrayOfString;
begin
  // add wireshark filter buttons after installation
  if (CurStep = ssPostInstall) then               
  begin
    if WizardIsComponentSelected('buttons') then
    begin
      FileName := GetWiresharkConfigPath + 'dfilter_buttons'
      StringsToCheck := ['"TRUE","[V2G ext]","v2gtp or v2gtlssecret or tls.handshake or tls.alert_message or tcp.flags.syn == 1 or tcp.flags.fin == 1 or homeplug or homeplug-av ",""',
                         '"TRUE","[V2G]","v2gtp or v2gtlssecret",""']
      StringsToAdd := CheckLines(FileName, StringsToCheck)
      if Length(StringsToAdd) > 0 then
        if not SaveStringsToFile(FileName, StringsToAdd, True) then
          MsgBox('Failed to add buttons to Wireshark', mbError, MB_OK);
    end;
        
    if WizardIsComponentSelected('colorfilters') then
    begin
      // add wireshark colorfilters after installation
      FileName := GetWiresharkConfigPath + 'colorfilters'
      StringsToCheck := [ '@Homeplug@homeplug-av@[26214,26214,26214][65535,65535,65535]',
                          '@V2G Warning@v2gtp and _ws.expert@[52685,65535,51657][54484,0,0]',
                          '@V2G Default@v2gtp@[52685,65535,51657][0,0,0]',
                          '@V2G TLS Secret@v2gtlssecret@[0,29555,2056][65535,65535,65535]'];
      StringsToAdd := CheckLines(FileName, StringsToCheck)
      if not FileExists(FileName) then
      begin
        // copy standard colorfilters to $FileName
        if not LoadStringsFromFile(ExpandConstant('{app}\colorfilters'), Lines) then
        begin
          MsgBox('Failed to add colorfilters to Wireshark. Default filter settings not found!', mbError, MB_OK);
        end
        else
        begin
          SaveStringsToFile(FileName, Lines, True);
        end;
      end;
      if Length(StringsToAdd) > 0 then
        if not PrependStringsToFile(FileName, StringsToAdd) then
          MsgBox('Failed to add colorfilters to Wireshark!', mbError, MB_OK);
    end;
  end;
end;

procedure DeinitializeUninstall;
var
  LinesToRemove: TArrayOfString;
  FileName: string;
begin
  // remove colorfilters
  FileName := GetWiresharkConfigPath + 'colorfilters';
  LinesToRemove := ['@Homeplug@homeplug-av@[26214,26214,26214][65535,65535,65535]',
                    '@V2G Warning@v2gtp and _ws.expert@[52685,65535,51657][54484,0,0]',
                    '@V2G Default@v2gtp@[52685,65535,51657][0,0,0]',
                    '@V2G TLS Secret@v2gtlssecret@[0,29555,2056][65535,65535,65535]'];
  RemoveFromFile(FileName, LinesToRemove);

  // remove buttons
  FileName := GetWiresharkConfigPath + 'dfilter_buttons';
  LinesToRemove := ['"TRUE","[V2G ext]","v2gtp or v2gtlssecret or tls.handshake or tls.alert_message or tcp.flags.syn == 1 or tcp.flags.fin == 1 or homeplug or homeplug-av ",""',
                    '"TRUE","[V2G]","v2gtp or v2gtlssecret",""']
  RemoveFromFile(FileName, LinesToRemove);
end;
