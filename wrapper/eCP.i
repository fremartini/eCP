%module eCP_wrapper
// %{
//   #include "combined.hpp"
//   using namespace eCP;
//   using namespace distance;
//   using namespace global;
//   using namespace pre_processing;
//   using namespace query_processing;
// %}

// %include "std_vector.i"
// %include "std_pair.i"
// %include "typemaps.i"

// namespace std {
//    %template(UIntVector) std::vector<unsigned int>;
//    %template(FloatVector) std::vector<float>;
//    %template(FloatFloatVector) std::vector<std::vector<float>>;
//    %template(PairVector) std::pair<std::vector<unsigned int>, std::vector<float>>;
//    %template(FloatPointerVector) std::vector<float*>;
// }

// Index* eCP::eCP_Index(const std::vector<std::vector<float>> descriptors, unsigned int L, unsigned int metric);
// std::pair<std::vector<unsigned int>, std::vector<float>> eCP::query(Index* index, std::vector<float> query, unsigned int k, unsigned int b);

%{
#include "combined.hpp"
// using namespace eCP;
// using namespace distance;
// using namespace global;
// using namespace pre_processing;
// using namespace query_processing;
%}

%include "files_generated/combined.hpp"
 