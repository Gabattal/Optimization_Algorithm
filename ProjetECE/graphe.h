#ifndef GRAPHE_H
#define GRAPHE_H
#include "sommet.h"
#include <vector>

class graphe
{
    public:
        graphe(std::string);
        graphe_weight(std::string,std::string);
        virtual ~graphe();

    protected:

    private:
// std::string a;
};

#endif // GRAPHE_H
