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

        body.Insert(0, new coordinates(body[0].x, body[0].y));

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

        Game.print(body[1].y, body[1].x, "#");
        Game.print(body[0].y, body[0].x, "@");

    }

    public void foodProcess(Food potato)
    {
        if(potato.ifFood(this))
        {
            Game.print(potato.y, potato.x, "♣");
        }
        else
        {
            Game.map[body[length].y, body[length].x] = ' ';
            Game.print(body[length].y, body[length].x, " ");
            body.RemoveAt(length);
        }

        Game.map[body[0].y, body[0].x] = 's';
    }

    bool checkCollision()
    {
        if(body[0].x < 1 || body[0].y < 1 || body[0].x >= Game.screenWidth - 1 || body[0].y >= Game.screenHeight - 1)
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