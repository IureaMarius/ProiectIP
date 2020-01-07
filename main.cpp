#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "display.h"
#include <cstdio>
#include "vscpu.h"
#include "logic.h"
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
Point selectedMove[16];
int GameBoardInRow[16]={2, 0, -1, -1,1, 0, 0, -1,1, 0, 0, -1,1, 1, 0, 2};
int GameBoard[4][4]={2, 0, -1, -1,
                     1, 0, 0, -1,
                     1, 0, 0, -1,
                     1, 1, 0, 2};
int currentPlayer=-1,stage=0;
bool firstPlayerCpu=false,secondPlayerCpu=true,madeCPUmove=false;




void makeMove(Point Move[4],int Board[4][4])
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



    startGameWindow();
    drawGameBoard(GameBoard);
    initMainMenuButton();
    while(stage!=-1)
    {

        drawStartScreen();
        drawStartScreen();
        currentPlayer=-1;

        for(int i=0;i<4;i++)
        {

            for(int j=0;j<4;j++)
                {
                    GameBoard[i][j]=GameBoardInRow[4*i+j];
                    selectedMove[i*4+j].x=0;
                    selectedMove[i*4+j].y=0;
                }


        }
        while(stage==0)//WAITS FOR PLAYER TO CHOOSE A BUTTON ON THE START MENU
           {
                selectMenuButton(stage);
                delay(1);//POLLING RATE OF 1000/SECOND
           }


    //SOMETIMES HAVE TO CALL DRAWGAMEBOARD TWICE FOR THE DOUBLE BUFFER TO WORK.
    // NOT REALLY A PROBLEM SINCE IT DOESN'T TAKE THAT MUCH TIME TO RUN, BUT MAYBE MAKE A FUNCTION THAT CALLS IT TWICE SO THE CODE ISN'T AS MESSY
        if(stage==1)
            {
            while(remainingPossibleMoves(GameBoard,currentPlayer))//
                {


                    drawGameBoard(GameBoard);
                    drawGameBoard(GameBoard);
                    madeCPUmove=false;
                        while(!checkMoveValidity(selectedMove,GameBoard,currentPlayer)&&stage!=0&&madeCPUmove==false)
                            {

                                drawGameBoard(GameBoard);
                                if(currentPlayer==-1)//CHECKS IF THE MOVE SHOULD BE MADE BY THE PLAYER OR BY THE CPU
                                {
                                    if(firstPlayerCpu==false)
                                        selectMove(selectedMove);
                                    else {
                                            delay(1000);
                                            doSmartMove(selectedMove);
                                            madeCPUmove=true;
                                         }
                                }else
                                {
                                    if(secondPlayerCpu==false)
                                        selectMove(selectedMove);
                                    else {
                                            delay(1000);
                                            doSmartMove(selectedMove);
                                            madeCPUmove=true;
                                         }
                                }
                                drawGameBoard(GameBoard);

                            }
                    if(stage==0)
                        {
                            break;
                        }
                    makeMove(selectedMove,GameBoard);

                    drawGameBoard(GameBoard);
                    drawGameBoard(GameBoard);

                    if(currentPlayer==-1)//CHECKS IF THE MOVE SHOULD BE MADE BY THE PLAYER OR BY THE CPU
                                {
                                    if(firstPlayerCpu==false)
                                        doNeutralMove(GameBoard);
                                    else
                                    {
                                        delay(1000);
                                        doSmartNeutralMove(GameBoard);
                                    }
                                }else
                                {
                                    if(secondPlayerCpu==false)
                                        doNeutralMove(GameBoard);
                                    else
                                    {
                                        delay(1000);
                                        doSmartNeutralMove(GameBoard);
                                    }
                                }




                    if(stage==0)
                        {
                            break;
                        }
                    drawGameBoard(GameBoard);
                    drawGameBoard(GameBoard);

                    currentPlayer=-currentPlayer;

        }

                drawGameBoard(GameBoard);
                drawGameBoard(GameBoard);
                if(stage!=0)
                    {
                    clearmouseclick(WM_LBUTTONDOWN);
                        int x,y;
                        while(1)
                        {
                            delay(1);
                            getmouseclick(WM_LBUTTONDOWN,x,y);
                            if(isButtonClicked(mainMenuButton,x,y))
                            {
                                stage=0;
                                break;
                            }
                        }
                    }

            }else if(stage==2)
            {
                closegraph();
                stage=-1;
            }
    }
    //getch();
    return 0;
}
