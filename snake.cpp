#include <Windows.h>
#include <list>

int screenWidth = 240;
int screenHeight = 160;
int screenSize = screenWidth * screenHeight;

struct coordinate
{
    int x, y;
};

int main()
{
    int length;
    std::list<coordinate> snakeParts = {{10,10}, {11, 10}, {12, 10}, {13, 10}};

    wchar_t *screen = new wchar_t[screenSize];
    for(int i = 0; i < screenSize; i++)    {    screen[i] = L' ';    }

    HANDLE gameConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(gameConsole);
    DWORD dwBytesWritten = 0;

    while(1)
    {


        WriteConsoleOutputCharacter(gameConsole, screen, screenSize, {0, 0}, &dwBytesWritten);
    }



    return 0;
}