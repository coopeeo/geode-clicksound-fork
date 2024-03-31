#pragma once

#include <matjson.hpp>

namespace click {

class Convert {
public:
    //! @brief Convert json value to string
    static std::string toString(matjson::Value val);
    //! @brief Convert json value to integer
    static int toInt(matjson::Value val);

};

}; // namespace click
