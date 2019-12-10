#pragma once
#include <graphics.h>
#include <winbgim.h>
#include "main.cpp"
#include <iostream>

using namespace std;
struct Point{
    int x;
    int y;
};

int windowWidth=getmaxwidth(),windowHeight=getmaxheight();
int realWidth=windowWidth-300,realHeight=windowHeight-300;
int tileSize=realHeight/4,offset=150;
int page=0;
void startGameWindow(){
    initwindow(windowHeight ,windowHeight);
    }

void drawGameBoard(int GameBoard[4][4])
{


    setvisualpage(1-page);
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
    page=1-page;
    setactivepage(page);


}
bool checkIfMoveInList(Point Move[4],int j,int i)
{
    for(int k=0;k<16;k++)
        if(Move[k].x==j&&Move[k].y==i)
            return false;

    return true;
}
void selectNeutralMove(Point Move)
{

}
void selectMove(Point Move[4])
{
    for(int i=0;i<16;i++)
    { Move[i].x=-1;
      Move[i].y=-1;
    }

    int x=-1,y=-1,counter=0;
    bool clicked=false;
//CHECK IF LEFT MOUSE BUTTON IS CLICKED
    while(!ismouseclick(WM_LBUTTONDOWN))
    {clicked=true;

    }

    clearmouseclick(WM_LBUTTONUP);
    while(clicked)
    {

        if(ismouseclick(WM_LBUTTONUP))
        {clicked=false;cout<<"OUT";}

        x=mousex();
        y=mousey();

        for(int i=0;i<4;i++)
        {

            for(int j=0;j<4;j++)
            {

                if((y>=tileSize*j+offset&&y<=tileSize*(j+1)+offset)&&(x>=tileSize*i+offset&&x<=tileSize*(i+1)+offset)&&checkIfMoveInList(Move,j,i))
                {
                    cout<<"Drew in block at "<<j<<' '<<i<<'\n';
                    Move[counter].x=j;
                    Move[counter].y=i;

                    setfillstyle(1,GREEN);
                    bar(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
                    counter++;



                }
            }

        }

    }
    //THIS PIECE OF CODE MAKES IT SO IF THE FIRST 4 TILES YOU CHOOSE ARE A VALID MOVE THE GAME WON'T ACCEPT IT
    if(counter>4)
        for(int i=0;i<16;i++)
    { Move[i].x=-1;
      Move[i].y=-1;
    }
    //MAKES SURE THAT ON THE NEXT CALL OF THIS FUNCTION THE GAME WILL WAIT FOR THE PLAYER TO PRESS LEFT CLICK
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);

}
