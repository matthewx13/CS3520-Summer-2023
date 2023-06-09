#include <cstdlib>
#include <ncurses.h>
#include "simulationWindow.hpp"

GameWindow* init_GameWindow(int x, int y, int w, int h)
{
    GameWindow* window = (GameWindow*)malloc(sizeof(GameWindow));
    window->xPos = x;
    window->yPos = y;
    window->width = w;
    window->height = h;
    window->drawChar = '*';
    window->color[0] = 0;
    window->color[1] = 0;
    window->color[2] = 255;
    return window;
}

void draw_GameWindow(GameWindow* window)
{
    int row, col;

    // Draw top of window
    for (col = window->xPos; col <= (window->xPos + window->width); col++) {
        mvprintw(window->yPos, col, "%c", window->drawChar);
    }

    // Draw left side of window
    for (row = window->yPos; row <= (window->yPos + window->height); row++) {
        mvprintw(row, window->xPos, "%c", window->drawChar);
    }

    // Draw right side of window
    for (row = window->yPos; row <= (window->yPos + window->height); row++) {
        mvprintw(row, (window->xPos + window->width), "%c", window->drawChar);
    }

    // Draw bottom of window
    for (col = window->xPos; col <= (window->xPos + window->width); col++) {
        mvprintw(window->yPos + window->height, col, "%c", window->drawChar);
    }
}

GameWindow* changeGameWindow(int x, int y, int w, int h, GameWindow* window)
{
    window->xPos = x;
    window->yPos = y;

    if (w < 10)
        window->width = 10;
    else
        window->width = w;

    if (h < 10)
        window->height = 10;
    else
        window->height = h;

    return window;
}

void undraw_GameWindow(GameWindow* window)
{
    int row, col;

    // Undraw top of window
    for (col = window->xPos; col <= (window->xPos + window->width); col++) {
        mvprintw(window->yPos, col, " ");
    }

    // Undraw left side of window
    for (row = window->yPos; row <= (window->yPos + window->height); row++) {
        mvprintw(row, window->xPos, " ");
    }

    // Undraw right side of window
    for (row = window->yPos; row <= (window->yPos + window->height); row++) {
        mvprintw(row, (window->xPos + window->width), " ");
    }

    // Undraw bottom of window
    for (col = window->xPos; col <= (window->xPos + window->width); col++) {
        mvprintw(window->yPos + window->height, col, " ");
    }
}
