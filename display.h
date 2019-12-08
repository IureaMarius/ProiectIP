#pragma once
#include <graphics.h>
#include <winbgim.h>
#include "main.cpp"
#include <iostream>
#include <cstdio>
using namespace std;
struct Point{
    int x;
    int y;
};

int windowWidth=getmaxwidth(),windowHeight=getmaxheight();
int realWidth=windowWidth-300,realHeight=windowHeight-300;
int tileSize=realHeight/4,offset=150;
void startGameWindow(){
    initwindow(windowHeight ,windowHeight);
    }
void drawGameBoard(int GameBoard[4][4])
{


    cleardevice();
    //CHECK ALL TITLES AND COLOR THEM ACCORDINGLY
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



}

void selectMove(Point Move[16])
{

    Move[0].x=-1;
    Move[0].y=-1;
    Move[1].x=-1;
    Move[1].y=-1;
    Move[2].x=-1;
    Move[2].y=-1;
    Move[3].x=-1;
    Move[3].y=-1;
    int x=0,y=0,counter=0;
    bool clicked=true;
    setfillstyle(1,GREEN);
char msg[128];


    while(clicked)
    {
        sprintf(msg, "variable=%d", x);
        outtextxy(900,900,msg);
        //cout<<x<<' '<<y<<'\n';
        getmouseclick(WM_LBUTTONDOWN,x,y);
        if(x!=-1&&y!=-1)
            clicked=true;
        getmouseclick(WM_LBUTTONUP,x,y);
        if(x==-1&&y==-1)
            clicked=false;

        x=mousex();
        y=mousey();
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
            {

                if((y>=tileSize*j+offset&&y<=tileSize*(j+1)+offset)&&(x>=tileSize*i+offset&&x<=tileSize*(i+1)+offset)&&!(j==Move[counter].x&&i==Move[counter].y))
                {
                    Move[counter].x=j;
                    Move[counter].y=i;
                    setfillstyle(1,GREEN);
                    bar(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
                    counter++;


                }
            }
       // cout<<"O";
    }


}
