#ifndef GRAPHE_H
#define GRAPHE_H
#include "sommet.h"
#include <vector>

class graphe
{
    public:
        graphe(std::string,std::string);
        void afficher_graph();
        //graphe_weight(std::string);
        virtual ~graphe();

    protected:

    private:
        float m_taille, m_taille2,m_taille3, m_cursor, m_cursor2;
        std::vector<float> tabID;
        std::vector<float> tabX;
        std::vector<float> tabY;

        std::vector<float> tabSID;
        std::vector<float> tabS1;
        std::vector<float> tabS2;

        std::vector<float> tabArete;
        std::vector<float> tabWeight1;
        std::vector<float> tabWeight2;

};

#endif // GRAPHE_H
