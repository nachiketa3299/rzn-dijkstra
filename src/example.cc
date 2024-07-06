#include <iostream>
#include <string>

#include "graph.h"

using namespace std;
using namespace rzn_dijkstra;

int main() {
	using graph_t = Graph<string, float>;
	using edge_t = graph_t::Edge;

	auto const nodes = std::vector<string> { 
		"A", "B", "C", "D", "E", "F", "G"
	};

	auto const edges = vector<edge_t> {
		{0, 1,  2.f}, {0, 2,  6.f}, 
		{2, 3,  8.f}, {1, 3,  5.f},
		{3, 4, 10.f}, {3, 5, 15.f},
		{4, 6,  2.f}, {5, 6,  6.f}
	};

	auto g = graph_t(nodes, edges, true);
	cout << "> Graph created:\n";
	cout << g;
	cout << "\n> Find shortest distances:\n";
	for (auto i = 0; i < nodes.size(); ++i) {
		cout << "\tBetween ";
		cout << "{[" << 0 << ", " << g.nodes[0] << "], ";
		cout << "[" << i << ", " << g.nodes[i] << "]}: ";
		cout << g.min_dist(0, i) << '\n';
	}
}
