%module eCP_wrapper
%{
#include "../include/eCP/index/eCP.hpp"
#include "../src/eCP/index/shared/data_structure.hpp"
%}

%include std_vector.i
%include std_pair.i
%include typemaps.i

namespace std {
  %template(UIntVector) std::vector<unsigned int>;
  %template(FloatVector) std::vector<float>;
  %template(FloatFloatVector) std::vector<std::vector<float>>;
  %template(PairVector) std::pair<std::vector<unsigned int>, std::vector<float>>;
  %template(FloatPointerVector) std::vector<float*>;
}

%include "../include/eCP/index/eCP.hpp"
%include "../src/eCP/index/shared/data_structure.hpp"

// This can line can be tried next if there still seems to be a leak
//%typemap(newfree) Index * "free($1);";

%newobject eCP::eCP_Index;

namespace eCP {
  Index* eCP::eCP_Index(const std::vector<std::vector<float>> &descriptors, unsigned int L, unsigned int metric);
  std::pair<std::vector<unsigned int>, std::vector<float>> eCP::query(Index* index, std::vector<float> query, unsigned int k, unsigned int b);
}
