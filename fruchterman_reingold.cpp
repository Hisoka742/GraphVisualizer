#include "fruchterman_reingold.h"
#include <cmath>
#include <random>
#include <algorithm>

void fruchtermanReingold(int V, int E, const std::vector<Edge>& edges, std::vector<Vertex>& vertices, int width, int height, int iterations) {
    double area = width * height;
    double k = std::sqrt(area / V);
    std::vector<double> dx(V, 0);
    std::vector<double> dy(V, 0);

    double t = width / 10.0;
    double dt = t / (iterations + 1);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    for (int i = 0; i < V; ++i) {
        vertices[i].x = dis(gen) * width;
        vertices[i].y = dis(gen) * height;
    }

    auto repulsiveForce = [&](double d) { return (k * k) / d; };
    auto attractiveForce = [&](double d) { return (d * d) / k; };

    for (int iter = 0; iter < iterations; ++iter) {
        std::fill(dx.begin(), dx.end(), 0);
        std::fill(dy.begin(), dy.end(), 0);

        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                double dx_ = vertices[i].x - vertices[j].x;
                double dy_ = vertices[i].y - vertices[j].y;
                double dist = std::sqrt(dx_ * dx_ + dy_ * dy_);
                if (dist > 0) {
                    double f = repulsiveForce(dist);
                    dx[i] += (dx_ / dist) * f;
                    dy[i] += (dy_ / dist) * f;
                    dx[j] -= (dx_ / dist) * f;
                    dy[j] -= (dy_ / dist) * f;
                }
            }
        }

        for (const auto& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            double dx_ = vertices[u].x - vertices[v].x;
            double dy_ = vertices[u].y - vertices[v].y;
            double dist = std::sqrt(dx_ * dx_ + dy_ * dy_);
            if (dist > 0) {
                double f = attractiveForce(dist);
                dx[u] -= (dx_ / dist) * f;
                dy[u] -= (dy_ / dist) * f;
                dx[v] += (dx_ / dist) * f;
                dy[v] += (dy_ / dist) * f;
            }
        }

        for (int i = 0; i < V; ++i) {
            vertices[i].x += dx[i] * t;
            vertices[i].y += dy[i] * t;
            vertices[i].x = std::min(width - 1.0, std::max(0.0, vertices[i].x));
            vertices[i].y = std::min(height - 1.0, std::max(0.0, vertices[i].y));
        }

        t -= dt;
    }
}

