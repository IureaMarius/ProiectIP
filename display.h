#pragma once
#include <graphics.h>
#include <winbgim.h>
#include "main.cpp"
#include <iostream>
#include <cstdio>
#include "logic.h"

using namespace std;

struct Button{
int leftCornerx,leftCornery,rightCornerx,rightCornery;
char label[100];
Button(int leftx,int lefty, int rightx, int righty):leftCornerx(leftx),leftCornery(lefty),rightCornerx(rightx),rightCornery(righty){}
};

extern int currentPlayer;


//VALUES OPEN TO CHANGE IN ORDER TO BETTER FIT THE UI IN THE WINDOW
int windowWidth=getmaxwidth(),windowHeight=getmaxheight(); // THE MAXIMUM SIZE OF THE SCREEN



int realWidth=windowWidth;// REAL WIDTH AND REAL HEIGHT ARE THE SIZE OF THE ACTUAL WINDOW.
int offset=windowHeight/10;// A STANDARDIZED OFFSET USED TO ALGIGN UI BECAUSE IT WILL SCALE WELL WITH DIFFERENT RESOLUTIONS
int realHeight=windowHeight*0.9f;
Button mainMenuButton(0,0,0,0);Button undoMoveButton(0,0,0,0);
extern int stage;
extern bool undoHasBeenPressed;
extern BoardHistoryNode* head;
int numberOfStartButtons=2;//NUMBERS IN THE START SCREEN
//TILESIZE IS ONLY USED WHEN INTERACTING WITH THE TILES
int tileSize=(realHeight-2*offset)/4,textSize1=20,textSize2=20,textSizeStart=20;//TEXT SIZE 1 AND 2 ARE FOR UI ELMENTS IN THE GAME AND TEXTSIZESTART IS FOR THE FONT IN THE START MENU
int textSizeMainMenu=20,textSizeUndo=20;
int page=0;//VARIABLE USED FOR DOUBLE BUFFERING THE FRAMES
Button titleButton(0,0,0,0);Button playButton(0,0,0,0);Button exitButton(0,0,0,0);//START MENU BUTTONS
int remainingPossibleMoves(int Board[4][4],int currPlayer);//DECLARED IN LOGIC.CPP

void initMainMenuButton()
{
    textSizeMainMenu=20;
    textSizeUndo=20;
    settextstyle(DEFAULT_FONT,HORIZ_DIR,textSizeMainMenu);
    while(textwidth(mainMenuButton.label)>=mainMenuButton.rightCornerx-mainMenuButton.leftCornerx||
          textheight(mainMenuButton.label)>=mainMenuButton.rightCornery-mainMenuButton.leftCornery)
    {
        textSizeMainMenu-=1;
        settextstyle(DEFAULT_FONT,HORIZ_DIR,textSizeMainMenu);
    }
    settextstyle(DEFAULT_FONT,HORIZ_DIR,textSizeUndo);
    while(textwidth(undoMoveButton.label)>=undoMoveButton.rightCornerx-undoMoveButton.leftCornerx||
          textheight(undoMoveButton.label)>=undoMoveButton.rightCornery-undoMoveButton.leftCornery)
    {
        textSizeUndo-=1;
        settextstyle(DEFAULT_FONT,HORIZ_DIR,textSizeUndo);
    }

}

void setButtonText(Button& B,char text[100])
{
    strcpy(B.label,text);
}

void displayButton(Button B, bool border=true,int borderColour=WHITE,int textColour=WHITE)
{
    textSizeStart=20;
    int currentColour=getcolor();
    if(border==true)
    {setcolor(borderColour);
    rectangle(B.leftCornerx,B.leftCornery,B.rightCornerx,B.rightCornery);
    }
    settextstyle(DEFAULT_FONT,HORIZ_DIR,textSizeStart);
    if(B.leftCornerx!=mainMenuButton.leftCornerx||B.leftCornerx!=undoMoveButton.leftCornerx)
    {
    while(textwidth(B.label)>=B.rightCornerx-B.leftCornerx||textheight(B.label)>=B.rightCornery-B.leftCornery)
        {   textSizeStart-=0.1;
            settextstyle(DEFAULT_FONT,HORIZ_DIR,textSizeStart);
        }
    }else
    {
        if(B.leftCornery==mainMenuButton.leftCornery)
        {
            textSizeStart=textSizeMainMenu;
            settextstyle(DEFAULT_FONT,HORIZ_DIR,textSizeStart);
        }
        if(B.leftCornery==undoMoveButton.leftCornery)
        {
            textSizeStart=textSizeUndo;
            settextstyle(DEFAULT_FONT,HORIZ_DIR,textSizeStart);
        }
    }

    setcolor(textColour);
    outtextxy((B.leftCornerx+B.rightCornerx)/2-textwidth(B.label)/2,(B.leftCornery+B.rightCornery)/2-textheight(B.label)/2,B.label);
    setcolor(currentColour);
}
bool isButtonClicked(Button B,int x,int y)
{
    if(x>B.leftCornerx&&x<B.rightCornerx&&y>B.leftCornery&&y<B.rightCornery)
        return true;
    return false;
}

