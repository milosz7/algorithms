#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "edge.h"


class MatrixGraph {
    bool** matrix;
    unsigned _size;
    int numberOfVertices;

public:
    MatrixGraph(int size);
    ~MatrixGraph();
    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);    
    void removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    int vertexDegree(int idx); 
    std::vector<int> getNeighbourIndices(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    void readFromFile(std::string path); 

private:
    void assertCorrectIndex(int idx);
    void clear();
    void resize(int size);
    void initMatrix();
    void deallocateMatrix();
};

