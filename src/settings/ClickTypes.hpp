#pragma once
#include <Geode/Geode.hpp>
#include <Geode/loader/SettingNode.hpp>
#include <Geode/loader/SettingNode.hpp>
using namespace geode::prelude;

#include <matjson.hpp>
#include <string>

struct CRTypeStruct {
    matjson::Value m_type;
};

class ClickTypeValue : public SettingValue {
protected:
    matjson::Value m_type;
public:
    ClickTypeValue(std::string const& key, std::string const& modID, matjson::Value const& type)
      : SettingValue(key, modID), m_type(type) {}

    bool load(matjson::Value const& json) override {
        if (!json["tab"].is<int>()) return false;
        m_type = json;
        return true;
    }

    bool save(matjson::Value& json) const override {
        json = m_type;
        return true;
    }

    SettingNode* createNode(float width) override;

    template <typename T>
    void setItem(std::string item, T value) {
        m_type[item] = value;
    }

    matjson::Value getItem(std::string item) const {
        return m_type[item];
    }

    matjson::Value getJson() const {
        return m_type;
    }
};

class ReleaseTypeValue : public SettingValue {
protected:
    matjson::Value m_type;
public:
    ReleaseTypeValue(std::string const& key, std::string const& modID, matjson::Value const& type)
      : SettingValue(key, modID), m_type(type) {}

    bool load(matjson::Value const& json) override {
        if (!json["tab"].is<int>() || !json["click"].is<int>() || !json["memeClick"].is<int>() || !json["customClick"].is<std::string>()) {return false;}
        m_type = json;
        return true;
    }

    bool save(matjson::Value& json) const override {
        json = m_type;
        return true;
    }

    SettingNode* createNode(float width) override;

    template <typename T>
    void setItem(std::string item, T* value) {
        m_type[item] = value;
    }

    matjson::Value getItem(std::string item) const {
        return m_type[item];
    }

    matjson::Value getJson() const {
        return m_type;
    }
};

template<>
struct SettingValueSetter<CRTypeStruct> {
    static CRTypeStruct get(SettingValue* setting) {
        auto CRSetting = static_cast<ClickTypeValue*>(setting);
        struct CRTypeStruct defaultStruct = { CRSetting->getJson() };
        return defaultStruct;
    };
};