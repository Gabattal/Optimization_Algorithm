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
        float m_taille, m_taille2, m_cursor;
        std::vector<float> tabID;
        std::vector<float> tabX;
        std::vector<float> tabY;

        std::vector<float> tabSID;
        std::vector<float> tabS1;
        std::vector<float> tabS2;

        std::vector<float> tabARRETE;
        std::vector<float> tabPoids1;
        std::vector<float> tabPoids2;

};

#endif // GRAPHE_H
