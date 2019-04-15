#include "graphe.h"
#include <iostream>
#include <fstream>
#include <vector>


graphe::graphe(std::string nomFichier){

    int taille;
    int taille2;
    int cursor;
    std::ifstream file{nomFichier};
    file>>taille;

    //std::cout<<taille;

    std::vector<int> tabID(taille);
    std::vector<int> tabX(taille);
    std::vector<int> tabY(taille);


    for(int i=0;i<taille;i++)
    {
        file>>cursor;
        tabID[i]=cursor;

        file>>cursor;
        tabX[i]=cursor;

        file>>cursor;
        tabY[i]=cursor;
    }

    file>>taille2;

    std::vector<int> tabSID(taille2);
    std::vector<int> tabS1(taille2);
    std::vector<int> tabS2(taille2);

    for(int i=0;i<taille2;i++)
    {
        file>>cursor;
        tabSID[i]=cursor;

        file>>cursor;
        tabS1[i]=cursor;

        file>>cursor;
        tabS2[i]=cursor;
    }
    //ctor
}

graphe::~graphe()
{
    //dtor
}
