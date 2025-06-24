#ifndef CLIENT_RENDER_H
#define CLIENT_RENDER_H

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>

#include <memory>
#include <unordered_map>
#include <utility>

#include "client/camera.h"
#include "client/providers/texture_provider.h"
#include "client/providers/animation_provider.h"
#include "client/hud_manager.h"
#include "client/renderables/map/renderable_map.h"
#include "client/renderables/renderable_player.h"
#include "common/maploader.h"
#include "common/network/dtos/snapshot_dto.h"
#include "client/field_of_view.h"
#include "client/game_config.h"


class Render {
private:
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

    const MapData& map_data;
    const int USE_FOV;

    std::unordered_map<uint8_t, std::unique_ptr<RenderablePlayer>>
        players_renderables;
    std::shared_ptr<AnimationProvider> animation_provider;
    std::unique_ptr<RenderableMap> renderable_map;
    std::unique_ptr<HUDManager> hud_manager;
    std::unique_ptr<FieldOfView> field_of_view;

    void update_players(const SnapshotDTO& snapshot, PrivatePlayerDTO& user_data);

public:
    Render(const MapData& map_data, const GameConfig& game_config);
    ~Render();

    void run();

    void update(const SnapshotDTO& snapshot, PrivatePlayerDTO& user_data,
        uint32_t& fps_timer);

    void calculate_fps(uint32_t& fps_timer);

    void skip_frames(int frames);

    void render();
};

#endif  // Render_H
