[Setup]
AppName=Parqueadero AVL
AppVersion=1.0.0
DefaultDirName={autopf}\Parqueadero AVL
DefaultGroupName=Parqueadero AVL
UninstallDisplayIcon={app}\main.exe
OutputDir=C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\dist
OutputBaseFilename=ParqueaderoAVL_Setup
Compression=lzma2
SolidCompression=yes
WizardImageFile="C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\UTILS\logo.bmp"
WizardSmallImageFile="C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\UTILS\logo.bmp"

[Dirs]
Name: "{localappdata}\Parqueadero AVL\data"; Flags: uninsneveruninstall
Name: "{localappdata}\Parqueadero AVL\data\contraseñas"; Flags: uninsneveruninstall

[Files]
Source: "C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\main.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\autos.txt"; DestDir: "{localappdata}\Parqueadero AVL\data"; Flags: onlyifdoesntexist
Source: "C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\autos_historial.txt"; DestDir: "{localappdata}\Parqueadero AVL\data"; Flags: onlyifdoesntexist
Source: "C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\propietarios.txt"; DestDir: "{localappdata}\Parqueadero AVL\data"; Flags: onlyifdoesntexist
Source: "C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\ruta.json"; DestDir: "{localappdata}\Parqueadero AVL\data"; Flags: onlyifdoesntexist
Source: "C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\estado_parqueadero.json"; DestDir: "{localappdata}\Parqueadero AVL\data"; Flags: onlyifdoesntexist
Source: "C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\posicion_coche.json"; DestDir: "{localappdata}\Parqueadero AVL\data"; Flags: onlyifdoesntexist
Source: "C:\REPOSITORIO\PROYECTO_FINAL_GOMEZ_JOFFRE\PROYECTO ARBOL AVL\ayuda.html"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Parqueadero AVL"; Filename: "{app}\main.exe"
Name: "{commondesktop}\Parqueadero AVL"; Filename: "{app}\main.exe"
Name: "{group}\Abrir Carpeta de Datos"; Filename: "{localappdata}\Parqueadero AVL\data"

[Run]
Filename: "{app}\main.exe"; Description: "Iniciar la aplicación"; Flags: nowait postinstall skipifsilent

[Code]
var
  PasswordPage: TInputQueryWizardPage;
  AllowedPasswords: TStringList;
  Attempts: Integer;


  function IncrementChar(ch: Char): Char;
var
  code: Integer;
begin
  code := Ord(ch) + 1;
  if code > 126 then
    code := 33;
  Result := Chr(code);
end;

function IncrementPassword(const S: String): String;
var
  i: Integer;
begin
  Result := '';
  for i := 1 to Length(S) do
    Result := Result + IncrementChar(S[i]);
end;


procedure CreatePasswords;
var
  FilePath: String;
  TempList: TStringList;
  BasePasswords: array[0..4] of String;
begin
  FilePath := ExpandConstant('{localappdata}\Parqueadero AVL\data\contraseñas\contraseñas.txt');
  ForceDirectories(ExtractFilePath(FilePath));
  TempList := TStringList.Create;
  try
    { Primera contraseña exactamente igual a la proporcionada }
    BasePasswords[0] := '-/ZH}Q_oBV3B79v2BjA$Jf~3:4pI##kc/$;pCg}!6JGE?kujZfj7=I39.YR\5Nm';

    { Generación de 4 contraseñas con variaciones estructuradas }
    BasePasswords[1] := '-/ZI}R_pBW3C80w3CkB%Kg}4;5qJ$$ld/&qDh"@7KHF@lvk[ek8>J40/ZS]6On';
    BasePasswords[2] := '-/YJ|S`qCX4D81x4DlC^Lh&5=6rK%%me)''rEi#~8LIGAlwm\fl9?K51]ZT7Po';
    BasePasswords[3] := '-/XK~T~rDY5E92y5EmD&Mi*6>7sL&&nf*%sFj$}9MJHBmwn^gm:?L62^[U8Pp';
    BasePasswords[4] := '-/WL_T{sEZ6F03z6FnE(Mj+7@8tM!!og+&tGk%#0NKICnxo`hn;@M73_U9Qq';

    { Guardar en archivo }
    TempList.Add(BasePasswords[0]);
    TempList.Add(BasePasswords[1]);
    TempList.Add(BasePasswords[2]);
    TempList.Add(BasePasswords[3]);
    TempList.Add(BasePasswords[4]);
    TempList.SaveToFile(FilePath);
  finally
    TempList.Free;
  end;
end;

{ Inicializa las contraseñas y página de autenticación. }
procedure InitializeWizard();
var
  FilePath: String;
  i: Integer;
begin
  FilePath := ExpandConstant('{localappdata}\Parqueadero AVL\data\contraseñas\contraseñas.txt');
  if not FileExists(FilePath) then
    CreatePasswords;

  AllowedPasswords := TStringList.Create;
  AllowedPasswords.LoadFromFile(FilePath);

  { Asegura que haya 5 contraseñas de la misma longitud (62 caracteres) }
  if (AllowedPasswords.Count <> 5) or (Length(AllowedPasswords[0]) <> 62) then
  begin
    CreatePasswords;
    AllowedPasswords.LoadFromFile(FilePath);
  end;

  { Incrementa cada contraseña para la siguiente instalación }
  for i := 0 to AllowedPasswords.Count - 1 do
    AllowedPasswords[i] := IncrementPassword(AllowedPasswords[i]);
  AllowedPasswords.SaveToFile(FilePath);

  Attempts := 0;
  PasswordPage := CreateInputQueryPage(wpWelcome, 'Autenticación',
    'Ingrese la contraseña para instalar', 'Escriba una de las contraseñas válidas:');
  PasswordPage.Add('Contraseña:', False);
end;

{ Verifica la contraseña ingresada }
function NextButtonClick(CurPageID: Integer): Boolean;
begin
  Result := True;
  if CurPageID = PasswordPage.ID then
  begin
    if AllowedPasswords.IndexOf(PasswordPage.Values[0]) = -1 then
    begin
      Inc(Attempts);
      if Attempts < 3 then
      begin
        MsgBox('Contraseña incorrecta. Intente nuevamente.', mbError, MB_OK);
        Result := False;
      end
      else
      begin
        MsgBox('Demasiados intentos fallidos. Instalación cancelada.', mbError, MB_OK);
        WizardForm.Close;
        Result := False;
      end;
    end;
  end;
end;

{ Libera memoria }
procedure DeinitializeSetup();
begin
  AllowedPasswords.Free;
end;
