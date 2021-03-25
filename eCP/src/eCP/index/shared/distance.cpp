#include <eCP/index/shared/distance.hpp>
#include <cmath>

/**
 * Distance functions defined for global use here. Can be imported and used
 * and will only be
 */
namespace distance {
/// Definition of global distance function, extern in header
float (*g_distance_function)(const float*, const float*, const float&);

inline float euclidean_distance_unroll_halt(const float* a, const float* b, const float& threshold) {
  float sum = 0;
  for (unsigned int i = 0; i < globals::g_vector_dimensions; i = i + 8) {
    sum += ((a[i] - b[i]) * (a[i] - b[i])) + ((a[i + 1] - b[i + 1]) * (a[i + 1] - b[i + 1])) + ((a[i + 2] - b[i + 2]) * (a[i + 2] - b[i + 2])) +
           ((a[i + 3] - b[i + 3]) * (a[i + 3] - b[i + 3])) + ((a[i + 4] - b[i + 4]) * (a[i + 4] - b[i + 4])) + ((a[i + 5] - b[i + 5]) * (a[i + 5] - b[i + 5])) +
           ((a[i + 6] - b[i + 6]) * (a[i + 6] - b[i + 6])) + ((a[i + 7] - b[i + 7]) * (a[i + 7] - b[i + 7]));

    if (sum > threshold) {
      return globals::FLOAT_MAX;
    }
  }
  return sum;
}

inline float euclidean_distance_unroll(const float* a, const float* b, const float& threshold = -1) {
  float sum = 0;
  for (unsigned int i = 0; i < globals::g_vector_dimensions; i = i + 8) {
    sum += ((a[i] - b[i]) * (a[i] - b[i])) + ((a[i + 1] - b[i + 1]) * (a[i + 1] - b[i + 1])) + ((a[i + 2] - b[i + 2]) * (a[i + 2] - b[i + 2])) +
           ((a[i + 3] - b[i + 3]) * (a[i + 3] - b[i + 3])) + ((a[i + 4] - b[i + 4]) * (a[i + 4] - b[i + 4])) + ((a[i + 5] - b[i + 5]) * (a[i + 5] - b[i + 5])) +
           ((a[i + 6] - b[i + 6]) * (a[i + 6] - b[i + 6])) + ((a[i + 7] - b[i + 7]) * (a[i + 7] - b[i + 7]));
  }
  return sum;
}

inline float euclidean_distance_halt(const float* a, const float* b, const float& threshold) {
  float sum = 0;
  for (unsigned int i = 0; i < globals::g_vector_dimensions; i++) {
    sum += (a[i] - b[i]) * (a[i] - b[i]);

    if (sum > threshold) {
      return globals::FLOAT_MAX;
    }
  }
  return sum;
}

inline float euclidean_distance(const float* a, const float* b, const float& threshold = -1) {
  float sums[] = {0.0, 0.0, 0.0, 0.0};
  for (unsigned int i = 0; i < globals::g_vector_dimensions; ++i) {
    float delta = a[i] - b[i];
    sums[i % 4] += delta * delta;
  }

  return sums[0] + sums[1] + sums[2] + sums[3];
}

inline float annoy_distance(const float* a, const float* b, const float& threshold = -1) {
  float d = 0.0;
  for (int i = 0; i < globals::g_vector_dimensions; ++i) {
    const float tmp=*a - *b;
    d += tmp * tmp;
    ++a;
    ++b;
  }
  return d;
}

Node* get_closest_node(std::vector<Node*>& nodes, float* query) {
  float closest = globals::FLOAT_MAX;
  Node* best = nullptr;

  for (Node* node : nodes) {
    const float distance = g_distance_function(query, node->points[0].descriptor, closest);

    if (distance <= closest) {
      closest = distance;
      best = node;
    }
  }
  return best;
}

inline float angular_distance(const float* a, const float* b, const float& max_distance = -1) {
  float mul = 0.0, d_a = 0.0, d_b = 0.0;

  for (unsigned int i = 0; i < globals::g_vector_dimensions; ++i) {
    mul += a[i] * b[i];
    d_a += a[i] * a[i];
    d_b += b[i] * b[i];
  }

  const float cosine_similarity = (mul / sqrt(d_a * d_b));

  return std::acos(cosine_similarity);
}

/**
 * Set the used distance function.
 */
void set_distance_function(Metrics func) {
  if (func == Metrics::EUCLIDEAN)             {g_distance_function = &euclidean_distance; std::cout << "EUCLIDEAN" << std::endl;}
  if (func == Metrics::EUCLIDEAN_UNROLL)      {g_distance_function = &euclidean_distance_unroll; std::cout << "EUCLIDEAN_UNROLL" << std::endl;}
  if (func == Metrics::EUCLIDEAN_HALT)        {g_distance_function = &euclidean_distance_halt; std::cout << "EUCLIDEAN_HALT" << std::endl;}
  if (func == Metrics::EUCLIDEAN_UNROLL_HALT) {g_distance_function = &euclidean_distance_unroll_halt; std::cout << "EUCLIDEAN_UNROLL_HALT" << std::endl;}
  if (func == Metrics::ANGULAR)               {g_distance_function = &angular_distance; std::cout << "ANGULAR" << std::endl;}
  if (func == Metrics::ANNOY_DISTANCE)        {g_distance_function = &annoy_distance; std::cout << "ANNOY_DISTANCE" << std::endl;}
}
}  // namespace distance
