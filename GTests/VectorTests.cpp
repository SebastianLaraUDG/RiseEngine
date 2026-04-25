#include "pch.h"
#include <Math/Public/Vector.h>
#include "../src/Math/RiseMath.hpp"

TEST(Matrix4TESTS, equality)
{
	Matrix4f m{}; // TODO FIX THIS AND MOVE TO MATRIX TESTS.cpp
	float* pm = &m.M[0][0];
	ASSERT_EQ(&pm[0], &m.M[0][0]);
	ASSERT_EQ(&pm[1], &m.M[0][1]);
	ASSERT_EQ(&pm[2], &m.M[0][2]);
	ASSERT_EQ(&pm[3], &m.M[0][3]);

	pm = &m.M[1][0];
	ASSERT_EQ(&pm[0], &m.M[1][0]);
	ASSERT_EQ(&pm[1], &m.M[1][1]);
	ASSERT_EQ(&pm[2], &m.M[1][2]);
	ASSERT_EQ(&pm[3], &m.M[1][3]);

	pm = &m.M[2][0];
	ASSERT_EQ(&pm[0], &m.M[2][0]);
	ASSERT_EQ(&pm[1], &m.M[2][1]);
	ASSERT_EQ(&pm[2], &m.M[2][2]);
	ASSERT_EQ(&pm[3], &m.M[2][3]);

	pm = &m.M[3][0];
	ASSERT_EQ(&pm[0], &m.M[3][0]);
	ASSERT_EQ(&pm[1], &m.M[3][1]);
	ASSERT_EQ(&pm[2], &m.M[3][2]);
	ASSERT_EQ(&pm[3], &m.M[3][3]);
}

TEST(Vector3_Tests, ScalarMultiplication)
{
	constexpr double sc1 = 4.9787632;
	const Vector3 v1(55.6, 123.5, 53);

	EXPECT_EQ(v1 * sc1, Vector3(v1.X * sc1, v1.Y * sc1, v1.Z * sc1 ));
}

TEST(Vector3_Tests, Constructors)
{
	const Vector3 v1(1.0);
	const Vector3 v2(1.0, 1.0, 1.0);
	EXPECT_EQ(v1, v2);
	// Zeros.
	const Vector3 vZero{};
	const Vector3 v0(0);
	EXPECT_EQ(vZero, v0);
	const Vector3 v0Double(0.0);
	EXPECT_EQ(v0, v0Double);

	const Vector3f vZeroFloat(0.f);
	const Vector3f vZeroF{};
	const Vector3f vOneF(1.f);
	EXPECT_EQ(vZeroFloat, vZeroF);
	EXPECT_NE(vOneF, vZeroFloat);

	EXPECT_EQ(vZero, Vector3::ZeroVector());

	SUCCEED();
}

TEST(Vector3_Tests, Magnitude)
{
	const Vector3 v1(1, 2, 6);
	const Vector3 v2(6, 2, 1);
	const Vector3 v3(3, 3, 3);
	EXPECT_EQ(v1.Magnitude(), v2.Magnitude());
	EXPECT_NE(v3.Magnitude(), v2.Magnitude());
	EXPECT_FLOAT_EQ(v3.Magnitude() * v3.Magnitude(), v3.SquaredMagnitude());
	const Vector3 v4(10000.0, 346342.562, 6788564.5682); // Random numbers on purpose.
	EXPECT_FLOAT_EQ(v4.Magnitude(), v4.Size());
	EXPECT_FLOAT_EQ(v4.Length(), v4.Size());
}

TEST(Vector3_Tests, UnitVectors)
{
	/*
	EXPECT_EQ(Vector3::UnitVectorX(), Vector3::RightVector());
	EXPECT_EQ(Vector3::UnitVectorY(), Vector3::UpVector());
	EXPECT_EQ(Vector3::UnitVectorZ(), Vector3::ForwardVector());
	*/
}

