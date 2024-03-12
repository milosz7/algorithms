#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int size) {
    _size = size; 
    initMatrix(); 
}

MatrixGraph::~MatrixGraph() {
    deallocateMatrix();
}

void MatrixGraph::assertCorrectIndex(int idx) {
    if (idx < 0 || idx >= _size)
        throw std::out_of_range("Index out of bounds!");
}

void MatrixGraph::addEdge(int from, int to) {
    assertCorrectIndex(from);
    assertCorrectIndex(to);
    matrix[from][to] = true;
}

void MatrixGraph::removeEdge(int from, int to) {
    assertCorrectIndex(from);
    assertCorrectIndex(to);
    
    if (checkEdge(from, to))
        matrix[from][to] = false;
    else
        std::cout << "Edge: (" << from << "," << to <<") not found!\n";
}

bool MatrixGraph::checkEdge(int from , int to) {
    assertCorrectIndex(from);
    assertCorrectIndex(to);

    return matrix[from][to];
}

int MatrixGraph::vertexDegree(int idx) {
    assertCorrectIndex(idx);

    int count = 0;
    bool* row = matrix[idx];
    for (int i = 0; i < _size; i++)
        if (row[i]) count++;
    return count;
}

std::vector<int> MatrixGraph::getNeighbourIndices(int idx) {
    assertCorrectIndex(idx);

    std::vector<int> neighbours;
    bool* row = matrix[idx];
    for (int i = 0; i < _size; i++)
        if (row[i]) neighbours.push_back(i);
    return neighbours;
}

void MatrixGraph::printNeighbourIndices(int idx) {
    assertCorrectIndex(idx);

    std::vector<int> neighbours = getNeighbourIndices(idx);
    std::cout << "[ ";
    for (int neighbour : neighbours)
        std::cout << "(" << idx << ", " << neighbour << ") ";
    std::cout << "]";
}

int MatrixGraph::getNumberOfEdges() {
    int count = 0;
    for (int i = 0; i < _size; i++)
        for (int j = 0; j < _size; j++)
            if (checkEdge(i,j))
                count++;
    return count;
}

void MatrixGraph::readFromFile(std::string path) {
    std::ifstream file{path};
    if (!file.is_open()) {
        std::cerr << "File: " << path << " not found!\n";
        exit(1);
    }
    int size;
    deallocateMatrix();
    file >> size;
    _size = size;
    initMatrix();
    do {
        int from, to;
        file >> from >> to;
        addEdge(from, to);
    } while (file.peek() != EOF);
    file.close();
}

void MatrixGraph::clear() {
    for (int i = 0; i < _size; i++)
        for (int j = 0; j < _size; j++)
            matrix[i][j] = false;
}

void MatrixGraph::resize(int size) {
    deallocateMatrix();
    _size = size;
    initMatrix();
}

void MatrixGraph::initMatrix() {
    matrix = new bool*[_size];
    for (int i = 0; i < _size; i++)
        matrix[i] = new bool[_size];
}

void MatrixGraph::deallocateMatrix() {
    for (int i = 0; i < _size; i++)
        delete[] matrix[i];
    delete[] matrix;
}