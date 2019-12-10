#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "display.h"
#include <cstdio>
using namespace std;
/*
PLAYER 1 IS RED AND PLAYER 2 IS BLUE,
IN THE GAME BOARD MATRIX THE CELLS WITH THE BLUE L WILL BE MARKED BY 1
AND THE CELLS WITH THE RED CELLS WILL BE MARKED BY -1
THE NEUTRAL PIECES WILL BE MARKED BY 2
THE EMPTY TILES WILL BE MARKED BY 0

*/
///feat tudor hutu
//GLOBAL VARIABLES
Point selectedMove[4],neutralMoveFrom,neutralMoveTo;
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
    //CHECK IF THE PIECE IS IN THET SHAPE OF _|_ : IF THE PIECE THAT IS ON  THE SAME ROW WITH 2 OTHER PIECES IS ADJACENT TO A THIRD ONE THEN IT IS _|_ AND NOT L
    int parseVariable=0;
    while(parseVariable<4)
    {
       if(MoveCounter[parseVariable]==3)
        break;
       parseVariable++;
    }

    if(MoveCounter[parseVariable]!=3)
        return false;//THERE ARE NO PIECES WITH VALUE 3
    int pieceWith3Counter=0;
    for(int i=0;i<4;i++)
        if(i!=parseVariable)
            if(isAdjacentTo(Move[parseVariable],Move[i]))
                pieceWith3Counter++;

    if(pieceWith3Counter==3)
        return false;   // _|_ SHAPED




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
    int checkDuplicateMove=0;//ALSO CHECKING IF THE MOVE IS THE SAME AS THE ORIGINAL POSITION
    for(int i=0;i<4;i++)
        {if(GameBoard[Move[i].x][Move[i].y]==-currentPlayer||GameBoard[Move[i].x][Move[i].y]==2)
            return false;
         if(GameBoard[Move[i].x][Move[i].y]==currentPlayer)
            checkDuplicateMove++;
        }
    if(checkDuplicateMove==4)
        return false;

    return true;
}


int remainingPossibleMoves()
{
    Point moveToBeChecked[4];
    int possibleMoves=0;
for(int j=0;j<4;j++)
    {for(int i=0;i<2;i++)
    {
    moveToBeChecked[0].x=i;
    moveToBeChecked[0].y=j;

    moveToBeChecked[1].x=i+1;
    moveToBeChecked[1].y=j;

    moveToBeChecked[2].x=i+2;
    moveToBeChecked[2].y=j;

    moveToBeChecked[3].x=i;
    moveToBeChecked[3].y=j-1;
    if(checkMoveValidity(moveToBeChecked))
        possibleMoves++;

    moveToBeChecked[3].x=i;
    moveToBeChecked[3].y=j+1;
    if(checkMoveValidity(moveToBeChecked))
        possibleMoves++;

    moveToBeChecked[3].x=i+2;
    moveToBeChecked[3].y=j-1;
    if(checkMoveValidity(moveToBeChecked))
        possibleMoves++;

    moveToBeChecked[3].x=i+2;
    moveToBeChecked[3].y=j+1;
    if(checkMoveValidity(moveToBeChecked))
        possibleMoves++;

    moveToBeChecked[0].x=j;
    moveToBeChecked[0].y=i;

    moveToBeChecked[1].x=j;
    moveToBeChecked[1].y=i+1;

    moveToBeChecked[2].x=j;
    moveToBeChecked[2].y=i+2;

    moveToBeChecked[3].x=j-1;
    moveToBeChecked[3].y=i;
    if(checkMoveValidity(moveToBeChecked))
        possibleMoves++;

    moveToBeChecked[3].x=j+1;
    moveToBeChecked[3].y=i;
    if(checkMoveValidity(moveToBeChecked))
        possibleMoves++;

    moveToBeChecked[3].x=j-1;
    moveToBeChecked[3].y=i+2;
    if(checkMoveValidity(moveToBeChecked))
        possibleMoves++;

    moveToBeChecked[3].x=j+1;
    moveToBeChecked[3].y=i+2;
    if(checkMoveValidity(moveToBeChecked))
        possibleMoves++;
    }
}
    return possibleMoves;

}

void makeMove(Point Move[4])
{//DOESN'T CHECK IF THE MOVE IS VALID
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(GameBoard[i][j]==currentPlayer)
                GameBoard[i][j]=0;
    for(int i=0;i<4;i++)
    {
        GameBoard[Move[i].x][Move[i].y]=currentPlayer;
    }
}


int main()
{
    //TESTING VALUES X IS VERTICAL AND Y IS HORIZONTAL


    startGameWindow();
    //SOMETIMES HAVE TO CALL DRAWGAMEBOARD TWICE FOR THE DOUBLE BUFFER TO WORK.
    // NOT REALLY A PROBLEM SINCE IT DOESN'T TAKE THAT MUCH TIME TO RUN, BUT MAYBE MAKE A FUNCTION THAT CALLS IT TWICE SO THE CODE ISN'T AS MESSY
    while(remainingPossibleMoves())
    {


    drawGameBoard(GameBoard);
    drawGameBoard(GameBoard);
    selectMove(selectedMove);
    while(!checkMoveValidity(selectedMove))
    {   drawGameBoard(GameBoard);
        selectMove(selectedMove);
        drawGameBoard(GameBoard);

    }
    cout<<"made a valid move";
    makeMove(selectedMove);
    drawGameBoard(GameBoard);
    drawGameBoard(GameBoard);
    doNeutralMove(GameBoard);
    drawGameBoard(GameBoard);
    drawGameBoard(GameBoard);

    currentPlayer=-currentPlayer;

    }
    cout<<"No more possible moves,"<<currentPlayer<<"wins!";
    drawGameBoard(GameBoard);
    drawGameBoard(GameBoard);
    getch();


    /*
    if(checkMoveValidity(selectedMove))
        cout<<"VALID MOVE";
    else cout<<"INVALID MOVE";

    cout<<'\n';
    for(int i=0;i<4;i++)
    {   for(int j=0;j<4;j++)
            cout<<GameBoard[i][j]<<' ';

        cout<<'\n';
    }
    makeMove(selectedMove);
    cout<<'\n';
    for(int i=0;i<4;i++)
    {   for(int j=0;j<4;j++)
            cout<<GameBoard[i][j]<<' ';

        cout<<'\n';
    }

*/
    //TODO: CHECK MORE CORNER CASES AND MAKE SURE THE FUNCTION DOESN'T HAVE ANY BUGS
    return 0;
}
