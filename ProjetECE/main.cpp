#include <iostream>
#include "graphe.h"
#include <vector>
#include "svgfile.h"
#include "couleur.h"
#define UNIT 76.0f

#define MAP_WIDTH 1920
#define MAP_HEIGHT 960

int main()
{
    Svgfile svgout("output.svg", MAP_WIDTH, MAP_HEIGHT);


   graphe g{"broadway.txt","broadway_weights_0.txt",&svgout};
   g.afficher_graph();
   g.Prim(1, 0);
   std::cout<<std::endl;
   g.Prim(1, 1);
   g.generateSvg();

   //graphe_weight {"broadway_weight_0.txt"};
    //std::cout<<tableau[0];
    return 0;
}
