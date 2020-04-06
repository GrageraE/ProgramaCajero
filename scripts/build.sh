#Descargamos y extraemos la libreria
wget https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip 
unzip include.zip -d include 
#Movemos la libreria al directorio adecuado
mv ./include/single_include ../..
#Compilamos el programa
echo "Compilando..."
cd ..
mkdir build
cd build
qmake ..
make
echo "Compilado"
#Limpiamos los mocs
echo "Limpiando..."
make clean

echo "TERMINADO. Usa '../build/ProgramaCajero' para ejecutarlo."