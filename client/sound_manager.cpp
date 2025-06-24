// sound_manager.cpp
#include "sound_manager.h"
#include <iostream>

SoundManager::SoundManager() : background_music(nullptr), music_enabled(true), 
                               sfx_enabled(true), sfx_volume(64), music_volume(32) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Error inicializando SDL_mixer: " << Mix_GetError() << std::endl;
    }

    // Cargar efectos de sonido
    load_sound("weapon_switch", "assets/sfx/items/ammo.wav");
    // load_sound("gunshot", "assets/sounds/gunshot.wav");
    // load_sound("reload", "assets/sounds/reload.wav");
    // load_sound("buy_weapon", "assets/sounds/buy.wav");
    // load_sound("bomb_plant", "assets/sounds/bomb_plant.wav");
    // load_sound("death", "assets/sounds/death.wav");
    
    // Cargar música de fondo
    load_music("assets/sfx/menu.wav");
    play_music();
}

SoundManager::~SoundManager() {
    // Limpiar efectos de sonido
    for (auto& [name, chunk] : sound_effects) {
        Mix_FreeChunk(chunk);
    }
    
    // Limpiar música
    if (background_music) {
        Mix_FreeMusic(background_music);
    }
    
    Mix_CloseAudio();
}

void SoundManager::load_sound(const std::string& name, const std::string& path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (!chunk) {
        std::cerr << "Error cargando sonido " << name << ": " << Mix_GetError() << std::endl;
        return;
    }
    sound_effects[name] = chunk;
}

void SoundManager::load_music(const std::string& path) {
    background_music = Mix_LoadMUS(path.c_str());
    if (!background_music) {
        std::cerr << "Error cargando música: " << Mix_GetError() << std::endl;
    }
}

void SoundManager::play_sound(const std::string& name, int volume) {
    if (!sfx_enabled) return;
    
    auto it = sound_effects.find(name);
    if (it != sound_effects.end()) {
        if (volume == -1) volume = sfx_volume;
        Mix_VolumeChunk(it->second, volume);
        Mix_PlayChannel(-1, it->second, 0);
    }
}

void SoundManager::play_sound_with_distance(const std::string& name, float distance) {
    if (!sfx_enabled) return;
    
    // Calcular volumen basado en distancia (máximo 500 unidades)
    int volume = sfx_volume * (1.0f - std::min(distance / 500.0f, 1.0f));
    play_sound(name, volume);
}

void SoundManager::play_music() {
    if (music_enabled && background_music) {
        Mix_VolumeMusic(music_volume);
        Mix_PlayMusic(background_music, -1); // -1 = loop infinito
    }
}

void SoundManager::stop_music() {
    Mix_HaltMusic();
}

// void SoundManager::set_sfx_volume(int volume) {
//     sfx_volume = std::clamp(volume, 0, 128);
// }

// void SoundManager::set_music_volume(int volume) {
//     music_volume = std::clamp(volume, 0, 128);
//     Mix_VolumeMusic(music_volume);
// }




void SoundManager::check_and_play_game_sounds(const SnapshotDTO& snapshot, const PrivatePlayerDTO& user_data) {
    static WeaponName last_weapon = WeaponName::NONE;
    static int last_hp = 100;
    
    // Sonido de cambio de arma
    if (user_data.current_weapon.name != last_weapon && last_weapon != WeaponName::NONE) {
        play_sound("weapon_switch");
        last_weapon = user_data.current_weapon.name;
    } else if (last_weapon == WeaponName::NONE) {
        last_weapon = user_data.current_weapon.name;
    }
    
    // Sonido de daño recibido
    // if (user_data.player_hp < last_hp) {
    //     play_sound("damage");
    // }
    // last_hp = user_data.player_hp;
    
    // Sonidos de disparos con distancia
    // Position my_pos = get_my_player_position(snapshot, user_data.player_id);
    // for (const auto& player : snapshot.players) {
    //     if (player.is_shooting && player.player_id != user_data.player_id) {
    //         float distance = calculate_distance(my_pos, Position(player.x, player.y));
    //         sound_manager->play_sound_with_distance("gunshot", distance);
    //     }
    // }
}

// Position SoundManager::get_my_player_position(const SnapshotDTO& snapshot, int my_id) {
//     for (const auto& player : snapshot.players) {
//         if (player.player_id == my_id) {
//             return Position(player.x, player.y);
//         }
//     }
//     return Position(0, 0);
// }

// float SoundManager::calculate_distance(const Position& pos1, const Position& pos2) {
//     float dx = pos1.x - pos2.x;
//     float dy = pos1.y - pos2.y;
//     return std::sqrt(dx*dx + dy*dy);
// }