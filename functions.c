#include<stdio.h>
#include<windows.h>
#include"header.h"


void printMap(char map[][53]){
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i=0;i<22;i++){
        for(int j=0;j<53;j++){
            if(map[i][j]==(char)250 || map[i][j]==(char)254) SetConsoleTextAttribute(handle, 15);
            else SetConsoleTextAttribute(handle, 1);
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
}

void hideCursor(){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void setxy(int x,int y){
    HANDLE hCon;
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

char getPacC(int f){
    if(f==0) return 'v';
    if(f==1) return '^';
    if(f==2) return '>';
    if(f==3) return '<';
}



void printPac(int x, int y, int f){
    setxy(x, y);
    char pacmanC = getPacC(f);
    printf("%c", pacmanC);
}


void printGhost(int x, int y){
    setxy(x, y);
    printf("G"); // Unicode ghost emoji
}


void clear(int x, int y){
    setxy(x,y);
    printf(" ");
}

void clearGhost(int x, int y, char map[][53], struct ghost ghosts[], int t, int buff){
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    setxy(x,y);
    for(int i=0; i<4; i++){
        if(x==ghosts[i].X && y==ghosts[i].Y && t!=i){
            if(buff==0) SetConsoleTextAttribute(handle, 11);
            else SetConsoleTextAttribute(handle, 3);
            printf("%c",(char)230);
            return;
        }
    }
    SetConsoleTextAttribute(handle, 15);
    printf("%c",(char)map[y][x]);
}

int valGhostHere(int x, int y, struct ghost ghosts[], int t, int f){
    if(f==0) y-=1;
    if(f==1) y+=1;
    if(f==2) x-=3;
    if(f==3) x+=3;
    for(int i=0; i<4; i++){
        if(x==ghosts[i].X && y==ghosts[i].Y && t!=i) return 1;
    }
    return 0;
}

int valGhostHereP(int x, int y, struct ghost ghosts[], int f){
    if(f==0) y-=1;
    if(f==1) y+=1;
    if(f==2) x-=3;
    if(f==3) x+=3;
    for(int i=0; i<4; i++){
        if(x==ghosts[i].X && y==ghosts[i].Y) return 1;
    }
    return 0;
}

int ghostHereIdGet(int x, int y, struct ghost ghosts[], int f){
    if(f==0) y-=1;
    if(f==1) y+=1;
    if(f==2) x-=3;
    if(f==3) x+=3;
    for(int i=0; i<4; i++){
        if(x==ghosts[i].X && y==ghosts[i].Y) return i;
    }
}

int valWall(int x, int y, char map[][53]){
    if(map[y][x]==' ' || map[y][x]==(char)250 || map[y][x]==(char)254) return 0;
    else return 1;
}

int valWallf(int x, int y, char map[][53],int f){//0-UP, 1-DOWN, 2-LEFT, 3-RIGHT
    if(f==0) y-=1;
    if(f==1) y+=1;
    if(f==2) x-=3;
    if(f==3) x+=3;
    if(map[y][x]==' ' || map[y][x]==(char)250 || map[y][x]==(char)254) return 0;
    else return 1;
}

int valFood(int x, int y, char map[][53]){
    if(map[y][x]==(char)250) return 1;
    else return 0;
}

int valBuff(int x, int y, char map[][53]){
    if(map[y][x]==(char)254) return 1;
    else return 0;
}

int valPacHere(int x, int y, int px, int py, int f){
    if(f==0) y-=1;
    if(f==1) y+=1;
    if(f==2) x-=3;
    if(f==3) x+=3;
    if(x==px && y==py) return 1;
    return 0;
}
