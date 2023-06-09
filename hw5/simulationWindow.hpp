#pragma once

#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 100

struct GameWindow
{
    int xPos;
    int yPos;
    int width;
    int height;
    char drawChar;
    char color[3];
};

typedef struct GameWindow GameWindow;

GameWindow* init_GameWindow(int, int, int, int);
GameWindow* changeGameWindow(int, int, int, int, GameWindow*);

void undraw_GameWindow(GameWindow*);
void draw_GameWindow(GameWindow*);
