#include "sommet.h"
#include <iostream>

sommet::sommet(std::string,double,double)
{
    //ctor
}

std::string sommet::getId(){
    return m_id;
}

double sommet::getX(){
    return m_x;
}

double sommet::getY(){
    return m_y;
}


sommet::~sommet()
{
    //dtor
}
