class Food
{
    public int x, y;

    public void genFood()
    {
        x = Random.Shared.Next(3, Game.screenWidth - 3);
        y = Random.Shared.Next(2, Game.screenHeight - 2);

        if(Game.map[y, x] == 's')
        {
            genFood();
        }
    }

    public bool ifFood(Snake s)
    {
        if(s.body[0].x == x && s.body[0].y == y)
        {
            s.length++;
            genFood();
            return true;
        }

        return false;
    }
}