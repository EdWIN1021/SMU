#include "Engine/Math/Vec3.hpp"
#include "Engine/Math/MathUtils.hpp"
#include <cmath>




Vec3::Vec3(Vec3 const& copyFrom)
{
	x = copyFrom.x;
	y = copyFrom.y;
	z = copyFrom.z;
}


//-----------------------------------------------------------------------------------------------
Vec3::Vec3(float initialX, float initialY, float initialZ)
	: x(initialX)
	, y(initialY)
	, z(initialZ)
{
}


//-----------------------------------------------------------------------------------------------
float Vec3::GetLength() const
{
	return std::sqrt(GetLengthSquared());
}


//-----------------------------------------------------------------------------------------------
float Vec3::GetLengthXY() const
{
	return std::sqrt(GetLengthXYSquared());
}


//-----------------------------------------------------------------------------------------------
float Vec3::GetLengthSquared() const
{
	return x * x + y * y + z * z;
}


//-----------------------------------------------------------------------------------------------
float Vec3::GetLengthXYSquared() const
{
	return x * x + y * y;
}


//-----------------------------------------------------------------------------------------------
float Vec3::GetOrientationAboutZDegrees() const
{
	return ConvertRadiansToDegrees(std::atan2(y, x));
}


//-----------------------------------------------------------------------------------------------
float Vec3::GetOrientationAboutZRadians() const
{
	return std::atan2(y, x);
}


//-----------------------------------------------------------------------------------------------
Vec3 const Vec3::GetRotatedAboutZDegrees(float rotationDegreesAboutZ) const
{
	float radians = ConvertDegreesToRadians(rotationDegreesAboutZ);
	return GetRotatedAboutZRadians(radians);
}


//-----------------------------------------------------------------------------------------------
Vec3 const Vec3::GetRotatedAboutZRadians(float rotationRadiansAboutZ) const
{
	float rotatedRadians = rotationRadiansAboutZ + std::atan2(y, x);
	float length = GetLengthXY();

	return Vec3(std::cos(rotatedRadians) * length, std::sin(rotatedRadians) * length, z);
}


//-----------------------------------------------------------------------------------------------
Vec3 const Vec3::GetClampedToMaxLength(float maxLength) const
{
	float length = GetLength();
	float scaleFactor = maxLength / length;
	return length <= maxLength ? Vec3(x, y, z) : Vec3(x * scaleFactor, y * scaleFactor, z * scaleFactor);
}


//-----------------------------------------------------------------------------------------------
Vec3 const Vec3::GetNormalized() const
{
	float length = std::sqrt(x * x + y * y + z * z);
	return Vec3(x / length, y / length, z / length);
}


//-----------------------------------------------------------------------------------------------
bool Vec3::operator==(Vec3 const& compare) const
{
	return x == compare.x && y == compare.y && z == compare.z;
}


//-----------------------------------------------------------------------------------------------
bool Vec3::operator!=(Vec3 const& compare) const
{
	return x != compare.x || y != compare.y || z != compare.z;
}


//-----------------------------------------------------------------------------------------------
Vec3 const Vec3::operator+(Vec3 const& vecToAdd) const
{
	return Vec3(x + vecToAdd.x, y + vecToAdd.y, z + vecToAdd.z);
}


//-----------------------------------------------------------------------------------------------
Vec3 const Vec3::operator-(Vec3 const& vecToSubtract) const
{
	return Vec3(x - vecToSubtract.x, y - vecToSubtract.y, z - vecToSubtract.z);
}


//-----------------------------------------------------------------------------------------------
Vec3 const Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}


//-----------------------------------------------------------------------------------------------
Vec3 const Vec3::operator*(float uniformScale) const
{
	return Vec3(x * uniformScale, y * uniformScale, z * uniformScale);
}


//-----------------------------------------------------------------------------------------------
Vec3 const Vec3::operator*(Vec3 const& vecToMultiply) const
{
	return Vec3();
}


//-----------------------------------------------------------------------------------------------
Vec3 const  Vec3::operator/(float inverseScale) const
{
	return Vec3(x / inverseScale, y / inverseScale, z / inverseScale);
}


//-----------------------------------------------------------------------------------------------
void Vec3::operator+=(Vec3 const& vecToAdd) {

	x += vecToAdd.x;
	y += vecToAdd.y;
	z += vecToAdd.z;
}


//-----------------------------------------------------------------------------------------------
void Vec3::operator-=(Vec3 const& vecToSubtract)
{
	x -= vecToSubtract.x;
	y -= vecToSubtract.y;
	z -= vecToSubtract.z;

}


//-----------------------------------------------------------------------------------------------
void Vec3::operator*=(const float uniformScale)
{
	x *= uniformScale;
	y *= uniformScale;
	z *= uniformScale;
}


//-----------------------------------------------------------------------------------------------
void Vec3::operator/=(const float uniformDivisor)
{
	x /= uniformDivisor;
	y /= uniformDivisor;
	z /= uniformDivisor;
}


//-----------------------------------------------------------------------------------------------
void Vec3::operator=(Vec3 const& copyFrom)
{
	x = copyFrom.x;
	y = copyFrom.y;
	z = copyFrom.z;
}


//-----------------------------------------------------------------------------------------------
Vec3 const operator*(float uniformScale, Vec3 const& vecToScale)
{
	return Vec3(vecToScale.x * uniformScale, vecToScale.y * uniformScale, vecToScale.z * uniformScale);
}

