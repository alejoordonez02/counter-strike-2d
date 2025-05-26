#include <iostream>
#include "./graphics_engine.h"

int main(int argc, char** argv) {
    /**
    Inicializar:
        - socket
        - cliente
        - motor grafico
        - motor de audio
        - ...
    */

    GraphicsEngine motor_grafico;
    motor_grafico.run();

    // tiene el bucle de renderizado, ahi mismo se hace un update y un input handler del cliente

    return 0;
}