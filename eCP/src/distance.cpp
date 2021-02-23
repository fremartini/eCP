#include <cmath>
#include <stdexcept>

#include <eCP/distance.hpp>
#include <eCP/eCP.hpp>
#include <eCP/data_structure.hpp>
#include <eCP/globals.hpp>

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
        float sum =0.0;
        for (unsigned int i = 0; i < globals::g_vector_dimensions; i = i + 8)
        {
            sum += (a[i] - b[i]) * (a[i] - b[i]);
            sum += (a[i+1] - b[i+1]) * (a[i+1] - b[i+1]);
            sum += (a[i+2] - b[i+2]) * (a[i+2] - b[i+2]);
            sum += (a[i+3] - b[i+3]) * (a[i+3] - b[i+3]);
            sum += (a[i+4] - b[i+4]) * (a[i+4] - b[i+4]);
            sum += (a[i+5] - b[i+5]) * (a[i+5] - b[i+5]);
            sum += (a[i+6] - b[i+6]) * (a[i+6] - b[i+6]);
            sum += (a[i+7] - b[i+7]) * (a[i+7] - b[i+7]);
	}

        return sum;
    }

    Node* get_closest_node(std::vector<Node*>& nodes, float* query)
    {
        float closest = globals::FLOAT_MAX;
        Node* best = nullptr;

        for (Node* node : nodes)
        {
            const float distance = g_distance_function(query, node->points[0].descriptor);
            
            if (distance <= closest)
            {
                closest = distance;
                best = node;
            }
        }
        return best;
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
