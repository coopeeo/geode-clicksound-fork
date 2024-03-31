#include <Geode/Geode.hpp>
#include <Geode/loader/SettingNode.hpp>
using namespace geode::prelude;

#include "Sections.hpp"

SettingNode* SectionSettingValue::createNode(float width) {
    return SectionSettingNode::create(this, width);
}

bool SectionSettingNode::init(SectionSettingValue* value, float width) {
        if (!SettingNode::init(value))
            return false;
        this->setContentSize({ width, 40.f });
        std::string name = Mod::get()->getSettingDefinition(value->getKey())->get<CustomSetting>()->json->get<std::string>("name");

        auto theMenu = CCMenu::create();
        auto theLabel = CCLabelBMFont::create(name.c_str(),"bigFont.fnt");

        theLabel->setScale(.5);
        theLabel->setPositionX(0);
        theMenu->addChild(theLabel);
        theMenu->setPosition(width / 2, 20.f);
        
        this->addChild(theMenu);



        return true;
    }