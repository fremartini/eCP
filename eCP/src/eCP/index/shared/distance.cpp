#include <cmath>
#include <eCP/index/shared/distance.hpp>

namespace distance {

/// Definition of global distance function, extern in header
float (*g_distance_function)(const float*, const float*, const float&);

inline float euclidean_distance_unroll_halt(const float* a, const float* b, const float& threshold)
{
  float sum = 0;
  for (unsigned int i = 0; i < globals::g_vector_dimensions; i = i + 8) {
    sum += ((a[i] - b[i]) * (a[i] - b[i])) + ((a[i + 1] - b[i + 1]) * (a[i + 1] - b[i + 1])) +
           ((a[i + 2] - b[i + 2]) * (a[i + 2] - b[i + 2])) + ((a[i + 3] - b[i + 3]) * (a[i + 3] - b[i + 3])) +
           ((a[i + 4] - b[i + 4]) * (a[i + 4] - b[i + 4])) + ((a[i + 5] - b[i + 5]) * (a[i + 5] - b[i + 5])) +
           ((a[i + 6] - b[i + 6]) * (a[i + 6] - b[i + 6])) + ((a[i + 7] - b[i + 7]) * (a[i + 7] - b[i + 7]));

    if (sum > threshold) {
      return globals::FLOAT_MAX;
    }
  }
  return sum;
}

inline float euclidean_distance_unroll(const float* a, const float* b, const float& threshold = -1)
{
  float sum = 0;
  for (unsigned int i = 0; i < globals::g_vector_dimensions; i = i + 8) {
    sum += ((a[i] - b[i]) * (a[i] - b[i])) + ((a[i + 1] - b[i + 1]) * (a[i + 1] - b[i + 1])) +
           ((a[i + 2] - b[i + 2]) * (a[i + 2] - b[i + 2])) + ((a[i + 3] - b[i + 3]) * (a[i + 3] - b[i + 3])) +
           ((a[i + 4] - b[i + 4]) * (a[i + 4] - b[i + 4])) + ((a[i + 5] - b[i + 5]) * (a[i + 5] - b[i + 5])) +
           ((a[i + 6] - b[i + 6]) * (a[i + 6] - b[i + 6])) + ((a[i + 7] - b[i + 7]) * (a[i + 7] - b[i + 7]));
  }
  return sum;
}

inline float euclidean_distance_halt(const float* a, const float* b, const float& threshold)
{
  float sum = 0;
  for (unsigned int i = 0; i < globals::g_vector_dimensions; i++) {
    sum += (a[i] - b[i]) * (a[i] - b[i]);

    if (sum > threshold) {
      return globals::FLOAT_MAX;
    }
  }
  return sum;
}

inline float euclidean_distance(const float* a, const float* b, const float& threshold = -1)
{
  float sums[] = {0.0, 0.0, 0.0, 0.0};
  for (unsigned int i = 0; i < globals::g_vector_dimensions; ++i) {
    float delta = a[i] - b[i];
    sums[i % 4] += delta * delta;
  }

  return sums[0] + sums[1] + sums[2] + sums[3];
}

inline float angular_distance(const float* a, const float* b, const float& max_distance = -1)
{
  float mul = 0.0, d_a = 0.0, d_b = 0.0;

  for (unsigned int i = 0; i < globals::g_vector_dimensions; ++i) {
    mul += a[i] * b[i];
    d_a += a[i] * a[i];
    d_b += b[i] * b[i];
  }

  const float cosine_similarity = (mul / sqrt(d_a * d_b));

  return std::acos(cosine_similarity);
}

void set_distance_function(Metric metric)
{
  auto is_dimensionality_divisable_by_8 = ((globals::g_vector_dimensions % 8) == 0) ? true : false;

  switch (metric) {
    case Metric::EUCLIDEAN_OPT_UNROLL:
      if (is_dimensionality_divisable_by_8) {
        g_distance_function = &euclidean_distance_unroll;
      }
      else {
        g_distance_function = &euclidean_distance;
      }
      break;

    case Metric::ANGULAR:
      g_distance_function = &angular_distance;
      break;

    case Metric::EUCLIDEAN_HALT_OPT_UNROLL:
      if (is_dimensionality_divisable_by_8) {
        g_distance_function = &euclidean_distance_unroll_halt;
      }
      else {
        g_distance_function = &euclidean_distance_halt;
      }
      break;

    default:
      throw std::invalid_argument("Invalid metric.");
  }
}

}  // namespace distance
