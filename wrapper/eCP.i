%module eCP_wrapper
%{
  #include "combined.hpp"
%}

%include "std_vector.i"
%include "std_pair.i"
namespace std {
   %template(UIntVector) std::vector<unsigned int>;
   %template(FloatVector) std::vector<float>;
   %template(FloatFloatVector) std::vector<std::vector<float>>;
   %template(PairVector) std::pair<std::vector<unsigned int>, std::vector<float>>;
   %template(FloatPointerVector) std::vector<float*>;
}

namespace eCP {
    Index* eCP_Index(const std::vector<std::vector<float>> descriptors, unsigned int L, unsigned int metric);
    std::pair<std::vector<unsigned int>, std::vector<float>> query(Index* index, std::vector<float> query, unsigned int k, unsigned int b);
}