void drawStartScreen()
{
    //CHANGE THESE 5 VARIABLES TO CHANGE THE WAY THE BUTTONS SHOW UP ON SCREEN
    int buttonGap=(realHeight-3*offset)/numberOfStartButtons;
    int titleLeftx=3*offset,titleLefty=offset,titleRightx=realWidth-3*offset,titleRighty=2*offset;
    char titleText[100]="BONOL!",playText[100]="PLAY",exitText[100]="EXIT";//CHANGE THE TEXT TO CHANGE THE TEXT IN THE START MENU BUTTONS

    titleButton.leftCornerx=titleLeftx;
    titleButton.leftCornery=titleLefty;
    titleButton.rightCornerx=titleRightx;
    titleButton.rightCornery=titleRighty;
    setButtonText(titleButton,titleText);

    playButton.leftCornerx=titleLeftx;
    playButton.leftCornery=titleLefty+buttonGap;
    playButton.rightCornerx=titleRightx;
    playButton.rightCornery=titleRighty+buttonGap;
    setButtonText(playButton,playText);

    exitButton.leftCornerx=titleLeftx;
    exitButton.leftCornery=titleLefty+2*buttonGap;
    exitButton.rightCornerx=titleRightx;
    exitButton.rightCornery=titleRighty+2*buttonGap;
    setButtonText(exitButton,exitText);

    setvisualpage(1-page);// DOUBLE BUFFERING
    cleardevice();

    displayButton(titleButton);
    displayButton(playButton);
    displayButton(exitButton);

    page=1-page;//DOUBLE BUFFERING
    setactivepage(page);

}

void startGameWindow()
{
    initwindow(realWidth,realHeight);
}

void clearClickQueue()
{
    int x,y;
    while(x!=-1)
    getmouseclick(WM_LBUTTONDOWN,x,y);
}

