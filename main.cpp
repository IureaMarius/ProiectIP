#include <iostream>
//Home test
using namespace std;
int GameBoard[4][4];
struct Point{
int x;
int y;
};

Point selectedMove[4];

bool checkPointBounds(Point A)
{
    if(A.x<4&&A.x>=0&&A.y<4&&A.y>=0)
        return true;
    return false;
}
bool checkMoveValidity(Point Move[4])
{
    //CHECK IF 3 ARE ON THE SAME LINE OR COLUMN
    Point MoveCounter[4];
    for(int i=0;i<4;i++)
    {
        for(int j=i;j<4;j++)
          {

            if(Move[i].x==Move[j].x)
                {
                    MoveCounter[i].x++;
                    MoveCounter[j].x++;

                }
            if(Move[i].y==Move[j].y)
            {
                MoveCounter[i].y++;
                MoveCounter[j].y++;
            }
          }
        if()
    }




    //CHECK IF THEY ARE NEXT TO EACHOTHER
    //CHECK IF THE LAST TILE IS IN ONE OF THE 4 VALID PLACES
}

int main()
{

    return 0;
}
