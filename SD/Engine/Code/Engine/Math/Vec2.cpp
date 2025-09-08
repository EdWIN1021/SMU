#include "Engine/Math/Vec2.hpp"
#include "Engine/Math/MathUtils.hpp"
//#include "Engine/Core/EngineCommon.hpp"
#include <cmath>




//-----------------------------------------------------------------------------------------------
Vec2::Vec2(Vec2 const& copy)
	: x(copy.x)
	, y(copy.y)
{
}


//-----------------------------------------------------------------------------------------------
Vec2::Vec2(float initialX, float initialY)
	: x(initialX)
	, y(initialY)
{
}


Vec2 const Vec2::MakeFromPolarDegrees(float orientationDegrees, float length)
{
	float radians = ConvertDegreesToRadians(orientationDegrees);
	return MakeFromPolarRadians(radians, length);
}


Vec2 const Vec2::MakeFromPolarRadians(float orentationRadians, float length)
{
	return Vec2(std::cos(orentationRadians) * length, std::sin(orentationRadians) * length);
}


//-----------------------------------------------------------------------------------------------
float Vec2::GetLength() const
{
	return std::sqrt(GetLengthSquared());
}


//-----------------------------------------------------------------------------------------------
float Vec2::GetLengthSquared() const
{
	return x * x + y * y;
}


//-----------------------------------------------------------------------------------------------
float Vec2::GetOrientationDegrees() const
{
	return Atan2Degrees(y, x);
};


//-----------------------------------------------------------------------------------------------
float Vec2::GetOrientationRadians() const
{
	return std::atan2(y, x);
};


/*
	cos(90) = 0 sin(90) = 1
	x' = x * cos(90) - y * sin(90) = -y
	y' = x * sin(90) + y * cos(90) = x
*/
Vec2 const  Vec2::GetRotatedBy90Degrees() const
{
	return Vec2(-y, x);
}


/*
*	cos(90) = 0 sin(90) = 1
	x' = x * cos(90) - y * sin(90) = -y
	y' = x * sin(90) + y * cos(90) = x
*/
Vec2 const Vec2::GetRotatedByMinus90Degrees() const
{
	return Vec2(y, -x);
}


//-----------------------------------------------------------------------------------------------
Vec2 const Vec2::GetRotatedByDegrees(float rotationDegrees)
{
	float radians = ConvertDegreesToRadians(rotationDegrees);
	return GetRotatedByRadians(radians);
}


//-----------------------------------------------------------------------------------------------
Vec2 const Vec2::GetRotatedByRadians(float rotationRadians)
{
	float rotatedRadians = rotationRadians + std::atan2(y, x);
	float length = GetLength();

	return Vec2(std::cos(rotatedRadians) * length, std::sin(rotatedRadians) * length);
}


//-----------------------------------------------------------------------------------------------
Vec2 const Vec2::GetClamped(float maxLength) const
{
	float length = GetLength();
	float scaleFactor = maxLength / length;
	return length <= maxLength ? Vec2(x, y) : Vec2(x * scaleFactor, y * scaleFactor);
}


//-----------------------------------------------------------------------------------------------
Vec2 const Vec2::GetNormalized() const
{
	float length = GetLength();
	return Vec2(x / length, y / length);
}


//-----------------------------------------------------------------------------------------------
void Vec2::SetOrientationDegrees(float newOrientationDegrees)
{
	float radians = ConvertDegreesToRadians(newOrientationDegrees);
	SetOrientationRadians(radians);
}


//-----------------------------------------------------------------------------------------------
void Vec2::SetOrientationRadians(float newOrientationRadians)
{
	float length = GetLength();

	x = length * std::cos(newOrientationRadians);
	y = length * std::sin(newOrientationRadians);
}


//-----------------------------------------------------------------------------------------------
void Vec2::SetPolarDegrees(float newOrientationDegrees, float newLength)
{
	float radians = ConvertDegreesToRadians(newOrientationDegrees);
	SetPolarRadians(radians, newLength);
}


//-----------------------------------------------------------------------------------------------
void Vec2::SetPolarRadians(float newOrientationRadians, float newLength)
{
	Vec2 newVec2 = MakeFromPolarRadians(newOrientationRadians, newLength);

	x = newVec2.x;
	y = newVec2.y;
}


