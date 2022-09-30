#include <iostream>
#include <cstdlib>

// objects
#define BOMB -11

// map layers
#define ROW 8
#define COL 8

int mainLayer[ROW][COL];
bool revealLayer[ROW][COL];
bool flagLayer[ROW][COL];

void mapGeneration();
void bombGeneration();
void bombCalculation();
int bombCount(int, int);
bool isValidIndex(int, int);

void startGame();
void revealPosition();
void expand(int, int);
void flag();

void showMainLayer();
void printGrid();
void gameOver();

std::string notReveal;
time_t timer;
int flagCounter;
int validFlagCounter;

int main()
{
    notReveal += 219;
    notReveal += notReveal;

    mapGeneration();
    timer = time(NULL);
    startGame();

    return 0;
}

void mapGeneration()
{
    bombGeneration();
    bombCalculation();

    int i = 0, j = 0;

    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            if(mainLayer[i][j] == BOMB)
            {
                flagCounter++;
                validFlagCounter++;
            }
        }
    }
}

void bombGeneration()
{
    int i = 0;
    srand(time(NULL));

    for(i = 0; i < ROW; i++)
    {
        int pos1 = std::rand() % ROW;
        int pos2 = std::rand() % COL;
        mainLayer[pos1][pos2] = BOMB;
    }
}

void bombCalculation()
{
    int i = 0, j = 0;

    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            if(mainLayer[i][j] == BOMB)
            {
                continue;
            }

            mainLayer[i][j] = bombCount(i, j);
        }
    }
}

int bombCount(int i, int j)
{
    int count = 0;

    if(isValidIndex(i - 1, j - 1) && mainLayer[i - 1][j - 1] == BOMB)
    {
        count++;
    }

    if(isValidIndex(i - 1, j) && mainLayer[i - 1][j] == BOMB)
    {
        count++;
    }

    if(isValidIndex(i - 1, j + 1) && mainLayer[i - 1][j + 1] == BOMB)
    {
        count++;
    }

    if(isValidIndex(i, j - 1) && mainLayer[i][j - 1] == BOMB)
    {
        count++;
    }

    if(isValidIndex(i + 1, j - 1) && mainLayer[i + 1][j - 1] == BOMB)
    {
        count++;
    }

    if(isValidIndex(i + 1, j) && mainLayer[i + 1][j] == BOMB)
    {
        count++;
    }

    if(isValidIndex(i + 1, j + 1) && mainLayer[i + 1][j + 1] == BOMB)
    {
        count++;
    }

    if(isValidIndex(i, j + 1) && mainLayer[i][j + 1] == BOMB)
    {
        count++;
    }

    return count;
}

bool isValidIndex(int i, int j)
{
    if((i > -1 && j > -1) && (i < ROW && j < COL))
    {
        return true;
    }

    return false;
}

void startGame()
{
    int choice = 0;

    while(1)
    {
        if(validFlagCounter == 0)
        {
            gameOver();
        }
        
        std::cout << "Flags Remaining : " << flagCounter << std::endl;
        std::cout << "1 - select position" << std::endl;
        std::cout << "2 - flag / unflag" << std::endl;
        std::cout << "3 - exit" << std::endl;
        std::cout << "4 - show map" << std::endl;
        std::cout << "Enter your choice : ";
        std::cin >> choice;

        system("clear");

        switch (choice)
        {
            case 1 : revealPosition(); break;
            case 2 : flag(); break;
            case 3 : gameOver(); break;
            case 4 : printGrid(); break;
            case 5 : showMainLayer(); break;
            default: std::cout << "Please enter one of the options shown above!" << std::endl;
        }
    }
    
}

void revealPosition()
{
    int pos1 = 0;
    int pos2 = 0;

    std::cout << "Enter the position : ";
    std::cin >> pos1 >> pos2;

    if(!isValidIndex(pos1, pos2))
    {
        std::cout << "Enter position within range" << std::endl;
        return ;
    }

    if(mainLayer[pos1][pos2] == BOMB)
    {
        gameOver();
    }
    else
    {
        expand(pos1, pos2);
    }

    printGrid();
}

void expand(int i, int j)
{
    if(flagLayer[i][j] == true || revealLayer[i][j] == true)
    {
        return ;
    }
    
    if(mainLayer[i][j] != 0 && mainLayer[i][j] != BOMB)
    {
        revealLayer[i][j] = true;
        return ;
    }

    revealLayer[i][j] = true;

    if(isValidIndex(i - 1, j - 1))
    {
        expand(i - 1, j - 1);
    }

    if(isValidIndex(i - 1, j))
    {
        expand(i - 1, j);
    }

    if(isValidIndex(i - 1, j + 1))
    {
        expand(i - 1, j + 1);
    }

    if(isValidIndex(i, j - 1))
    {
        expand(i, j - 1);
    }

    if(isValidIndex(i + 1, j - 1))
    {
        expand(i + 1, j - 1);
    }

    if(isValidIndex(i + 1, j))
    {
        expand(i + 1, j);
    }

    if(isValidIndex(i + 1, j + 1))
    {
        expand(i + 1, j + 1);
    }

    if(isValidIndex(i, j + 1))
    {
        expand(i, j +1);
    }
}

void flag()
{
    std::cout << "Which position do you want to flag/unflag?" << std::endl;

    int pos1 = 0, pos2 = 0;

    std::cin >> pos1 >> pos2;

    if(flagLayer[pos1][pos2] == false)
    {
        if(revealLayer[pos1][pos2] == true)
        {
            std::cout << "position revealed cannot flag" << std::endl;
        }
        else
        {
            if(flagCounter <= 0)
            {
                std::cout << "flag count is 0";
                return ;
            }

            flagLayer[pos1][pos2] = true;
            flagCounter--;

            if(mainLayer[pos1][pos2] == BOMB)
            {
                validFlagCounter--;
            }

            std::cout << "flag sucessful" << std::endl;
        }
    }
    else
    {
        flagLayer[pos1][pos2] = false;
        flagCounter++;

        if(mainLayer[pos1][pos2] == BOMB)
        {
            validFlagCounter++;
        }

        std::cout << "unflag successful" << std::endl;
    }

    printGrid();
}

void showMainLayer()
{
    int i = 0, j = 0;

    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            std::cout << mainLayer[i][j] << "\t";
        }

        std::cout << std::endl;
    }
}

void printGrid()
{
    int i = 0, j = 0;

    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            if(flagLayer[i][j] == true)
            {
                std::cout << "?" << "\t";
            }
            else
            {
                if(revealLayer[i][j] == true)
                {
                    std::cout << mainLayer[i][j] << "\t";
                }
                else
                {
                    std::cout << notReveal << "\t";
                }
            }
        }

        std::cout << std::endl;
        std::cout << std::endl;
    }
}

void gameOver()
{
    system("clear");
    int i = 0, j = 0;

    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            if(flagLayer[i][j] == true)
            {
                std::cout << "?" << "\t";
            }
            else
            {
                if(revealLayer[i][j] == true || mainLayer[i][j] == BOMB)
                {
                    std::cout << mainLayer[i][j] << "\t";
                }
                else
                {
                    std::cout << notReveal << "\t";
                }
            }
        }

        std::cout << std::endl;
        std::cout << std::endl;
        
    }

    timer = time(NULL) - timer;
    int minutes = timer / 60;
    int seconds = timer % 60;

    std::cout << "Time Taken  " << minutes << "m : " << seconds << "s" << std::endl;


    std::cout << "Game Over" << std::endl;
    std::exit(0);
}