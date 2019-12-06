#include <iostream>
#include <math.h>
#include <stdlib.h>
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

void sortMoveByValue(int values[4])
{
    int aux;
for(int i=0;i<4;i++)
    for(int j=i;j<4;j++)
    {
        if(values[i]>values[j])
         {
         aux=values[i];
         values[i]=values[j];
         values[j]=aux;
         }

    }

}
bool isAdjacentTo(Point A,Point B)
{
    if(abs(A.x-B.x)==1||abs(A.y-B.y)==1)
        return true;
    return false;
}
bool checkMoveValidity(Point Move[4])
{
    //CHECK IF 3 ARE ON THE SAME LINE OR COLUMN
    int MoveCounter[4];
    for(int i=0;i<4;i++)
    {
        for(int j=i;j<4;j++)
          {

            if(Move[i].x==Move[j].x)
                {
                    MoveCounter[i]++;
                    MoveCounter[j]++;

                }
            if(Move[i].y==Move[j].y)
            {
                MoveCounter[i]++;
                MoveCounter[j]++;
            }
          }

    }




    //CHECK IF THEY ARE NEXT TO EACHOTHER
    //CHECK IF THE LAST TILE IS IN ONE OF THE 4 VALID PLACES
}

int main()
{

    return 0;
}
