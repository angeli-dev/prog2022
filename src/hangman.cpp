#include <array>
#include <iostream>
//#include <string_view>
#include "algorithm"
#include "get_input_from_user.h"
#include "random.h"

std::string pick_a_word_to_guess()
{
    static std::vector<std::string> words = {
        "code",
        "crous",
        "imac",
        "opengl",
    };
    const size_t n = rand<size_t>(0, words.size() - 1);
    return words[n];
}

void show_number_of_lives(const int number_of_lives)
{
    std::cout << "Nombre de vie : " << number_of_lives << std::endl;
}

bool player_is_alive(const int number_of_lives)
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
    for (size_t letter = 0; letter < word.size(); letter++) {
        if (letters_guessed[letter]) {
            std::cout << word[letter];
        }
        else {
            std::cout << "_";
        }
    }
    std::cout << '\n';
}

bool word_contains(const std::string letter, const std::string word)
{
    if (word.find(letter) == std::string::npos) {
        return 0;
    }
    return 1;
}

void mark_as_guessed(const std::string guessed_letter, std::vector<bool>& letters_guessed, const std::string word_to_guess)
{
    size_t pos = 0;
    std::cout << word_to_guess.find(guessed_letter, pos) << std::endl;
    while (word_to_guess.find(guessed_letter, pos) != std::string::npos) {
        pos                  = word_to_guess.find(guessed_letter, pos);
        letters_guessed[pos] = 1;
        pos++;
    }
}

void remove_one_life(int& lives_count)
{
    lives_count--;
}

void show_congrats_message(const std::string word_to_guess)
{
    std::cout << "Congratulations!" << std::endl;
    std::cout << "The word was: " << word_to_guess << "!" << std::endl;
}

void show_defeat_message()
{
    std::cout << "You're dead, bad guy!" << std::endl;
}

void play_hangman()
{
    int               number_of_lives = 10;
    const std::string word            = pick_a_word_to_guess();
    std::vector<bool> letters_guessed(word.size(), 0);

    while (player_is_alive(number_of_lives) && !player_has_won(letters_guessed)) {
        show_number_of_lives(number_of_lives);
        show_word_to_guess_with_missing_letters(word, letters_guessed);
        const auto guess = get_input_from_user<std::string>();
        if (word_contains(guess, word)) {
            mark_as_guessed(guess, letters_guessed, word);
        }
        else {
            remove_one_life(number_of_lives);
        }
    }
    if (player_has_won(letters_guessed)) {
        show_congrats_message(word);
    }
    else {
        show_defeat_message();
    }
}