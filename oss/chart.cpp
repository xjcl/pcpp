#include "chart.h"

Chart::Chart(int a, int b, int c, int d)
{
  x = a;
  y = b;
  w = c;
  h = d;
}

void Chart::set_values (int a, int b, int c, int d) {
    x = a;      y = b;      w = c;      h = d;
}

int Chart::update () {
    return 0;
}
