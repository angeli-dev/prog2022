#include <iostream>
#include <random>

/// Returns a random int between min (included) and max (included)
int rand(int min, int max)
{
    static std::default_random_engine  generator{std::random_device{}()};
    std::uniform_int_distribution<int> distribution{min, max};
    return distribution(generator);
}

int get_int_from_user()
{
    int n;
    while (!(std::cin >> n)) {
        std::cin.clear(); // The user did not input a number so we need
        std::cin.sync();  // to clear cin and try again
        std::cout << "This is not a number, try again!\n";
    }
    return n;
}

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

int main()
{
    play_guess_the_number();
}