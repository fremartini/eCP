#include <ittnotify.h>

#include <eCP/debugging/debug_tools.hpp>
#include <eCP/index/eCP.hpp>
#include <eCP/utilities/utilities.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
  /* For debugging params */
  int L = 2;           // L parameter - number of levels in index
  int metric = 1;      // Distance metric - 0 = euclidean - 1 = angular - 2 = euclidean early halt
  int k = 2;           // number points to return
  int b = 2;           // number clusters to search
  unsigned p = 1000;   // number of vectors
  const int d = 128;   // dimensions of vector
  const int r = 1000;  // upper bound of generated vectors
  const int qs = 15;   // queries to make on created index
  bool hdf5 = false;   // generate S and queries

  /* Setup ITTAPI instrumentation domain */
  __itt_domain* domain_build = __itt_domain_create("ECP.BENCHMARKING.BUILD");
  __itt_domain* domain_query = __itt_domain_create("ECP.BENCHMARKING.QUERY");
  __itt_string_handle* handle_build = __itt_string_handle_create("ecp_build");
  __itt_string_handle* handle_query = __itt_string_handle_create("ecp_query");

  /* Generate dummy data */
  std::vector<std::vector<float>> S;
  std::vector<std::vector<float>> queries;

  /* Handling of program arguments */
  if (argc > 1 && argc % 2 != 0) {
    for (int i = 1, j = 2; j != argc + 1; i += 2, j += 2) {
      std::string flag = argv[i];

      // hdf5 file
      if (flag == "-f") {
        std::cout << "Running with hdf5 file: " << argv[j] << std::endl;
        std::string file = std::string(argv[j]);
        std::string dataset = "train";
        S = utilities::load_hdf5_file(file, dataset);
        dataset = "test";
        queries = utilities::load_hdf5_file(file, dataset);
        p = S.size();
        hdf5 = true;
      }
      else if (flag == "-k") {
        k = atoi(argv[j]);
      }
      else if (flag == "-b") {
        b = atoi(argv[j]);
      }
      // distance metric
      else if (flag == "-m") {
        metric = atoi(argv[j]);
      }
      else if (flag == "-l") {
        L = atoi(argv[j]);
      }
      else {
        throw std::invalid_argument("Invalid flag: " + flag);
      }
    }
  }
  if (!hdf5) {
    std::cout << "Generating " << p << " descriptors with " << d << " dimensions and values up to " << r
              << std::endl;
    S = utilities::generate_descriptors(p, d, r);
    queries = utilities::generate_descriptors(qs, d, r);
  }

  /* Index build instrumentation */
  __itt_task_begin(domain_build, __itt_null, __itt_null, handle_build);
  Index* index = eCP::eCP_Index(S, L, metric);
  __itt_task_end(domain_build);

  /* Query instrumentation */
  __itt_task_begin(domain_query, __itt_null, __itt_null, handle_query);
  for (auto& q : queries) {
    auto result = eCP::query(index, q, k, b);
    //        debugging::print_query_results(result, q, k, S);   // debugging
  }
  __itt_task_end(domain_query);

  /* Debugging */
  // debugging::print_clusters(index->top_level);      // debugging
  // debugging::print_index_levels(index->top_level);  // debugging

  /* Clean up */
  delete index;
  std::cout << "eCP run OK with arguments: L = " << L << ", b = " << b << ", k = " << k
            << " metric = " << metric << "\n";
  std::cout << "dataset size: " << p << "\n";
  return 0;
}
