#pragma once
#include <map>
#include <string>
#include <vector>

class Hangman {
public:
    Hangman(std::string word)
        : _word{word}
        , _letters_guessed(word.size(), false)
        , _number_of_lives(10)
    {
    }

    bool player_has_won();
    void mark_as_guessed(const std::string guessed_letter);
    void show_word_to_guess_with_missing_letters();
    bool word_contains(const std::string letter);
    void show_congrats_message();
    bool player_is_alive();
    void remove_one_life();
    void show_number_of_lives();

private:
    std::string       _word;
    std::vector<bool> _letters_guessed;
    int               _number_of_lives;
};

void play_hangman();
