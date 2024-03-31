#include <Geode/Geode.hpp>
#include <Geode/loader/SettingNode.hpp>
using namespace geode::prelude;

#include "ClickTypes.hpp"
#include "ClickTypeNodes.hpp"

SettingNode* ReleaseTypeValue::createNode(float width) {
    return ClickTypeNode::create(this, width, "Release");
}

SettingNode* ClickTypeValue::createNode(float width) {
    return ClickTypeNode::create(this, width, "Click");
}

template <typename T>
bool ClickTypeNode::init(T* value, float width, std::string prefixText) {
    if (!SettingNode::init(value))
        return false;

    m_kind = prefixText;
    m_currentPos = value->getItem("tab");
    m_currentClick = value->getItem("click");
    m_currentMemeClick = value->getItem("memeClick");
    m_currentCustomClick = value->getItem("customClick");
    this->setContentSize({ width, 70.f });

    menu = CCMenu::create();
    menu->setContentSize({ width/2, 20.f} );
    menu->setPosition(width*3/4 - 7.f, 50.f);
    menu->setLayout(RowLayout::create()
            ->setGap(4.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAutoScale(false)
            ->setCrossAxisOverflow(true)
    );

    usefulBtn = CCMenuItemToggler::create(
        ButtonSprite::create("Useful", 40.f, true, "bigFont.fnt", "GJ_button_01.png", 20.f, 0.5f),
        ButtonSprite::create("Useful", 40.f, true, "bigFont.fnt", "GJ_button_04.png", 20.f, 0.5f),
        this,
        menu_selector(ClickTypeNode::onCornerClick)
    );
    memeBtn = CCMenuItemToggler::create(
        ButtonSprite::create("Meme", 40.f, true, "bigFont.fnt", "GJ_button_01.png", 20.f, 0.5f),
        ButtonSprite::create("Meme", 40.f, true, "bigFont.fnt", "GJ_button_04.png", 20.f, 0.5f),
        this,
        menu_selector(ClickTypeNode::onCornerClick)
    );
    customBtn = CCMenuItemToggler::create(
        ButtonSprite::create("Custom", 40.f, true, "bigFont.fnt", "GJ_button_01.png", 20.f, 0.5f),
        ButtonSprite::create("Custom", 40.f, true, "bigFont.fnt", "GJ_button_04.png", 20.f, 0.5f),
        this,
        menu_selector(ClickTypeNode::onCornerClick)
    );

    usefulBtn->setTag(getActiveCornerTag(1));
    memeBtn->setTag(getActiveCornerTag(2));
    customBtn->setTag(getActiveCornerTag(3));
    usefulBtn->setTag(getActiveCornerTag(1));
    memeBtn->setTag(getActiveCornerTag(2));
    customBtn->setTag(getActiveCornerTag(3));
    int currentCorner = m_currentPos;
    usefulBtn->toggle(!(usefulBtn->getTag() == getActiveCornerTag(currentCorner)));
    memeBtn->toggle(!(memeBtn->getTag() == getActiveCornerTag(currentCorner)));
    customBtn->toggle(!(customBtn->getTag() == getActiveCornerTag(currentCorner)));
    
    this->addChild(menu);
    menu->addChild(usefulBtn);
    menu->addChild(memeBtn);
    menu->addChild(customBtn);

    label = CCLabelBMFont::create(fmt::format("{} Type",prefixText).c_str(), "bigFont.fnt");
    label->setScale(.5F);
    label->setAnchorPoint({ 0.f, 0.5f });
    label->setPosition(20.f, 50.f);

    this->addChild(label);
    menu->updateLayout();

    menu1 = CCMenu::create();
    menu1->setPosition({ width - 20.f, 20.f });
    menu1->setVisible(false);
    menu1->setTag(5001);
    this->addChild(menu1);

    anotherLabel = CCLabelBMFont::create(fmt::format("{} Sound",prefixText).c_str(), "bigFont.fnt");
    anotherLabel->setScale(.5F);
    anotherLabel->setAnchorPoint({ 0.f, 0.5f });
    anotherLabel->setPosition(20.f, 20.f);
    this->addChild(anotherLabel);

    inputNode1 = InputNode::create(200.f, "...", "chatFont.fnt");
    inputNode1->setScale(0.65f);
    inputNode1->setPosition(-75.f, 0);
    inputNode1->setString("...");
    inputNode1->getInput()->setAllowedChars("");
    menu1->addChild(inputNode1);

    arrowRight = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    arrowRight->setScale(0.3f);
    buttonRight = CCMenuItemSpriteExtra::create(arrowRight, this, menu_selector(ClickTypeNode::onNext));
    menu1->addChild(buttonRight);

    arrowLeft = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    arrowLeft->setScale(0.3f);
    arrowLeft->setFlipX(true);
    buttonLeft = CCMenuItemSpriteExtra::create(arrowLeft, this, menu_selector(ClickTypeNode::onPrev));
    buttonLeft->setPosition(-150.f, 0);
    menu1->addChild(buttonLeft);

    menu2 = CCMenu::create();
    menu2->setPosition({ width - 20.f, 20.f });
    menu2->setVisible(false);
    menu2->setTag(5002);
    this->addChild(menu2);

    inputNode2 = InputNode::create(200.f, "...", "chatFont.fnt");
    inputNode2->setScale(0.65f);
    inputNode2->setPosition(-80.f, 0);
    inputNode2->setString(m_currentCustomClick.c_str());
    inputNode2->getInput()->setAllowedChars("");
    menu2->addChild(inputNode2);

    folderSpr = CCSprite::createWithSpriteFrameName("gj_folderBtn_001.png");
    folderSpr->setScale(0.5f);
    folderBtn = CCMenuItemSpriteExtra::create(
        folderSpr,
        this,
        menu_selector(ClickTypeNode::onFolder)
    );
    menu2->addChild(folderBtn);

    if (m_currentPos == 1 || m_currentPos == 2) {
        if(m_currentPos == 1) {if(m_kind == "Click"){inputNode1->setString(Clicks::get()->getClickList()[m_currentClick]["name"].as<std::string>().c_str());} else {inputNode1->setString(Clicks::get()->getReleaseList()[m_currentClick]["name"].as<std::string>().c_str());}} else {if(m_kind == "Click"){inputNode1->setString(Clicks::get()->getClickList()[m_currentMemeClick]["name"].as<std::string>().c_str());} else {inputNode1->setString(Clicks::get()->getReleaseList()[m_currentMemeClick]["name"].as<std::string>().c_str());}} 
        this->getChildByTag(5001)->setVisible(true);
        this->getChildByTag(5002)->setVisible(false);
    } else if (m_currentPos == 3) {
        this->getChildByTag(5001)->setVisible(false);
        this->getChildByTag(5002)->setVisible(true);
    }

    if (currentCorner == 1 || currentCorner == 2) {
        menu1->setVisible(true);
    } else if (currentCorner == 3) {
        menu2->setVisible(true);
    }
    return true;
}

void ClickTypeNode::onCornerClick(CCObject* sender) {
    usefulBtn->toggle(true);
    memeBtn->toggle(true);
    customBtn->toggle(true);
    m_currentPos = tagToCorner(sender->getTag());

    if (m_currentPos == 1 || m_currentPos == 2) {
        if(m_currentPos == 1) {if(m_kind == "Click"){inputNode1->setString(Clicks::get()->getClickList()[m_currentClick]["name"].as<std::string>().c_str());} else {inputNode1->setString(Clicks::get()->getReleaseList()[m_currentClick]["name"].as<std::string>().c_str());}} else {if(m_kind == "Click"){inputNode1->setString(Clicks::get()->getClickList()[m_currentMemeClick]["name"].as<std::string>().c_str());} else {inputNode1->setString(Clicks::get()->getReleaseList()[m_currentMemeClick]["name"].as<std::string>().c_str());}} 
        this->getChildByTag(5001)->setVisible(true);
        this->getChildByTag(5002)->setVisible(false);
    } else if (m_currentPos == 3) {
        this->getChildByTag(5001)->setVisible(false);
        this->getChildByTag(5002)->setVisible(true);
    }

    this->dispatchChanged();
};

void ClickTypeNode::onNext(CCObject* sender) {
    log::debug("next");
    this->dispatchChanged();
}

void ClickTypeNode::onPrev(CCObject* sender) {
    log::debug("prev");
    this->dispatchChanged();
}

void ClickTypeNode::onFolder(CCObject* sender) {
    file::pickFile(
        file::PickMode::OpenFile,
        {
            dirs::getGameDir()
        },
        [&](auto path) {
            m_currentCustomClick = path.string();
            inputNode2->setString(path.string().c_str());
        }
    );
    this->dispatchChanged();
}