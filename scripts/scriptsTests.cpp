#include <iostream>
#include "scripts/AIScript.h"

int main() {
    std::string scriptName("helloWorld");
    AIScript script(scriptName);
    std::string s = script.getVariable("testString");
    std::cout << s << std::endl;
    int result = script.callFunction("sumNumbers", {1, 2, 3});
    std::cout << result << std::endl;
}
