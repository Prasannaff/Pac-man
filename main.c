#include"header.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<pthread.h>


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
const char rt=187, lt=201, rb=188, lb=200, hor=205, vert=186, food=250, hord=203, hort=202, vertr=204, vertl=185, buffc=254;

struct pac{
    int X;
    int Y;
    f f;
};

char z;

pthread_mutex_t lock= PTHREAD_MUTEX_INITIALIZER;
struct pac pac;
struct ghost ghosts[4];

int score=0;
int foodEaten=0;
int end=0;
int buff=0;

char mapc[22][53]={
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
};

int main() {
    char map[22][53]={
            {lt,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hord,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,rt},
            {vert,' ',buffc,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',buffc,' ',vert},
            {vert,' ',food,' ',' ',lt,hor,hor,rt,' ',' ',food,' ',' ',lt,hor,hor,hor,hor,hor,rt,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',lt,hor,hor,hor,hor,hor,rt,' ',' ',food,' ',' ',lt,hor,hor,rt,' ',' ',food,' ',vert},
            {vert,' ',food,' ',' ',lb,hor,hor,rb,' ',' ',food,' ',' ',lb,hor,hor,hor,hor,hor,rb,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',lb,hor,hor,hor,hor,hor,rb,' ',' ',food,' ',' ',lb,hor,hor,rb,' ',' ',food,' ',vert,},
            {vert,' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',vert},
            {vert,' ',food,' ',' ',hor,hor,hor,hor,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',hor,hor,hor,hor,hor,hor,hord,hor,hor,hor,hor,hor,hor,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',hor,hor,hor,hor,' ',' ',food,' ',vert},
            {vert,' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',vert},
            {lb,hor,hor,hor,hor,hor,hor,hor,rt,' ',' ',food,' ',' ',vertr,hor,hor,hor,hor,hor,hor,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',hor,hor,hor,hor,hor,hor,vertl,' ',' ',food,' ',' ',lt,hor,hor,hor,hor,hor,hor,hor,rb},
            {' ',' ',' ',' ',' ',' ',' ',' ',vert,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',vert},
            {hor,hor,hor,hor,hor,hor,hor,hor,rb,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',lt,hor,hor,hor,' ',' ',' ',' ',' ',hor,hor,hor,rt,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',lb,hor,hor,hor,hor,hor,hor,hor,hor},
            {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
            {hor,hor,hor,hor,hor,hor,hor,hor,rt,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',lb,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,rb,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',lt,hor,hor,hor,hor,hor,hor,hor,hor},
            {' ',' ',' ',' ',' ',' ',' ',' ',vert,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',vert},
            {lt,hor,hor,hor,hor,hor,hor,hor,rb,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',hor,hor,hor,hor,hor,hor,hord,hor,hor,hor,hor,hor,hor,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',lb,hor,hor,hor,hor,hor,hor,hor,rt},
            {vert,' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',vert},
            {vert,' ',food,' ',' ',hor,hor,hor,rt,' ',' ',food,' ',' ',hor,hor,hor,hor,hor,hor,hor,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',hor,hor,hor,hor,hor,hor,hor,' ',' ',food,' ',' ',lt,hor,hor,hor,' ',' ',food,' ',vert},
            {vert,' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',vert},
            {vertr,hor,hor,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',hor,hor,hor,hor,hor,hor,hord,hor,hor,hor,hor,hor,hor,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',hor,hor,vertl},
            {vert,' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',vert},
            {vert,' ',food,' ',' ',hor,hor,hor,hor,hor,hor,hor,hor,hor,hort,hor,hor,hor,hor,hor,hor,' ',' ',food,' ',' ',vert,' ',' ',food,' ',' ',hor,hor,hor,hor,hor,hor,hort,hor,hor,hor,hor,hor,hor,hor,hor,hor,' ',' ',food,' ',vert},
            {vert,' ',buffc,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',food,' ',' ',buffc,' ',vert},
            {lb,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,hor,rb},
    };

    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    system("mode con: cols=53 lines=23");

    hideCursor();
    printMap(map);

    pac.X=26;
    pac.Y=12;
    pac.f=LEFT;
    map[pac.Y][pac.X]=' ';
    setxy(pac.X,pac.Y);
    SetConsoleTextAttribute(handle, 14);
    printPac(pac.X,pac.Y,pac.f);

    ghosts[0].X=23; ghosts[0].Y=10; ghosts[0].f=0;
    ghosts[1].X=26; ghosts[1].Y=10; ghosts[1].f=0;
    ghosts[2].X=29; ghosts[2].Y=10; ghosts[2].f=0;
    ghosts[3].X=26; ghosts[3].Y=9; ghosts[3].f=0;
    if(buff==0) SetConsoleTextAttribute(handle, 11);
    else SetConsoleTextAttribute(handle, 3);
    printGhost(ghosts[0].X,ghosts[0].Y);
    printGhost(ghosts[1].X,ghosts[1].Y);
    printGhost(ghosts[2].X,ghosts[2].Y);
    printGhost(ghosts[3].X,ghosts[3].Y);

    setxy(0,22);
    SetConsoleTextAttribute(handle, 15);
    printf("PRESS ENTER TO START");
    do{
        z=getch();
    }while(z!=13);
    setxy(0,22);
    SetConsoleTextAttribute(handle, 15);
    printf("                      ");

    void* gameLoop(char map[][53]);
    void* keyListener();
    void* ghostLoop(char map[][53]);
    void* buffTimer();

    pthread_attr_t tattr;
    pthread_attr_init(&tattr);

    pthread_t thread1, thread2, thread3, thread4;

    pthread_create(&thread1, &tattr, (void *(*)(void *)) gameLoop, map);
    pthread_create(&thread2, &tattr, keyListener, NULL);
    pthread_create(&thread3, &tattr, (void *(*)(void *)) ghostLoop, map);
    pthread_create(&thread4, &tattr, buffTimer, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}

void* gameLoop(char map[][53]) {
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    while(1){
        if(end==1) break;
        pthread_mutex_lock(&lock);
        if(valGhostHereP(pac.X,pac.Y,ghosts,pac.f) && buff){
            int t=ghostHereIdGet(pac.X,pac.Y,ghosts,pac.f);
            ghosts[t].X=23;
            ghosts[t].Y=10;
            ghosts[t].f=0;
            if(buff==0) SetConsoleTextAttribute(handle, 11);
            else SetConsoleTextAttribute(handle, 3);
            printGhost(ghosts[t].X,ghosts[t].Y);
            score+=200;
        }
        if(valGhostHereP(pac.X,pac.Y,ghosts,pac.f) && !buff){
            clear(pac.X,pac.Y);
            if(pac.f==1) pac.Y-=1;
            if(pac.f==1) pac.Y+=1;
            if(pac.f==2) pac.X-=3;
            if(pac.f==3) pac.X+=3;
            SetConsoleTextAttribute(handle, 11);
            printGhost(pac.X,pac.Y);

            setxy(21,22);
            SetConsoleTextAttribute(handle, 15);
            printf("YOU LOSE (press ENTER to exit)");

            end=1;
            break;
        }
        if(pac.X==50 && pac.Y==10){
            clear(pac.X,pac.Y);
            pac.f=3;
            pac.X=5;
            SetConsoleTextAttribute(handle, 14);
            printPac(pac.X,pac.Y,pac.f);
        }
        if(pac.X==2 && pac.Y==10){
            clear(pac.X,pac.Y);
            pac.f=2;
            pac.X=47;
            SetConsoleTextAttribute(handle, 14);
            printPac(pac.X,pac.Y,pac.f);
        }
        if(pac.f==0 && !valWall(pac.X,pac.Y-1,map)){
            clear(pac.X,pac.Y);
            pac.Y -= 1;
            if(valFood(pac.X,pac.Y, map)){
                map[pac.Y][pac.X]=' ';
                foodEaten++;
            }
            if(valBuff(pac.X,pac.Y, map)){
                map[pac.Y][pac.X]=' ';
                buff=1;
                foodEaten++;
            }
            SetConsoleTextAttribute(handle, 14);
            printPac(pac.X,pac.Y,pac.f);
        }
        else if(pac.f==1 && !valWall(pac.X,pac.Y+1,map)){
            clear(pac.X,pac.Y);
            pac.Y += 1;
            if(valFood(pac.X,pac.Y, map)){
                map[pac.Y][pac.X]=' ';
                foodEaten++;
            }
            if(valBuff(pac.X,pac.Y, map)){
                map[pac.Y][pac.X]=' ';
                buff=1;
                foodEaten++;
            }
            SetConsoleTextAttribute(handle, 14);
            printPac(pac.X,pac.Y,pac.f);
        }
        else if(pac.f==2 && !valWall(pac.X-3,pac.Y,map)){
            clear(pac.X,pac.Y);
            pac.X -= 3;
            if(valFood(pac.X,pac.Y, map)){
                map[pac.Y][pac.X]=' ';
                foodEaten++;
            }
            if(valBuff(pac.X,pac.Y, map)){
                map[pac.Y][pac.X]=' ';
                buff=1;
                foodEaten++;
            }
            SetConsoleTextAttribute(handle, 14);
            printPac(pac.X,pac.Y,pac.f);
        }
        else if(pac.f==3 && !valWall(pac.X+3,pac.Y,map)){
            clear(pac.X,pac.Y);
            pac.X += 3;
            if(valFood(pac.X,pac.Y, map)){
                map[pac.Y][pac.X]=' ';
                foodEaten++;
            }
            if(valBuff(pac.X,pac.Y, map)){
                map[pac.Y][pac.X]=' ';
                buff=1;
                foodEaten++;
            }
            SetConsoleTextAttribute(handle, 14);
            printPac(pac.X,pac.Y,pac.f);
        }

        if(foodEaten==182){
            setxy(21,22);
            SetConsoleTextAttribute(handle, 15);
            printf("YOU WIN (press ENTER to exit)");
            end=1;
            break;
        }

        setxy(0,22);
        SetConsoleTextAttribute(handle, 15);
        printf("Score: %d",score+foodEaten*10);

        pthread_mutex_unlock(&lock);
        Sleep(350);
    }
}

void* keyListener(){
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    while(1){
        z = getch();
        if(end==1 && z==13) exit(0);
        if(z==(char)224 && end==0) {
            z = getch();
            pthread_mutex_lock(&lock);
            SetConsoleTextAttribute(handle, 14);
            if(z==75){
                pac.f = LEFT;
                printPac(pac.X,pac.Y,pac.f);
            }
            else if(z==77){
                pac.f = RIGHT;
                printPac(pac.X,pac.Y,pac.f);
            }
            else if(z==72){
                pac.f = UP;
                printPac(pac.X,pac.Y,pac.f);
            }
            else if(z==80){
                pac.f = DOWN;
                printPac(pac.X,pac.Y,pac.f);
            }
            pthread_mutex_unlock(&lock);
        }
    }
}

void* ghostLoop(char map[][53]){
    int l,r,er=0,ermax=20;
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    while(1){
        pthread_mutex_lock(&lock);
        srand(time(NULL));
        for(int i=0; i<4; i++){
            if (valPacHere(ghosts[i].X,ghosts[i].Y,pac.X,pac.Y,ghosts[i].f) && !buff){
                clear(ghosts[i].X,ghosts[i].Y);
                if(ghosts[i].f==0) ghosts[i].Y-=1;
                if(ghosts[i].f==1) ghosts[i].Y+=1;
                if(ghosts[i].f==2) ghosts[i].X-=3;
                if(ghosts[i].f==3) ghosts[i].X+=3;
                if(buff==0) SetConsoleTextAttribute(handle, 11);
                else SetConsoleTextAttribute(handle, 3);
                printGhost(ghosts[i].X,ghosts[i].Y);

                setxy(21,22);
                SetConsoleTextAttribute(handle, 15);
                printf("YOU LOSE (press ENTER to exit)");

                end=1;
                break;
            }else if (valPacHere(ghosts[i].X,ghosts[i].Y,pac.X,pac.Y,ghosts[i].f) && buff){
                clearGhost(ghosts[i].X,ghosts[i].Y,map,ghosts,i,buff);
                ghosts[i].X=23;
                ghosts[i].Y=10;
                ghosts[i].f=0;
                SetConsoleTextAttribute(handle, 3);
                printGhost(ghosts[i].X,ghosts[i].Y);
                score+=200;
            }
            if(ghosts[i].X==50 && ghosts[i].Y==10){
                clear(ghosts[i].X,ghosts[i].Y);
                ghosts[i].f=3;
                ghosts[i].X=5;
                if(buff==0) SetConsoleTextAttribute(handle, 11);
                else SetConsoleTextAttribute(handle, 3);
                printGhost(ghosts[i].X,ghosts[i].Y);
            }else if(ghosts[i].X==2 && ghosts[i].Y==10){
                clear(ghosts[i].X,ghosts[i].Y);
                ghosts[i].f=2;
                ghosts[i].X=47;
                if(buff==0) SetConsoleTextAttribute(handle, 11);
                else SetConsoleTextAttribute(handle, 3);
                printGhost(ghosts[i].X,ghosts[i].Y);
            }
            if(valGhostHere(ghosts[i].X, ghosts[i].Y, ghosts, i, ghosts[i].f)){
                if(ghosts[i].f==0) r=1;
                if(ghosts[i].f==1) r=0;
                if(ghosts[i].f==2) r=3;
                if(ghosts[i].f==3) r=2;
                er=0;
                do{
                    l=rand()%4;
                    er++;
                }while(er<ermax && (l==ghosts[i].f || l==r || valWallf(ghosts[i].X,ghosts[i].Y,map,l) || valGhostHere(ghosts[i].X, ghosts[i].Y, ghosts, i, ghosts[i].f)));
                ghosts[i].f=l;
            }
            if(mapc[ghosts[i].Y][ghosts[i].X]=='.'){

                if(ghosts[i].f==0) r=1;
                if(ghosts[i].f==1) r=0;
                if(ghosts[i].f==2) r=3;
                if(ghosts[i].f==3) r=2;
                er=0;
                do{
                    l=rand()%4;
                    er++;
                }while(er<ermax && (l==ghosts[i].f || l==r || valWallf(ghosts[i].X,ghosts[i].Y,map,l) || valGhostHere(ghosts[i].X, ghosts[i].Y, ghosts, i, ghosts[i].f)));
                ghosts[i].f=l;
            }
            if(ghosts[i].X==26 && ghosts[i].Y==10){
                clearGhost(ghosts[i].X,ghosts[i].Y,map,ghosts,i,buff);
                ghosts[i].f=0;
                ghosts[i].Y -= 1;
                if(buff==0) SetConsoleTextAttribute(handle, 11);
                else SetConsoleTextAttribute(handle, 3);
                printGhost(ghosts[i].X,ghosts[i].Y);
            }
            if(ghosts[i].f==0 && !valWall(ghosts[i].X,ghosts[i].Y-1,map)){
                clearGhost(ghosts[i].X,ghosts[i].Y,map,ghosts,i,buff);
                ghosts[i].Y -= 1;
                if(buff==0) SetConsoleTextAttribute(handle, 11);
                else SetConsoleTextAttribute(handle, 3);
                printGhost(ghosts[i].X,ghosts[i].Y);
            }
            else if(ghosts[i].f==1 && !valWall(ghosts[i].X,ghosts[i].Y+1,map)){
                clearGhost(ghosts[i].X,ghosts[i].Y,map,ghosts,i,buff);
                ghosts[i].Y += 1;
                if(buff==0) SetConsoleTextAttribute(handle, 11);
                else SetConsoleTextAttribute(handle, 3);
                printGhost(ghosts[i].X,ghosts[i].Y);
            }
            else if(ghosts[i].f==2 && !valWall(ghosts[i].X-3,ghosts[i].Y,map)){
                clearGhost(ghosts[i].X,ghosts[i].Y,map,ghosts,i,buff);
                ghosts[i].X -= 3;
                if(buff==0) SetConsoleTextAttribute(handle, 11);
                else SetConsoleTextAttribute(handle, 3);
                printGhost(ghosts[i].X,ghosts[i].Y);
            }
            else if(ghosts[i].f==3 && !valWall(ghosts[i].X+3,ghosts[i].Y,map)){
                clearGhost(ghosts[i].X,ghosts[i].Y,map,ghosts,i,buff);
                ghosts[i].X += 3;
                if(buff==0) SetConsoleTextAttribute(handle, 11);
                else SetConsoleTextAttribute(handle, 3);
                printGhost(ghosts[i].X,ghosts[i].Y);
            }else{
                if(ghosts[i].f==0) r=1;
                if(ghosts[i].f==1) r=0;
                if(ghosts[i].f==2) r=3;
                if(ghosts[i].f==3) r=2;
                er=0;
                do{
                    l=rand()%4;
                    er++;
                }while(er<ermax && (l==ghosts[i].f || l==r || valWallf(ghosts[i].X,ghosts[i].Y,map,l) || valGhostHere(ghosts[i].X, ghosts[i].Y, ghosts, i, ghosts[i].f)));
                ghosts[i].f=l;
            }
        }
        pthread_mutex_unlock(&lock);
        if(end==1)break;
        if(buff==0)Sleep(300);
        else Sleep(500);
    }
}

void* buffTimer(){
    while(1){
        if(buff==1){
            Sleep(10000);
            buff=0;
        }
    }
}

#pragma clang diagnostic pop