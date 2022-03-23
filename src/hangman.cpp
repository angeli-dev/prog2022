#include "hangman.h"
#include <assert.h>
#include <array>
#include <iostream>
#include "algorithm"
#include "get_input_from_user.h"
#include "random.h"

std::string pick_a_word_to_guess()
{
    static std::vector<std::string> words = {
        "mushroom",
        "brioche",
        "chocolate",
        "turtle",
    };
    const auto n = rand<size_t>(0, words.size() - 1);
    return words[n];
}

void Hangman::show_number_of_lives()
{
    std::cout << "Life : " << _number_of_lives << std::endl;
}

bool Hangman::player_is_alive()
{
    if (_number_of_lives <= 0) {
        return 0;
    }
    return 1;
}

bool Hangman::player_has_won()
{
    if (std::all_of(_letters_guessed.cbegin(), _letters_guessed.cend(), [](int x) { return x == 1; })) {
        return 1;
    }
    return 0;
}

void Hangman::show_word_to_guess_with_missing_letters()
{
    for (size_t letter = 0; letter < _word.size(); letter++) {
        if (_letters_guessed[letter]) {
            std::cout << _word[letter];
        }
        else {
            std::cout << "_";
        }
    }
    std::cout << '\n';
}

bool Hangman::word_contains(const std::string letter)
{
    if (_word.find(letter) == std::string::npos) {
        return 0;
    }
    return 1;
}

void Hangman::mark_as_guessed(const std::string guessed_letter)
{
    size_t pos = 0;
    while (_word.find(guessed_letter, pos) != std::string::npos) {
        pos                   = _word.find(guessed_letter, pos);
        _letters_guessed[pos] = 1;
        pos++;
    }
}

void Hangman::remove_one_life()
{
    _number_of_lives--;
}

void Hangman::show_congrats_message()
{
    std::cout << "Congratulations!" << std::endl;
    std::cout << "The word was: " << _word << "!" << std::endl;
}

void show_defeat_message()
{
    std::cout << "You're dead, bad guy!" << std::endl;
}

void play_hangman()
{
    const std::string word = pick_a_word_to_guess();
    Hangman           game(word);

    while (game.player_is_alive() && !game.player_has_won()) {
        game.show_number_of_lives();
        game.show_word_to_guess_with_missing_letters();
        const auto guess = get_input_from_user<std::string>();
        if (game.word_contains(guess)) {
            game.mark_as_guessed(guess);
        }
        else {
            game.remove_one_life();
        }
    }
    if (game.player_has_won()) {
        game.show_congrats_message();
    }
    else {
        show_defeat_message();
    }
}