#include "AdjacencyGraph.h"

AdjacencyGraph::AdjacencyGraph(int size) {
    vertexList = std::vector<std::vector<edge>>(size);
}

void AdjacencyGraph::addEdge(int from, int to) {
    if (!checkEdge(from, to))
        vertexList.at(from).push_back(edge(from, to));
    else
        std::cerr << "Edge: (" << from << ", " << to << ") already present!\n";
}

bool AdjacencyGraph::removeEdge(int from, int to) {
    assertCorrectIndex(from);
    assertCorrectIndex(to);

    bool removed = false;
    std::vector<edge> *list = &vertexList[from];

    for (auto it = list->begin(); it != list->end(); it++) {
        edge _edge = *it;
        if (_edge.to == to) {
            list->erase(it);
            removed = true;
            break;
        } 
    }
    return removed;
}

bool AdjacencyGraph::checkEdge(int from, int to) {
    assertCorrectIndex(from);
    assertCorrectIndex(to);

    std::vector<edge> list = vertexList[from];
    for (auto it = list.begin(); it != list.end(); it++) {
        edge _edge = *it;
        if (_edge.to == to)
            return true;
    }
    return false;
}

int AdjacencyGraph::vertexDegree(int idx) {
    assertCorrectIndex(idx);
    return (&vertexList[idx])->size();
}

std::vector<int> AdjacencyGraph::getNeighbourIndices(int idx) {
    assertCorrectIndex(idx);
    auto adjacent = std::vector<int>();
    std::vector<edge> list = vertexList[idx];
    for (edge _edge : list)
        adjacent.push_back(_edge.to);
    return adjacent;
}

void AdjacencyGraph::printNeighbourIndices(int idx) {
    std::vector<int> adjacent = getNeighbourIndices(idx);
    std::cout << "[ ";
    for (int adj : adjacent)
        std::cout << "(" << idx << ", " << adj << "), ";
    std::cout << "]";
}

void AdjacencyGraph::readFromFile(std::string path) {
    std::ifstream file{path};
    if (!file.is_open()) {
        std::cerr << "File: " << path << " not found!\n";
        exit(1);
    }
    int size;
    file >> size;
    vertexList.clear();
    vertexList.resize(size);
    do {
        int from, to;
        file >> from >> to;
        addEdge(from, to);
    } while (file.peek() != EOF);
    file.close();
}   

int AdjacencyGraph::getNumberOfEdges() {
    int count = 0;
    for (auto list : vertexList)
        count += list.size();
    return count;
}

void AdjacencyGraph::assertCorrectIndex(int idx) {
    if (idx < 0 || idx >= vertexList.size())
        throw std::out_of_range("Index out of range!");
}