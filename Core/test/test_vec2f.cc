#include <gtest/gtest.h>

#include "maths/vec2f.h"

struct Vec2fOperationFixture :
	public testing::TestWithParam<std::pair<core::Vec2f, core::Vec2f>>
{

};

TEST_P(Vec2fOperationFixture, Add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;
	EXPECT_FLOAT_EQ(result.x, v1.x + v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y + v2.y);
}

TEST_P(Vec2fOperationFixture, Sub)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 - v2;
	EXPECT_FLOAT_EQ(result.x, v1.x - v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y - v2.y);

	const auto neg1 = -v1;
	const auto neg2 = -v2;
	EXPECT_FLOAT_EQ(neg1.x, -v1.x);
	EXPECT_FLOAT_EQ(neg1.y, -v1.y);
	EXPECT_FLOAT_EQ(neg2.x, -v2.x);
	EXPECT_FLOAT_EQ(neg2.y, -v2.y);
}

TEST_P(Vec2fOperationFixture, mutiplie)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 * v2.x;
	const auto result2 = v1.x * v2;

	EXPECT_FLOAT_EQ(result.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y * v2.x);

	EXPECT_FLOAT_EQ(result2.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result2.y, v1.x * v2.y);
}

TEST_P(Vec2fOperationFixture, divide)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 / v2.x;


	if (v2.x == 0)
	{
		EXPECT_FLOAT_EQ(result.x, 0);
		EXPECT_FLOAT_EQ(result.y, 0);
	}
	else
	{
		EXPECT_FLOAT_EQ(result.x, v1.x / v2.x);
		EXPECT_FLOAT_EQ(result.y, v1.y / v2.x);
	}
}



TEST_P(Vec2fOperationFixture, Dot)
{
	auto [v1, v2] = GetParam();
	const auto result = core::Vec2f::Dot(v1, v2);
	EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

TEST_P(Vec2fOperationFixture, Perpendicular)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Perpendicular();
	const auto p2 = v2.Perpendicular();
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v1, p1), 0);
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v2, p2), 0);

	const auto r1 = v1.Perpendicular2();
	const auto r2 = v2.Perpendicular2();
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v1, r1), 0);
	EXPECT_FLOAT_EQ(core::Vec2f::Dot(v2, r2), 0);
}

TEST_P(Vec2fOperationFixture, lerp)
{

	auto [v1, v2] = GetParam();
	const auto p1 = v1.lerp(v2, 1);
	const auto p2 = v1.lerp(v2, 0);

	EXPECT_FLOAT_EQ(p1.x, v2.x);
	EXPECT_FLOAT_EQ(p2.x, v1.x);

	EXPECT_FLOAT_EQ(p1.y, v2.y);
	EXPECT_FLOAT_EQ(p2.y, v1.y);

}

TEST_P(Vec2fOperationFixture, magintude)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Magnitude();
	const auto p2 = v2.Magnitude();

	EXPECT_FLOAT_EQ(p1, sqrt(v1.x * v1.x + v1.y * v1.y));
	EXPECT_FLOAT_EQ(p2, sqrt(v2.x * v2.x + v2.y * v2.y));
}


TEST_P(Vec2fOperationFixture, squaredMagnitude)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.squaredMagnitude();
	const auto p2 = v2.squaredMagnitude();
	EXPECT_FLOAT_EQ(p1, v1.x * v1.x + v1.y * v1.y);
	EXPECT_FLOAT_EQ(p2, v2.x * v2.x + v2.y * v2.y);

}


TEST_P(Vec2fOperationFixture, normalized)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Normalized();
	const auto p2 = v2.Normalized();
	if (v1.x == 0 || v1.y == 0)
	{
		EXPECT_FLOAT_EQ(p1.x, 0);
		EXPECT_FLOAT_EQ(p1.y, 0);
	}
	else
	{
		EXPECT_FLOAT_EQ(p1.Magnitude(), 1);

	}
	if (v2.x == 0 || v2.y == 0)
	{
		EXPECT_FLOAT_EQ(p2.x, 0);
		EXPECT_FLOAT_EQ(p2.y, 0);
	}
	else
	{
		EXPECT_FLOAT_EQ(p2.Magnitude(), 1);
	}


}


INSTANTIATE_TEST_SUITE_P(AllNumbers,
	Vec2fOperationFixture,
	testing::Values(
		std::pair{ core::Vec2f{1.3f, 3.0f}, core::Vec2f{2.0f, -4.0f} },
		std::pair{ core::Vec2f{-10.0f, 15.0f}, core::Vec2f{-25.4f, -35.0f} },
		std::pair{ core::Vec2f{}, core::Vec2f{} },
		std::pair{ core::Vec2f{1.0f, 2.0f}, core::Vec2f{} },
		std::pair{ core::Vec2f{0.5f, 3.6f}, core::Vec2f{1.4f, 2.3f} },
		std::pair{ core::Vec2f{4.2f, -5.1f}, core::Vec2f{0.0f, 3.3f} },
		std::pair{ core::Vec2f{-2.7f, 8.9f}, core::Vec2f{7.1f, -3.4f} },
		std::pair{ core::Vec2f{10.5f, 10.5f}, core::Vec2f{-10.5f, -10.5f} },
		std::pair{ core::Vec2f{3.14159f, 2.71828f}, core::Vec2f{-1.41421f, 1.73205f} },
		std::pair{ core::Vec2f{6.6f, 7.7f}, core::Vec2f{-8.8f, 9.9f} },
		std::pair{ core::Vec2f{1.0f, -1.0f}, core::Vec2f{2.0f, -2.0f} }
	)
);