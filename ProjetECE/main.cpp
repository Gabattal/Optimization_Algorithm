#include <iostream>
#include "graphe.h"
#include <vector>

int main()
{
   graphe g{"broadway.txt","broadway_weights_0.txt"};
   g.afficher_graph();
   g.Prim(1, 0);
   std::cout<<std::endl;
   g.Prim(1, 1);
   //graphe_weight {"broadway_weight_0.txt"};
    //std::cout<<tableau[0];
    return 0;
}
