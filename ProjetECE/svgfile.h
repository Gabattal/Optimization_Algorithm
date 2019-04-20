#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include <string>
#include <fstream>
#include <set>
#include <vector>

constexpr char defcol[] = "black";

/*struct Pos
{
	double x;
	double y;

	Pos operator+(Pos pos)
	{
		return Pos{x+pos.x, y+pos.y};
	}

	Pos operator-(Pos pos)
	{
		return Pos{x-pos.x, y-pos.y};
	}

	Pos operator*(float mult)
	{
		return Pos{mult*x, mult*y};
	}

	Pos operator*(Pos pos)
	{
		return Pos{pos.x*x, pos.y*y};
	}

	Pos operator/(float divide)
	{
		return Pos{x/divide, y/divide};
	}
};*/

class Svgfile
{
public:
	Svgfile(std::string _filename = "output.svg", int _width = 1900, int _height = 1140);
	~Svgfile();

	void addDisk(double x, double y, double r, std::string color = defcol);
	void addLine(double x1, double y1, double x2, double y2, std::string color = defcol);
	void addText(double x, double y, double number, std::string color = defcol);
	void addText(double x, double y, std::string str, std::string color = defcol);
	void addGrid(double span, bool numbering, std::string color);


	static std::string makeRGB(int r, int g, int b, float a);

	/// Type non copiable
	Svgfile(const Svgfile&) = delete;
	Svgfile& operator=(const Svgfile&) = delete;

private:
	std::string m_filename;
	std::ofstream m_ostrm;
	int m_width;
	int m_height;

	// Pour éviter les ouverture multiples
	static std::set<std::string> s_openfiles;
};

#endif // SVGFILE_H_INCLUDED
