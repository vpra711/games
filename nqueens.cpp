#include <iostream>
#define BOARDLENGTH 5

bool placeQueens(int);
bool checkCollision(int x, int y);
void printBoard();

char board[BOARDLENGTH][BOARDLENGTH];

int main()
{
    int i = 0, j = 0;

    for(i = 0; i < BOARDLENGTH; i++)
    {
        for(j = 0; j < BOARDLENGTH; j++)
        {
            board[i][j] = ' ';
        }
    }

    placeQueens(0);
    printBoard();
    
    return 0;
}

bool placeQueens(int x)
{
    int i;

    if(x == BOARDLENGTH)
    {
        return true;
    }

    for(i = 0; i < BOARDLENGTH; i++)
    {
        if(!checkCollision(x, i))
        {
            board[x][i] = 'Q';

            if(placeQueens(x+1))
            {
                return true;
            }

            board[x][i] = ' ';
        }
    }

    return false;
}

bool checkCollision(int x, int y)
{
    int i = x, j = y;
    while( i > -1 && j > -1)
    {
        if(board[i][j] == 'Q')
        {
            return true;
        }

        i--, j--;
    }

    i = x, j = y;
    while(i > -1)
    {
        if(board[i][j] == 'Q')
        {
            return true;
        }

        i--;
    }

    i = x;
    while(i > -1 && j < BOARDLENGTH)
    {
        if(board[i][j] == 'Q')
        {
            return true;
        }

        i--, j++;
    }

    return false;
}

void printBoard()
{
    int i = 0, j = 0;

    for(i = 0; i < BOARDLENGTH; i++)
    {
        for(j = 0; j < BOARDLENGTH; j++)
        {
            std::cout << board[i][j] << " | ";
        }

        std::cout << std::endl;
    }
}