#include <windows.h>
#include <gl/gl.h>		
#include "PlayerShip.hpp"			
#include <Engine/Core/Vertex.hpp>
#include "Engine/Math/Vec3.hpp"
#include "GameCommon.hpp"
#include <Engine/Core/VertexUtils.hpp>
#include <Engine/Core/Engine.cpp>
#include "App.hpp"


PlayerShip::PlayerShip(Game* owner, Vec2 const& startPos)
	: Entity( owner, startPos )
{
	m_physicsRadius = PLAYER_SHIP_PHYSICS_RADIUS;
	m_cosmeticRadius = PLAYER_SHIP_COSMETIC_RADIUS;
	InitializeLocalVerts();
}


PlayerShip::~PlayerShip()
{

}


void PlayerShip::Update(float deltaSeconds)
{
	UpdateFromKeyboard(deltaSeconds);

	m_position.x += m_velocity.x * deltaSeconds;
	m_position.y += m_velocity.y * deltaSeconds;
}


void PlayerShip::Render() const
{
	if( m_isDead )
		return;

	Vertex tempShipWorldVerts[NUM_SHIP_VERTS];
	for (int vertIndex = 0; vertIndex < NUM_SHIP_VERTS; ++vertIndex)
	{
		tempShipWorldVerts[vertIndex] = m_localVerts[vertIndex];
	}

	TransformVertexArrayXY3D(NUM_SHIP_VERTS, tempShipWorldVerts, 1.f, m_orientationDegrees, m_position);
	g_engine->m_render->DrawVertexArray(NUM_SHIP_VERTS, tempShipWorldVerts);
}


void PlayerShip::DebugRender() const
{
}


void PlayerShip::InitializeLocalVerts()
{
	// Nose cone
	m_localVerts[0].m_position = Vec3( 1.f,  0.f, 0.f );
	m_localVerts[1].m_position = Vec3( 0.f,  1.f, 0.f );
	m_localVerts[2].m_position = Vec3( 0.f, -1.f, 0.f );

	// Left wing
	m_localVerts[3].m_position = Vec3(  2.f, 1.f, 0.f );
	m_localVerts[4].m_position = Vec3(  0.f, 2.f, 0.f );
	m_localVerts[5].m_position = Vec3( -2.f, 1.f, 0.f );

	// Right wing
	m_localVerts[6].m_position = Vec3(  2.f, -1.f, 0.f );
	m_localVerts[7].m_position = Vec3( -2.f, -1.f, 0.f );
	m_localVerts[8].m_position = Vec3(  0.f, -2.f, 0.f );

	// Body (quad tri 1 of 2)
	m_localVerts[9].m_position = Vec3( 0.f, 1.f, 0.f );
	m_localVerts[10].m_position = Vec3( -2.f, -1.f, 0.f );
	m_localVerts[11].m_position = Vec3( 0.f, -1.f, 0.f );

	// Body (quad tri 2 of 2)
	m_localVerts[12].m_position = Vec3(  0.f,  1.f, 0.f );
	m_localVerts[13].m_position = Vec3( -2.f,  1.f, 0.f );
	m_localVerts[14].m_position = Vec3( -2.f, -1.f, 0.f );
	
	for ( int vertIndex = 0; vertIndex < NUM_SHIP_VERTS; ++ vertIndex )
	{
		m_localVerts[vertIndex].m_color = Rgba8( 102, 153, 204 );
	}
}

void PlayerShip::UpdateFromKeyboard(float deltaSeconds)
{
	if(m_isDead)
		return;

	if(g_app->IsKeyDown('E'))
	{
		Vec2 forwardVector = GetForwardNormal();
		m_velocity.x += forwardVector.x * PLAYER_SHIP_ACCELERATION * deltaSeconds;
		m_velocity.y += forwardVector.y * PLAYER_SHIP_ACCELERATION * deltaSeconds;
	}
	else if(g_app->IsKeyDown('S'))
	{
		m_orientationDegrees += PLAYER_SHIP_TURN_SPEED * deltaSeconds;
	}
	else if (g_app->IsKeyDown('F'))
	{
		m_orientationDegrees -= PLAYER_SHIP_TURN_SPEED * deltaSeconds;
	}
	else {
		m_velocity.x = 0.f;
		m_velocity.y = 0.f;
	}
}
