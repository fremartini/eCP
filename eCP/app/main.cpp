#include <iostream>
#include <ittnotify.h>

#include <eCP/eCP.hpp>
#include <utility.hpp>

int main()
{
    /* time ~20 sec */
    const int L = 2;      //L parameter - number of levels in index
    const int metric = 0; //Distance metric - 0 = euclidean - 1 = angular
    const int k = 100;    //# points to return
    const int b = 40;     //# clusters to search
    const int p = 200000; //# of vectors
    const int d = 128;    //dimensions of vector
    const int r = 10000;  //upper bound of generated vectors
    const bool debug = false;

    /* time ~2 sec */
    // const int L = 2;    	//L parameter - number of levels in index
    // const int metric = 0;	//Distance metric - 0 = euclidean - 1 = angular
    // const int k = 1;		//# points to return
    // const int b = 1;		//# clusters to search
    // const int p = 6;	    //# of vectors
    // const int d = 3;		//dimensions of vector
    // const int r = 100;		//upper bound of generated vectors
    // const bool debug = true;

    /* Setup ITTAPI instrumentation domain */
    __itt_domain *domain_build = __itt_domain_create("ECP.BENCHMARKING.BUILD");
    __itt_domain *domain_query = __itt_domain_create("ECP.BENCHMARKING.QUERY");
    __itt_string_handle *handle_build = __itt_string_handle_create("ecp_build");
    __itt_string_handle *handle_query = __itt_string_handle_create("ecp_query");

    /* Generate dummy data */
    std::vector<std::vector<float>> S = generate_descriptors(p, d, r);
    // std::vector<float> q = S[0];

    /* Index build instrumentation */
    __itt_task_begin(domain_build, __itt_null, __itt_null, handle_build);
    Index *index = eCP_Index(S, L, metric);
    __itt_task_end(domain_build);

    /* Query instrumentation */
    __itt_task_begin(domain_query, __itt_null, __itt_null, handle_query);
    for (int i = 0; i < p / 10; ++i) {
        auto result = query(index, S[i], k, b);
    }
    __itt_task_end(domain_query);

    /* Debugging */
    // if (debug) {
    //     print_clusters(index->top_level);
    //     print_index_levels(index->top_level);
    // }
    // print_query_results(result, q, k, index->dataset);

    delete index;
    std::cout << "eCP run done.\n";
    return 0;
}