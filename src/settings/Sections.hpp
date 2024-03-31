#pragma once
#include <Geode/Geode.hpp>
#include <Geode/loader/SettingNode.hpp>
using namespace geode::prelude;


// SECTIONS
// Copied from Coop's new Hide+ mod (get it now!)

class SectionSettingValue;

class SectionSettingValue : public SettingValue {
protected:
    std::string m_placeholder;
public:
    SectionSettingValue(std::string const& key, std::string const& modID, std::string const& placeholder)
      : SettingValue(key, modID), m_placeholder(placeholder) {}
    bool load(matjson::Value const& json) override {return true;}
    bool save(matjson::Value& json) const override {return true;}
    SettingNode* createNode(float width) override;
};

class SectionSettingNode : public SettingNode {
protected:
    bool init(SectionSettingValue* value, float width);

public:
    void commit() override {
        this->dispatchCommitted();
    }
    bool hasUncommittedChanges() override {
        return false;
    }
    bool hasNonDefaultValue() override {
        return true;
    }
    void resetToDefault() override {}

    static SectionSettingNode* create(SectionSettingValue* value, float width) {
        auto ret = new SectionSettingNode();
        if (ret && ret->init(value, width)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};