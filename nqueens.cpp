#include <iostream>

#define BOARDLENGTH 4

void printBoard(char board[BOARDLENGTH][BOARDLENGTH])
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

int main()
{

    char board[BOARDLENGTH][BOARDLENGTH];

    int i = 0, j = 0;

    for(i = 0; i < BOARDLENGTH; i++)
    {
        for(j = 0; j < BOARDLENGTH; j++)
        {
            board[i][j] = ' ';
        }
    }

    printBoard(board);
    
    return 0;
}