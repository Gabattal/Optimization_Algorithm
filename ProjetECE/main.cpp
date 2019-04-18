#include <iostream>
#include <vector>
#include <cstdlib>
#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"
#define UNIT 76.0f

#define MAP_WIDTH 1920
#define MAP_HEIGHT 960

int main()
{
    Svgfile svgout("output.svg", MAP_WIDTH, MAP_HEIGHT);
    int choix=1;
    std::string nom;
    std::string poids;
/*
       do
    {

        std::cout<<"Que voulez-vous faire ?"<<std::endl;
        std::cout<<"1 - Choisir un graphe"<<std::endl;
        std::cout<<"2 - Executer un algorithme sur le graphe"<<std::endl;
        std::cout<<"3 - Quitter"<<std::endl;
        std::cin>>(choix);

        system("cls");
        if(choix==1)
        {
        std::cout<<"Choisir un fichier de base"<<std::endl;
        std::cin>>(nom);

        system("cls");
        std::cout<<"Choisir un poids"<<std::endl;
        std::cin>>(poids);
        }
        if (choix==2)
        {
            graphe g{nom+".txt",nom+"_weights_"+poids+".txt",&svgout};
            g.afficher_graph();
            g.Prim(1, 0);
            g.generateSvg();
            choix=0;
        }

    }while(choix!=3);

*/
   //std::cout<<std::endl;
   //g.Prim(1, 1);
    std::string city = "manhattan";
    graphe g{city+".txt",city+"_weights_0.txt",&svgout};
    g.Pareto();
   //graphe_weight {"broadway_weight_0.txt"};
    //std::cout<<tableau[0];
    return 0;
}
