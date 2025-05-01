#include "main_game.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>


int main(int argc, char** argv)
{
    std::srand(std::time({})); // use current time as seed for random generator
    
    // 𝑴𝒆𝒐𝒘. (•- •マ
    std::cout << "Hellow World !\n";
    MainGame main_game = MainGame();
    main_game.mainloop();

    return 0;
}
