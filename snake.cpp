#include <iostream>
#include <conio.h>
#include <thread>
#include <Windows.h>

using position = struct coordinate;

const int GROUNDHEIGHT = 70;
const int GROUNDWIDTH = 10;
char ground[GROUNDHEIGHT][GROUNDWIDTH];

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
            x = rand() % GROUNDHEIGHT;
            y = rand() % GROUNDWIDTH;

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
        position body[GROUNDHEIGHT * GROUNDWIDTH];

        void move()
        {

            //setCurPos(body[0].x, body[0].y);
            std::cout << ' ';

            switch(direction)
            {
                case 'w': body[0].x--; break;
                case 'a': body[0].y--; break;
                case 's': body[0].x++; break;
                case 'd': body[0].y++; break;
            }

            
            std::cout << '@' << direction;
            std::cout << body[0].x << " " << body[0].y;

        }

        bool ifFood(Food &f)
        {
            if(body[0].x == f.x && body[0].y == f.y)
            {
                score++;
                length++;
                f.generateFood();
                return true;
            }

            return false;
        }

        bool checkInputInverse(char input)
        {
            if((input == 'w' && direction == 's') || (input == 's' && direction == 'w'))
            {
                return true;
            }
            else if((input == 'a' && direction == 'd') || (input == 'd' && direction == 'a'))
            {
                return true;
            }

            return false;
        }
};

void getInput();
void startGame();

void setCurPos(int, int);

Food f;
Snake nagini;

int main()
{
    int i = 0, j = 0;
    system("clear");

    for(i = 0; i <= GROUNDWIDTH; i++)
    {
        for(j = 0; j <= GROUNDHEIGHT; j++)
        {
            if(i == 0 || j == 0 || i == GROUNDWIDTH || j == GROUNDHEIGHT)
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
    nagini.body[0].x = GROUNDWIDTH / 2;
    nagini.body[0].y = GROUNDHEIGHT / 2;

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

        if(!nagini.checkInputInverse(input))
        {
            nagini.direction = input;
        }

    }while(nagini.direction != 'e');
}

void startGame()
{
    do
    {
        system("sleep 0.1");
        nagini.move();
        //nagini.ifFood(f);

    }while(nagini.direction != 'e');
}

void setCurPos(int x, int y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}