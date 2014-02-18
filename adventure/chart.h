class Chart
{
    public:
        double x, xold, y, yold, w, h, vx, vy, hp;
        Chart(int, int, int, int);
        //void set_values (int, int);
        //int get_x (); etc.
        int update ();
};
