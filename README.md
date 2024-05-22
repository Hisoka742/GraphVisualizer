# GraphVisualizer
GraphVisualizer is a C++ program that generates visual representations of undirected graphs using the Fruchterman-Reingold algorithm.

Overview
This program takes a text file containing the description of an undirected graph as input and generates a graphical representation of the graph in BMP format.

Features
Supports undirected graphs with up to 500 vertices.
Uses the Fruchterman-Reingold algorithm for graph layout.
Produces graphical representations with minimal edge crossings.
Customizable vertex and edge size.
Usage
Clone the repository:

bash
Copy code
git clone https://github.com/Hisoka742/GraphVisualizer.git
Navigate to the project directory:

bash
Copy code
cd GraphVisualizer
Build the project:

go
Copy code
cmake .
make
Run the program:

css
Copy code
./GraphVisualizer input.txt
Replace input.txt with the path to your input file.

View the output:

The program will generate an output file named output.bmp in the current directory, containing the visual representation of the graph.

Input Format
The input file should contain the following format:

python
Copy code
V E
u v
u v
...
V is the number of vertices in the graph.
E is the number of edges in the graph.
Each subsequent line represents an edge between vertices u and v.
Dependencies
CMake
C++ compiler (supporting C++11)
License
This project is licensed under the MIT License.
