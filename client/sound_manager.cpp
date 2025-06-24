// sound_manager.cpp
#include "sound_manager.h"
#include <iostream>
#include <algorithm>
#include <cmath>

SoundManager::SoundManager(const GameConfig& game_config) 
    : mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, 4096), // Inicializar mixer con SDL2pp
      background_music(nullptr),
      music_enabled(game_config.sfx.use_music), 
      sfx_enabled(game_config.sfx.use_sound), 
      sfx_volume(game_config.sfx.sound_volume), 
      music_volume(game_config.sfx.music_volume) {
    
    try {
        // configurar canales con grupos (permite separar sonidos)
        mixer.AllocateChannels(CHANNELS);
        
        // sonidos de armas
        load_sound("weapon_switch", DATA_PATH "/assets/sfx/wpn_select.wav");
        
        load_sound("buy_weapon", DATA_PATH "/assets/sfx/items/pickup.wav");
        load_sound("buy_ammo", DATA_PATH "/assets/sfx/items/ammo.wav");
        
        load_sound("gunshot_ak47", DATA_PATH "/assets/sfx/weapons/ak47.wav");
        load_sound("gunshot_m3", DATA_PATH "/assets/sfx/weapons/m3.wav");
        load_sound("knife_swing", DATA_PATH "/assets/sfx/weapons/melee.wav");
        load_sound("glock", DATA_PATH "/assets/sfx/weapons/glock18.wav");
        load_sound("awp", DATA_PATH "/assets/sfx/weapons/awp.wav");
        
        load_sound("reload", DATA_PATH "/assets/sfx/player/repair.wav");        // simil, no encontre la original

        // bomba
        load_sound("bomb_plant", DATA_PATH "/assets/sfx/radio/bombpl.wav");
        load_sound("bombdef", DATA_PATH "/assets/sfx/radio/bombdef.ogg");           // counter terrorits won
        load_sound("bomb_exploded", DATA_PATH "/assets/sfx/radio/explode1.wav");     // terrorists won
        load_sound("bomb_tick", DATA_PATH "/assets/sfx/weapons/c4.wav");     // queda poco tiempo

        // jugador
        load_sound("death", DATA_PATH "/assets/sfx/player/die1.wav");
        load_sound("footstep_dirt_1", DATA_PATH "/assets/sfx/player/pl_dirt1.wav");
        load_sound("footstep_dirt_2", DATA_PATH "/assets/sfx/player/pl_dirt2.wav");
        load_sound("footstep_dirt_3", DATA_PATH "/assets/sfx/player/pl_dirt3.wav");
        
        load_sound("hit1", DATA_PATH "/assets/sfx/player/hit1.wav");
        load_sound("hit2", DATA_PATH "/assets/sfx/player/hit2.wav");
        load_sound("hit3", DATA_PATH "/assets/sfx/player/hit3.wav");
        
        // radio
        load_sound("gogogo", DATA_PATH "/assets/sfx/radio/go.ogg");


        // Cargar música de fondo
        load_music(DATA_PATH "/assets/sfx/menu.wav");
        play_music();
        
    } catch (const SDL2pp::Exception& e) {
        std::cerr << "Error inicializando SoundManager: " << e.what() << std::endl;
    }
}

void SoundManager::load_sound(const std::string& name, const std::string& path) {
    // chunk se utiliza para efectos de sonido cortos
    try {
        auto chunk = std::make_unique<SDL2pp::Chunk>(path);
        sound_effects[name] = std::move(chunk);
    } catch (const SDL2pp::Exception& e) {
        std::cerr << "Error cargando sonido " << name << " desde " << path << ": " << e.what() << std::endl;
    }
}

void SoundManager::load_music(const std::string& path) {
    try {
        background_music = std::make_unique<SDL2pp::Music>(path);
    } catch (const SDL2pp::Exception& e) {
        std::cerr << "Error cargando música desde " << path << ": " << e.what() << std::endl;
    }
}

