# ProgramaCajero [![Build Status](https://travis-ci.com/GrageraE/ProgramaCajero.svg?branch=master)](https://travis-ci.com/GrageraE/ProgramaCajero)
Una prueba para crear un programa que serviría para las cajas
## Compilación
#### Dependencias 
1. Qt y `qmake`
2. GNU/Make:
```
sudo apt update && sudo apt install build-essential
```
3. [JSON for Modern C++](https://github.com/nlohmann/json). Si estás en Linux, puedes usar el script `build.sh` para despreocuparte de su descarga e instalación. Si estás en Windows, descarga el paquete `include.zip` de las releases de la librería, extráelo y pon la carpeta `single_include` en el directorio superior de este repositorio (es posible que haya traducción del script para Wndows en algún futuro...).
#### Compilación en Linux
1. Clona el repositorio: 
```
git clone https://github.com/GrageraE/ProgramaCajero.git
```
2. Añade permisos de ejecución al script de compilación y ejecútalo:
```
cd scripts/
chmod +x build.sh
./build.sh
```
3. Espera a que termine el proceso y tendrás el ejecutable en `./build/ProgramaCajero`
## Características
#### Ya desarrolladas
- De momento hay dos tipos (de tres) de pago desarrollados:
  - Con tarjeta (no incluye API)
  - Con cheques
  - En efectivo (hay que programar el driver a usar)
- Una lista para ver los precios a pagar
- Un generador de cheques, escrito en Python ~~(aunque de momento esté en la raíz, lo cambiaré a una subcarpeta)~~ y localizado en la carpeta `scripts/`
- La característica de guardar las sesiones en archivos JSON para después interpretarlos y retomadas de vuelta.
  - Hay un modelo del JSON que es como el que escribe el programa en la carpeta `JSON/`
- Imprimir un recibo usando la clase [QPrinter](https://doc.qt.io/qt-5/qprinter.html) 
  - Hay un modelo del PDF que es como el que el programa dibuja en `pdf/`
## Generar Cheques
* Para generar cheques, puedes usar el script de Python ya incluído en el proyecto
## Impresión
**NOTA:** Al seleccionar la impresora en el diálogo de impresión, al menos en Windows, **QUITA** la casilla `Imprimir a un archivo` para que el documento binario/XML (esto depende de tu impresora) se mande a la impresora y no solo se guarde en el disco.
