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
## Características
#### Ya desarrolladas
- De momento hay dos tipos (de tres) de pago desarrollados:
  - Con tarjeta (no incluye API)
  - Con cheques
  - En efectivo (hay que programar el driver a usar)
- Una lista para ver los precios a pagar
- Un generador de cheques, escrito en Python ~~(aunque de momento esté en la raíz, lo cambiaré a una subcarpeta)~~ y localizado en la carpeta `scripts/`
- Imprimir un recibo usando la clase [QPrinter](https://doc.qt.io/qt-5/qprinter.html) 
  - Hay un modelo del PDF que es como el que el programa escribe en `pdf/`
#### Futuro
- Incluir un intérprete de JSON para guardar y crear sesiones de compra
## Generar Cheques
* Para generar cheques, puedes usar el script de Python ya incluído en el proyecto
