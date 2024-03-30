#include "AdjacencyGraph.h"
#include <cassert>
#include <functional>

void test_error(std::function<void()> func){
    try {
        func();
    } catch (std::out_of_range& e) {
        std::cout << e.what() << "\n";
    }
}

int main(int argc, char const *argv[])
{
    // test if the graph is created correctly
    AdjacencyGraph* G = new AdjacencyGraph(10);
    G->addEdge(1, 2);
    G->addEdge(2, 3);
    G->addEdge(1, 5);
    int degree = G->vertexDegree(1);
    assert(degree == 2);

    degree = G->vertexDegree(8);
    std::cout << G->vertexDegree(8) << "\n";
    assert(degree == 0);

    G->printNeighbourIndices(1);
    bool is_edge = G->checkEdge(1, 2);
    assert(is_edge);
    std::cout << '\n' << (is_edge ? "true" : "false") <<"\n";
    
    G->removeEdge(1, 2);
    G->printNeighbourIndices(1);
    degree = G->vertexDegree(1);
    assert(degree == 1);

    is_edge = G->checkEdge(1, 2);
    assert(!is_edge);
    std::cout << '\n' << (is_edge ? "true" : "false") << "\n";
    
    // test if the graph respects bounds
    test_error([&](){G->addEdge(11, 2);});
    test_error([&](){G->addEdge(9, 11);});
    test_error([&](){G->checkEdge(9, 11);});
    test_error([&](){G->removeEdge(9, 11);});
    test_error([&](){G->vertexDegree(11);});
    test_error([&](){G->getNeighbourIndices(11);});
    test_error([&](){G->printNeighbourIndices(11);});
    //load graph from file
    G->readFromFile("GrafSmall.txt");
    G->printNeighbourIndices(1);
    degree = G->vertexDegree(1);
    assert(degree == 3);

    G->removeEdge(1, 2);
    degree = G->vertexDegree(1);
    assert(degree == 2);

    int nedges = G->getNumberOfEdges();
    assert(nedges == 8);

    return 0;
}
