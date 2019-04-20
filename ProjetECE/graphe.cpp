#include "graphe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <numeric>

graphe::graphe(std::string nomFichier, std::string nomFichier2, Svgfile *svgout)
{
	this->svgout = svgout;

	std::ifstream file{ nomFichier };
	int verticesNum, edgesNum;
	file >> verticesNum;

	int vertexId, edgeId;
	float x, y, weight;
	int vertex1, vertex2;

	for (int i = 0; i < verticesNum; i++)
	{
		file >> vertexId >> x >> y;
		vertices.push_back(Vertex{ x,y });
	}

	file >> edgesNum;

	for (int i = 0; i < edgesNum; i++)
	{
		file >> edgeId >> vertex1 >> vertex2;
		edges.push_back(Edge{ vertex1,vertex2 });
	}

	std::ifstream file2{ nomFichier2 };
	file2 >> edgesNum;
	file2 >> weightsNum;

	for (int i = 0; i < edgesNum; i++)
	{
		file2 >> edgeId;

		for (int j = 0; j < weightsNum; j++)
		{
			file2 >> weight;
			edges[i].weights.push_back(weight);
		}
	}
}

void graphe::afficher_graph()
{
	for (int i = 0; i < edges.size(); i++) //svg
	{
		svgout->addLine(vertices[edges[i].vertex1].x, vertices[edges[i].vertex1].y,
			vertices[edges[i].vertex2].x, vertices[edges[i].vertex2].y, Couleur{ 255,0,0 });
		if (vertices[edges[i].vertex1].x == vertices[edges[i].vertex2].x)
		{
			svgout->addText(vertices[edges[i].vertex1].x - 10, (vertices[edges[i].vertex1].y + vertices[edges[i].vertex2].y) / 2, edges[i].weights[0], Couleur{ 0,0,255 });
		}
		else if (vertices[edges[i].vertex1].y == vertices[edges[i].vertex2].y)
		{
			svgout->addText((vertices[edges[i].vertex1].x + vertices[edges[i].vertex2].x) / 2, vertices[edges[i].vertex1].y - 2, edges[i].weights[0], Couleur{ 0,0,255 });
		}
		else
		{
			svgout->addText((vertices[edges[i].vertex1].x + vertices[edges[i].vertex2].x) / 2 - 4,
				(vertices[edges[i].vertex1].y + vertices[edges[i].vertex2].y) / 2, edges[i].weights[0], Couleur{ 0,0,255 });
		}
	}
	for (int i = 0; i < vertices.size(); i++)
	{
		svgout->addDisk(vertices[i].x, vertices[i].y, 10, Couleur{ 0,0,0 });

		if (i < 10)
		{
			svgout->addText(vertices[i].x - 5, vertices[i].y + 5, i, Couleur{ 255,255,255 });
		}
		else
		{
			svgout->addText(vertices[i].x - 8, vertices[i].y + 5, i, Couleur{ 255,255,255 });
		}
	}

	std::cout << "Liste des sommets :\n" << std::endl;//console

	for (int i = 0; i < vertices.size(); i++)
	{
		std::cout << i << "   " << vertices[i].x << "   " << vertices[i].y << std::endl;
	}
	std::cout << "\n";
	std::cout << "Liste des aretes :\n" << std::endl;
	for (int i = 0; i < edges.size(); i++)
	{
		std::cout << i << "   " << edges[i].vertex1 << "   " << edges[i].vertex2 << "   " << "[";
		for (int j = 0; j < edges[i].weights.size(); j++)
		{
			if (j != 0)
			{
				std::cout << ",";
			}
			std::cout << edges[i].weights[j];
		}
		std::cout << "]" << std::endl;
	}
	std::cout << std::endl;
}

