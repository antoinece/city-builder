#include <maths/vec2i.h>

#include <gtest/gtest.h>

struct Vec2iOperationFixture : public ::testing::TestWithParam<std::pair<core::Vec2i, core::Vec2i>>
{
};

TEST_P(Vec2iOperationFixture, Add)
{
    auto [v1, v2] = GetParam();
    const auto result = v1 + v2;
    EXPECT_EQ(result.x, v1.x + v2.x);
    EXPECT_EQ(result.y, v1.y + v2.y);
}

TEST_P(Vec2iOperationFixture, Sub)
{
    auto [v1, v2] = GetParam();
    const auto result = v1 - v2;
    EXPECT_EQ(result.x, v1.x - v2.x);
    EXPECT_EQ(result.y, v1.y - v2.y);

    const auto neg1 = -v1;
    const auto neg2 = -v2;
    EXPECT_EQ(neg1.x, -v1.x);
    EXPECT_EQ(neg1.y, -v1.y);
    EXPECT_EQ(neg2.x, -v2.x);
    EXPECT_EQ(neg2.y, -v2.y);
}

TEST_P(Vec2iOperationFixture, mutiplie)
{
    auto [v1, v2] = GetParam();
    const auto result = v1 * v2.x;
    EXPECT_EQ(result.x, v1.x * v2.x);
    EXPECT_EQ(result.y, v1.y * v2.x);
}

TEST_P(Vec2iOperationFixture, Perpendicular)
{
    auto [v1, v2] = GetParam();
    const auto p1 = v1.Perpendicular();
    const auto p2 = v2.Perpendicular();
    EXPECT_EQ(core::Vec2i::Dot(v1, p1), 0);
    EXPECT_EQ(core::Vec2i::Dot(v2, p2), 0);

    const auto r1 = v1.Perpendicular2();
    const auto r2 = v2.Perpendicular2();
    EXPECT_EQ(core::Vec2i::Dot(v1, r1), 0);
    EXPECT_EQ(core::Vec2i::Dot(v2, r2), 0);
}

INSTANTIATE_TEST_SUITE_P(PositiveNumbers,
    Vec2iOperationFixture,
    testing::Values(
        std::pair{ core::Vec2i{1,3}, core::Vec2i{2,4} },
        std::pair{ core::Vec2i{10, 15}, core::Vec2i{25, -35} },
        std::pair{ core::Vec2i{0, 15}, core::Vec2i{5, 35} },
        std::pair{ core::Vec2i{-10, 15}, core::Vec2i{2, 3} }
    )
);