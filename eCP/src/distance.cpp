#include <cmath>
#include <stdexcept>

#include <eCP/distance.hpp>
#include <eCP/eCP.hpp>
#include <eCP/data_structure.hpp>
#include <eCP/global.hpp>

/**
 * Distance functions defined for global use here. Can be imported and used 
 * and will only be
 */
namespace distance
{
    // Definition of global distance function, extern in header
    float (*g_distance_function)(float *&, float *&);

    float euclidean_distance(float *&a, float *&b)
    {
        float sum = 0;
        for (unsigned int i = 0; i < global::g_vector_dimensions; ++i)
        {
            auto pow = a[i] - b[i]; //dont use pow, its very slow
            sum += pow * pow;
        }

        return sum;
    }

    float angular_distance(float *&a, float *&b)
    {
        float mul = 0.0, d_a = 0.0, d_b = 0.0;

        for (unsigned int i = 0; i < global::g_vector_dimensions; ++i)
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
    void set_distance_function(METRIC func)
    {
        switch (func)
        {
        case EUCLIDEAN:
            g_distance_function = &euclidean_distance;
            break;
        case ANGULAR:
            g_distance_function = &angular_distance;
            break;
        default:
            std::invalid_argument("Invalid metric.");
        }
    }

} // namespace distance