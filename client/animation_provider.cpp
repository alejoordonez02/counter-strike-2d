#include "client/animation_provider.h"
#include "client/renderables/animation.h"
#include "client/texture_provider.h"

AnimationProvider::AnimationProvider(){
        load_animations();
}

void AnimationProvider::load_animations() {
    // ====== PLAYERS =======
    animation_prototypes["terrorist_1_holding_knife"] = {TextureProvider::get_texture("terrorist_1").get(), AnimationData{2, 0, false}};
    animation_prototypes["terrorist_1_idle"] = {TextureProvider::get_texture("terrorist_1").get(), AnimationData{2, 1, false}};
    animation_prototypes["terrorist_1_placing_bomb"] = {TextureProvider::get_texture("terrorist_1").get(), AnimationData{2, 2, false}};
    animation_prototypes["terrorist_1_holding_pistol"] = {TextureProvider::get_texture("terrorist_1").get(), AnimationData{2, 3, false}};
    animation_prototypes["terrorist_1_holding_rifle"] = {TextureProvider::get_texture("terrorist_1").get(), AnimationData{2, 5, false}};
    
    animation_prototypes["terrorist_2_idle"] = {TextureProvider::get_texture("terrorist_2").get(), AnimationData{2, 1, false, 1}};
    animation_prototypes["terrorist_3_idle"] = {TextureProvider::get_texture("terrorist_3").get(), AnimationData{2, 1, false, 1}};
    animation_prototypes["terrorist_4_idle"] = {TextureProvider::get_texture("terrorist_4").get(), AnimationData{2, 1, false, 1}};

    animation_prototypes["legs"] = {TextureProvider::get_texture("legs").get(), AnimationData{4, 8, true, 5, 0}};

    // ====== GUNS ======
    animation_prototypes["bomb"] = {TextureProvider::get_texture("bomb").get(), AnimationData{1, 0, false}};
    animation_prototypes["knife"] = {TextureProvider::get_texture("knife").get(), AnimationData{1, 0, false}};
    animation_prototypes["glock"] = {TextureProvider::get_texture("glock").get(), AnimationData{1, 0, false}};
    animation_prototypes["ak47"] = {TextureProvider::get_texture("ak47").get(), AnimationData{1, 0, false}};
    animation_prototypes["m3"] = {TextureProvider::get_texture("m3").get(), AnimationData{1, 0, false}};
    animation_prototypes["awp"] = {TextureProvider::get_texture("awp").get(), AnimationData{1, 0, false}};


    // ====== BACKGROUNDS ======
    animation_prototypes["background_dust"] = {TextureProvider::get_texture("background_dust").get(), AnimationData{1, 0, false, 0}};
    animation_prototypes["background_sand1"] = {TextureProvider::get_texture("background_sand1").get(), AnimationData{1, 0, false, 0}};
    animation_prototypes["background_aztec"] = {TextureProvider::get_texture("background_aztec").get(), AnimationData{1, 0, false, 0}};
    animation_prototypes["background_nuke"] = {TextureProvider::get_texture("background_nuke").get(), AnimationData{1, 0, false, 0}};
    
    
    // ====== HUD ICONS ======
    animation_prototypes["heart"] = {TextureProvider::get_texture("hud_symbols").get(), AnimationData{13, 0, false, 0, 0, 0, 0.3}};
    animation_prototypes["shield"] = {TextureProvider::get_texture("hud_symbols").get(), AnimationData{13, 1, false, 0, 0, 0, 0.3}};
    animation_prototypes["clock"] = {TextureProvider::get_texture("hud_symbols").get(), AnimationData{13, 2, false, 0, 0, 0, 0.3}};
    animation_prototypes["money"] = {TextureProvider::get_texture("hud_symbols").get(), AnimationData{13, 7, false, 0, 0, 0, 0.3}};
    

    // ====== HUD NUMBERS ======
    animation_prototypes["0"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 0, false, 0, 0, 66, 0.3}};
    animation_prototypes["1"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 1, false, 0, 0, 66, 0.3}};
    animation_prototypes["2"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 2, false, 0, 0, 66, 0.3}};
    animation_prototypes["3"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 3, false, 0, 0, 66, 0.3}};
    animation_prototypes["4"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 4, false, 0, 0, 66, 0.3}};
    animation_prototypes["5"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 5, false, 0, 0, 66, 0.3}};
    animation_prototypes["6"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 6, false, 0, 0, 66, 0.3}};
    animation_prototypes["7"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 7, false, 0, 0, 66, 0.3}};
    animation_prototypes["8"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 8, false, 0, 0, 66, 0.3}};
    animation_prototypes["9"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 9, false, 0, 0, 66, 0.3}};
    animation_prototypes[":"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 10, false, 0, 0, 66, 0.3}};
    animation_prototypes["|"] = {TextureProvider::get_texture("hud_nums").get(), AnimationData{12, 11, false, 0, 0, 66, 0.3}};

    // ======= TILES / BLOCKS ========
    // ======= DUST BLOCKS ========
    animation_prototypes["ctspawn"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 69, false, 0}};
    animation_prototypes["floor1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 72, false, 0}};
    animation_prototypes["floor2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 73, false, 0}};
    animation_prototypes["floor3"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 74, false, 0}};
    animation_prototypes["floor4"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 75, false, 0}};
    animation_prototypes["floor5"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 76, false, 0}};
    animation_prototypes["floor6"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 77, false, 0}};
    animation_prototypes["floor7"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 78, false, 0}};
    animation_prototypes["floor8"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 79, false, 0}};
    animation_prototypes["floor9"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 80, false, 0}};
    animation_prototypes["floor10"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 81, false, 0}};
    animation_prototypes["floor11"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 82, false, 0}};
    animation_prototypes["floor12"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 83, false, 0}};
    animation_prototypes["floor13"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 84, false, 0}};
    animation_prototypes["floor14"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 85, false, 0}};
    animation_prototypes["floor15"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 86, false, 0}};
    animation_prototypes["floor16"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 87, false, 0}};
    animation_prototypes["floor17"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 88, false, 0}};
    animation_prototypes["floor18"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 89, false, 0}};
    animation_prototypes["floor19"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 90, false, 0}};
    animation_prototypes["floor20"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 91, false, 0}};
    animation_prototypes["floor21"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 92, false, 0}};
    animation_prototypes["floor22"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 93, false, 0}};
    animation_prototypes["grass0"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 19, false, 0}};
    animation_prototypes["grass1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 22, false, 0}};
    animation_prototypes["grass2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 23, false, 0}};
    animation_prototypes["grass3"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 39, false, 0}};
    animation_prototypes["grass4"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 48, false, 0}};
    animation_prototypes["grass5"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 49, false, 0}};
    animation_prototypes["grass6"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 50, false, 0}};
    animation_prototypes["grass7"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 51, false, 0}};
    animation_prototypes["grass8"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 52, false, 0}};
    animation_prototypes["grass9"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 53, false, 0}};
    animation_prototypes["grass10"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 54, false, 0}};
    animation_prototypes["grass11"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 56, false, 0}};
    animation_prototypes["grass12"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 57, false, 0}};
    animation_prototypes["grass13"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 60, false, 0}};
    animation_prototypes["grass14"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 61, false, 0}};
    animation_prototypes["gravel1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 32, false, 0}};
    animation_prototypes["gravel2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 33, false, 0}};
    animation_prototypes["gravel3"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 34, false, 0}};
    animation_prototypes["path1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 40, false, 0}};
    animation_prototypes["path2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 41, false, 0}};
    animation_prototypes["path3"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 42, false, 0}};
    animation_prototypes["path4"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 43, false, 0}};
    animation_prototypes["path5"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 44, false, 0}};
    animation_prototypes["path6"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 45, false, 0}};
    animation_prototypes["path7"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 46, false, 0}};
    animation_prototypes["plantspot1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 68, false, 0}};
    animation_prototypes["plantspot2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 69, false, 0}};
    animation_prototypes["purple"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 0, false, 0}};
    animation_prototypes["sand0"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 8, false, 0}};
    animation_prototypes["sand1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 9, false, 0}};
    animation_prototypes["sand2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 10, false, 0}};
    animation_prototypes["sand3"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 11, false, 0}};
    animation_prototypes["sand4"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 12, false, 0}};
    animation_prototypes["sand5"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 13, false, 0}};
    animation_prototypes["sand6"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 14, false, 0}};
    animation_prototypes["sand7"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 15, false, 0}};
    animation_prototypes["sand8"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 16, false, 0}};
    animation_prototypes["sand9"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 24, false, 0}};
    animation_prototypes["sand10"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 48, false, 0}};
    animation_prototypes["sand11"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 48, false, 0}};
    animation_prototypes["sand12"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 48, false, 0}};
    animation_prototypes["sand13"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 48, false, 0}};
    animation_prototypes["sandpath1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 40, false, 0}};
    animation_prototypes["sandpath2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 41, false, 0}};
    animation_prototypes["sandpath3"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 42, false, 0}};
    animation_prototypes["sandpath4"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 43, false, 0}};
    animation_prototypes["sandgrass1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 24, false, 0}};
    animation_prototypes["sandgrass2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 25, false, 0}};
    animation_prototypes["sandgrass3"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 26, false, 0}};
    animation_prototypes["sandgrass4"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 27, false, 0}};
    animation_prototypes["sandgravel1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 28, false, 0}};
    animation_prototypes["sandgravel2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 29, false, 0}};
    animation_prototypes["sandgravel3"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 30, false, 0}};
    animation_prototypes["sandgravel4"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 31, false, 0}};
    animation_prototypes["sitea"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 70, false, 0}};
    animation_prototypes["siteb"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 71, false, 0}};
    animation_prototypes["solid1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 1, false, 0}};
    animation_prototypes["solid2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 2, false, 0}};
    animation_prototypes["solid3"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 3, false, 0}};
    animation_prototypes["solid4"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 4, false, 0}};
    animation_prototypes["solid5"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 5, false, 0}};
    animation_prototypes["solid6"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 6, false, 0}};
    animation_prototypes["solid7"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 7, false, 0}};
    animation_prototypes["solid8"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 8, false, 0}};
    animation_prototypes["solid9"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 9, false, 0}};
    animation_prototypes["tspawn"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 68, false, 0}};
    animation_prototypes["woodenbox1"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 20, false, 0}};
    animation_prototypes["woodenbox2"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 57, false, 0}};
    animation_prototypes["woodenbox3"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 58, false, 0}};
    animation_prototypes["woodenbox4"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 64, false, 0}};
    animation_prototypes["woodenbox5"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 65, false, 0}};
    animation_prototypes["woodenbox6"] = {TextureProvider::get_texture("embrador_tiles").get(), AnimationData{8, 66, false, 0}};
}

// devuelve un nuevo puntero a la animacion
std::unique_ptr<Animation> AnimationProvider::make_animation(
        const std::string& animation_name) {
    auto it = animation_prototypes.find(animation_name);
    if (it == animation_prototypes.end()) {
        throw std::runtime_error("Animation not found: " + animation_name);
    }
    return std::make_unique<Animation>(*(it->second.texture), it->second.data);
}