void selectMenuButton(int &stageSelect)
{
    int x,y;

    //CHECKS WHICH BUTTON YOU PRESSED IN THE START MENU AND CHANGES THE STAGE VARIABLE ACCORDINGLY
//    clearmouseclick(WM_LBUTTONDOWN);
    clearClickQueue();

    while(!ismouseclick(WM_LBUTTONDOWN))
        delay(1);//THIS DELAY RESULTS IN A POLLING RATE OF 1000/SECOND, DON'T DELETE THIS LINE BECAUSE THE PROGRAM WILL USE THE PROCESSOR TOO MUCH

    getmouseclick(WM_LBUTTONDOWN,x,y);
    if(isButtonClicked(playButton,x,y))
        stageSelect=1;

    if(isButtonClicked(exitButton,x,y))
        stageSelect=2;

//    clearmouseclick(WM_LBUTTONDOWN);
}
void drawGameBoard(int GameBoard[4][4])
{

    int winner=0;//STORES THE WINNER OF THE GAME WHEN REMAININGMOVES GOES TO 0
    int leftTurnx=9*offset,leftTurny=realHeight/2-offset,rightTurnx=realWidth,rightTurny=realHeight/2;//THE POSITION OF TEXT
    Button turnButton(leftTurnx,leftTurny,rightTurnx,rightTurny);
    leftTurny+=2*offset;//PLACES THE REMAINING MOVES TEXT BELOW THE TURN TEXT
    rightTurny+=2*offset;
    Button remainingButton(leftTurnx,leftTurny,rightTurnx,rightTurny);
    leftTurny+=2*offset;//PLACES THE REMAINING MOVES TEXT BELOW THE REMAINING TURNS TEXT
    rightTurny+=2*offset;
    mainMenuButton.leftCornerx=leftTurnx+offset;//textwidth("MAIN MENU")/2;
    mainMenuButton.leftCornery=leftTurny;
    mainMenuButton.rightCornerx=rightTurnx-offset;//textwidth("MAIN MENU")/2;
    mainMenuButton.rightCornery=rightTurny;

    leftTurny-=6*offset;
    rightTurny-=6*offset;

    undoMoveButton.leftCornerx=leftTurnx+offset;
    undoMoveButton.leftCornery=leftTurny;
    undoMoveButton.rightCornerx=rightTurnx-offset;
    undoMoveButton.rightCornery=rightTurny;

    setvisualpage(1-page);//DOUBLE BUFFERING
    cleardevice();
    //CHECK ALL TITLES AND COLOR THEM ACCORDINGLY:
    //0 - EMPTY
    //1 - BLUE
    //-1 - RED
    //2 - NETURAL
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
                rectangle(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
            }

            if(GameBoard[j][i]==-1)
            {   setfillstyle(1,RED);
                bar(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
                rectangle(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
            }
            if(GameBoard[j][i]==2)
            {   setfillstyle(1,WHITE);
                bar(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
                rectangle(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
            }
        }
    //THE NEXT PART OF THE FUNCTION DEALS WITH THE DISPLAYING OF TEXT AND IT'S SIZING IN RELATION TO THE RESOLUTION THE GAME IS PLAYED AT
    //THIS FIRST PART CHECKS WHO'S TURN IT IS OR IF SOMEONE WON
    if(remainingPossibleMoves(GameBoard,currentPlayer)!=0)
        if(currentPlayer==1)
            {
                setButtonText(turnButton,"BLUE'S TURN");
            }
            else {
                    setButtonText(turnButton,"RED'S TURN");
                 }

    if(remainingPossibleMoves(GameBoard,currentPlayer)==0)
        if(currentPlayer==1)
            {
                setButtonText(turnButton,"RED WINS!");
                winner=-currentPlayer;
            }
            else {
                    winner=-currentPlayer;
                    setButtonText(turnButton,"BLUE WINS!");
                 }

    char remainingText[100];//HOLDS THE TEXT THAT SHOWS HOW MANY MOVES POSSIBLE REMAIN
    int colour;//THE COLOUR OF THE TEXT TO BE DISPLAYED

    if(currentPlayer==1)
        {
            colour=BLUE;
        }else
        {
            colour=RED;

        }
    //WINNER OVERRIDES THE COLOUR OF THE TEXT SINCE WHEN IT'S THE PLAYER'S TURN AND HE LOSES, THE TEXT SAYING THAT THE OTHER PLAYER
    //HAS WON SHOULD BE THE COLOUR OF THE OTHER PLAYER
    if(winner==1)
        colour=BLUE;
    if(winner==-1)
        colour=RED;

    displayButton(turnButton,false,WHITE,colour);
    int remainingMoves=remainingPossibleMoves(GameBoard,currentPlayer);

    sprintf(remainingText,"REMAINING MOVES: %d",remainingMoves);//FILLS IN THE TEXT WITH THE ACTUAL VALUE OF THE REMAINING VALUES

    setButtonText(remainingButton,remainingText);
    displayButton(remainingButton,false,WHITE,colour);

    setButtonText(mainMenuButton,"MAIN MENU");
    displayButton(mainMenuButton,true);

    setButtonText(undoMoveButton,"UNDO");
    displayButton(undoMoveButton,true);

    page=1-page;//DOUBLE BUFFERING
    setactivepage(page);


}
bool checkIfMoveInList(Point Move[4],int j,int i)
{
    //AUXILIARY FUNCTION, CHECKS IF THE MOVE DEFINED BY THE COORDONATES J AND I IS IN THE POINT LIST MOVE[4]
    for(int k=0;k<16;k++)
        if(Move[k].x==j&&Move[k].y==i)
            return false;

    return true;
}
void doNeutralMove(int GameBoard[4][4])
{
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);//REMOVES THE CLICK THAT WAS IN THE QUEUE FORMERLY, SINCE THE QUEUE COULD HAVE CHANGED OUTSIDE THE FUNCTION
    int x,y,toDeletex=-1,toDeletey=-1;//TODELETE HOLDS THE TILES THE PROGRAM MAKES EMPTY WHEN YOU MOVE A NEUTRAL MOVE
    bool madeTheMove=false;//IN ORDER TO WAIT UNTIL A VALID NEUTRAL MOVE IS DONE
    while(!madeTheMove)
    {

    //THIS TODELETEX CHECK ALSO CHECKS IF THE PLAYER HAS ALREADY SELECTED THE TILE TO MOVE OR IF HE MADE AN INVALID MOVE
    //IF HE MAKES AN INVALID MOVE THE SELECTED PIECE REMAINS SELECTED
    while(toDeletex==-1)//THIS WHILE MAKES THE PLAYER PICK A NEUTRAL TILE TO MOVE. IF HE DOESN'T WISH TO MOVE HE CAN MOVE IN PLACE
    {

    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN))//CHECKS IF THE USER HAS CLICKED
    {
        delay(1);//POLLING AT A RATE OF 1000/SECOND
    }
    x=mousex();
    y=mousey();//X AND Y COORDONATES OF THE CLICK
    if(isButtonClicked(mainMenuButton,x,y))
    {
        stage=0;
        return;
    }
    if(isButtonClicked(undoMoveButton,x,y)&&moveCounter!=0)
    {
        undoHasBeenPressed=true;
        return;
    }

    //THE FOLOWING NESTED FORS ERASE THE TILE THE USER WANTS TO MOVE
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if((y>tileSize*j+offset&&y<tileSize*(j+1)+offset)&&(x>tileSize*i+offset&&x<tileSize*(i+1)+offset))
                if(GameBoard[j][i]==2&&toDeletex==-1)
                    {
                        toDeletex=j;
                        toDeletey=i;
                        setfillstyle(1,CYAN);
                    bar(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
                    rectangle(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
                    }

    }

    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);//REMOVES THE CLICK THAT CHOSE THE PIECE THAT HAS TO BE MOVED
    while(!ismouseclick(WM_LBUTTONDOWN))//WAITS FOR PLAYER TO CLICK WHERE HE WANTS THE SELECTED PIECE TO BE PLACED
    {
        delay(1);//POOLING RATE OF 1000/SECOND
    }
    x=mousex();
    y=mousey();//X AND Y COORDONATES OF THE CLICK
    //THE FOLLOWING PART OF THE FUNCTION MOVES THE NEUTRAL PIECE TO THE CHOSEN TILE AND DELETES THE FORMER POSITION OF THE TILE
    if(isButtonClicked(mainMenuButton,x,y))
    {
        stage=0;
        return;
    }
    if(isButtonClicked(undoMoveButton,x,y)&&moveCounter!=0)
    {
        undoHasBeenPressed=true;
        return;
    }
    addBoardToHistory(GameBoard,head,currentPlayer);
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
void selectMove(Point Move[16])
{
    //INITIALIZES THE MOVE
    for(int i=0;i<16;i++)
    { Move[i].x=-1;
      Move[i].y=-1;
    }

    int x=-1,y=-1,counter=0;
    bool clicked=false;
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONDOWN))//CHECK IF LEFT MOUSE BUTTON IS CLICKED
    {
        clicked=true;
        delay(1);//POLLING RATE OF 1000/SECOND
    }
    x=mousex();
    y=mousey();
    if(isButtonClicked(mainMenuButton,x,y))
    {
        stage=0;
        return;
    }
    if(isButtonClicked(undoMoveButton,x,y)&&moveCounter!=0)
    {
        undoHasBeenPressed=true;
        return;
    }
    //addBoardToHistory(GameBoard,head,currentPlayer);
    clearmouseclick(WM_LBUTTONUP);
    while(clicked)//THE INSTRUCTIONS IN THIS WHILE ARE EXECUTED ONLY WHEN THE LEFT MOUSE BUTTON IS BEING DELD PRESSED, NOT IF IT IS CLICKED
    {

        if(ismouseclick(WM_LBUTTONUP))
        {
            clicked=false;
            delay(1);//POLLING RATE OF 1000/SECOND
        }

        x=mousex();
        y=mousey();//THESE X AND Y CHANGE WHEN THE PLAYER MOVES THE CURSOR AND DON'T STAY FIXED TO THE VALUE OF THE FIRST CLICK
        //THE FOLLOWING PART OF THE FUNCTION CHECKS IF THE MOUSE IS INSIDE OF ANY TILES AND SELECTS A TILE IF THE MOUSE PASSES OVER IT ADDING IT INTO THE MOVE ARRAY
        for(int i=0;i<4;i++)
        {

            for(int j=0;j<4;j++)
            {

                if((y>=tileSize*j+offset&&y<=tileSize*(j+1)+offset)&&(x>=tileSize*i+offset&&x<=tileSize*(i+1)+offset)&&checkIfMoveInList(Move,j,i))
                {
                    Move[counter].x=j;
                    Move[counter].y=i;

                    setfillstyle(1,GREEN);
                    bar(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
                    rectangle(tileSize*i+offset,tileSize*j+offset,tileSize*(i+1)+offset,tileSize*(j+1)+offset);
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


void drawSettingsScreen()
{
    //CHANGE THESE 5 VARIABLES TO CHANGE THE WAY THE BUTTONS SHOW UP ON SCREEN
    int buttonGap=(realHeight-3*offset)/numberOfStartButtons;
    int titleLeftx=3*offset,titleLefty=offset,titleRightx=realWidth-3*offset,titleRighty=2*offset;
    char titleText[100]="SETTINGS",playText[100]="PLAYER VS PLAYER",exitText[100]="PLAYER VS CPU";//CHANGE THE TEXT TO CHANGE THE TEXT IN THE START MENU BUTTONS

    titleButton.leftCornerx=titleLeftx;
    titleButton.leftCornery=titleLefty;
    titleButton.rightCornerx=titleRightx;
    titleButton.rightCornery=titleRighty;
    setButtonText(titleButton,titleText);

    playButton.leftCornerx=titleLeftx;
    playButton.leftCornery=titleLefty+buttonGap;
    playButton.rightCornerx=titleRightx;
    playButton.rightCornery=titleRighty+buttonGap;
    setButtonText(playButton,playText);

    exitButton.leftCornerx=titleLeftx;
    exitButton.leftCornery=titleLefty+2*buttonGap;
    exitButton.rightCornerx=titleRightx;
    exitButton.rightCornery=titleRighty+2*buttonGap;
    setButtonText(exitButton,exitText);

    setvisualpage(1-page);// DOUBLE BUFFERING
    cleardevice();

    displayButton(titleButton);
    displayButton(playButton);
    displayButton(exitButton);

    page=1-page;//DOUBLE BUFFERING
    setactivepage(page);

}
void drawDifficultyScreen()
{
    //CHANGE THESE 5 VARIABLES TO CHANGE THE WAY THE BUTTONS SHOW UP ON SCREEN
    int buttonGap=(realHeight-3*offset)/numberOfStartButtons;
    int titleLeftx=3*offset,titleLefty=offset,titleRightx=realWidth-3*offset,titleRighty=2*offset;
    char titleText[100]="SELECT DIFFICULTY",playText[100]="EASY",exitText[100]="HARD";//CHANGE THE TEXT TO CHANGE THE TEXT IN THE START MENU BUTTONS

    titleButton.leftCornerx=titleLeftx;
    titleButton.leftCornery=titleLefty;
    titleButton.rightCornerx=titleRightx;
    titleButton.rightCornery=titleRighty;
    setButtonText(titleButton,titleText);

    playButton.leftCornerx=titleLeftx;
    playButton.leftCornery=titleLefty+buttonGap;
    playButton.rightCornerx=titleRightx;
    playButton.rightCornery=titleRighty+buttonGap;
    setButtonText(playButton,playText);

    exitButton.leftCornerx=titleLeftx;
    exitButton.leftCornery=titleLefty+2*buttonGap;
    exitButton.rightCornerx=titleRightx;
    exitButton.rightCornery=titleRighty+2*buttonGap;
    setButtonText(exitButton,exitText);

    setvisualpage(1-page);// DOUBLE BUFFERING
    cleardevice();

    displayButton(titleButton);
    displayButton(playButton);
    displayButton(exitButton);

    page=1-page;//DOUBLE BUFFERING
    setactivepage(page);

}

void selectSettingsButton(int& CPU)
{
    int x,y;

    //CHECKS WHICH BUTTON YOU PRESSED IN THE START MENU AND CHANGES THE STAGE VARIABLE ACCORDINGLY

    clearClickQueue();

    while(!ismouseclick(WM_LBUTTONDOWN))
        delay(1);//THIS DELAY RESULTS IN A POLLING RATE OF 1000/SECOND, DON'T DELETE THIS LINE BECAUSE THE PROGRAM WILL USE THE PROCESSOR TOO MUCH

    getmouseclick(WM_LBUTTONDOWN,x,y);
    if(isButtonClicked(playButton,x,y))
        CPU=1;

    if(isButtonClicked(exitButton,x,y))
        CPU=2;


}

void selectDifficultyButton(int& difficulty)
{
    int x,y;

    //CHECKS WHICH BUTTON YOU PRESSED IN THE START MENU AND CHANGES THE STAGE VARIABLE ACCORDINGLY

    clearClickQueue();

    while(!ismouseclick(WM_LBUTTONDOWN))
        delay(1);//THIS DELAY RESULTS IN A POLLING RATE OF 1000/SECOND, DON'T DELETE THIS LINE BECAUSE THE PROGRAM WILL USE THE PROCESSOR TOO MUCH

    getmouseclick(WM_LBUTTONDOWN,x,y);
    if(isButtonClicked(playButton,x,y))
        difficulty=1;

    if(isButtonClicked(exitButton,x,y))
        difficulty=2;


}



