#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
/*
PLAYER 1 IS RED AND PLAYER 2 IS BLUE,
IN THE GAME BOARD MATRIX THE CELLS WITH THE BLUE L WILL BE MARKED BY 1
AND THE CELLS WITH THE RED CELLS WILL BE MARKED BY -1
THE NEUTRAL PIECES WILL BE MARKED BY 2
THE EMPTY TILES WILL BE MARKED BY 0
*/
struct Point{
    int x;
    int y;
};
//GLOBAL VARIABLES
Point selectedMove[4];
int GameBoard[4][4]={2, 0, -1, -1,
                     1, 0, 0, -1,
                     1, 0, 0, -1,
                     1, 1, 0, 2};
int currentPlayer=-1;


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
    if((A.x==B.x&&abs(A.y-B.y)==1)||(A.y==B.y&&abs(A.x-B.x)==1))
        return true;
    return false;
}
bool checkMoveValidity(Point Move[4])
{
    //CHECK IF THE POINTS DON'T GO OUTSIDE THE GAMEBOARD
    for(int i=0;i<4;i++)
        if(!checkPointBounds(Move[i]))
            return false;
    //CHECK IF 3 ARE ON THE SAME LINE OR COLUMN
    int MoveCounter[4]={0};
    for(int i=0;i<4;i++)
    {
        for(int j=i+1;j<4;j++)
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
    //IF THE CELLS ARE IN THE L POSITION THE VALUES IN THE SORTED MOVECOUNTER ARRAY WILL BE 1 2 2 3
    sortMoveByValue(MoveCounter);
    int shapeCheckArray[4]={1,2,2,3};
    for(int i=0;i<4;i++)
        if(MoveCounter[i]!=shapeCheckArray[i])
            return false;
    //CHECK IF THEY ARE ADJACENT
    int adjacencyCounter=0;//
    for(int i=0;i<4;i++)
    {
        for(int j=i;j<4;j++)
        {
            if(isAdjacentTo(Move[i],Move[j]))
                adjacencyCounter++;
        }
    }
    if(adjacencyCounter!=3)
        return false;
    //CHECK IF THE CELLS SELECTED ARE AVAILABLE
    for(int i=0;i<4;i++)
        if(GameBoard[Move[i].x][Move[i].y]==-currentPlayer)
            return false;

    return true;
}

int main()
{
    //TESTING VALUES
    selectedMove[0].x=2;
    selectedMove[0].y=1;
    selectedMove[1].x=2;
    selectedMove[1].y=0;
    selectedMove[2].x=2;
    selectedMove[2].y=2;
    selectedMove[3].x=2;
    selectedMove[3].y=3;
    if(checkMoveValidity(selectedMove))
        cout<<"VALID MOVE";
    else cout<<"INVALID MOVE";
    //TODO: CHECK MORE CORNER CASES AND MAKE SURE THE FUNCTION DOESN'T HAVE ANY BUGS
    return 0;
}
