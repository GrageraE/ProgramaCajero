#Primero, configuramos el PATH
#Es posible que tengas que modificar alguno de estos strings:
$env:Path="C:\Qt\5.14.2\msvc2017\bin;"+$env:Path #qmake.exe
                                                 #Esto depende de donde tengas instalado Qt
#cl.exe :
#Depende de donde tengas instalado Visual Studio. No deberias cambiar nada a partir del cuarto directorio
$env:Path="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.24.28314\bin\Hostx86\x86;"+$env:Path
$env:Path="C:\Qt\Tools\mingw730_64\bin;"+$env:Path #mingw32-make.exe
                                                   #Esto tambien depende de donde tengas instalado Qt
                                                   #y de la version de mingw
#Descargamos y extraemos la libreria
Invoke-WebRequest https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip -OutFile libreria.zip
Expand-Archive -Path .\libreria.zip -DestinationPath .\libreria
#Movemos la libreria al directorio adecuado
Move-Item .\libreria\single_include ..\..\
#Compilamos el programa
cd ..
mkdir build
cd .\build
qmake.exe ..
mingw32-make.exe debug
echo "Compilado."
echo "Limpiando..."
mingw32-make.exe clean
echo "TERMINADO."