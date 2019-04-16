#ifndef POS_H_INCLUDED
#define POS_H_INCLUDED

struct Pos
{
    double x;
    double y;

    Pos operator+(Pos pos)
    {
        return Pos{x+pos.x, y+pos.y};
    }

    Pos operator-(Pos pos)
    {
        return Pos{x-pos.x, y-pos.y};
    }

    Pos operator*(float mult)
    {
        return Pos{mult*x, mult*y};
    }

    Pos operator*(Pos pos)
    {
        return Pos{pos.x*x, pos.y*y};
    }

    Pos operator/(float divide)
    {
        return Pos{x/divide, y/divide};
    }
};

#endif // POS_H_INCLUDED
