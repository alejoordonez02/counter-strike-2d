#ifndef CLIENT_SOUND_MANAGER_H
#define CLIENT_SOUND_MANAGER_H

#include <SDL2/SDL_mixer.h>

#include <unordered_map>
#include <string>
#include <memory>

#include "common/network/dtos/snapshot_dto.h"

class SoundManager {
private:
    std::unordered_map<std::string, Mix_Chunk*> sound_effects;
    Mix_Music* background_music;
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
    void play_sound(const std::string& name, int volume = -1);
    void play_sound_with_distance(const std::string& name, float distance);
    
    // Controlar música
    void play_music();
    void stop_music();
    // void pause_music();
    // void resume_music();
    
    // Configuración
    // void set_sfx_volume(int volume);
    // void set_music_volume(int volume);
    void enable_sfx(bool enabled) { sfx_enabled = enabled; }
    void enable_music(bool enabled) { music_enabled = enabled; }

    void check_and_play_game_sounds(const SnapshotDTO& snapshot, const PrivatePlayerDTO& user_data);
};

#endif