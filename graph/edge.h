#pragma once

struct edge {
    int from;
    int to;
    float weight;   
public:
    edge(int _from, int _to);
    edge(int _from, int _to, float _weight); 
};
