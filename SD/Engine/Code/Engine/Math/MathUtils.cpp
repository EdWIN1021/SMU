#include "MathUtils.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include <cmath>


/* radians = degrees * (PI / 180) */
float ConvertDegreesToRadians(float degrees)
{
	return degrees * (PI / 180.f);
}


/* degree = radians * (180 / PI) */
float ConvertRadiansToDegrees(float radians)
{
	return radians * (180.f / PI);
}


/* radians = degrees * (PI / 180) */
float CosDegrees(float degree)
{
	return std::cos(ConvertDegreesToRadians(degree));
}


/* radians = degrees * (PI / 180) */
float SinDegrees(float degree)
{
	return std::sin(ConvertDegreesToRadians(degree));
}


/* radians = std::atan2(y, x) */
float Atan2Degrees(float y, float x)
{
	return ConvertRadiansToDegrees(std::atan2(y, x));
}


/* distance = sqrt((y2 - y1) ^ 2  + (x2 - x1) ^ 2 */
float GetDistance2D(Vec2 const& positionA, Vec2 const& positionB)
{
	return std::sqrt(GetDistanceSquared2D(positionA, positionB));
}

/* distanceSquared2D = (y2 - y1) ^ 2 + (x2 - x1) ^ 2 */
float GetDistanceSquared2D(Vec2 const& positionA, Vec2 const& positionB)
{
	float deltaY = positionB.y - positionA.y;
	float deltaX = positionB.x - positionA.x;

	return  deltaY * deltaY + deltaX * deltaX;
}

/* distance = sqrt((y2 - y1) ^ 2  + (x2 - x1) ^ 2 + (z2 - z1) ^ 2) */
float GetDistance3D(Vec3 const& positionA, Vec3 const& positionB)
{
	return std::sqrt(GetDistanceSquared3D(positionA, positionB));
}

/* distanceSquared2D = (y2 - y1) ^ 2  + (x2 - x1) ^ 2 + (z2 - z1) ^ 2  */
float GetDistanceSquared3D(Vec3 const& positionA, Vec3 const& positionB)
{
	float deltaZ = positionB.z - positionA.z;
	return GetDistanceSquared2D(Vec2(positionA.x, positionA.y), Vec2(positionB.x, positionB.y)) + deltaZ * deltaZ;
}

/* GetDistance2D */
float GetDistanceXY3D(Vec3 const& positionA, Vec3 const& positionB)
{
	return GetDistance2D(Vec2(positionA.x, positionA.y), Vec2(positionB.x, positionB.y));
}

/* GetDistanceSquared2D */
float GetDistanceXYSquared3D(Vec3 const& positionA, Vec3 const& positionB)
{
	return GetDistanceSquared2D(Vec2(positionA.x, positionA.y), Vec2(positionB.x, positionB.y));
}

/* distance of the 2 center < radius B + radius A */
bool DoDiscsOverlap(Vec2 const& centerA, float radiusA, Vec2 const& centerB, float radiusB)
{
	return GetDistanceSquared2D(centerA, centerB) < (radiusA + radiusB) * (radiusA + radiusB);
}

bool DoSpheresOverlap(Vec3 const& centerA, float radiusA, Vec3 const& centerB, float radiusB)
{
	return GetDistanceSquared3D(centerA, centerB) < (radiusA + radiusB) * (radiusA + radiusB);
}

/*
	Approach #2:
	x' = x * cos(theta) - y * sin(theta)
	y' = x * sin(theta) + y * cos(theta)
*/
void TransformPosition2D(Vec2& posToTransform, float uniformScale, float rotationDegrees, Vec2 const& translation)
{
	// uniformScale
	posToTransform.x *= uniformScale;
	posToTransform.y *= uniformScale;

	// rotation
	float rotationRadians = ConvertDegreesToRadians(rotationDegrees + Atan2Degrees(posToTransform.y, posToTransform.x));
	float length = posToTransform.GetLength();

	posToTransform.x = std::cos(rotationRadians) * length; // rotatedX
	posToTransform.y = std::sin(rotationRadians) * length; // rotatedY

	// translation
	posToTransform.x += translation.x;
	posToTransform.y += translation.y;
}

void TransformPositionXY3D(Vec3& posToTransform, float xyScale, float zRotationDegrees, Vec2 const& xyTranslation)
{
	Vec2 temp(posToTransform.x, posToTransform.y);
	TransformPosition2D(temp, xyScale, zRotationDegrees, xyTranslation);
	posToTransform.x = temp.x;
	posToTransform.y = temp.y;
}



