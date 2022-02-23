#pragma once
#include <array>
#include <iostream>
#include "random.h"

const char* pick_a_random_word()
{
    static constexpr std::array words = {
        "code",
        "crous",
        "imac",
        "opengl",
    };
    const int n = rand<size_t>(0, words.size() - 1);
    return words[n];
}