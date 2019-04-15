#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>

class sommet
{
    public:
        sommet(double,double,double);
        double getId();
        double getX();
        double getY();
        virtual ~sommet();


    protected:

    private:
 // Identifiant
        double m_x, m_y, m_id; // Position
};

#endif // SOMMET_H