void graphe::Prim(int startId, int weightNum)
{
	std::vector<bool> visitedVertices(vertices.size(), false);
	std::vector<int> edgesToCheck;
	std::vector<float> OthersEdges(weightsNum, 0);

	int visitedCount = 0;
	int cursor = startId;
	float shortest = 0;
	int vert1;
	int vert2;


	std::cout << "Shortest way only by using Edge number " << weightNum + 1 << std::endl;

	while (visitedCount < vertices.size())
	{
		std::cout << "Visit vertex " << cursor << std::endl;
		visitedVertices[cursor] = true;
		visitedCount++;

		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].checkIfVertex(cursor))
			{
				edgesToCheck.push_back(i);
			}
		}

		auto newEnd = std::remove_if(edgesToCheck.begin(), edgesToCheck.end(), [this, visitedVertices](const int& edge)
		{
			return visitedVertices[this->edges[edge].vertex1] && visitedVertices[this->edges[edge].vertex2];
		});

		edgesToCheck.erase(newEnd, edgesToCheck.end());

		std::sort(edgesToCheck.begin(), edgesToCheck.end(), [this, weightNum](const int& edge1, const int& edge2)
		{
			return this->edges[edge1].weights[weightNum] < this->edges[edge2].weights[weightNum];
		});
		cursor = visitedVertices[edges[edgesToCheck[0]].vertex1] ? edges[edgesToCheck[0]].vertex2 : edges[edgesToCheck[0]].vertex1;

		vert1 = edges[edgesToCheck[0]].vertex1;
		vert2 = edges[edgesToCheck[0]].vertex2;

		svgout->addLine(vertices[vert1].x + 800 * (weightNum + 1), vertices[vert1].y,
			vertices[vert2].x + 800 * (weightNum + 1), vertices[vert2].y, Couleur{ 255,0,0 });

		if (vertices[vert1].x == vertices[vert2].x)
		{
			svgout->addText(vertices[vert1].x - 10 + 800, (vertices[vert1].y + vertices[vert2].y) / 2, edges[edgesToCheck[0]].weights[weightNum], Couleur{ 0,0,255 });
		}
		else if (vertices[vert1].y == vertices[vert2].y)
		{
			svgout->addText((vertices[vert1].x + vertices[vert2].x) / 2 + 800, vertices[vert1].y - 2, edges[edgesToCheck[0]].weights[weightNum], Couleur{ 0,0,255 });
		}
		else
		{
			svgout->addText((vertices[vert1].x + vertices[vert2].x) / 2 - 4 + 800,
				(vertices[vert1].y + vertices[vert2].y) / 2, edges[edgesToCheck[0]].weights[weightNum], Couleur{ 0,0,255 });
		}


		if (visitedCount != vertices.size() - 1)
		{
			for (int j = 0; j < weightsNum; j++)
			{
				OthersEdges[j] += edges[edgesToCheck[0]].weights[j];

			}
		}
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		svgout->addDisk(vertices[i].x + 800, vertices[i].y, 10, Couleur{ 0,0,0 });
		if (i < 10)
		{
			svgout->addText(vertices[i].x - 5 + 800, vertices[i].y + 5, i, Couleur{ 255,255,255 });
		}
		else
		{
			svgout->addText(vertices[i].x - 8 + 800, vertices[i].y + 5, i, Couleur{ 255,255,255 });
		}
	}

	for (int j = 0; j < weightsNum; j++)
	{
		std::cout << OthersEdges[j] << " ";
	}
	std::cout << std::endl;
}

unsigned int graphe::countSetBits(unsigned int n)
{
	unsigned int count = 0;
	while (n)
	{
		count += n & 1;
		n >>= 1;
	}
	return count;
}


std::vector<int> graphe::getAllNBitsNumbers(int N, int k)
{
	//std::string str;
	std::vector<bool> b;

	int j = N;
	while (j--)
	{
		b.push_back(j >= k ? false : true);
	}

	std::vector<int> result;

	do
	{
		result.push_back(std::accumulate(b.rbegin(), b.rend(), 0, [](int x, int y) { return (x << 1) + y; }));
		//result.push_back(std::stoi(str, nullptr, 2));
	} while (next_permutation(b.begin(), b.end()));

	return result;
}

