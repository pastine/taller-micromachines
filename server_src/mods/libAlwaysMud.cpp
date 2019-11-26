#include <common/json.h>
#include <common/CommunicationConstants.h>

void modify_json(char *jsonstr) {
    JSON json = JSON::parse(jsonstr);
    json[J_USER][J_MUD] = true;
    strcpy(jsonstr, json.dump().c_str());
}

extern "C" {
void middleman(char *json) {
    modify_json(json);
}
}
