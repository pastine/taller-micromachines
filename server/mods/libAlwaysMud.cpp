#include <common/json.h>
#include <string>
#include <unordered_map>
#include <common/CommunicationConstants.h>

char *modify_json(char *jsonstr) {
    JSON json = JSON::parse(jsonstr);
    json[J_USER][J_MUD] = true;
    return strdup(json.dump().c_str());
}

extern "C" {
char *middleman(char *json) {
    return modify_json(json);
}
}
