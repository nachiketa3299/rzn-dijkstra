#pragma once

#include <vector>
#include <queue>
#include <string>
#include <numeric>
#include <algorithm>

namespace rzn_dijkstra {

/// @brief Simple graph structure implemented by adjacent list.
/// @details `struct` on purpose to easily modify
template <class T, class W>
struct Graph {
	static constexpr W INF = std::numeric_limits<W>::max();

	/// @brief Graph's adjacent list item's type.
	using adj_t = std::pair<W, std::size_t>;

	/// @brief Edge type for defining graph. 
	struct Edge {
		std::size_t f;
		std::size_t t;
		W w;
	};

	// Constructor
	Graph(
		std::vector<T> const& nodes, 
		std::vector<Edge> const& edges, 
		bool is_directed=false
	):
		adj_list(nodes.size(), std::vector<adj_t>()),
		nodes(nodes)
	{
		for (auto const& [f, t, w]: edges) {
			adj_list[f].push_back(adj_t{w, t});

			if(!is_directed) {
				adj_list[t].push_back(adj_t{w, f});
			}
		}
	}

	/**
	 * @brief Find shortest distance between \p start node to \p dest node,
	 * using Dijkstra's algorithm
	 */
	W min_dist(std::size_t start, std::size_t dest) {
		auto dists = std::vector<W>(nodes.size(), INF);

		auto to_visit = 
			std::priority_queue<adj_t, std::vector<adj_t>, std::greater<adj_t>>();

		dists[start] = 0; // Is 0 correct for various W types?
		to_visit.push(adj_t{dists[start], start});

		while (!to_visit.empty()) {
			auto const [dist, cv] = to_visit.top();
			to_visit.pop();

			if (cv == dest) {
				return dist;
			}

			for (auto const& [w, av]: adj_list[cv]) {
				auto const cdist = dists[cv] + w;

				if (cdist >= dists[av]) {
					continue;
				}

				dists[av] = cdist;
				to_visit.push(adj_t{cdist, av});
			}
		}

		return dists[dest];
	}

	std::vector<std::vector<adj_t>> adj_list;
	std::vector<T> nodes;

	friend std::ostream& operator<<(std::ostream& out, Graph const& rhs) {
		for (auto i = 0; i < rhs.nodes.size(); ++i) {
			out << "[" << i << ", " << rhs.nodes[i] << "]: ";

			for (auto j = 0; j < rhs.adj_list[i].size(); ++j) {
				auto const& [w, av] = rhs.adj_list[i][j];
				out << "(" << w << ", [" << av << ", " << rhs.nodes[av] << "])";

				if (j < rhs.adj_list[i].size() - 1) {
					out << ", ";
				}
			}

			out << '\n';
		}

		return out;
	}
};

} // namespace