void SoundManager::play_sound(const std::string& name, int channel_group) {
    if (!sfx_enabled) return;
    
    auto it = sound_effects.find(name);
    if (it != sound_effects.end()) {
        try {
            // configurar volumen del chunk
            it->second->SetVolume(sfx_volume);
            
            // con -1 se reproduce en cualquier canal disponbile
            // Si se especifica un grupo, usa reserva de canales para ese grupo
            int channel = -1;
            if (channel_group != -1) {
                // Reservar canales para grupos específicos
                switch (channel_group) {
                    case WEAPON_GROUP:
                        channel = mixer.PlayChannel(0, *it->second, 0); // Canales 0-1 para armas
                        break;
                    case UI_GROUP:
                        channel = mixer.PlayChannel(2, *it->second, 0); // Canales 2-3 para UI
                        break;
                    case WORLD_GROUP:
                        channel = mixer.PlayChannel(4, *it->second, 0); // Canales 4-7 para mundo
                        break;
                    default:
                        channel = mixer.PlayChannel(-1, *it->second, 0);
                        break;
                }
            } else {
                channel = mixer.PlayChannel(-1, *it->second, 0);
            }
            
            if (channel == -1) {
                std::cerr << "No se pudo reproducir sonido: " << name << std::endl;
            }
        } catch (const SDL2pp::Exception& e) {
            std::cerr << "Error reproduciendo sonido " << name << ": " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Sonido no encontrado: " << name << std::endl;
    }
}

// void SoundManager::play_sound_with_distance(const std::string& name, float distance, int channel_group) {
//     if (!sfx_enabled) return;
    
//     auto it = sound_effects.find(name);
//     if (it != sound_effects.end()) {
//         try {
//             // Calcular volumen basado en distancia (máximo 500 unidades)
//             float distance_factor = 1.0f - std::min(distance / 500.0f, 1.0f);
//             int volume = static_cast<int>(sfx_volume * distance_factor);
            
//             // Configurar volumen del chunk
//             it->second->SetVolume(volume);
            
//             // Reproducir con el grupo especificado
//             int channel = -1;
//             if (channel_group != -1) {
//                 switch (channel_group) {
//                     case WEAPON_GROUP:
//                         channel = mixer.PlayChannel(0, *it->second, 0);
//                         break;
//                     case UI_GROUP:
//                         channel = mixer.PlayChannel(2, *it->second, 0);
//                         break;
//                     case WORLD_GROUP:
//                         channel = mixer.PlayChannel(4, *it->second, 0);
//                         break;
//                     default:
//                         channel = mixer.PlayChannel(-1, *it->second, 0);
//                         break;
//                 }
//             } else {
//                 channel = mixer.PlayChannel(-1, *it->second, 0);
//             }
            
//         } catch (const SDL2pp::Exception& e) {
//             std::cerr << "Error reproduciendo sonido con distancia " << name << ": " << e.what() << std::endl;
//         }
//     }
// }

void SoundManager::play_music() {
    if (music_enabled && background_music) {
        try {
            mixer.SetMusicVolume(music_volume);
            mixer.PlayMusic(*background_music, -1); // -1 = loop infinito
        } catch (const SDL2pp::Exception& e) {
            std::cerr << "Error reproduciendo música: " << e.what() << std::endl;
        }
    }
}

void SoundManager::stop_music() {
    try {
        mixer.HaltMusic();
    } catch (const SDL2pp::Exception& e) {
        std::cerr << "Error deteniendo música: " << e.what() << std::endl;
    }
}

// mas adelante se podria hacer para controlar el volumen
// o detener la musica y sonido
// ==================
void SoundManager::set_sfx_volume(int volume) {
    sfx_volume = std::clamp(volume, 0, 128);
}

void SoundManager::set_music_volume(int volume) {
    music_volume = std::clamp(volume, 0, 128);
    if (music_enabled) {
        try {
            mixer.SetMusicVolume(music_volume);
        } catch (const SDL2pp::Exception& e) {
            std::cerr << "Error ajustando volumen de música: " << e.what() << std::endl;
        }
    }
}

void SoundManager::toggle_mute() {
    sfx_enabled = !sfx_enabled;
    music_enabled = !music_enabled;
    
    if (!music_enabled) {
        stop_music();
    } else {
        play_music();
    }
}
// ==================


/**
 * Se llama en cada ciclo, verifica el estado del jugador y reproduce sonidos
 * para no hacerlo en el input handler (ej. cambiar de arma) es mas conveniente
 * manejarlo desde aca y aplicar un poco de logica
 */
void SoundManager::check_and_play_game_sounds(const SnapshotDTO& snapshot, const PrivatePlayerDTO& user_data) {
    static WeaponName last_weapon = WeaponName::NONE;
    static int last_hp = 100;
    static int last_ammo = -1;
    
    // Sonido de cambio de arma
    if (user_data.current_weapon.name != last_weapon && last_weapon != WeaponName::NONE) {
        play_sound("weapon_switch", WEAPON_GROUP);
        last_weapon = user_data.current_weapon.name;
    } else if (last_weapon == WeaponName::NONE) {
        last_weapon = user_data.current_weapon.name;
    }
    
    // Sonido de recarga (cuando las balas cargadas aumentan significativamente)
    if (last_ammo != -1 && user_data.current_weapon.loaded_ammo > last_ammo + 3) {
        play_sound("reload", WEAPON_GROUP);
    }
    last_ammo = user_data.current_weapon.loaded_ammo;
    
    // Sonido de daño recibido
    if (user_data.player_hp < last_hp && last_hp > 0) {
        play_sound("hit1", WORLD_GROUP);
    }
    last_hp = user_data.player_hp;

    // itera todos los jugadores y reproduce sonidos segun la distancia al user

    
    
    // Position my_pos = get_my_player_position(snapshot, user_data.player_id);
    // for (const auto& player : snapshot.players) {
    //     if (player.is_shooting && player.player_id != user_data.player_id) {
    //         float distance = calculate_distance(my_pos, Position(player.x, player.y));
    //         play_sound_with_distance("gunshot", distance, WEAPON_GROUP);
    //     }
    // }
}

// Métodos auxiliares para calcular distancias (para futura implementación)
/*
Position SoundManager::get_my_player_position(const SnapshotDTO& snapshot, int my_id) {
    for (const auto& player : snapshot.players) {
        if (player.player_id == my_id) {
            return Position(player.x, player.y);
        }
    }
    return Position(0, 0);
}

float SoundManager::calculate_distance(const Position& pos1, const Position& pos2) {
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    return std::sqrt(dx*dx + dy*dy);
}
*/