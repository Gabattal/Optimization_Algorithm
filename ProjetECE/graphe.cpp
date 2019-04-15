#include "graphe.h"
#include <iostream>
#include <fstream>
#include <vector>


graphe::graphe(std::string nomFichier){


    std::ifstream file{nomFichier};
    file>>m_taille;

    //std::cout<<taille;

    for(int i=0;i<m_taille;i++)
    {
        file>>m_cursor;
        tabID.push_back(m_cursor);

        file>>m_cursor;
        tabX.push_back(m_cursor);

        file>>m_cursor;
        tabY.push_back(m_cursor);
    }

    file>>m_taille2;

    for(int i=0;i<m_taille2;i++)
    {
        file>>m_cursor;
        tabSID.push_back(m_cursor);

        file>>m_cursor;
        tabS1.push_back(m_cursor);

        file>>m_cursor;
        tabS2.push_back(m_cursor);
    }
    std::cout<<tabS1[1];
    //ctor
}
graphe::graphe_weight(std::string nomFichier){

    std::ifstream file{nomFichier};
    file>>m_taille;

    for(int i=0;i<m_taille;i++)
    {
        file>>m_cursor;
        tabArete.push_back(m_cursor);

        file>>m_cursor;
        tabPoids1.push_back(m_cursor);

        file>>m_cursor;
        tabPoids2.push_back(m_cursor);

    }
}

graphe::~graphe()
{
    //dtor
}
