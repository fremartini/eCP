#include <cmath>
#include <eCP/index/shared/distance.hpp>
#include <eCP/index/shared/globals.hpp>

/**
 * Distance functions defined for global use here. Can be imported and used
 * and will only be
 */
namespace distance
{
// Definition of global distance function, extern in header
float (*g_distance_function)(const float*, const float*);

inline float euclidean_distance(const float* a, const float* b)
{
  float sums[] = {0.0, 0.0, 0.0, 0.0};
  for (unsigned int i = 0; i < globals::g_vector_dimensions; ++i)
  {
    float delta = a[i] - b[i];
    sums[i % 4] += delta * delta;
  }

  return sums[0] + sums[1] + sums[2] + sums[3];
}

// Assumes the given vector of nodes is not empty
Node* get_closest_node(std::vector<Node>& nodes, float* query)
{
  float max = globals::FLOAT_MAX;
  Node* closest = nullptr;

  for (Node& node : nodes) {
    const float distance = g_distance_function(query, node.points[0].descriptor);

    if (distance < max) {
      max = distance;
      closest = &node;
    }
  }
  return closest;
}

inline float angular_distance(const float* a, const float* b)
{
  float mul = 0.0, d_a = 0.0, d_b = 0.0;

  for (unsigned int i = 0; i < globals::g_vector_dimensions; ++i)
  {
    mul += a[i] * b[i];
    d_a += a[i] * a[i];
    d_b += b[i] * b[i];
  }

  const float cosine_similarity = (mul / sqrt(d_a * d_b));

  return acos(cosine_similarity);
}

/**
    * Set the used distance function.
    */
void set_distance_function(Metrics func)
{
  if (func == Metrics::EUCLIDEAN) g_distance_function = &euclidean_distance;
  if (func == Metrics::ANGULAR) g_distance_function = &angular_distance;
  std::invalid_argument("Invalid metric.");
}

}
