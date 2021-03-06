#ifndef COULEUR_H_INCLUDED
#define COULEUR_H_INCLUDED

#include <string>
#include <cstdint>

class Couleur
{
public:
	Couleur(int rouge, int vert, int bleu, float alpha = 1.0f);
	Couleur();
	void afficher() const;
	void saisir();

	operator std::string() const;


	Couleur operator+(Couleur color)
	{
		return Couleur{ m_rouge + color.m_rouge,m_vert + color.m_vert,m_bleu + color.m_bleu };
	}

	Couleur operator-(Couleur color)
	{
		return Couleur{ m_rouge - color.m_rouge,m_vert - color.m_vert,m_bleu - color.m_bleu };
	}

	Couleur operator*(float a)
	{
		return Couleur{ (int)a*m_rouge,(int)a*m_vert,(int)a*m_bleu };
	}

private:
	// uint8_t �quivalent � unsigned char :
	// unsigned 8 bits (8 bits non sign�)
	int m_rouge, m_vert, m_bleu;
	float m_alpha;
};

#endif // COULEUR_H_INCLUDED
