#ifndef CHART_H
#define CHART_H

class Chart
{
  int x, y, w, h;

public:
  Chart(int x, int y, int w, int h); // do i really have to name the variables now already?
  void set_values (int a, int b, int c, int d); // same here.
  int update ();
  
};



#endif
