class coordinates
{
    public int x, y;

    public coordinates(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

}

class Snake
{
    
    public char direction;
    public int length;

    public List<coordinates> body;

    public Snake(char direction, int length)
    {
        this.direction = direction;
        this.length = length;
        this.body = new List<coordinates>();
        this.body.Add(new coordinates(10, 10));
    }

    public void move()
    {

        body.Insert(0, new coordinates(body[0].y, body[0].x));

        switch(direction)
        {
            case 'w': body[0].y--; break;
            case 'a': body[0].x--; break;
            case 's': body[0].y++; break;
            case 'd': body[0].x++; break;
        }


        if(checkCollision())
        {
            direction = 'e';
        }


        Console.SetCursorPosition(body[1].y, body[1].x);
        Console.Write('#');

        Console.SetCursorPosition(body[0].y, body[0].x);
        Console.Write('@');
    }

    bool checkCollision()
    {
        if(body[0].x < 1 || body[0].y < 1 || body[0].x >= Game.screenWidth || body[0].y >= Game.screenHeight)
        {
            return true;
        }
        else if(Game.map[body[0].y, body[0].x] == 's')
        {
            return true;
        }

        return false;
    }
}