#pragma once
#include <functional>
#include <string>

struct Game {
    std::string           name;
    std::function<void()> function;
};