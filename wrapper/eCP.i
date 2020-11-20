%module eCP_wrapper
%{
  #include "combined.hpp"
%}
// %include "std_vector.i"
// %include "std_pair.i"
// namespace std {
//    %template(UIntVector) std::vector<unsigned int>;
//    %template(FloatVector) std::vector<float>;
//    %template(FloatFloatVector) std::vector<std::vector<float>>;
//    %template(PairVector) std::pair<std::vector<unsigned int>, std::vector<float>>;
//    %template(FloatPointerVector) std::vector<float*>;
// }
// float euclidean_distance(const float* a, const float* b);
// float angular_distance(const float* a, const float* b);
// void set_distance_function(Metrics func);

Index* eCP::eCP_Index(const std::vector<std::vector<float>> descriptors, unsigned int L, unsigned int metric);
std::pair<std::vector<unsigned int>, std::vector<float>> eCP::query(Index* index, std::vector<float> query, unsigned int k, unsigned int b);

// std::vector<Node*> create_index(std::vector<Point>& dataset, unsigned int L);
// std::vector<Node*> insert_points(std::vector<Node*>& index_top_level, std::vector<Point>& points, unsigned int from_index);
// Node* find_nearest_node(std::vector<Node*>& nodes, float*& query);
// Node* find_nearest_leaf_from_level(float*& query, Node*& node, unsigned int depth);
// Node* find_nearest_leaf(float*& query, std::vector<Node*>& nodes);
// std::vector<Node*> find_b_nearest_clusters(std::vector<Node*>& root, float*& query, unsigned int b, unsigned int L);
// void scan_node(float*& query, std::vector<Node*>& nodes, unsigned int& b, std::vector<Node*>& nodes_accumulated);
// std::pair<int, float> find_furthest_node(float*& query, std::vector<Node*>& nodes);
// void scan_leaf_node(float*& query, std::vector<Point>& points, const unsigned int k, std::vector<std::pair<unsigned int, float>>& nearest_points);
// unsigned int index_to_max_element(std::vector<std::pair<unsigned int, float>>& point_pairs);
// bool smallest_distance(std::pair<unsigned int, float>& a, std::pair<unsigned int, float>& b);
