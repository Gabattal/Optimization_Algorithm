#include "graphe.h"
#include <iostream>
#include <fstream>
#include <vector>


graphe::graphe(std::string nomFichier){

    float taille;
    float taille2;
    float cursor;
    std::ifstream file{nomFichier};
    file>>taille;

    //std::cout<<taille;

    std::vector<float> tabID(taille);
    std::vector<float> tabX(taille);
    std::vector<float> tabY(taille);


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

    std::vector<float> tabSID(taille2);
    std::vector<float> tabS1(taille2);
    std::vector<float> tabS2(taille2);

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
graphe::graphe_weight(std::string nomFichier1,std::string nomFichier2){

    graphe(nomFichier1);
    float taille;
    float cursor;
    std::ifstream file{nomFichier2};
    file>>taille;



    std::vector<float> tabARRETE(taille);
    std::vector<float> tabPoids1(taille);
    std::vector<float> tabPoids2(taille);



    for(int i=0;i<taille;i++)
    {
        file>>cursor;
        tabARRETE[i]=cursor;

        file>>cursor;
        tabPoids1[i]=cursor;

        file>>cursor;
        tabPoids2[i]=cursor;


    }



}

graphe::~graphe()
{
    //dtor
}
