#include <iostream>
#include <random>

void instructions();

int main()
{
    std::random_device rd;  // random device
    std::mt19937 gen(rd()); // Mersenne Twister random engine
    std::uniform_int_distribution<int> dist(0, 15); // A random distribution
    int randomNumber = dist(gen);
    int userInput = 0;
    int round = 0;
    std::cout << "Welcome to Hangman Game" << std::endl;
    std::cout << "The random numer : " << randomNumber << std::endl;
    instructions();

    while(round < 3)
    {
        std::cout << "Guess the number : " ;
        std::cin >> userInput;

        if(userInput == randomNumber)
        {
            std::cout << "Congratulations!. YOU WIN" << std::endl;
            break;
        }
        else if(userInput == -1)
        {
            instructions();
        }
        else
        {
            round++;

            if(userInput > randomNumber)
            {
                std::cout << "you entered a greater number";
            }
            else
            {
                std::cout << "you entered a lesser number";
            }

            std::cout << "Try again" << std::endl;
        }

    }

    if(round > 3)
    {
        std::cout << "you lose." << std::endl;
    }
    std::cout << "End of the game.";
    system("pause>0");
    return 0;
}

void instructions()
{
    std::cout << "THe Hangman - instructions" << std::endl;
    std::cout << "The goal is simple. Hangman must not die until end of the game." << std::endl;
    std::cout << "You will provided with three rounds and you need to guess a number. " << std::endl;
    std::cout << "If you guessed the correct number hangman will live and you win. " << std::endl;
    std::cout << "Otherwise hangman will die and you lose. " << std::endl;
    std::cout << "Hint will provided at each end of the round as you enter the number. " <<std::endl;
    std::cout << "You need to guess the number between (including) 0 - 15. " << std::endl;
    std::cout << "Enter -1 for instruction" << std::endl;
}