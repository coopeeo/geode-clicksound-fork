#include <Geode/Geode.hpp>
#include <Geode/loader/SettingNode.hpp>
using namespace geode::prelude;


#include "ClickTypes.hpp"
#include "ClickTypeNodes.hpp"
#include "Sections.hpp"
#include "SoundTest.hpp"

$on_mod(Loaded) {
    Mod::get()->addCustomSetting<SettingClickValue>("test-click-btn", "none");
    Mod::get()->addCustomSetting<SettingReleaseValue>("test-release-btn", "none");
    Mod::get()->addCustomSetting<SectionSettingValue>("clicksound-section", "none");
    Mod::get()->addCustomSetting<ClickTypeValue>("clicksound-type", matjson::parse(R"({"tab":1,"click":1,"memeClick":1,"customClick":"..."})"));
    Mod::get()->addCustomSetting<ReleaseTypeValue>("releasesound-type", matjson::parse(R"({"tab":1,"click":1,"memeClick":1,"customClick":"..."})"));
    Mod::get()->addCustomSetting<SectionSettingValue>("releasesound-section", "none");
    Mod::get()->addCustomSetting<SectionSettingValue>("misc-section", "none");
}
