#include "graphe.h"
#include <iostream>
#include <fstream>
#include <vector>


graphe::graphe(std::string nomFichier, std::string nomFichier2){


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
    //ctor

    std::ifstream file2{nomFichier2};
    file2>>m_taille3;
    file2>>m_cursor2;

    for(int i=0;i<m_taille3;i++)
    {
        file2>>m_cursor2;
        tabArete.push_back(m_cursor2);

        file2>>m_cursor2;
        tabWeight1.push_back(m_cursor2);

        file2>>m_cursor2;
        tabWeight2.push_back(m_cursor2);

    }
}

void graphe::afficher_graph()
{
    std::cout<<"Liste des sommets :\n"<<std::endl;

    for(int i=0; i<m_taille ; i++)
    {
        std::cout<<tabID[i]<<"   "<<tabX[i]<<"   "<<tabY[i]<<std::endl;
    }
    std::cout<<"\n";
    std::cout<<"Liste des aretes :\n"<<std::endl;
    for(int i=0; i<m_taille2 ; i++)
    {
        std::cout<<tabSID[i]<<"   "<<tabS1[i]<<"   "<<tabS2[i]<<std::endl;
    }
    std::cout<<"\n";
    std::cout<<"Longueur des sommets :\n"<<std::endl;
    for(int i=0; i<m_taille3 ; i++)
    {
        std::cout<<tabArete[i]<<"   "<<tabWeight1[i]<<"   "<<tabWeight2[i]<<std::endl;
    }
}


graphe::~graphe()
{
    //dtor
}
