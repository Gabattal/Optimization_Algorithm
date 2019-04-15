#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>

class sommet
{
    public:
        sommet(std::string,double,double);
        std::string getId();
        double getX();
        double getY();
        virtual ~sommet();


    protected:

    private:
        std::string m_id; // Identifiant
        double m_x, m_y; // Position
};

#endif // SOMMET_H
