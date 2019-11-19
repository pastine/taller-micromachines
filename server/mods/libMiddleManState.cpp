#include <common/json.h>
#include <string>
#include <unordered_map>

char *modify_json(char *jsonstr) {
    JSON json = JSON::parse(jsonstr);
    json["elements"]["lives"] = "1";
    return strdup(json.dump().c_str());
}

extern "C" {
char *middleman(char *json) {
    return modify_json(json);
}
}
