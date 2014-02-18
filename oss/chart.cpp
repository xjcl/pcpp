#include "chart.h"

Chart::Chart(int a, int b, int c, int d)
{
    x = a;
    xold = a;
    y = b;
    yold = b;
    w = c;
    h = d;
    vx = 0;
    vxmax = 6;
    vy = 0;
    vymax = 18;
    ac = 1;
    //in_air is covered by the jump variable
    //of the main loop at the moment
    in_air = 0;
    //return Chart; //I'M DESPARATE OK
}

int Chart::update () {
    return 0;
}

