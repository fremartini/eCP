#include <queue>
#include <cmath>
#include <iostream>

#include <eCP/debugging/debug_tools.hpp>
#include <eCP/index/shared/globals.hpp>

namespace debugging {

void print_query_results(std::pair<std::vector<unsigned int>, std::vector<float>>& result, std::vector<float>& query, unsigned int k, const std::vector<Point>& S)
{
	std::cout << "k = " << k << "\nQuery: ";

	//Print query
	auto* q = new float[globals::g_vector_dimensions];
	for (unsigned int i = 0; i < globals::g_vector_dimensions; i++) {
		q[i] = query[i];
	}
	Point pq = Point(q, -1);    // TODO: Misuse of unsigned int

	print_point(pq);

	std::cout << "\n\nresult from " << S.size() << " points\n";

	//Print results
	for (unsigned int i = 0; i < result.first.size(); ++i)
	{
		unsigned int id = result.first[i];
		Point p = S[id];
		print_point(p);
		std::cout << ", " << result.second[i] << "\n";
	}
  std::cout << "\nreturned " << result.first.size() << " points, wanted " << k << std::endl;
	delete[] q;
}

void print_point(Point& p)
{
	std::cout << "[";
	auto desc = p.descriptor;
	for (unsigned int i = 0; i < globals::g_vector_dimensions; i++) {
		std::cout << desc[i];

		if (i != globals::g_vector_dimensions - 1) {
			std::cout << ' ';
		}
	}
	std::cout << "]";
}

void print_points(std::vector<Point>& points)
{
	for (Point& i : points) {
		print_point(i);
		std::cout << "\n";
	}
}

bool is_leaf(Node& node) 
{
    return node.children.empty();
}

void print_cluster(Node& c, const unsigned int d)
{
	if (globals::g_vector_dimensions < 5)
	{
		auto p = Point(c.points[0].descriptor, -1);
		print_point(p);
	}

	if (is_leaf(c)) {
		std::cout << " {";

		if (globals::g_vector_dimensions < 5) {
			for (Point& p : c.points) {
				print_point(p);
			}
		}
		else {
			std::cout << c.points.size() << " points";
		}

		std::cout << "}";
	}

	std::cout << "\n";

  for (Node& i : c.children) {
		auto space = std::string(d * 4, ' ');
    if (!is_leaf(i))
		{
			std::cout << space << "C";
		}
		else
		{
			std::cout << space << "L";
		}

    print_cluster(i, d + 1);
	}
}

void print_clusters(std::vector<Node>& clusters)
{
  for (Node& i : clusters) {
		std::cout << "R";
    print_cluster(i, 1);
	}

	std::cout << "--------------\n";
}

/**
 * Levels prints for small levels sizes
 * @param root Top level of index
 */
void print_index_levels(std::vector<Node>& root)
{
	// Standard level order traversal code
	// using queue
  std::queue<Node> q;  // Create a queue
	// Enqueue top_level
  for (auto &cluster : root)
	{
		q.push(cluster);
	}

	while (!q.empty())
	{
		int n = q.size();

		// If this node has children
		while (n > 0)
		{
			// Dequeue an item from queue and print it
      Node node = q.front();
			q.pop();

      if (is_leaf(node))
			{
        std::cout << " [L: " << node.points.size() << " ]";
			}
			else
        std::cout << " [N: " << node.children.size() << "] ";

			// Enqueue all children of the dequeued item
      for (unsigned int i = 0; i < node.children.size(); i++)
        q.push(node.children[i]);
			n--;
		}

		std::cout << "\n"; // Print new line between two levels
	}
	std::cout << "--------------\n";
}

}
