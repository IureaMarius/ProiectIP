#pragma once
#include <graphics.h>
#include <winbgim.h>


int windowWidth=getmaxwidth(),windowHeight=getmaxheight();
void startGameWindow(){
    initwindow(windowHeight ,windowHeight);
    }
void drawGameBoard(int GameBoard[4][4])
{


    cleardevice();
    int realWidth=windowWidth-300,realHeight=windowHeight-300;
    int tileSize=realHeight/4,offset=150;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {

            if(GameBoard[j][i]==0)
            {
                rectangle(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
            }
            if(GameBoard[j][i]==1)
            {   setfillstyle(1,BLUE);
                bar(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
            }

            if(GameBoard[j][i]==-1)
            {   setfillstyle(1,RED);
                bar(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
            }
            if(GameBoard[j][i]==2)
            {   setfillstyle(1,WHITE);
                bar(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
            }
        }

getch();

}
