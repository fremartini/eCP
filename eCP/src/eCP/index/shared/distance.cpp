#include <cmath>
#include <eCP/index/shared/distance.hpp>

namespace distance {

/// Definition of global distance function, extern in header
float (*g_distance_function)(const float*, const float*, const float&);

inline float euclidean_distance_unroll_halt(const float* a, const float* b, const float& threshold)
{
  globals::DIST_CALCULATIONS++;
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
  globals::DIST_CALCULATIONS++;
  float sums[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  for (unsigned int i = 0; i < globals::g_vector_dimensions; i = i + 16) {
    sums[0] += (a[i] - b[i]) * (a[i] - b[i]);
    sums[1] += (a[i + 1] - b[i + 1]) * (a[i + 1] - b[i + 1]);
    sums[2] += (a[i + 2] - b[i + 2]) * (a[i + 2] - b[i + 2]);
    sums[3] += (a[i + 3] - b[i + 3]) * (a[i + 3] - b[i + 3]);
    sums[4] += (a[i + 4] - b[i + 4]) * (a[i + 4] - b[i + 4]);
    sums[5] += (a[i + 5] - b[i + 5]) * (a[i + 5] - b[i + 5]);
    sums[6] += (a[i + 6] - b[i + 6]) * (a[i + 6] - b[i + 6]);
    sums[7] += (a[i + 7] - b[i + 7]) * (a[i + 7] - b[i + 7]);
    sums[8] += (a[i + 8] - b[i + 8]) * (a[i + 8] - b[i + 8]);
    sums[9] += (a[i + 9] - b[i + 9]) * (a[i + 9] - b[i + 9]);
    sums[10] += (a[i + 10] - b[i + 10]) * (a[i + 10] - b[i + 10]);
    sums[11] += (a[i + 11] - b[i + 11]) * (a[i + 11] - b[i + 11]);
    sums[12] += (a[i + 12] - b[i + 12]) * (a[i + 12] - b[i + 12]);
    sums[13] += (a[i + 13] - b[i + 13]) * (a[i + 13] - b[i + 13]);
    sums[14] += (a[i + 14] - b[i + 14]) * (a[i + 14] - b[i + 14]);
    sums[15] += (a[i + 15] - b[i + 15]) * (a[i + 15] - b[i + 15]);
  }

  return sums[0] + sums[1] + sums[2] + sums[3] + sums[4] + sums[5] + sums[6] + sums[7] + sums[8] + sums[9] + sums[10] + sums[11] + sums[12] + sums[13] + sums[14] + sums[15];
}

inline float euclidean_distance_halt(const float* a, const float* b, const float& threshold)
{
  globals::DIST_CALCULATIONS++;
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
  globals::DIST_CALCULATIONS++;
  float sums[] = {0.0, 0.0, 0.0, 0.0};
  for (unsigned int i = 0; i < globals::g_vector_dimensions; ++i) {
    float delta = a[i] - b[i];
    sums[i % 4] += delta * delta;
  }

  return sums[0] + sums[1] + sums[2] + sums[3];
}

inline float angular_distance(const float* a, const float* b, const float& max_distance = -1)
{
  globals::DIST_CALCULATIONS++;
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
  g_distance_function = &euclidean_distance_unroll;
}

}  // namespace distance
