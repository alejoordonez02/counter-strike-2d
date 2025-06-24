#ifndef CLIENT_SOUND_MANAGER_H
#define CLIENT_SOUND_MANAGER_H

#include <string>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Music.hh>
#include <SDL2pp/Mixer.hh>

#include "common/network/dtos/snapshot_dto.h"

#define CHANNELS 8      // permite reproducir 8 sonidos en simultaneo
#define WEAPON_GROUP 1
#define UI_GROUP 2
#define WORLD_GROUP 3

#define MUSIC_VOLUME 20
#define SOUND_VOLUME 50

class SoundManager {
private:
    SDL2pp::Mixer mixer;
    std::unordered_map<std::string, std::unique_ptr<SDL2pp::Chunk>> sound_effects;
    std::unique_ptr<SDL2pp::Music> background_music;
    
    bool music_enabled;
    bool sfx_enabled;
    int sfx_volume;
    int music_volume;

public:
    SoundManager();
    ~SoundManager();
    
    // Cargar sonidos
    void load_sound(const std::string& name, const std::string& path);
    void load_music(const std::string& path);
    
    // Reproducir sonidos
    void play_sound(const std::string& name, int channel_group = -1);
    void play_sound_with_distance(const std::string& name, float distance, int channel_group = WORLD_GROUP);
    
    // Controlar música
    void play_music();
    void stop_music();
    
    // Sonidos específicos de UI
    void play_ui_sound(const std::string& name) { play_sound(name, UI_GROUP); }
    void play_weapon_sound(const std::string& name) { play_sound(name, WEAPON_GROUP); }
    void play_world_sound(const std::string& name) { play_sound(name, WORLD_GROUP); }
    
    // Configuración
    void set_sfx_volume(int volume);
    void set_music_volume(int volume);
    void enable_sfx(bool enabled) { sfx_enabled = enabled; }
    void enable_music(bool enabled) { music_enabled = enabled; }
    void toggle_mute();

    void check_and_play_game_sounds(const SnapshotDTO& snapshot, const PrivatePlayerDTO& user_data);
};

#endif