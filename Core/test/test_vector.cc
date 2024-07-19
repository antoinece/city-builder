#include "maths/basic_vector.h"
#include <gtest/gtest.h>
#include <vector>

class BasicVectorComplexFixture : public ::testing::TestWithParam<std::vector<int>> {};

TEST_P(BasicVectorComplexFixture, CombinedOperations) {
    constexpr size_t N = 10; // Vous pouvez ajuster cette valeur selon vos besoins
    core::BasicVector<int, N> vector;
    auto values = GetParam();

    // Ajout initial de tous les éléments
    for (const auto& value : values) {
        vector.push_back(value);
    }

    // Vérification de la taille et des éléments
    ASSERT_EQ(vector.size(), values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        EXPECT_EQ(vector.at(i), values[i]);
    }

    // Suppression de la moitié des éléments
    size_t originalSize = vector.size();
    for (size_t i = 0; i < originalSize / 2; ++i) {
        vector.pop_back();
    }

    // Vérification de la taille après suppression
    ASSERT_EQ(vector.size(), originalSize / 2);

    // Réinsertion d'éléments
    for (size_t i = 0; i < originalSize / 2; ++i) {
        vector.push_back(values[i]);
    }

    // Vérification finale de la taille et des éléments
    ASSERT_EQ(vector.size(), originalSize);
    for (size_t i = 0; i < originalSize; ++i) {
        EXPECT_EQ(vector.at(i), values[i % (originalSize / 2)]);
    }
}

INSTANTIATE_TEST_SUITE_P(Values, BasicVectorComplexFixture,
    ::testing::Values(
        std::vector<int>{1, 4, 5, 123},
        std::vector<int>{5, 123, 3, -1},
        std::vector<int>{10, 20, 30, 40, 50, 60}
)
);




#include "maths/small_vector.h"


class SmallVectorComplexFixture : public ::testing::TestWithParam<std::vector<int>> {};

TEST_P(SmallVectorComplexFixture, CombinedOperations) {
    core::SmallVector<int, 6> vector;
    auto values = GetParam();

    // Ajout initial de tous les éléments
    for (auto value : values) {
        vector.push_back(value);
    }

    // Vérification de la taille et des éléments
    ASSERT_EQ(vector.size(), values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        EXPECT_EQ(vector.at(i), values[i]);
    }

    // Suppression de la moitié des éléments
    size_t originalSize = vector.size();
    for (size_t i = 0; i < originalSize / 2; ++i) {
        vector.pop_back();
    }

    // Vérification de la taille après suppression
    ASSERT_EQ(vector.size(), originalSize / 2);

    // Réinsertion d'éléments
    for (size_t i = 0; i < originalSize / 2; ++i) {
        vector.push_back(values[i]);
    }

    // Vérification finale de la taille et des éléments
    ASSERT_EQ(vector.size(), originalSize);
    for (size_t i = 0; i < originalSize; ++i) {
        EXPECT_EQ(vector.at(i), values[i % (originalSize / 2)]);
    }
}

INSTANTIATE_TEST_SUITE_P(Values, SmallVectorComplexFixture,
    ::testing::Values(
        std::vector<int>{1, 4, 5, 123},
        std::vector<int>{5, 123, 3, -1},
        std::vector<int>{10, 20, 30, 40, 50, 60}
)
);



#include "maths/vector.h"

// Définir un test fixture pour les opérations complexes sur Vector
class VectorComplexFixture : public ::testing::TestWithParam<std::vector<int>> {};


TEST_P(VectorComplexFixture, CombinedOperations) {

    constexpr int GrowthDividend = 3;
    constexpr int GrowthDivisor = 2;

    core::Vector<int, std::allocator<int>, GrowthDividend, GrowthDivisor> vector;
    auto& values = GetParam();


    for (auto value : values) {
        vector.push_back(value);
    }


    ASSERT_EQ(vector.size(), values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        EXPECT_EQ(vector.at(i), values[i]);
    }


    ASSERT_GE(vector.capacity(), vector.size());


    std::size_t initial_capacity = vector.capacity();


    size_t originalSize = vector.size();



    for (size_t i = 0; i < originalSize / 2; ++i) {
        vector.pop_back();
    }


    ASSERT_EQ(vector.size(), originalSize / 2);


    for (size_t i = 0; i < originalSize / 2; ++i) {
        vector.push_back(values[i]);
    }


    ASSERT_EQ(vector.size(), originalSize);
    for (size_t i = 0; i < originalSize; ++i) {
        EXPECT_EQ(vector.at(i), values[i % (originalSize / 2)]);
    }


    ASSERT_GE(vector.capacity(), initial_capacity);


    std::size_t before_realloc = vector.capacity();


    for (int i = 0; i < 4; ++i) {
        vector.push_back(i);
    }


    ASSERT_EQ(vector.capacity(), before_realloc * GrowthDividend / GrowthDivisor);
}


INSTANTIATE_TEST_SUITE_P(Values, VectorComplexFixture,
    ::testing::Values(
        std::vector<int>{1, 4, 5, 123, 4, 5, 6, 3},
        std::vector<int>{5, 123, 3, -1},
        std::vector<int>{10, 20, 30, 40, 50, 60}
)
);