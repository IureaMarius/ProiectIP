#pragma once
#include "display.h"
#include "logic.h"

using namespace std;

//THIS FILE IS MEANT FOR THE VS CPU PART OF THE GAME


extern void makeMove(Point Move[4],int Board[4][4]);




void doStupidMove(Point Move[4])
{
    //THIS FUNCTION FINDS THE FIRST VALID MOVE AND RETURNS IT
    delay(1000);
    Point moveToBeChecked[4];//STORES THE MOVE THAT IS BEING CHECKED, IT CHANGES WITH EVERY ITERATION OF THE WHILE LOOP
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
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
                return;// IF THE MOVE IS VALID THE FUNCTION ENDS AND STORES THE MOVE IN THE MOVE VARIABLE
        }

    moveToBeChecked[3].x=i;
    moveToBeChecked[3].y=j+1;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
       {
            for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
                return;
        }

    moveToBeChecked[3].x=i+2;
    moveToBeChecked[3].y=j-1;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
                return;
        }

    moveToBeChecked[3].x=i+2;
    moveToBeChecked[3].y=j+1;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
                return;
        }

    moveToBeChecked[0].x=j;
    moveToBeChecked[0].y=i;

    moveToBeChecked[1].x=j;
    moveToBeChecked[1].y=i+1;

    moveToBeChecked[2].x=j;
    moveToBeChecked[2].y=i+2;

    moveToBeChecked[3].x=j-1;
    moveToBeChecked[3].y=i;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
                return;
        }

    moveToBeChecked[3].x=j+1;
    moveToBeChecked[3].y=i;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
                return;
        }

    moveToBeChecked[3].x=j-1;
    moveToBeChecked[3].y=i+2;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
                return;
        }

    moveToBeChecked[3].x=j+1;
    moveToBeChecked[3].y=i+2;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
                return;
        }
    }
}


}


void doStupidNeutralMove(int Board[4][4])
{
    //THIS FUNCTION FINDS THE FIRST NEUTRAL MOVE AND PERFORMS IT ON THE BOARD
    delay(1000);
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
    {

        if(Board[i][j]==2)
        {
            Board[i][j]==0;
        }

    }

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
    {

        if(Board[i][j]==0)
            Board[i][j]==2;
    }

}


void doSmartNeutralMove(int Board[4][4])
{
    //THIS FUNCTION CHECKS ALL POSSIBLE NEUTRAL MOVES AND DOES ONLY THE MOVE THAT LETS THE OTHER PLAYER WITH THE LEAST AMOUNT OF POSSIBLE MOVES
    int VirtualBoard[4][4],bestMove=INT_MAX,BestBoard[4][4];


    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            for(int k=0;k<4;k++)
                for(int l=0;l<4;l++)
                    {
                        if(Board[i][j]!=2)
                            continue;
                        copyBoard(VirtualBoard,Board);
                        VirtualBoard[i][j]=0;
                        if(VirtualBoard[k][l]!=0)
                            continue;

                        VirtualBoard[k][l]=2;
                        if(remainingPossibleMoves(VirtualBoard,-currentPlayer)<bestMove)
                        {
                            bestMove=remainingPossibleMoves(VirtualBoard,-currentPlayer);
                            copyBoard(BestBoard,VirtualBoard);
                        }
                    }
    copyBoard(Board,BestBoard);



}


