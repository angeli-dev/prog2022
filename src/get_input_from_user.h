#pragma once
#include <iostream>

/// Blocks until the user inputs something of type T in the console, and then returns it
template<typename T>
T get_input_from_user()
{
    T n;
    while (!(std::cin >> n)) {
        std::cin.clear(); // The user did not input a number so we need
        std::cin.sync();  // to clear cin and try again
        std::cout << "This is not a number, try again!\n";
    }
    return n;
}