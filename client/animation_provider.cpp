#include "animation_provider.h"

#include <vector>

#include "client/renderables/animation.h"
#include "common/snapshot.h"

#define FPS_BASE 60

std::unordered_map<std::string, AnimationData> AnimationProvider::frames_data;

void AnimationProvider::load_animations() {
    frames_data["terrorist_idle"] = AnimationData{2, 1, false};
    frames_data["terrorist_running"] = AnimationData{4, 8, true};

}

const AnimationData& AnimationProvider::get_animation_data(const std::string& name) {
    if (frames_data.find(name) == frames_data.end()) {
        throw std::runtime_error("Animation data not found: " + name);
    }
    return frames_data[name];
}

