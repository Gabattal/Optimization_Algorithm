#include "couleur.h"
#include "svgfile.h"
#include <iostream>

Couleur::Couleur(int rouge, int vert, int bleu, float alpha)
	: m_rouge{ rouge }, m_vert{ vert }, m_bleu{ bleu }, m_alpha(alpha)
{ }


Couleur::Couleur()
	: Couleur(0, 0, 0) // Délégation de constructeur
{ }


void Couleur::afficher() const
{
	std::cout << "(" << m_rouge << ", " << m_vert << ", " << m_bleu << ", " << m_alpha << ")" << std::endl;
}

Couleur::operator std::string() const
{
	return Svgfile::makeRGB(m_rouge, m_vert, m_bleu, m_alpha);
}
