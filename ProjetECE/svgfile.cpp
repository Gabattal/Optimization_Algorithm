#include "svgfile.h"
#include <iostream>
#include <sstream>

const std::string svgHeader =
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
	m_filename{ _filename }, m_width{ _width }, m_height{ _height }
{

	//std::cout << "Opening SVG output file : "
	//	<< m_filename << std::endl;

	if (s_openfiles.count(m_filename))
		throw std::runtime_error("File " + m_filename + " already open !");

	m_ostrm.open(m_filename);
	s_openfiles.insert(m_filename);

	if (!m_ostrm)
	{
		std::cout << "Problem opening " << m_filename << std::endl;
		throw std::runtime_error("Could not open file " + m_filename);
	}

	//std::cout << "OK" << std::endl;

	// Writing the header into the SVG file
	m_ostrm << svgHeader;
	m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
	// Writing the ending into the SVG file
	m_ostrm << svgEnding;

	// Removing this file from the list of open files
	s_openfiles.erase(m_filename);

	// No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
	std::ostringstream oss;
	oss << name << "=\"" << val << "\" ";
	return oss.str();
}

void Svgfile::addDisk(double x, double y, double r, std::string color)
{
	m_ostrm << "<circle "
		<< attrib("cx", x)
		<< attrib("cy", y)
		<< attrib("r", r)
		<< attrib("fill", color)
		<< "/>\n";
}

void Svgfile::addText(double x, double y, double number, std::string color)
{
	/// <text x="180" y="60">Un texte</text>
	m_ostrm << "<text "
		<< attrib("x", x)
		<< attrib("y", y)
		<< attrib("fill", color)
		<< ">" << number << "</text>\n";
}

void Svgfile::addText(double x, double y, std::string str, std::string color)
{
	/// <text x="180" y="60">Un texte</text>
	m_ostrm << "<text "
		<< attrib("x", x)
		<< attrib("y", y)
		<< attrib("fill", color)
		<< ">" << str << "</text>\n";
}
/*
void Svgfile::addText(double x, double y, std::string str, std::string color, int size)
{
	/// <text x="180" y="60">Un texte</text>
	m_ostrm << "<text "
		<< attrib("x", x)
		<< attrib("y", y)
		<< attrib("fill", color)
		<< attrib("font-size", std::to_string(size) + "px")
		<< ">" << str << "</text>\n";
}*/




void Svgfile::addLine(double x1, double y1, double x2, double y2, std::string color)
{
	m_ostrm << "<line "
		<< attrib("x1", x1)
		<< attrib("y1", y1)
		<< attrib("x2", x2)
		<< attrib("y2", y2)
		<< attrib("stroke", color)
		<< "/>\n";
}

void Svgfile::addGrid(double span, bool numbering, std::string color)
{
	double y = 0;
	while (y <= m_height / 2)
	{
		addLine(100, y, 100 + m_width / 2, y, color);
		addText(5 + 100, y - 5, y, color);
		y += span;
	}

	double x = 0;
	while (x <= m_width / 2)
	{
		addLine(x, 100, x, m_height / 2 + 100, color);
		addText(x + 5 + 100, 15, x, color);
		x += span;
	}
}

std::string Svgfile::makeRGB(int r, int g, int b, float a)
{
	std::ostringstream oss;
	oss << "rgba(" << r << "," << g << "," << b << "," << a << ")";
	return oss.str();
}
