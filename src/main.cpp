#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <filesystem>

using namespace geode::prelude;

class $modify(OsuPlayerObject, PlayerObject) {
    void pushButton(PlayerButton p0) {
        PlayerObject::pushButton(p0);

        if (p0 != PlayerButton::Jump || !Mod::get()->getSettingValue<bool>("enabled")) {
            return;
        }

        auto volume = Mod::get()->getSettingValue<double>("volume");
        if (volume <= 0.0) {
            return;
        }

        auto soundFile = Mod::get()->getSettingValue<std::filesystem::path>("sound-file");
        auto soundPath = soundFile.empty() ? "osu.wav"_spr : soundFile.string();
        FMODAudioEngine::sharedEngine()->playEffect(soundPath, 1.0f, 1.0f, static_cast<float>(volume));
    }
};
