#include "Engine/Math/Vec3.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Math/Vec2.hpp"
#include "Engine/Core/Vertex.hpp"
#include "Engine/Core/Engine.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "GameCommon.hpp"



void DebugDrawLine(Vec2 const& startPos, Vec2 const& endPos, float thickness, Rgba8 const& color)
{
	constexpr int NUM_TRIS = 2;
	constexpr int NUM_VERTS = 3 * NUM_TRIS;

	float halfThickness = 0.5f * thickness;
	
	Vec2 forwardVector = (endPos - startPos).GetNormalized();
	Vec2 leftVector = forwardVector.GetRotatedBy90Degrees();
	
	Vec2 startMid = startPos - forwardVector * halfThickness;
	Vec2 endMid = endPos + forwardVector * halfThickness;

	Vec2 startLeft = startMid + leftVector * halfThickness;
	Vec2 startRight = startMid - leftVector * halfThickness;

	Vec2 endLeft = endMid + leftVector * halfThickness;
	Vec2 endRight = endMid - leftVector * halfThickness;

	Vertex verts[NUM_VERTS];
	verts[0].m_position = Vec3(startLeft.x, startLeft.y, 0.f);
	verts[1].m_position = Vec3(startRight.x, startRight.y, 0.f);
	verts[2].m_position = Vec3(endRight.x, endRight.y, 0.f);
	verts[3].m_position = Vec3(startLeft.x, startLeft.y, 0.f);
	verts[4].m_position = Vec3(endRight.x, endRight.y, 0.f);
	verts[5].m_position = Vec3(endLeft.x, endLeft.y, 0.f);

	verts[0].m_color = color;
	verts[1].m_color = color;
	verts[2].m_color = color;
	verts[3].m_color = color;
	verts[4].m_color = color;
	verts[5].m_color = color;

	g_engine->m_render->DrawVertexArray(NUM_VERTS, verts);
}

void DebugDrawRing(Vec2 const& center, float radius, float thickness, Rgba8 const& color)
{
	float halfThickness = 0.5f * thickness;
	float innerRadius = radius - halfThickness;
	float outerRadius = radius + halfThickness;

	constexpr int NUM_SIDES = 32;
	constexpr int NUM_TRIS = 2 * NUM_SIDES;
	constexpr int NUM_VERTS = 3 * NUM_TRIS;
	Vertex verts[NUM_VERTS];

	constexpr float DEGREES_PER_SIDE = 360.f / static_cast<float> ( NUM_SIDES );
	for( int sideNum = 0 ; sideNum < NUM_SIDES; ++ sideNum )
	{
		float startDegree = DEGREES_PER_SIDE * static_cast<float>( sideNum );
		float endDegrees = DEGREES_PER_SIDE * static_cast<float>( sideNum + 1 );
		float cosStart = CosDegrees( startDegree );
		float sinStart = SinDegrees( startDegree );
		float cosEnd = CosDegrees( endDegrees );
		float sinEnd = SinDegrees( endDegrees );

		Vec3 innerStartPos( center.x + innerRadius * cosStart, center.y + innerRadius * sinStart, 0.f );
		Vec3 outerStartPos( center.x + outerRadius * cosStart, center.y + outerRadius * sinStart, 0.f );
		Vec3 outerEndPos( center.x +outerRadius * cosEnd, center.y + outerRadius * sinEnd, 0.f );
		Vec3 innerEndPos( center.x +innerRadius * cosEnd, center.y + innerRadius * sinEnd, 0.f );

		int vertIndexA = (6 * sideNum) + 0;
		int vertIndexB = (6 * sideNum) + 1;
		int vertIndexC = (6 * sideNum) + 2;
		int vertIndexD = (6 * sideNum) + 3;
		int vertIndexE = (6 * sideNum) + 4;
		int vertIndexF = (6 * sideNum) + 5;

		verts[ vertIndexA ].m_position = innerEndPos;
		verts[ vertIndexB ].m_position = innerStartPos;
		verts[ vertIndexC ].m_position = outerStartPos;
		verts[ vertIndexA ].m_color = color;
		verts[ vertIndexB ].m_color = color;
		verts[ vertIndexC ].m_color = color;


		verts[ vertIndexD ].m_position = innerEndPos;
		verts[ vertIndexE ].m_position = outerStartPos;
		verts[ vertIndexF ].m_position = outerEndPos;
		verts[ vertIndexD ].m_color = color;
		verts[ vertIndexE ].m_color = color;
		verts[ vertIndexF ].m_color = color;
	}

	g_engine->m_render->DrawVertexArray( NUM_VERTS, verts );
}

