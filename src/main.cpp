#include "main_game.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>


int main(int argc, char** argv)
{
    std::srand(std::time({})); // use current time as seed for random generator

    // 𝑴𝒆𝒐𝒘. (•- •マ
    std::cout << "Hellow World 𓃠 !\n";

    // Initialize the game
    MainGame main_game = MainGame();

    // Mainloop while the game is on
    main_game.mainloop();

    // 𝑴𝒆𝒐𝒘. (•- •マ
    std::cout << "It was really fun to play with you ! ⸜(｡ ˄ᵕ˄ )⸝♡\n";

    // End of the game
    return 0;
}
