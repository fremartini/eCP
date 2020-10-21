#include <eCP/eCP.hpp>  // TODO: Refac global vars away completely or into own file
#include <cmath>

float euclidean_distance(float*& a, float*& b)
{
	float sum = 0;
	for (unsigned int i = 0; i < g_vector_dimensions; ++i)
	{
		auto pow = a[i] - b[i]; //dont use pow, its very slow
		sum += pow * pow;
	}

	return sum; // TOOD: This function square the result to fulfill the specification of the function name
}

float angular_distance(float*& a, float*& b)
{
	float mul = 0.0, d_a = 0.0, d_b = 0.0;

	for (unsigned int i = 0; i < g_vector_dimensions; ++i)
	{
		mul += a[i] * b[i];
		d_a += a[i] * a[i];
		d_b += b[i] * b[i];
	}

	const float cosine_similarity = (mul / sqrt(d_a * d_b));

	return acos(cosine_similarity);
}