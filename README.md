# ProgramaCajero
Una prueba para crear un programa que serviría para las cajas
## Compilación
#### Dependencias 
1. Qt y `qmake`
1. GNU/Make: `sudo apt update && sudo apt install build-essential`
1. [JSON for Modern C++](https://github.com/nlohmann/json). Tienes que modificar el archivo [ProgramaCajero.pro](https://github.com/GrageraE/ProgramaCajero/blob/master/ProgramaCajero.pro) con el directorio donde tengas la librería.
#### Compilación en Linux
1. Clona el repositorio: `git clone https://github.com/GrageraE/ProgramaCajero.git`
1. Crea el directorio de compilación: `mkdir build && cd build`
1. Crea el `makefile`: `qmake ..`
1. Compila el programa: `make`
