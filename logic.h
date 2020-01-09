#pragma once
#include <iostream>
#include "display.h"
using namespace std;
 extern int GameBoard[4][4];

struct Point{
    int x;
    int y;
};

struct BoardHistoryNode{
    int Board[4][4];
    int Player;
    BoardHistoryNode* previous;
};

void copyBoard(int receiver[4][4],int sender[4][4])
{
    //THIS FUNCTION COPIES THE BOARD STATE FROM SENDER TO RECEIVER
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            receiver[i][j]=sender[i][j];
        }
    }
}

void addBoardToHistory(int Board[4][4],BoardHistoryNode* &head,int Player)
{
    if(head!=NULL)
    {
        bool differentFromLastBoard=false;
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
            if(Board[i][j]!=head->Board[i][j])
                differentFromLastBoard=true;
        if(differentFromLastBoard==false)
            return;
    }
    BoardHistoryNode* Node=new BoardHistoryNode;
    copyBoard(Node->Board,GameBoard);
    Node->Player=Player;
    Node->previous=head;
    head=Node;
}
void deleteBoardFromHistory(BoardHistoryNode* &head)
{
    BoardHistoryNode* toDelete;
    toDelete=head;
    head=head->previous;
    delete toDelete;
}
void loadLastBoard(int Board[4][4],int &Player,BoardHistoryNode* head)
{
    copyBoard(Board,head->Board);
    Player=head->Player;
}
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
bool checkMoveValidity(Point Move[4],int Board[4][4],int currPlayer)
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
        {if(Board[Move[i].x][Move[i].y]==-currPlayer||Board[Move[i].x][Move[i].y]==2)
            return false;
         if(Board[Move[i].x][Move[i].y]==currPlayer)
            checkDuplicateMove++;
        }
    if(checkDuplicateMove==4)
        return false;

    return true;
}


int remainingPossibleMoves(int Board[4][4],int currPlayer)
{
    Point moveToBeChecked[4];//STORES THE MOVE THAT IS BEING CHECKED, IT CHANGES WITH EVERY ITERATION OF THE WHILE LOOP
    int possibleMoves=0;
    //INSIDE THIS NESTED FOR LOOP ALL OF THE POSITIONS AN L PIECE COULD BE ARE CHECKED
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
    if(checkMoveValidity(moveToBeChecked,Board,currPlayer))
        possibleMoves++;

    moveToBeChecked[3].x=i;
    moveToBeChecked[3].y=j+1;
    if(checkMoveValidity(moveToBeChecked,Board,currPlayer))
        possibleMoves++;

    moveToBeChecked[3].x=i+2;
    moveToBeChecked[3].y=j-1;
    if(checkMoveValidity(moveToBeChecked,Board,currPlayer))
        possibleMoves++;

    moveToBeChecked[3].x=i+2;
    moveToBeChecked[3].y=j+1;
    if(checkMoveValidity(moveToBeChecked,Board,currPlayer))
        possibleMoves++;

    moveToBeChecked[0].x=j;
    moveToBeChecked[0].y=i;

    moveToBeChecked[1].x=j;
    moveToBeChecked[1].y=i+1;

    moveToBeChecked[2].x=j;
    moveToBeChecked[2].y=i+2;

    moveToBeChecked[3].x=j-1;
    moveToBeChecked[3].y=i;
    if(checkMoveValidity(moveToBeChecked,Board,currPlayer))
        possibleMoves++;

    moveToBeChecked[3].x=j+1;
    moveToBeChecked[3].y=i;
    if(checkMoveValidity(moveToBeChecked,Board,currPlayer))
        possibleMoves++;

    moveToBeChecked[3].x=j-1;
    moveToBeChecked[3].y=i+2;
    if(checkMoveValidity(moveToBeChecked,Board,currPlayer))
        possibleMoves++;

    moveToBeChecked[3].x=j+1;
    moveToBeChecked[3].y=i+2;
    if(checkMoveValidity(moveToBeChecked,Board,currPlayer))
        possibleMoves++;
    }
}
    return possibleMoves;

}
