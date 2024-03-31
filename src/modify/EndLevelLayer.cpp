#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>

#include "../click/Toolbox.hpp"
#include "../click/Manager.hpp"

// 🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕🥕
class $modify(EndLevelLayer) {
    void customSetup(){
        EndLevelLayer::customSetup();
        auto manager = click::Manager::shared();
        
        if (manager->getWatermark()) {
            auto watermarkNode = CCNode::create();
            auto watermarkSprite = click::Toolbox::createSprite("watermark_001.png"_spr);
            watermarkNode->setPosition(450, 260);
            watermarkNode->setAnchorPoint({0.5, 0.5});
            watermarkNode->setScale(0.2);
            watermarkSprite->setOpacity(10);
            watermarkNode->addChild(watermarkSprite);
            
            static_cast<cocos2d::CCLayer*>(
                this->getChildren()->objectAtIndex(0)
            )->addChild(watermarkNode);
        }
        
        manager->setWatermark(false);
    }
};