void graphe::Pareto()
{
	//compteur binaire

	std::map<std::pair<float, float>, std::pair<bool, std::vector<std::vector<bool>>>> drawedDisk;
	//std::map<int, bool> betterEdges;

	int nb = 0;
	//int nbVertices
	svgout->addLine(50, 350, 50, 50, Couleur{ 0,0,0 });
	svgout->addLine(50, 350, 350, 350, Couleur{ 0,0,0 });

	for (int i = 0; i < 13; i++)
	{
		svgout->addLine(50 + 25 * i, 350, 50 + 25 * i, 50, Couleur{ 0,0,0,0.3f });
		svgout->addLine(50, 350 - 25 * i, 350, 350 - 25 * i, Couleur{ 0,0,0,0.3f });
	}


	//int lastPurcentage = 0;

	std::vector<int> h = getAllNBitsNumbers(edges.size(), vertices.size() - 1);

	std::vector<bool> edgesUsed(edges.size(), false);
	std::vector<bool> verticesUsed(vertices.size(), false);
	std::vector<float> weightWay(weightsNum, 0);

	std::queue<int> pointsToCheck;

	for (auto const &i : h)
	{
		/*
		int newPurcentage = (5.0f * i / pow(2.0, edges.size()));
		if (newPurcentage > lastPurcentage)
		{
			std::cout << newPurcentage * 5 << "%" << std::endl;
			lastPurcentage = newPurcentage;
		}*/

		edgesUsed.clear();
		edgesUsed.resize(edges.size(), false);

		verticesUsed.clear();
		verticesUsed.resize(vertices.size(), false);

		weightWay.clear();
		weightWay.resize(weightsNum, 0.0f);

		int n = i;

		for (int j = 0; j < edges.size(); j++)
		{
			if (n & 1)
			{
				edgesUsed[edges.size() - 1 - j] = n & 1;

				for (int k = 0; k < weightsNum; k++)
				{
					weightWay[k] += edges[edges.size() - 1 - j].weights[k];
				}
			}
			n >>= 1;
		}

		/*for (int j = (edges.size() - 1); j >= 0; j--)
		{
			if (((i & (1 << j)) >> j) == 1)
			{
				edgesUsed[edges.size() - 1 - j] = true;

				for (int k = 0; k < weightsNum; k++)
				{
					weightWay[k] += edges[edges.size() - 1 - j].weights[k];
				}
				//std::cout<<((i & (1 << j)) >> j);
			}
		}*/
		//std::cout<<std::endl;

		if (drawedDisk.count(std::pair<float, float>(weightWay[0], weightWay[1])))
		{
			if (drawedDisk[std::pair<float, float>(weightWay[0], weightWay[1])].first)
			{
				continue;
			}
		}

		pointsToCheck = std::queue<int>();
		pointsToCheck.push(0);

		int numberOfVertices = 0;

		do
		{
			int currentPoint = pointsToCheck.front();
			pointsToCheck.pop();
			if (verticesUsed[currentPoint])
			{
				continue;
			}
			verticesUsed[currentPoint] = true;
			numberOfVertices++;

			for (int j = 0; j < edges.size(); j++)
			{
				if (edgesUsed[j])
				{
					if ((edges[j].vertex1 == currentPoint) && (!verticesUsed[edges[j].vertex2]))
					{
						pointsToCheck.push(edges[j].vertex2);
					}
					if ((edges[j].vertex2 == currentPoint) && (!verticesUsed[edges[j].vertex1]))
					{
						pointsToCheck.push(edges[j].vertex1);
					}
				}
			}
		} while (pointsToCheck.size() > 0);

		if (numberOfVertices == vertices.size())
		{
			std::pair<float, float> key(weightWay[0], weightWay[1]);
			drawedDisk[key].second.push_back(edgesUsed);

			for (const auto &point2 : drawedDisk)
			{
				if (key == point2.first)
				{
					continue;
				}
				if (((key.first > point2.first.first) && (key.second >= point2.first.second)) || ((key.first >= point2.first.first) && (key.second > point2.first.second)))
				{
					drawedDisk[key].first = true;
				}
				if (((key.first < point2.first.first) && (key.second <= point2.first.second)) || ((key.first <= point2.first.first) && (key.second < point2.first.second)))
				{
					drawedDisk[point2.first].first = true;
				}
			}
		}
	}

	int countExtremum = 0;

	for (const auto &point : drawedDisk)
	{
		//nb++;
		//std::vector<int> edgesUsed(edges.size(), 0);

		if (!point.second.first)
		{
			//std::cout << point.first.first << "," << point.first.second;
			//std::cout << std::endl;
			svgout->addDisk(point.first.first * 2.5f + 50, -point.first.second * 2.5f + 350, 2, Couleur{ 0,255,0 });

			for (const auto &extremum : point.second.second)
			{
				for (int i = 0; i < extremum.size(); i++)
				{
					if (extremum[i])
					{
						//std::cout << edges[i].vertex1 << ";" << edges[i].vertex2 << std::endl;
						svgout->addLine(25 + 40 * (countExtremum % 5) * 4 + vertices[edges[i].vertex1].x*0.3f, 400 + 160 * (countExtremum / 5) + vertices[edges[i].vertex1].y*0.3f,
							25 + 40 * (countExtremum % 5) * 4 + vertices[edges[i].vertex2].x*0.3f, 400 + 160 * (countExtremum / 5) + vertices[edges[i].vertex2].y*0.3f, Couleur{ 0,0,0 });
					}
				}

				for (int i = 0; i < vertices.size(); i++)
				{
					svgout->addDisk(25 + 40 * (countExtremum % 5) * 4 + vertices[i].x*0.3f, 400 + 160 * (countExtremum / 5) + vertices[i].y*0.3f, 3, Couleur{ 0,0,0 });
					//svgout->addDisk(25 + 40 * countExtremum + vertices[i].x*0.3f, 600 + vertices[i].y*0.3f, 8, Couleur{ 0,0,0 });
					//svgout->addText(25 + 40 * countExtremum + vertices[i].x*0.3f - ((i > 9) ? 8 : 5), 600 + vertices[i].y*0.3f + 5, i, Couleur{ 255,255,255 });
				}

				svgout->addText(25 + 40 * (countExtremum % 5) * 4, 400 + 160 * (countExtremum / 5), "( " + std::to_string((int)point.first.first) + " , " + std::to_string((int)point.first.second) + " )", Couleur{ 50,50,50 });

				countExtremum++;
				//std::cout << std::endl;
			}
		}
		else
		{
			svgout->addDisk(point.first.first * 2.5f + 50, -point.first.second * 2.5f + 350, 1, Couleur{ 255,0,0 });
		}
	}
}


void graphe::generateSvg()
{

}

graphe::~graphe()
{
	//dtor
}
