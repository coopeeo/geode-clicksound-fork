#pragma once
#include <Geode/Geode.hpp>
#include <Geode/loader/SettingNode.hpp>
using namespace geode::prelude;

#include "../click/utils/Clicks.hpp"
#include "../click/Convert.hpp"
#include "ClickTypes.hpp"
#include <matjson.hpp>
#include <string>


// STOLE FROM VIPER'S BETTER MENU BUT CUSTOMIZED BY COOPER 
class ClickTypeNode : public SettingNode {
protected:
    // values
    int m_currentPos;
    int m_currentClick;
    int m_currentMemeClick;
    std::string m_kind;
    std::string m_currentCustomClick;

    // Buttons and Menus
    CCMenuItemToggler* usefulBtn;
    CCMenuItemToggler* memeBtn;
    CCMenuItemToggler* customBtn;
    CCMenu* menu;
    CCMenu* menu1;
    CCMenu* menu2;
    CCLabelBMFont* label;
    CCLabelBMFont* anotherLabel;
    InputNode* inputNode1;
    InputNode* inputNode2;
    CCSprite* arrowRight;
    CCMenuItemSpriteExtra* buttonRight;
    CCSprite* arrowLeft;
    CCMenuItemSpriteExtra* buttonLeft;
    CCSprite* folderSpr;
    CCMenuItemSpriteExtra* folderBtn;

    int getActiveCornerTag(int corner) {
        switch (corner) {
            case 1: // useful
                return 2004;
            case 2: // meme
                return 2005;
            case 3: // custom
                return 2006;
            default:
                return 2007;
        }
    }
    int tagToCorner(int tag) {
        switch (tag) {
            case 2004: // useful
                return 1;
            case 2005: // meme
                return 2;
            case 2006: // custom
                return 3;
            default:
                return 4;
        }
    }
    template <typename T>
    bool init(T* value, float width, std::string prefixText);
    
    void onCornerClick(CCObject* sender);

    void onNext(CCObject* sender);

    void onPrev(CCObject* sender);

    void onFolder(CCObject* sender);

public:
    void commit() override {
        static_cast<ClickTypeValue*>(m_value)->setItem("tab", m_currentPos);
        static_cast<ClickTypeValue*>(m_value)->setItem("click", m_currentClick);
        static_cast<ClickTypeValue*>(m_value)->setItem("memeClick", m_currentMemeClick);
        static_cast<ClickTypeValue*>(m_value)->setItem("customClick", m_currentCustomClick);
        this->dispatchCommitted();
    }
    bool hasUncommittedChanges() override {
        return m_currentPos != click::Convert::toInt(static_cast<ClickTypeValue*>(m_value)->getItem("tab")) || m_currentClick != click::Convert::toInt(static_cast<ClickTypeValue*>(m_value)->getItem("click")) || click::Convert::toInt(m_currentMemeClick != static_cast<ClickTypeValue*>(m_value)->getItem("memeClick")) || m_currentCustomClick != click::Convert::toString(static_cast<ClickTypeValue*>(m_value)->getItem("customClick"));
    }
    bool hasNonDefaultValue() override {
        return m_currentPos != 1 || m_currentClick != 1 || m_currentMemeClick != 1 || m_currentCustomClick != "...";
    }

    // Geode calls this to reset the setting's value back to default
    void resetToDefault() override {
        usefulBtn->toggle(false);
        memeBtn->toggle(true);
        customBtn->toggle(true);
        m_currentPos = 1;
        m_currentClick = 1;
        m_currentMemeClick = 1;
        m_currentCustomClick = "...";
        static_cast<ClickTypeValue*>(m_value)->setTab(m_currentPos);
        static_cast<ClickTypeValue*>(m_value)->setClick(m_currentClick);
        static_cast<ClickTypeValue*>(m_value)->setMemeClick(m_currentMemeClick);
        static_cast<ClickTypeValue*>(m_value)->setCustomClick(m_currentCustomClick);
    }
    template <typename T>
    static ClickTypeNode* create(T* value, float width, std::string prefixText = "?") {
        auto ret = new ClickTypeNode;
        if (ret && ret->init(value, width, prefixText)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};
