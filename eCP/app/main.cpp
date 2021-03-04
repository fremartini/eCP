#include <iostream>
#include <ittnotify.h>

#include <eCP/eCP.hpp>
#include <utility.hpp>

int main()
{
    /* For vtune params */
    const int L = 3;           // L parameter - number of levels in index
    const int metric = 0;      // Distance metric - 0 = euclidean - 1 = angular
    const int k = 100;         // number points to return
    const int b = 40;          // number clusters to search
    const int p = 150000;      // number of vectors
    const int d = 128;         // dimensions of vector
    const int r = 1000;        // upper bound of generated vectors
    const int qs = 15000;      // queries to make on created index

    /* For debugging params */
//     const int L = 3;            // L parameter - number of levels in index
//     const int metric = 0;       // Distance metric - 0 = euclidean - 1 = angular
//     const int k = 2;            // number points to return
//     const int b = 2;            // number clusters to search
//     const int p = 12;           // number of vectors
//     const int d = 128;          // dimensions of vector
//     const int r = 10;         // upper bound of generated vectors
//     const int qs = 2;          // queries to make on created index

    /* Debugging prints */
     const bool debug = true;   // print debugging of index

    /* Setup ITTAPI instrumentation domain */
    __itt_domain *domain_build = __itt_domain_create("ECP.BENCHMARKING.BUILD");
    __itt_domain *domain_query = __itt_domain_create("ECP.BENCHMARKING.QUERY");
    __itt_string_handle *handle_build = __itt_string_handle_create("ecp_build");
    __itt_string_handle *handle_query = __itt_string_handle_create("ecp_query");

    /* Generate dummy data */
    std::vector<std::vector<float>> S = utility::generate_descriptors(p, d, r);
    std::vector<std::vector<float>> queries = utility::generate_descriptors(qs, d, r);

    /* Index build instrumentation */
    __itt_task_begin(domain_build, __itt_null, __itt_null, handle_build);
    Index *index = eCP::eCP_Index(S, L, metric);
    __itt_task_end(domain_build);


    /* Query instrumentation */
    std::vector<std::pair<std::vector<unsigned int>, std::vector<float>>> neighbors{};

    __itt_task_begin(domain_query, __itt_null, __itt_null, handle_query);
    for (auto& q : queries) {
        neighbors.emplace_back(eCP::query(index, q, k, b));
    }
    __itt_task_end(domain_query);

    /* Debugging */
     if (debug) {
         utility::print_clusters(index->top_level);
         utility::print_index_levels(index->top_level);
         // if (debug) { utility::print_query_results(result, q, k, index->dataset); }
     }

    std::cout << "eCP run OK.\n";
    std::cout << "dataset size: " << p << "\n";
    std::cout << "Program ended OK." << std::endl;

    /* Clean up */
    delete index;
    return 0;
}
