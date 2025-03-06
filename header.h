#ifndef PACMAN_HEADER_H
#define PACMAN_HEADER_H
typedef enum {UP, DOWN, LEFT, RIGHT} f;

struct ghost{
    int X;
    int Y;
    f f;
};
void hideCursor();
void printMap(char map[][53]);
void setxy(int x,int y);
void printPac(int x, int y, int f);
char getPacC(int f);
void clear(int x, int y);
void clearGhost(int x, int y, char map[][53], struct ghost ghosts[], int t, int buff);
int valWall(int x, int y, char map[][53]);
int valWallf(int x, int y, char map[][53], int f);
int valFood(int x, int y, char map[][53]);
int valBuff(int x, int y, char map[][53]);
void printGhost(int x, int y);
int valGhostHere(int x, int y, struct ghost ghosts[], int t, int f);
int valPacHere(int x, int y, int px, int py, int f);
int valGhostHereP(int x, int y, struct ghost ghosts[], int f);
int ghostHereIdGet(int x, int y, struct ghost ghosts[], int f);

#endif //PACMAN_HEADER_H
