#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(OsuPlayerObject, PlayerObject) {
    void pushButton(PlayerButton p0) {
        PlayerObject::pushButton(p0);

        // Verifica si el mod está activado en los ajustes de Geode
        if (!Mod::get()->getSettingValue<bool>("enabled")) {
            return;
        }

        // Solo reproduce el sonido en el botón principal de salto/acción
        if (p0 == PlayerButton::Jump) {
            float volume = static_cast<float>(Mod::get()->getSettingValue<double>("volume"));
            if (volume > 0.0f) {
                FMODAudioEngine::sharedEngine()->playEffect("osu.wav"_spr, 1.0f, 1.0f, volume);
            }
        }
    }
};
