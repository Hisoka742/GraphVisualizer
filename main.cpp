#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include "fruchterman_reingold.h"

using namespace std;

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t bfType = 0x4D42; // 'BM'
    uint32_t bfSize;
    uint16_t bfReserved1 = 0;
    uint16_t bfReserved2 = 0;
    uint32_t bfOffBits = 54;
    uint32_t biSize = 40;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes = 1;
    uint16_t biBitCount = 24;
    uint32_t biCompression = 0;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter = 2835;
    int32_t biYPelsPerMeter = 2835;
    uint32_t biClrUsed = 0;
    uint32_t biClrImportant = 0;
};
#pragma pack(pop)


void saveBMP(const string& filename, int width, int height, const vector<uint8_t>& image) {
    BMPHeader header;
    header.bfSize = sizeof(BMPHeader) + image.size();
    header.biWidth = width;
    header.biHeight = height;
    header.biSizeImage = image.size();

    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        exit(1);
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(image.data()), image.size());
    file.close();
}

void drawCircle(vector<uint8_t>& image, int img_width, int img_height, int x0, int y0, int radius, uint8_t r, uint8_t g, uint8_t b) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int px = x0 + x;
                int py = y0 + y;
                if (px >= 0 && px < img_width && py >= 0 && py < img_height) {
                    int idx = 3 * (py * img_width + px);
                    image[idx] = r;
                    image[idx + 1] = g;
                    image[idx + 2] = b;
                }
            }
        }
    }
}

void drawLine(vector<uint8_t>& image, int img_width, int img_height, int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x1 >= 0 && x1 < img_width && y1 >= 0 && y1 < img_height) {
            int idx = 3 * (y1 * img_width + x1);
            image[idx] = r;
            image[idx + 1] = g;
            image[idx + 2] = b;
        }
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

void drawGraph(int V, int E, const vector<Edge>& edges, const vector<Vertex>& vertices, const string& filename) {
    const int img_width = 800;
    const int img_height = 800;
    vector<uint8_t> image(img_width * img_height * 3, 255);

    for (const auto& edge : edges) {
        int x1 = static_cast<int>(vertices[edge.u].x);
        int y1 = static_cast<int>(vertices[edge.u].y);
        int x2 = static_cast<int>(vertices[edge.v].x);
        int y2 = static_cast<int>(vertices[edge.v].y);
        drawLine(image, img_width, img_height, x1, y1, x2, y2, 0, 0, 0);
    }

    for (int i = 0; i < V; ++i) {
        int x = static_cast<int>(vertices[i].x);
        int y = static_cast<int>(vertices[i].y);
        drawCircle(image, img_width, img_height, x, y, 5, 0, 0, 0);
    }

    saveBMP(filename, img_width, img_height, image);
}

void readGraph(const string& filename, int& V, int& E, vector<Edge>& edges) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        exit(1);
    }
    file >> V >> E;
    edges.resize(E);
    for (int i = 0; i < E; ++i) {
        file >> edges[i].u >> edges[i].v;
    }
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input.txt>" << endl;
        return 1;
    }

    string filename = argv[1];
    int V, E;
    vector<Edge> edges;
    readGraph(filename, V, E, edges);

    vector<Vertex> vertices(V);
    fruchtermanReingold(V, E, edges, vertices, 800, 800);

    drawGraph(V, E, edges, vertices, "graph.bmp");

    return 0;
}
