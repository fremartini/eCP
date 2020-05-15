#include <iostream>

#include "../eCP/eCP.hpp"
#include "utility.hpp"

int main()
{
	const int l = 2;		//L parameter - number of levels in index
	const int metric = 0;	//Distance metric - 0 = euclidean - 1 = angular
	const int k = 100;		//# points to return
	const int b = 40;		//# clusters to search
	const int p = 60000;	//# of vectors
	const int d = 3;		//dimensions of vector
	const int r = 100;		//upper bound of generated vectors
	const bool debug = false;

	std::vector<std::vector<float>> S = generate_descriptors(p, d, r);
	std::vector<float> q = S[0];

	Index* index = eCP_Index(S, l, metric);

	if (debug)
	{
		print_clusters(index->top_level);
		//print_index_levels(index->top_level);
	}

	auto result = query(index, q, k, b);

	print_query_results(result, q, k, index->dataset);

	//done with querying, the index should now be cleared to prevent leaks
	delete index;
	return 0;
}