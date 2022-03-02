#include <array>
#include <iostream>
#include <string_view>
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

void show_word_to_guess_with_missing_letters(const std::string& word, const std::vector<bool>& letters_guessed)
{
    for (size_t letter; letter < word.size(); letter++) {
        if (letters_guessed[letter]) {
            std::cout << letter;
        }
        else {
            std::cout << "_";
        }
    }
}

bool word_contains(char letter, std::string_view word)
{
    if (word.find(letter) == std::string_view::npos) {
        return 0;
    }
    return 1;
}

void mark_as_guessed(char guessed_letter, std::vector<bool>& letters_guessed, std::string_view word_to_guess)
{
    size_t pos = 0;
    while (word_to_guess.find(guessed_letter, pos) != std::string_view::npos) {
        pos                  = word_to_guess.find(guessed_letter, pos);
        letters_guessed[pos] = 1;
    }
}

void remove_one_life(int& lives_count)
{
    lives_count--;
}

void show_congrats_message(std::string_view word_to_guess)
{
    std::cout << "Congratulations!" << std::endl;
}

void show_defeat_message()
{
    std::cout << "You're dead, bad guy!" << std::endl;
}
