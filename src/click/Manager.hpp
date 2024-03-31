#pragma once

#include <Geode/loader/Mod.hpp>
#include <unordered_set>

namespace click {

//! @brief Manager singleton class.
class Manager final {
public:
    //! @brief Get manager singleton.
    //! @return Manager singleton.
    static Manager* shared();

    Manager();
    ~Manager() {}

    //! @brief Get whether an account ID is held by a contributor.
    //! @return Whether an account ID is held by a contributor.
    bool isContributor(int accountID) const {
        return m_contributors.contains(accountID);
    }

    //! @brief Get whether the settings button is enabled.
    //! @return Whether the settings button is enabled.
    bool getSettingsButton() const {
        return geode::Mod::get()->getSettingValue<bool>("settings-button");
    }

    bool getWatermark() const {
        return m_watermark;
    }

    void setWatermark(bool statusToSet) {
        m_watermark = statusToSet;
    }

private:
    static Manager* s_sharedManager;
    
    std::unordered_set<int> m_contributors;
    bool m_watermark;
};

} // namespace click
