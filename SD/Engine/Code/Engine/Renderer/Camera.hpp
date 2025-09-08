#pragma once
#include "Engine/Math/Vec2.hpp"

class Camera
{
public:
	Camera(const Vec2& orthoBottomLeft, const Vec2& orthoTopRight);
	~Camera() = default;

	void SetOrthoView(Vec2 const& bottomLeft, Vec2 const& topRight);
	Vec2 GetOrthoBottomLeft() const;
	Vec2 GetOrthoTopRight() const;

private:
	Vec2 m_orthoBottomLeft;
	Vec2 m_orthoTopRight;
};