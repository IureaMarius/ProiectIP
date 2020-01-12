#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "display.h"
#include <cstdio>
#include "vscpu.h"
#include "logic.h"
#include "resource.h"
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
int GameBoardInRow[16]={2, -1, -1, 0,0, 1, -1, 0,0, 1, -1, 0,0, 1, 1, 2};
int GameBoard[4][4]={2, -1, -1, 0,
                     0, 1, -1, 0,
                     0, 1, -1, 0,
                     0, 1, 1, 2};
int currentPlayer=-1,stage=0,difficulty=0,selectedCPUButton=-1,moveCounter=0;
bool firstPlayerCpu=false,secondPlayerCpu=false,madeCPUmove=false,undoHasBeenPressed=false,undoGameEnd=false;
BoardHistoryNode* head=NULL;



void makeMove(Point Move[4],int Board[4][4])
{//DOESN'T CHECK IF THE MOVE IS VALID
    if(secondPlayerCpu==false||currentPlayer==-1)addBoardToHistory(GameBoard,head,currentPlayer);
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(Board[i][j]==currentPlayer)
                Board[i][j]=0;
    for(int i=0;i<4;i++)
    {
        Board[Move[i].x][Move[i].y]=currentPlayer;
    }
}

void initializeGame()
{
            currentPlayer=-1;
        while(head!=NULL)
            deleteBoardFromHistory(head);

        for(int i=0;i<4;i++)
        {

            for(int j=0;j<4;j++)
                {
                    GameBoard[i][j]=GameBoardInRow[4*i+j];
                    selectedMove[i*4+j].x=0;
                    selectedMove[i*4+j].y=0;
                }

        }
        difficulty=0;
                secondPlayerCpu=false;
                selectedCPUButton=-1;
}



int main()
{
    startGameWindow();
    drawGameBoard(GameBoard);
    initMainMenuButton();
    PlaySound(MAKEINTRESOURCE(IDR_SOUND),GetModuleHandle(NULL),SND_RESOURCE|SND_LOOP|SND_ASYNC);

    while(stage!=-1)
    {
        if(undoGameEnd==false)
        {
            initializeGame();
            drawStartScreen();
            drawStartScreen();

            while(stage==0)//WAITS FOR PLAYER TO CHOOSE A BUTTON ON THE START MENU
            {
                    selectMenuButton(stage);
                    delay(1);//POLLING RATE OF 1000/SECOND
            }
            if(stage==2)
            {
                closegraph();
                break;
            }

            drawSettingsScreen();
            drawSettingsScreen();
            while(selectedCPUButton==-1)
            {
                selectSettingsButton(selectedCPUButton);
                delay(1);
            }
            if(selectedCPUButton==1)
                secondPlayerCpu=false;

            if(selectedCPUButton==2)
                secondPlayerCpu=true;

            if(secondPlayerCpu)
            {
                drawDifficultyScreen();
                drawDifficultyScreen();
                while(difficulty==0)
                {
                    selectDifficultyButton(difficulty);
                    delay(1);
                }
            }
        }
        while(remainingPossibleMoves(GameBoard,currentPlayer))
        {
            if(undoGameEnd==true)
            {
                undoGameEnd=false;
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
                    break;
                if(undoHasBeenPressed&&moveCounter!=0)
                {
                    copyBoard(GameBoard,head->Board);
                    currentPlayer=head->Player;
                    deleteBoardFromHistory(head);
                    undoHasBeenPressed=false;
                    drawGameBoard(GameBoard);
                    drawGameBoard(GameBoard);
                    selectedMove[0].x=-1;//SO THAT SELECTED MOVE IS AN INVALID MOVE IN THE OLD BOARDSTATE
                    clearmouseclick(WM_LBUTTONDOWN);
                }else
                {
                    drawGameBoard(GameBoard);
                    drawGameBoard(GameBoard);
                    currentPlayer=-currentPlayer;
                }
            }
            if(stage==0)
                break;
            drawGameBoard(GameBoard);
            drawGameBoard(GameBoard);
            madeCPUmove=false;
            while(!checkMoveValidity(selectedMove,GameBoard,currentPlayer))
            {
                if(currentPlayer==-1)//CHECKS IF THE MOVE SHOULD BE MADE BY THE PLAYER OR BY THE CPU
                {
                    if(firstPlayerCpu==false)
                        selectMove(selectedMove);
                    else if(difficulty==1)
                    {
                        doStupidMove(selectedMove);
                    }else if(difficulty==2)
                    {
                        delay(1000);
                        doSmartMove(selectedMove);
                        madeCPUmove=true;
                        break;
                    }
                }else
                {
                    if(secondPlayerCpu==false)
                        selectMove(selectedMove);
                    else if(difficulty==1)
                    {
                        doStupidMove(selectedMove);
                    }else if(difficulty==2)
                    {
                        delay(1000);
                        doSmartMove(selectedMove);
                        madeCPUmove=true;
                        break;
                    }
                }

                if(stage==0)
                {
                    break;
                }

                if(undoHasBeenPressed&&moveCounter!=0)
                {
                   break;
                }


                drawGameBoard(GameBoard);
            }

            if(stage==0)
                break;

            if(undoHasBeenPressed&&moveCounter!=0)
                {
                    copyBoard(GameBoard,head->Board);
                    currentPlayer=head->Player;
                    deleteBoardFromHistory(head);
                    undoHasBeenPressed=false;
                    drawGameBoard(GameBoard);
                    drawGameBoard(GameBoard);
                    selectedMove[0].x=-1;//SO THAT SELECTED MOVE IS AN INVALID MOVE IN THE OLD BOARDSTATE
                    clearmouseclick(WM_LBUTTONDOWN);
                }else
                {
                    if(checkMoveValidity(selectedMove,GameBoard,currentPlayer))
                        makeMove(selectedMove,GameBoard);
                }

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
                    break;
                if(undoHasBeenPressed&&moveCounter!=0)
                {
                    copyBoard(GameBoard,head->Board);
                    currentPlayer=head->Player;
                    deleteBoardFromHistory(head);
                    undoHasBeenPressed=false;
                    drawGameBoard(GameBoard);
                    drawGameBoard(GameBoard);
                    selectedMove[0].x=-1;//SO THAT SELECTED MOVE IS AN INVALID MOVE IN THE OLD BOARDSTATE
                    clearmouseclick(WM_LBUTTONDOWN);
                }else
                {
                    drawGameBoard(GameBoard);
                    drawGameBoard(GameBoard);
                    currentPlayer=-currentPlayer;
                }






        }
        drawGameBoard(GameBoard);
        drawGameBoard(GameBoard);


        clearmouseclick(WM_LBUTTONDOWN);
        int x,y;
        if(stage!=0)
        {
            while(1)
            {
                delay(1);
                getmouseclick(WM_LBUTTONDOWN,x,y);
                if(isButtonClicked(mainMenuButton,x,y))
                {
                    stage=0;
                    undoGameEnd=false;
                    break;
                }


                if(isButtonClicked(undoMoveButton,x,y))
                {
                    madeCPUmove=false;
                    copyBoard(GameBoard,head->Board);
                    currentPlayer=head->Player;
                    deleteBoardFromHistory(head);
                    undoHasBeenPressed=false;
                    drawGameBoard(GameBoard);
                    drawGameBoard(GameBoard);
                    clearmouseclick(WM_LBUTTONDOWN);
                    undoGameEnd=true;
                    break;
                }
            }
        }






    }
return 0;

}
