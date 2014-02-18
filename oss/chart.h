#ifndef CHART_H
#define CHART_H

class Chart
{

    public:
        double x, xold, y, yold, w, h, vx, vxmax, vy, vymax, ac, in_air;
        Chart(int, int, int, int);
        //int get_x (); etc.
        int update ();
  
};



#endif


