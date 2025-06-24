# Readme
El proyecto usa una estructura de carpetas muy simple:

```
client/
server/
editor/
common/
```

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


## Editor de niveles
Una vez compilado el proyecto ejecutar el editor mediante
```bash
./build/cs2d_editor
```


## Licencia:
GPL v2

