#include <common/json.h>
#include <string>
#include <unordered_map>

void modify_json(char** jsonstr) {
    JSON json = JSON::parse(*jsonstr);
    std::cout<<json.dump()<<"\n";
    json["elements"]["lives"] = "1";
    std::cout<<json.dump()<<"\n";
    char* dup = strdup(json.dump().c_str());
    *jsonstr = dup;
}

extern "C" {
    void middleman(char** json) {
        modify_json(json);
    }
}