//-----------------------------------------------------------------------------------------------
void Vec2::Rotate90Degrees()
{
	Vec2 rotated = GetRotatedBy90Degrees();

	x = rotated.x;
	y = rotated.y;
}

//-----------------------------------------------------------------------------------------------
void Vec2::RotateMinus90Degrees()
{
	Vec2 rotated = GetRotatedByMinus90Degrees();
	x = rotated.x;
	y = rotated.y;
}


//-----------------------------------------------------------------------------------------------
void Vec2::RotateDegrees(float rotationDegrees)
{
	float radians = ConvertDegreesToRadians(rotationDegrees);
	RotateRadians(radians);
}

//-----------------------------------------------------------------------------------------------
void Vec2::RotateRadians(float rotationRadians)
{
	Vec2 rotatedVec = GetRotatedByRadians(rotationRadians);

	x = rotatedVec.x;
	y = rotatedVec.y;
}


//-----------------------------------------------------------------------------------------------
void Vec2::SetLength(float newLength)
{
	Vec2 normalized = GetNormalized();

	x = normalized.x * newLength;
	y = normalized.y * newLength;
}


//-----------------------------------------------------------------------------------------------
void Vec2::ClampLength(float maxLength)
{
	Vec2 clamped = GetClamped(maxLength);

	x = clamped.x;
	y = clamped.y;
}


//-----------------------------------------------------------------------------------------------
void Vec2::Normalize()
{
	Vec2 normalized = GetNormalized();

	x = normalized.x;
	y = normalized.y;
}

float Vec2::NormalizeAndGetPreviousLength()
{
	float length = GetLength();

	x /= length;
	y /= length;

	return length;
}


//-----------------------------------------------------------------------------------------------
bool Vec2::operator==(Vec2 const& compare) const
{
	return  x == compare.x && y == compare.y;
}


//-----------------------------------------------------------------------------------------------
bool Vec2::operator!=(Vec2 const& compare) const
{
	return  x != compare.x || y != compare.y;
}


//-----------------------------------------------------------------------------------------------
Vec2 const Vec2::operator + (Vec2 const& vecToAdd) const
{
	return Vec2(x + vecToAdd.x, y + vecToAdd.y);
}


//-----------------------------------------------------------------------------------------------
Vec2 const Vec2::operator-(Vec2 const& vecToSubtract) const
{
	return Vec2(x - vecToSubtract.x, y - vecToSubtract.y);
}


//------------------------------------------------------------------------------------------------
Vec2 const Vec2::operator-() const
{
	return Vec2(-x, -y);
}


//-----------------------------------------------------------------------------------------------
Vec2 const Vec2::operator*(float uniformScale) const
{
	return Vec2(x * uniformScale, y * uniformScale);
}


//------------------------------------------------------------------------------------------------
Vec2 const Vec2::operator*(Vec2 const& vecToMultiply) const
{
	return Vec2(x * vecToMultiply.x, y * vecToMultiply.y);
}


//-----------------------------------------------------------------------------------------------
Vec2 const Vec2::operator/(float inverseScale) const
{
	return Vec2(x / inverseScale, y / inverseScale);
}


//-----------------------------------------------------------------------------------------------
void Vec2::operator+=(Vec2 const& vecToAdd)
{
	x += vecToAdd.x;
	y += vecToAdd.y;
}


//-----------------------------------------------------------------------------------------------
void Vec2::operator-=(Vec2 const& vecToSubtract)
{
	x -= vecToSubtract.x;
	y -= vecToSubtract.y;
}


//-----------------------------------------------------------------------------------------------
void Vec2::operator*=(const float uniformScale)
{
	x *= uniformScale;
	y *= uniformScale;
}


//-----------------------------------------------------------------------------------------------
void Vec2::operator/=(const float uniformDivisor)
{
	x /= uniformDivisor;
	y /= uniformDivisor;
}



//-----------------------------------------------------------------------------------------------
void Vec2::operator=(Vec2 const& copyFrom)
{
	x = copyFrom.x;
	y = copyFrom.y;
}


//-----------------------------------------------------------------------------------------------
Vec2 const operator*(float uniformScale, Vec2 const& vecToScale)
{
	return Vec2(vecToScale.x * uniformScale, vecToScale.y * uniformScale);
}