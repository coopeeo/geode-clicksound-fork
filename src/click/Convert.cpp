#include <matjson.hpp>

#include "Convert.hpp"


namespace click {

std::string Convert::toString(matjson::Value val) {
    return val.as<std::string>();
}

int Convert::toInt(matjson::Value val) {
    return val.as<int>();
}

} // namespace click
