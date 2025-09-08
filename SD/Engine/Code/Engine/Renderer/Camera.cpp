#include "Camera.hpp"

Camera::Camera(const Vec2& orthoBottomLeft, const Vec2& orthoTopRight)
	: m_orthoBottomLeft(orthoBottomLeft)
	, m_orthoTopRight(orthoTopRight)
{
}

Vec2 Camera::GetOrthoBottomLeft() const
{
	return m_orthoBottomLeft;
}

Vec2 Camera::GetOrthoTopRight() const
{
	return m_orthoTopRight;
}
