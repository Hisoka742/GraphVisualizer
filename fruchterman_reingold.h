#ifndef FRUCHTERMAN_REINGOLD_H
#define FRUCHTERMAN_REINGOLD_H

#include <vector>

struct Edge {
    int u, v;
};

struct Vertex {
    double x, y;
};

void fruchtermanReingold(int V, int E, const std::vector<Edge>& edges, std::vector<Vertex>& vertices, int width, int height, int iterations = 500);

#endif // FRUCHTERMAN_REINGOLD_H

