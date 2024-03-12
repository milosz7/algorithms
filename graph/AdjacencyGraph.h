#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "edge.h"


class AdjacencyGraph
{
    std::vector<std::vector<edge>> vertexList;

public:
    AdjacencyGraph(int size);
    void addEdge(int from, int to);    
    bool removeEdge(int from, int to);
    bool checkEdge(int from, int to);
    int vertexDegree(int idx); 
    std::vector<int> getNeighbourIndices(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    void readFromFile(std::string path); 
private:
    void assertCorrectIndex(int idx);
};