TEST(Vector3_Tests, DotProduct)
{
	const Vector3 v1(4.5, 1.33, 5.7), v2(6.7, 24.23, 8.4);

	const double angleBetweenVectors = Vector3::FindAngle(v1, v2); // this is actually cos, but calling acos is not optimal.
	
	EXPECT_FLOAT_EQ(Vector3::DotProduct(v1, v2), v1.Magnitude() * v2.Magnitude() * angleBetweenVectors);
	EXPECT_NEAR(Vector3::DotProduct(v1, v2), v1.Magnitude() * v2.Magnitude() * angleBetweenVectors, 0.0000000001);

	constexpr double arbitraryScalar = 4.673;
	const Vector3 v3(5.67, 3426.73, 7784.3);
	// PROPERTIES
	EXPECT_FLOAT_EQ(Vector3::DotProduct(v1, v2), Vector3::DotProduct(v2, v1));
	EXPECT_FLOAT_EQ(Vector3::DotProduct(v1 * arbitraryScalar, v2), Vector3::DotProduct(v1, v2) * arbitraryScalar);
	EXPECT_FLOAT_EQ(Vector3::DotProduct(v1, v2 + v3), (Vector3::DotProduct(v1, v2) + Vector3::DotProduct(v1, v3)));
	EXPECT_FLOAT_EQ(Vector3::DotProduct(v1, v1), v1.Magnitude() * v1.Magnitude());
	EXPECT_LE(std::abs(Vector3::DotProduct(v1, v2)), v1.Magnitude() * v2.Magnitude());
}

TEST(Vector3_Tests, CrossProduct)
{
	EXPECT_EQ(Vector3::CrossProduct(Vector3::UnitVectorX(), Vector3::UnitVectorY()), Vector3::UnitVectorZ());
	EXPECT_EQ(Vector3::CrossProduct(Vector3::UnitVectorY(), Vector3::UnitVectorX()), -Vector3::UnitVectorZ()); // Inverted X and Y should make the opposite Z direction.

	const Vector3 vec1(1.6, 345.3, 42.765);
	const Vector3 vec2(656.23, -7645.2333, 5742.225628);

	auto crossItself = Vector3::CrossProduct(vec1, vec1);
	EXPECT_EQ(crossItself, Vector3::ZeroVector())<< "The cross product of a vector by itself should be zero vector."; // The cross product of a vector by itself should be zero vector.
	EXPECT_FLOAT_EQ(crossItself.Magnitude(), 0.0);
	EXPECT_NEAR(Vector3::DotProduct(Vector3::CrossProduct(vec1, vec2), vec1), 0.0, 0.00000001);
	EXPECT_FLOAT_EQ(Vector3::DotProduct(Vector3::CrossProduct(vec1, vec2), vec2), 0.0);
	
	EXPECT_NE(Vector3::CrossProduct(vec1, vec2), Vector3::CrossProduct(vec2, vec1)) << "(A Cross B) and (B Cross A) should be different!";
	EXPECT_EQ(Vector3::CrossProduct(vec1, vec2), -Vector3::CrossProduct(vec2, vec1)) << "anti commutative property failed";
}

TEST(Vector3_Tests, DistanceAndDistanceSquared)
{
	const Vector3 v1(13.62, -342356.342342, 50203.573);
	const Vector3 v2(- 45309.62, 56.342342, -3.573);
	
	EXPECT_DOUBLE_EQ(Vector3::Distance(v1, v2) * Vector3::Distance(v1, v2), Vector3::DistanceSquared(v1, v2));
	EXPECT_FLOAT_EQ(Vector3::Distance(v1, v2) * Vector3::Distance(v1, v2), Vector3::DistanceSquared(v1, v2));
}

TEST(Vector3_Tests, FindAngleBetweenVectors)
{
	const Vector3 v1(1,3,0);
	const Vector3 v2(-1,3,2);
	// TODO: EXPECT_DOUBLE_EQ(Vector3::FindAngle(v1, v2), 131.64);
}