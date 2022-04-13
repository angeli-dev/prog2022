#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "game.h"
#include "get_input_from_user.h"
#include "hangman.h"
#include "play_guess_the_number.h"

void show_the_list_of_commands(const std::map<char, Game> games)
{
    for (const auto& game : games) {
        std::cout << "Press " << game.first << " to play '"
                  << game.second.name
                  << "' " << std::endl;
    }

    std::cout << "Press q to quit" << std::endl;
}

void read_pressed_key(const char pressed_key, std::map<char, Game> games)
{
    if (pressed_key == 'q') {
        std::cout << "Bye bye no funny guy" << std::endl;
    }
    else if (games.count(pressed_key)) {
        games[pressed_key].function();
        show_the_list_of_commands(games);
        char new_pressed_key = get_input_from_user<char>();
        read_pressed_key(new_pressed_key, games);
    }
    else {
        std::cout << "Haha you don't read carefully what I said" << std::endl;
        std::cout << "Read again:" << std::endl;
        show_the_list_of_commands(games);
        char new_pressed_key = get_input_from_user<char>();
        read_pressed_key(new_pressed_key, games);
    }
}

void display_menu()
{
    std::map<char, Game> games;

    Game guess_the_number;
    guess_the_number.name     = "Guess the number";
    guess_the_number.function = play_guess_the_number;

    Game hangman;
    hangman.name     = "Hangman";
    hangman.function = play_hangman;

    games['1'] = guess_the_number;
    games['2'] = hangman;

    std::cout << "What do you want to play today?" << std::endl;
    show_the_list_of_commands(games);
    char pressed_key = get_input_from_user<char>();
    read_pressed_key(pressed_key, games);
}
