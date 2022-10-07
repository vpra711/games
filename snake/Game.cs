class Game
{
    public static int screenHeight = 20, screenWidth = 100;
    public static char[,] map =  new char[screenHeight, screenWidth];
    Snake nagini;
    Food potato;

    Thread inputThread;
    Thread functionThread;

    public Game()
    {
        this.nagini = new Snake('d', 1);
        this.potato = new Food();
        inputThread = new Thread(new ThreadStart(initInput));
        functionThread = new Thread(new ThreadStart(initGame));
    }

    public void init()
    {
        String inst = "w - up \na - left \ns - down \nd - right \nPress any key to start.....";
        Console.Write(inst);
        Console.ReadKey();
        Console.Clear();
        Console.CursorVisible = false;
        Console.WindowHeight = screenHeight + 20;
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

        gameOver();

    }

    void initInput()
    {
        char input;

        do
        {
            input =  Console.ReadKey().KeyChar;

            if(!checkInverseInput(input))
            {
                nagini.direction = input;
            }

        }while(input != 'e');
    }

    void initGame()
    {
        potato.genFood();
        Game.map[potato.y, potato.x] = 'f';
        Console.SetCursorPosition(potato.y, potato.x);
        Console.Write('f');

        while(nagini.direction != 'e')
        {
            Thread.Sleep(100);
            nagini.move();

            if(!potato.ifFood(nagini))
            {
                Game.map[nagini.body[nagini.length].y, nagini.body[nagini.length].x] = ' ';
                Console.SetCursorPosition(nagini.body[nagini.length].y, nagini.body[nagini.length].x);
                Console.Write(' ');
                nagini.body.RemoveAt(nagini.length);
            }

            Game.map[nagini.body[0].y, nagini.body[0].x] = 's';

            updateStatus();
        }
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

    void updateStatus()
    {
        Console.SetCursorPosition(0, Game.screenHeight + 2);
        String s = $"score       : {nagini.length} \nposition    : y - {nagini.body[0].y}, x - {nagini.body[0].x} \nFood        : {potato.y}, {potato.x} \nkey pressed : ";
        Console.Write(s);
    }

    void gameOver()
    {
        Console.Clear();
        Console.WriteLine("game over");
    }
}