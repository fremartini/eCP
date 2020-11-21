#include <gtest/gtest.h>

#include <eCP/pre-processing.hpp>
#include <eCP/distance.hpp>
#include <eCP/globals.hpp>

/* Helpers */
std::vector<Node*> get_empty_index(unsigned int L = 2) 
{
    std::vector<Point> S = {
        Point(new float[3] {1, 1, 1}, 0),
        Point(new float[3] {4, 4, 4}, 1),
        Point(new float[3] {2, 2, 2}, 2),
        Point(new float[3] {12, 12, 12}, 3),
        Point(new float[3] {3, 3, 3}, 4),
        Point(new float[3] {9, 9, 9}, 5),
        Point(new float[3] {5, 5, 5}, 6),
        Point(new float[3] {20, 20, 20}, 7),
        Point(new float[3] {17, 17, 17}, 8),
        Point(new float[3] {7, 7, 7}, 9),
        Point(new float[3] {10, 10, 10}, 10),
    };

    return pre_processing::create_index(S, L);
};

/* Tests */

TEST(pre_processing_tests, get_closest_cluster_returns_closest_cluster)
{
    distance::set_distance_function(distance::Metrics::EUCLIDEAN);
    distance::g_distance_function = distance::g_distance_function;
    globals::g_vector_dimensions = 3;

    std::vector<Node*> clusters {
        new Node{Point(new float[3] {1, 1, 1}, 0)},
        new Node{Point(new float[3] {4, 4, 4}, 1)},
        new Node{Point(new float[3] {7, 7, 7}, 2)},
        new Node{Point(new float[3] {8, 8, 8}, 3)},
    };

    float* query = new float[3]{ 3, 3, 3 };

    Node* actual = pre_processing::find_nearest_node(clusters, query);

    EXPECT_TRUE(*actual->get_representative() == (*new float[3]{ 4, 4, 4 }));
}

TEST(pre_processing_tests, get_closest_cluster_given_query_in_clusters_returns_same)
{
    distance::set_distance_function(distance::Metrics::EUCLIDEAN);
    distance::g_distance_function = distance::g_distance_function;
    globals::g_vector_dimensions = 3;

    std::vector<Node*> clusters = {
        new Node{Point {new float[3] {1,1,1}, 0}},
        new Node(Point(new float[3] {4, 4, 4}, 1)),
        new Node(Point(new float[3] {7, 7, 7}, 2)),
        new Node(Point(new float[3] {8, 8, 8}, 3)),
    };

    float* query = new float[3]{ 8, 8, 8 };

    Node* actual = pre_processing::find_nearest_node(clusters, query);

    EXPECT_TRUE(*actual->get_representative() == (*new float[3]{ 8, 8, 8 }));
}

TEST(pre_processing_tests, create_index_bottom_up_creates_empty_datastructure) {
    distance::set_distance_function(distance::Metrics::EUCLIDEAN);
    distance::g_distance_function = distance::g_distance_function;
    globals::g_vector_dimensions = 3;

    std::vector<Point> S = {
        Point(new float[3] {1, 1, 1}, 0),
        Point(new float[3] {4, 4, 4}, 1),
        Point(new float[3] {2, 2, 2}, 2),
        Point(new float[3] {3, 3, 3}, 3),
        Point(new float[3] {9, 9, 9}, 4),
        Point(new float[3] {6, 6, 6}, 5)
    };
    unsigned int L = 1;

    auto root = pre_processing::create_index(S, L);

    EXPECT_TRUE(root.size() != 0);

    for (Node* cluster : root) {
        EXPECT_TRUE(cluster->children.size() == 0);
        EXPECT_TRUE(cluster->points.size() == 1);
    }
}

TEST(pre_processing_tests, insert_points_given_empty_index_inserts_points) {
    distance::set_distance_function(distance::Metrics::EUCLIDEAN);
    distance::g_distance_function = distance::g_distance_function;
    globals::g_vector_dimensions = 3;

    std::vector<Node*> root = get_empty_index(1);

    std::vector<Point> descriptors = {
        Point(new float[3] {2, 2, 2}, 0),
        Point(new float[3] {9, 9, 9}, 1),
        Point(new float[3] {4, 4, 4}, 2),
        Point(new float[3] {1, 1, 1}, 3),
        Point(new float[3] {12, 12, 12}, 4),
        Point(new float[3] {17, 17, 17}, 5),
        Point(new float[3] {5, 5, 5}, 6),
        Point(new float[3] {3, 3, 3}, 7),
        Point(new float[3] {20, 20, 20}, 8),
        Point(new float[3] {7, 7, 7}, 9),
        Point(new float[3] {10, 10, 10}, 10)
    };

    std::vector<Node*> actual = pre_processing::insert_points(root, descriptors);

    for (auto cluster : actual) {
        for (auto leaf : cluster->children) {
            EXPECT_TRUE(leaf->points.size() != 0);
        }
    }
}