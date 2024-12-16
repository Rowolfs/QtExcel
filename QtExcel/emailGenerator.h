#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

namespace emailGenerator {
    void initializeRandomSeed();
    std::string generateRandomString(size_t length);
    std::string generateEmail();
}
