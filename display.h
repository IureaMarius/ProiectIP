#pragma once
#include <graphics.h>
#include <winbgim.h>
#include "main.cpp"
#include <iostream>
#include <cstdio>
using namespace std;

struct Button{
int leftCornerx,leftCornery,rightCornerx,rightCornery;
char label[100];
Button(int leftx,int lefty, int rightx, int righty):leftCornerx(leftx),leftCornery(lefty),rightCornerx(rightx),rightCornery(righty){}
};



extern int currentPlayer;
struct Point{
    int x;
    int y;
};
//VALUES OPEN TO CHANGE IN ORDER TO BETTER FIT THE UI IN THE WINDOW
int windowWidth=getmaxwidth(),windowHeight=getmaxheight();
int realWidth=windowHeight*1.5f;
int offset=windowHeight/10;
int realHeight=windowHeight*0.9f;

int tileSize=(windowHeight-3*offset)/4,textSize1=20,textSize2=20,textSizeStart=20;
int page=0;
int remainingPossibleMoves();

void setButtonText(Button B,char text[100])
{
    strcpy(B.label,text);
}

void displayButton(Button B)
{
    rectangle(B.leftCornerx,B.leftCornery,B.rightCornerx,B.rightCornery);

}
bool isButtonClicked(Button B)
{
    int x,y;
    getmouseclick(WM_LBUTTONDOWN,x,y);
    if(x>B.leftCornerx&&x<B.rightCornerx&&y>B.leftCornery&&B.rightCornery)
        return true;
    return false;
}

void drawStartScreenStruct()
{
    //Button titlescreen(3*offset,offset,realWidth-3*offset,2*offset),playButton(3*offset,3*offset,realWidth-3*offset,4*offset),exitButton()
}

void startGameWindow(){
    initwindow(realWidth,realHeight);
    }

void drawStartScreen()
{

    char msg[100]="BONOL!";
    setvisualpage(1-page);
    cleardevice();
    int boxCornerLeftx=3*offset*1.5f,boxCornerLefty=offset-offset/2,boxCornerRightx=7*offset*1.5f,boxCornerRighty=3*offset-offset/2;

    rectangle(boxCornerLeftx,boxCornerLefty,boxCornerRightx,boxCornerRighty);
    settextstyle(DEFAULT_FONT,HORIZ_DIR ,textSizeStart);

    while(textheight(msg)>=(boxCornerLefty+boxCornerRighty)||textwidth(msg)>=(boxCornerLeftx+boxCornerRightx))
    {
    textSizeStart-=0.1;

    settextstyle(DEFAULT_FONT,HORIZ_DIR ,textSizeStart);
    }
    outtextxy((boxCornerLeftx+boxCornerRightx)/2-textwidth(msg)/2,(boxCornerLefty+boxCornerRighty)/2-textheight(msg)/2,msg);
    boxCornerLefty+=3*offset;
    boxCornerRighty+=3*offset;
    rectangle(boxCornerLeftx,boxCornerLefty,boxCornerRightx,boxCornerRighty);
    sprintf(msg,"PLAY");
    outtextxy((boxCornerLeftx+boxCornerRightx)/2-textwidth(msg)/2,(boxCornerLefty+boxCornerRighty)/2-textheight(msg)/2,msg);
    boxCornerLefty+=3*offset;
    boxCornerRighty+=3*offset;
    rectangle(boxCornerLeftx,boxCornerLefty,boxCornerRightx,boxCornerRighty);
    sprintf(msg,"EXIT");
    outtextxy((boxCornerLeftx+boxCornerRightx)/2-textwidth(msg)/2,(boxCornerLefty+boxCornerRighty)/2-textheight(msg)/2,msg);
    page=1-page;
    setactivepage(page);


}
void selectMenuButton(int &stageSelect)
{
    int boxCornerLeftx=3*offset*1.5f,boxCornerLefty=offset-offset/2,boxCornerRightx=7*offset*1.5f,boxCornerRighty=3*offset-offset/2;
    int x,y;
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN))
    {

    }
    x=mousex();
    y=mousey();
    boxCornerLefty+=3*offset;
    boxCornerRighty+=3*offset;
    if(x>boxCornerLeftx&&x<boxCornerRightx&&y>boxCornerLefty&&y<boxCornerRighty)
        stageSelect=1;
    boxCornerLefty+=3*offset;
    boxCornerRighty+=3*offset;
    if(x>boxCornerLeftx&&x<boxCornerRightx&&y>boxCornerLefty&&y<boxCornerRighty)
        stageSelect=2;


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
    //THE NEXT PART OF THE FUNCTION DEALS WITH THE DISPLAYING OF TEXT AND IT'S SIZING IN RELATION TO THE RESOLUTION THE GAME IS PLAYED AT
    char msg[100];
    if(remainingPossibleMoves()!=0)
        if(currentPlayer==1)
            {sprintf(msg,"BLUE'S TURN");
            setcolor(BLUE);
            }
            else {
                    sprintf(msg,"RED'S TURN");
                    setcolor(RED);
                 }

    if(remainingPossibleMoves()==0)
        if(currentPlayer==1)
            {sprintf(msg,"RED WINS!");
            setcolor(RED);
            }
            else {
                    sprintf(msg,"BLUE WINS!");
                    setcolor(BLUE);
                 }
    settextstyle(DEFAULT_FONT,HORIZ_DIR ,textSize1);
    while(textwidth(msg)+offset>windowHeight*1.5f-(4*tileSize+2*offset))
    {
    textSize1-=0.1;
    settextstyle(DEFAULT_FONT,HORIZ_DIR ,textSize1);

    }

    outtextxy(4*tileSize+2*offset,windowHeight/2-offset,msg);
    int remainingMoves=remainingPossibleMoves();

    sprintf(msg,"REMAINING MOVES: %d",remainingMoves);
    settextstyle(DEFAULT_FONT,HORIZ_DIR ,textSize2);
    while(textwidth(msg)+offset>windowHeight*1.5f-(4*tileSize+2*offset))
    {
    textSize2-=0.1;

    settextstyle(DEFAULT_FONT,HORIZ_DIR ,textSize2);
    }

    outtextxy(4*tileSize+2*offset,windowHeight/2,msg);
    setcolor(WHITE);


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
void doNeutralMove(int GameBoard[4][4])
{
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);
    int x,y,toDeletex=-1,toDeletey=-1;
    bool madeTheMove=false;
    while(!madeTheMove)
    {


    while(toDeletex==-1)
    {

    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN))
    {

    }
    x=mousex();
    y=mousey();
    //ERASE THE TILE YOU WANT TO MOVE
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if((y>tileSize*j+offset&&y<tileSize*(j+1)+offset)&&(x>tileSize*i+offset&&x<tileSize*(i+1)+offset))
                if(GameBoard[j][i]==2&&toDeletex==-1)
                    {
                        toDeletex=j;
                        toDeletey=i;
                        setfillstyle(1,CYAN);
                    bar(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
                    }

    }
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);
    while(!ismouseclick(WM_LBUTTONDOWN))
    {

    }
    x=mousex();
    y=mousey();

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if((y>tileSize*j+offset&&y<tileSize*(j+1)+offset)&&(x>tileSize*i+offset&&x<tileSize*(i+1)+offset))
                if(GameBoard[j][i]==0||(j==toDeletex&&i==toDeletey))
                   {
                    GameBoard[toDeletex][toDeletey]=0;
                    GameBoard[j][i]=2;
                    madeTheMove=true;
                   }
    }



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





