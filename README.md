# Ejemplo de CMAKE para el TP Final

**Importante:** el primer commit de este repositorio tiene el setup
básico para el TP Final que incluye la instalación de la lib de Google
Tests, `SDL2` y `SDL2pp` (el wrapper de C++).

El resto de los commits son a modo de ejemplo de como se pueden
agregar mas código fuente al proyecto.

Este ejemplo **no** incluye instalarse otras libs que son dependencias
tanto de `SDL2` como de `SDL2pp` (pero si estan documentadas en el
`CMakeFile` para Xubuntu 24.04).

Este repo **no** incluye tampoco un instalador.

**Se deben agregar las librerias necesarias y el instalador.**

También el ejemplo usa una estructura de carpetas muy simple:

```
client/
server/
editor/
common/
```

Bien se puede mejorar (cambiando el cmakefile) agregando mas
sub-carpetas.

Asi tambien **deben** ser cambiados los *targets* del cmake (`taller_client`,
`taller_server`, ...) por nombres mas acordes al TP que se este
haciendo.

Tambien, por default solo se compila una version *debug* sin
optimizar. Si se quiere compilar binarios optimizados
(lo que cmake llama *release*) se puede, solo hay modificar
cmake.

Aprender del ejemplo para saber como extenderlo!

**Importante:** este repositorio **no** incluye pre-commits hooks,
ni scripts adicionales (como correr valgrind).

**Eso esta a cargo de los estudiantes,** tal como fue mostrado
en los tps individuales, recaps y hands-on.

## Origen del código
El componente `socket` fue tomado de [hands-on-sockets-in-cpp](https://github.com/eldipa/hands-on-sockets-in-cpp), y los componentes `queue` y `thread` de [hands-on-thread](https://github.com/eldipa/hands-on-threads). Todos se encuentran bajo la licencia GPL v2.
Este repositorio respeta la misma licencia para cumplir con los términos de distribución.

## Instalador
Para compilar el proyecto es primero instalar las dependencias necesarias, para esto se proporciona el script `install.sh`. Para ejecutarlo, se debe correr el siguiente comando:
```bash
./install.sh
```
Este script instalará las dependencias necesarias para compilar el proyecto.

## Compilación
Ejecutar
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCS2D_CLIENT=ON -DCS2D_SERVER=ON -DCS2D_EDITOR=ON -DCS2D_TESTS=ON -DCS2D_MAKE_WARNINGS_AS_ERRORS=OFF
```


## Correr tests
```bash
make run-tests
```

## Development
Si solo queres ejecutar una parte del proyecto, por ejemplo el cliente, podés correr el siguiente comando:
```bash
cmake -S . -B build -DCS2D_CLIENT=ON -DCS2D_SERVER=OFF -DCS2D_EDITOR=OFF -DCS2D_TESTS=OFF -DCS2D_MAKE_WARNINGS_AS_ERRORS=OFF

cmake --build build
# o bien "cd build && make"
```

Para levantar la interfaz grafica
```bash
# levantar el servidor
./build/cs2d_server
# levantar cliente
./build/cs2d_client localhost 7878
```



## Licencia:
GPL v2