void doSmartMove(Point Move[4])
{
    //THIS FUNCTION SIMULATES THE MOVES IT COULD MAKE AND CHOOSES THE ONE WHICH LEAVES THE ENEMY WITH THE LEAST AMOUNT OF MOVES
    int VirtualBoard[4][4],bestMove=INT_MAX;

    Point moveToBeChecked[4];//STORES THE MOVE THAT IS BEING CHECKED, IT CHANGES WITH EVERY ITERATION OF THE WHILE LOOP
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
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {   //THIS IF IS THE SAME IN THE REST OF THE FUNTION
            copyBoard(VirtualBoard,GameBoard);//SAVE CURRENT BOARD STATE IN THE VIRTUAL BOARD
            makeMove(moveToBeChecked,VirtualBoard);//DO THE SELECTED MOVE
            doSmartNeutralMove(VirtualBoard);//DO THE BEST POSSIBLE NEUTRAL MOVE
            if(remainingPossibleMoves(VirtualBoard,-currentPlayer)<bestMove)
            {//CHECKS IF THIS IS THE BEST MOVE FOUND YET
                bestMove=remainingPossibleMoves(VirtualBoard,-currentPlayer);
                for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
            }
        }

    moveToBeChecked[3].x=i;
    moveToBeChecked[3].y=j+1;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
       {
            copyBoard(VirtualBoard,GameBoard);
            makeMove(moveToBeChecked,VirtualBoard);
            doSmartNeutralMove(VirtualBoard);
            if(remainingPossibleMoves(VirtualBoard,-currentPlayer)<bestMove)
            {
                bestMove=remainingPossibleMoves(VirtualBoard,-currentPlayer);
                for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
            }
        }

    moveToBeChecked[3].x=i+2;
    moveToBeChecked[3].y=j-1;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            copyBoard(VirtualBoard,GameBoard);
            makeMove(moveToBeChecked,VirtualBoard);
            doSmartNeutralMove(VirtualBoard);
            if(remainingPossibleMoves(VirtualBoard,-currentPlayer)<bestMove)
            {
                bestMove=remainingPossibleMoves(VirtualBoard,-currentPlayer);
                for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
            }
        }

    moveToBeChecked[3].x=i+2;
    moveToBeChecked[3].y=j+1;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            copyBoard(VirtualBoard,GameBoard);
            makeMove(moveToBeChecked,VirtualBoard);
            doSmartNeutralMove(VirtualBoard);
            if(remainingPossibleMoves(VirtualBoard,-currentPlayer)<bestMove)
            {
                bestMove=remainingPossibleMoves(VirtualBoard,-currentPlayer);
                for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
            }
        }

    moveToBeChecked[0].x=j;
    moveToBeChecked[0].y=i;

    moveToBeChecked[1].x=j;
    moveToBeChecked[1].y=i+1;

    moveToBeChecked[2].x=j;
    moveToBeChecked[2].y=i+2;

    moveToBeChecked[3].x=j-1;
    moveToBeChecked[3].y=i;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            copyBoard(VirtualBoard,GameBoard);
            makeMove(moveToBeChecked,VirtualBoard);
            doSmartNeutralMove(VirtualBoard);
            if(remainingPossibleMoves(VirtualBoard,-currentPlayer)<bestMove)
            {
                bestMove=remainingPossibleMoves(VirtualBoard,-currentPlayer);
                for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
            }
        }

    moveToBeChecked[3].x=j+1;
    moveToBeChecked[3].y=i;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            copyBoard(VirtualBoard,GameBoard);
            makeMove(moveToBeChecked,VirtualBoard);
            doSmartNeutralMove(VirtualBoard);
            if(remainingPossibleMoves(VirtualBoard,-currentPlayer)<bestMove)
            {
                bestMove=remainingPossibleMoves(VirtualBoard,-currentPlayer);
                for(int k=0;k<4;k++)
                {

                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
            }
        }

    moveToBeChecked[3].x=j-1;
    moveToBeChecked[3].y=i+2;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            copyBoard(VirtualBoard,GameBoard);
            makeMove(moveToBeChecked,VirtualBoard);
            doSmartNeutralMove(VirtualBoard);
            if(remainingPossibleMoves(VirtualBoard,-currentPlayer)<bestMove)
            {
                bestMove=remainingPossibleMoves(VirtualBoard,-currentPlayer);
                for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
            }
        }

    moveToBeChecked[3].x=j+1;
    moveToBeChecked[3].y=i+2;
    if(checkMoveValidity(moveToBeChecked,GameBoard,currentPlayer))
        {
            copyBoard(VirtualBoard,GameBoard);
            makeMove(moveToBeChecked,VirtualBoard);
            doSmartNeutralMove(VirtualBoard);
            if(remainingPossibleMoves(VirtualBoard,-currentPlayer)<bestMove)
            {
                bestMove=remainingPossibleMoves(VirtualBoard,-currentPlayer);
                for(int k=0;k<4;k++)
                {
                    Move[k].x=moveToBeChecked[k].x;
                    Move[k].y=moveToBeChecked[k].y;
                }
            }
        }
    }
}



}



