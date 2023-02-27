#include <windows.h>
#include <list>
#include <string>


const int bufferHeight = 47;
const int bufferWidth = 158;
const int bufferSize = bufferWidth * bufferHeight;
const int scoreRow = bufferWidth * 2 + (bufferWidth - 10) / 2;
const int border = bufferWidth * 4;

LPCTSTR over, quit, cont;

void controls();
void updateScore();
void collisionAndMove();
void generateFood();
void gameover();
bool operator==(_COORD&, _COORD&);

wchar_t* buffer;
HANDLE console;
HWND hwnd;
DWORD bytesWritten;

std::list<_COORD> nagini;
_COORD food, head, tail;
int direction;
bool dead;
int score;

int main()
{
    buffer = new wchar_t[bufferSize];
    console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(console);
    hwnd = GetConsoleWindow();
    bytesWritten = 0;

    MoveWindow(hwnd, 100, 100, 1280, 800, FALSE);
    over = L"                                                                   ===== Game Over =====                                                          ";
    quit = L"                                                                         e to quit                                                                ";
    cont = L"                                                                     space to continue                                                            ";
    
    nagini = { {20,20}, {20, 19}, {20, 18}, {20, 17} };
    food = { 50, 50 };
    direction = 2;
    dead = false;
    score = 0;

    for (int i = 0; i < bufferSize; i++)
    {
        buffer[i] = i > (border - 1) && i < (border + bufferWidth) ? '=' : ' ';
    }

    for (_COORD i : nagini)
    {
        buffer[i.X * bufferWidth + i.Y] = (i == nagini.front()) ? '@' : 'O';
    }

    generateFood();

    while (1)
    {
        Sleep(100);

        head = nagini.front();
        tail = nagini.back();

        controls();
        collisionAndMove();

        nagini.push_front(head);

        updateScore();

        buffer[head.X * bufferWidth + head.Y] = dead ? 'X' : '@';

        WriteConsoleOutputCharacter(console, buffer, bufferSize, { 0, 0 }, &bytesWritten);

        if (dead)
        {
            gameover();
        }

        buffer[head.X * bufferWidth + head.Y] = 'O';    
    }

    return 0;
}

bool operator==(_COORD &first, _COORD &second)
{
    if (first.X == second.X && first.Y == second.Y) 
    {
        return true; 
    }

    return false;
}


void controls()
{
    bool upKey, downKey, leftKey, rightKey, spacebarKey;

    upKey = GetAsyncKeyState(VK_UP) & 0x01;
    downKey = GetAsyncKeyState(VK_DOWN) & 0x01;
    leftKey = GetAsyncKeyState(VK_LEFT) & 0x01;
    rightKey = GetAsyncKeyState(VK_RIGHT) & 0x01;
    spacebarKey = GetAsyncKeyState(VK_SPACE) & 0x01;

    if (spacebarKey)
    {
        while (1)
        {
            WriteConsoleOutputCharacter(console, cont, 160, { 0, 20 }, &bytesWritten);
            WriteConsoleOutputCharacter(console, quit, 160, { 0, 21 }, &bytesWritten);

            Sleep(500);

            if (GetAsyncKeyState(VK_SPACE) & 0x01)
            {
                break;
            }
            else if (GetAsyncKeyState('E') & 0x01)
            {
                gameover();
            }
        }
    }

    //left:     x,  y--     i:0
    //up:       x--,y       i:1
    //right:    x,  y++     i:2
    //down:     x++,y       i:3

    switch (direction)
    {
        case 0: head.Y--; break;
        case 1: head.X--; break;
        case 2: head.Y++; break;
        case 3: head.X++; break;
    }

    if (upKey && direction != 3)
    {
        direction = 1;
    }
    else if (downKey && direction != 1)
    {
        direction = 3;
    }
    else if (leftKey && direction != 2)
    {
        direction = 0;
    }
    else if (rightKey && direction != 0)
    {
        direction = 2;
    }

    if (head.X <= 4)
    {
        head.X = 47;
    }

    if (head.X >= 48)
    {
        head.X = 4 + 1;
    }

    if (head.Y <= -1)
    {
        head.Y = 157;
    }

    if (head.Y >= 158)
    {
        head.Y = 0;
    }

}

void collisionAndMove()
{
    for (_COORD i : nagini)
    {
        if (head == i)
        {
            dead = true;
            return;
        }
    }

    if (head == food)
    {
        score += 1;
        generateFood();
    }
    else
    {
        buffer[tail.X * bufferWidth + tail.Y] = ' ';
        nagini.pop_back();
    }
}

void generateFood()
{
    while (buffer[food.X * bufferWidth + food.Y] != ' ')
    {
        food.X = (rand() % 40) + 5;
        food.Y = rand() % 155;
    }

    buffer[food.X * bufferWidth + food.Y] = '#';
}

void updateScore()
{

    char scoreBuffer[50];

    sprintf_s(scoreBuffer, "score : %d", score);

    int i = 0;
    while (scoreBuffer[i] != '\0')
    {
        buffer[scoreRow + i] = scoreBuffer[i];
        i++;
    }

}

void gameover()
{

    WriteConsoleOutputCharacter(console, over, 160, {0, 20}, &bytesWritten);
    WriteConsoleOutputCharacter(console, quit, 160, {0, 21}, &bytesWritten);

    while (1)
    {
        Sleep(500);
        if (GetAsyncKeyState('E') & 0x01)
        {
            exit(0);
        }
    }
}