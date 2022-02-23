#include <iostream>
#include "get_int_from_user.h"

void play_guess_the_number()
{
    static constexpr int MIN            = 0;
    static constexpr int MAX            = 100;
    const int            program_number = rand(MIN, MAX);
    std::cout << "I pick a number between " << MIN << " and " << MAX << " :" << '\n';

    bool finished = false;

    while (!finished) {
        const int player_number = get_int_from_user();

        if (player_number == program_number) {
            finished = true;
            std::cout << "Congrats, you won!" << '\n';
        }
        else if (player_number < program_number) {
            std::cout << "Greater " << '\n';
        }
        else {
            std::cout << "Smaller " << '\n';
        }
    }
}