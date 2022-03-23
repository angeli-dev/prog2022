#include <iostream>
#include "get_input_from_user.h"
#include "hangman.h"
#include "play_guess_the_number.h"

void show_the_list_of_commands();

int main()
{
    char pressed_number = '0';
    std::cout << "What do you want to play today?" << std::endl;
    while (pressed_number != 'q') {
        show_the_list_of_commands();
        pressed_number = get_input_from_user<char>();

        if (pressed_number == '1') {
            play_guess_the_number();
        }
        else if (pressed_number == '2') {
            play_hangman();
        }
        else if (pressed_number == 'q') {
            std::cout << "Bye bye no funny guy" << std::endl;
        }
        else {
            std::cout << "Haha you don't read carefully what I said" << std::endl;
            std::cout << "Read again:" << std::endl;
        }
    }
}

void show_the_list_of_commands()
{
    std::cout << "Press 1 to play 'Guess the number'" << std::endl;
    std::cout << "Press 2 to play 'Hangman'" << std::endl;
    std::cout << "Press q to quit" << std::endl;
}