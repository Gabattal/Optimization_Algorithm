#include <iostream>
#include <vector>
#include <cstdlib>
#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"

#define MAP_WIDTH 1920
#define MAP_HEIGHT 960

int main()
{
	int choix;
	int choix2;
	int choix3;
	int weightNum;
	int StartNode;
	std::string nom;
	std::string poids;

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
			    std::cout<<"Que voulez-vous faire ?"<<std::endl;
			    std::cout<<"1 - Executer Prim "<<std::endl;
			    std::cout<<"2 - Executer Pareto"<<std::endl;
			    std::cout<<"3 - Executer Pareto-Dijkstra"<<std::endl;
			    std::cout<<"4 - Visualiser le graphe"<<std::endl;
			    std::cin>>(choix2);
			    system("cls");

			    Svgfile svgout("output.svg", MAP_WIDTH, MAP_HEIGHT);
                graphe g{nom+".txt",nom+"_weights_"+poids+".txt",&svgout};
			    if(choix2==1)
                {
                    std::cout<<"Saisissez le numero du poids"<<std::endl;
                    std::cin>>weightNum;
                    std::cout<<"Saisissez le point d'origine"<<std::endl;
                    std::cin>>StartNode;
                    g.Prim(weightNum, StartNode);
                }
                else if(choix2==2)
                {
                    g.Pareto();
                }
                else if(choix2==3)
                {
                    g.Dijkstra();
                }
                else if (choix2==4)
                {
                    g.afficher_graph();
                }
                else
                {
                    std::cout<<"Erreur"<<std::endl;
                }
			}
		}while(choix!=4);

	return 0;
}
