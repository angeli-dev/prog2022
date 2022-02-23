#include <array>
#include <iostream>
#include "algorithm"
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

void show_number_of_lives(int number_of_lives)
{
    std::cout << number_of_lives << "/n";
}

bool player_is_alive(int number_of_lives)
{
    if (number_of_lives <= 0) {
        return 0;
    }
    return 1;
}

bool player_has_won(const std::vector<bool>& letters_guessed)
{
    if (std::all_of(letters_guessed.cbegin(), letters_guessed.cend(), [](int x) { return x == 1; })) {
        return 1;
    }
    return 0;
}