#include <windows.h>
#include <gl/gl.h>		
#include "PlayerShip.hpp"			
#include <Engine/Core/Vertex.hpp>
#include "Engine/Math/Vec3.hpp"


PlayerShip::PlayerShip(Vec2 const& startingPosition, Vec2 const& startingVelocity)
	: m_position(startingPosition)
	, m_velocity(startingVelocity)
{
}

void PlayerShip::Update(float deltaSeconds)
{
	m_position.x += m_velocity.x * deltaSeconds;
	if (m_position.x >= 200) { exit(0); }
}

void PlayerShip::Render()
{
	Vertex v1(Vec3(4.f + m_position.x, 0.f + m_position.y, 0.f), Rgba8(255, 255, 255), Vec2(0.f, 0.f));
	Vertex v2(Vec3(-2.f + m_position.x, 2.f + m_position.y, 0.f), Rgba8(0, 127, 255), Vec2(0.f, 0.f));
	Vertex v3(Vec3(-2.f + m_position.x, -2.f + m_position.y, 0.f), Rgba8(0, 0, 0), Vec2(0.f, 0.f));

	Vertex vertexArray[] = { v1, v2, v3 };

	for (int i = 0; i < sizeof(vertexArray) / sizeof(vertexArray[0]); i++)
	{
		Vertex vertex = vertexArray[i];

		glColor4ub(vertex.m_color.r, vertex.m_color.g, vertex.m_color.b, vertex.m_color.a);
		glTexCoord2f(0.f, 0.f);
		glVertex2f(vertex.m_position.x, vertex.m_position.y);
	}
}
