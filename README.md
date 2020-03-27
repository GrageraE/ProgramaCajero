# ProgramaCajero
Una prueba para crear un programa que serviría para las cajas
## Compilación
#### Dependencias 
1. Qt y `qmake`
1. GNU/Make:
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
- Una lista para ver los precios a pagar
- Un generador de cheques, escrito en Python ~~(aunque de momento esté en la raíz, lo cambiaré a una subcarpeta)~~ y localizado en la carpeta `scripts/`
- La característica de guardar las sesiones en archivos JSON para después interpretarlos y retomadas de vuelta. Esta característica está en desarrollo.
#### Futuro
**NOTA:** estas características están ya presentes en el branch de Impresion o en el master, cuando el anterior emerja.
- Implementar el efectivo
- Implementar la clase [QPrinter](https://doc.qt.io/qt-5/qprinter.html) para imprimir un recibo
## Generar Cheques
* Para generar cheques, puedes usar el script de Python ya incluído en el proyecto
