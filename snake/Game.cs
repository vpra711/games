class Game
{
    public static int screenHeight = 20, screenWidth = 100;
    public static char[,] map =  new char[screenHeight, screenWidth];
    Snake nagini;
    Food potato;

    bool pause;

    Thread inputThread;
    Thread functionThread;

    public Game()
    {
        nagini = new Snake('d', 1);
        potato = new Food();
        inputThread = new Thread(new ThreadStart(initInput));
        functionThread = new Thread(new ThreadStart(initGame));
    }

    public static void print(int height, int width, String content)
    {
        Console.SetCursorPosition(width, height);
        Console.Write(content);
    }

    public void init()
    {
        String inst = "welcome to snake game..... \nw - up \na - left \ns - down \nd - right \n♣ - food \npress space to pause\\resume the game \nPress any key to start.....";
        Console.Write(inst);
        Console.ReadKey();
        Console.Clear();
        Console.CursorVisible = false;
        Console.WindowHeight = screenHeight + 10;
        Console.WindowWidth = screenWidth + 5;
        Console.Title = "Snake Game";

        int i = 0, j = 0;

        for(i = 0; i < screenHeight; i++)
        {
            for(j = 0; j < screenWidth; j++)
            {
                if(i == 0 || j == 0 || i == screenHeight - 1 || j == screenWidth - 1)
                {
                    Console.Write('*');
                }
                else
                {
                    Console.Write(' ');
                }
            }

            Console.WriteLine();
        }

        inputThread.Start();
        functionThread.Start();
        

        functionThread.Join();
        inputThread.Join();

        Console.Clear();
    }

    void initInput()
    {
        char input;

        do
        {
            input =  Console.ReadKey().KeyChar;

            if(!checkInverseInput(input))
            {
                if(input == ' ')
                {
                    pause = !pause;
                }
                else
                {
                    nagini.direction = input;
                }
            }

        }while(input != 'e');
    }

    void initGame()
    {
        String content = "";
        potato.genFood();
        map[potato.y, potato.x] = '♣';
        print(potato.y, potato.x, "♣");

        while(nagini.direction != 'e')
        {
            if(!pause)
            {
                Thread.Sleep(100);
                nagini.move();
                nagini.foodProcess(potato);
                content = $"score       : {nagini.length} \nposition    : y - {nagini.body[0].y}, x - {nagini.body[0].x} \nFood(♣)     : {potato.y}, {potato.x} \nkey pressed : ";
                print(screenHeight + 2, 0, content);
            }
        }

        Console.Clear();
        Console.WriteLine(content);
        Console.WriteLine("game over / press e to exit");
    }

    bool checkInverseInput(char input)
    {
        if((input == 'w' && nagini.direction == 's') || (input == 's' && nagini.direction == 'w'))
        {
            return true;
        }
        else if((input == 'a' && nagini.direction == 'd') || (input == 'd' && nagini.direction == 'a'))
        {
            return true;
        }

        return false;
    }
}