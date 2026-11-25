#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

namespace {
void playClickSound() {
    auto volume = Mod::get()->getSettingValue<double>("volume");
    if (volume <= 0.0) {
        return;
    }

    auto soundFile = Mod::get()->getSettingValue<asp::fs::Path>("sound-file");
    auto soundPath = soundFile.empty() ? "osu.wav"_spr : soundFile.string();
    FMODAudioEngine::sharedEngine()->playEffect(soundPath, 1.0f, 1.0f, static_cast<float>(volume));
}
}

$on_mod(Loaded) {
    static auto listener = ButtonSettingPressedEventV3(Mod::get(), "test-sound")
        .listen([](std::string_view buttonKey) {
            if (buttonKey == "play") {
                playClickSound();
            }
        });
}

class $modify(OsuPlayerObject, PlayerObject) {
    void pushButton(PlayerButton p0) {
        PlayerObject::pushButton(p0);

        if (p0 != PlayerButton::Jump || !Mod::get()->getSettingValue<bool>("enabled")) {
            return;
        }

        playClickSound();
    }
};
