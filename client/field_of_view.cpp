#include "client/field_of_view.h"
#include <SDL2/SDL2_gfxPrimitives.h>

FieldOfView::FieldOfView(SDL2pp::Renderer& renderer, uint32_t width, uint32_t height)
    : stencil(
        renderer, 
        SDL_PIXELFORMAT_RGBA8888, // formato de 32 bits: 8 bits por canal: R, G, B, A
        SDL_TEXTUREACCESS_TARGET, // permite dibujar sobre la textura (por default las texture son de solo lectura, en este caso permite hacer una de escritura)
        width,
        height
    ),
      width(width), height(height) {
    // inicializa textura negra vacía
    stencil
        .SetBlendMode(SDL_BLENDMODE_BLEND); // modo mezcla: permite transparencia
        // .SetAlphaMod(240);  // controlar opacidad (alpha) de la textura, va de 0 a 255
}

void FieldOfView::update(SDL2pp::Renderer& renderer) {
    // obtiene la posición del mouse
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    // centro de la pantalla
    int cx = width / 2;
    int cy = height / 2;

    // calcula dirección hacia el mouse
    float angle = atan2(mouse_y - cy, mouse_x - cx);
    float cone_radius = 300;  // tamaño del cono
    float cone_width_angle = M_PI / 6;  // 30 grados

    // puntos del triángulo que representa el cono
    short vx[3] = {
        static_cast<short>(cx),
        static_cast<short>(cx + cone_radius * cos(angle - cone_width_angle)),
        static_cast<short>(cx + cone_radius * cos(angle + cone_width_angle))
    };

    short vy[3] = {
        static_cast<short>(cy),
        static_cast<short>(cy + cone_radius * sin(angle - cone_width_angle)),
        static_cast<short>(cy + cone_radius * sin(angle + cone_width_angle))
    };

    
    // establecer la textura como target
    // todo lo que haga de aqui en adelante se dibujará en la textura
    SDL_SetRenderTarget(renderer.Get(), stencil.Get());

    // limpiar la textura con negro opaco
    renderer.SetDrawColor(0, 0, 0, 255);
    // limpia la textura (no borra lo anterior renderizado, ya que se cambió el render target)
    renderer.Clear();

    // dibuja el cono blanco sobre el fondo negro
    filledPolygonRGBA(renderer.Get(), vx, vy, 3, 255, 255, 255, 255);

    // crear una Surface para aplicar color key (tomar un color como transparente, simil png)
    SDL2pp::Surface surface_temp(
        0, width, height, 32, 
        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000
    );

    if (SDL_RenderReadPixels(renderer.Get(), nullptr, SDL_PIXELFORMAT_ARGB8888,
                             surface_temp.Get()->pixels, surface_temp.Get()->pitch) != 0) {
        throw std::runtime_error("Failed to read pixels from stencil render target");
    }

    // aplicar color key al blanco
    surface_temp.SetColorKey(true, 0xFFFFFF);

    // crear nueva textura desde la Surface
    stencil = SDL2pp::Texture(renderer, surface_temp);

    // blend mode + alpha mod (transparencia de la textura en general, aplica para el fondo negro)
    stencil.SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220);

    // vuelvo a dibujar sobre el target original
    SDL_SetRenderTarget(renderer.Get(), nullptr);
    renderer.SetDrawColor(0, 0, 0);
}

void FieldOfView::render(SDL2pp::Renderer& renderer) {
    // dibuja la textura encima del juego
    renderer.Copy(stencil, SDL2pp::NullOpt, SDL2pp::NullOpt);
}
