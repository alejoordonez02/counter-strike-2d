#ifndef CLIENT_RENDER_H
#define CLIENT_RENDER_H

#include <memory>
#include <unordered_map>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>

#include "client/providers/animation_provider.h"
#include "client/renderables/renderable_player.h"
#include "common/snapshot.h"
#include "common/maploader.h"
#include "client/renderables/map/renderable_map.h"
#include "client/hud_manager.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class Render {
    private:
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

    int user_player_id;
    const MapData& map_data;
    
    std::unordered_map<uint16_t, std::unique_ptr<RenderablePlayer>>
            players_renderables;
    std::shared_ptr<AnimationProvider> animation_provider;
    std::unique_ptr<RenderableMap> renderable_map;
    std::unique_ptr<HUDManager> hud_manager;

    public:
    Render(int user_player_id, const MapData& map_data);
    ~Render();

    void run();

    void update(Snapshot snapshot);

    // void skip_frames(uint8_t frames);

    void skip_frames(uint8_t frames);

    void render();
};

#endif  // Render_H
