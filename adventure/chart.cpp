#include "chart.h"

Chart::Chart(int a, int b, int c, int d)
{
    x = a;
    xold = a;
    y = b;
    yold = b;
    w = c;
    h = d;
    /*vx = 3;
    vy = 3;*/
    //DEBUG
    vx = 12;
    vy = 12;
    hp = 3;
}

int Chart::update () {
    return 0;
}

