#include <iostream>
#include <conio.h>
#include <thread>
#include <Windows.h>

#define setCurPos(x, y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD(x, y))

using position = struct coordinate;

const int groundHeight = 70;
const int groundWidth = 10;
char ground[groundHeight][groundWidth];

struct coordinate
{
    int x, y;
};

class Food
{
    public:
        int x, y;

        void generateFood()
        {
            x = rand() % groundHeight;
            y = rand() % groundWidth;

            if(ground[x][y] != ' ')
            {
                generateFood();
            }
        }
};

class Snake
{
    public:
        char direction;
        int score, length;
        position body[groundHeight * groundWidth];

        void move(Food &f)
        {
            setCurPos(body[0].x, body[0].y);
            std::cout << '*';

            switch(direction)
            {
                case 'w': body[0].x--; break;
                case 'a': body[0].y--; break;
                case 's': body[0].y++; break;
                case 'd': body[0].x++; break;
            }

            setCurPos(body[0].x, body[0].y);
            std::cout << '{';

            if(!this->ifFood(f))
            {
                setCurPos(body[length].x, body[length].y);
                std::cout << ' ';
            }
        }

        bool ifFood(Food &f)
        {
            if(body[0].x == f.x && body[0].y == f.y)
            {
                f.generateFood();
                score++;
                length++;
                return true;
            }

            return false;
        }
};

void getInput();
void startGame();
bool checkOppositeDirection(char input, char direction);

Food f;
Snake nagini;

int main()
{
    int i = 0, j = 0;
    system("clear");

    for(i = 0; i <= groundWidth; i++)
    {
        for(j = 0; j <= groundHeight; j++)
        {
            if(i == 0 || j == 0 || i == groundWidth || j == groundHeight)
            {
                std::cout << '*';
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    nagini.direction = 'd';
    nagini.length = 1;
    nagini.score = 0;

    std::thread input(getInput);
    std::thread game(startGame);
    
    input.join();
    game.join();

    return 0;
}

void getInput()
{
    char input;

    do
    {
        input = getch();

        if(!checkOppositeDirection(input, nagini.direction))
            nagini.direction = input;

    }while(nagini.direction != 'e');
}

bool checkOppositeDirection(char input, char direction)
{
    bool state;

    if((input == 'w' && direction == 's') || (input == 's' && direction == 'w'))
        state = true;
    else if((input == 'a' && direction == 'd') || (input == 'd' && direction == 'a'))
        state = true;

    return state;
}

void startGame()
{
    // do
    // {
    //     nagini.move(f);
    // }while(nagini.direction != 'e');

    do
    {
        std::cout << nagini.direction;
    }while(nagini.direction != 'e');
}