#include "edge.h"

edge::edge(int _from, int _to) {
    from = _from;
    to = _to;
    weight = 0;
}

edge::edge(int _from, int _to, float _weight = 0) {
    from = _from;
    to = _to;
    weight = _weight;
}