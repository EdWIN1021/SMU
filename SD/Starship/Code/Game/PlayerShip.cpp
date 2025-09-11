/* OpenGl */
#include <windows.h>
#include <gl/gl.h>		

/* Engine */
#include "Engine/Core/Vertex.hpp"
#include "Engine/Math/Vec3.hpp"
#include "Engine/Core/VertexUtils.hpp"
#include "Engine/Core/Engine.cpp"
#include "Engine/Core/Rgba8.hpp"

#include "PlayerShip.hpp"			
#include "Bullet.hpp"

#include "App.hpp"
#include "Game/Game.hpp"
#include "GameCommon.hpp"
#include <Engine/Core/ErrorWarningAssert.hpp>
#include <Engine/Core/StringUtils.hpp>


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
	m_position += m_velocity * deltaSeconds;

	BounceOffWalls();
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
	if (g_app->WasKeyJustPressed('N') && m_isDead)
	{
		Respawn();
	}

	if (m_isDead)
		return;

	if(g_app->IsKeyDown('E'))
	{
		Vec2 forwardVector = GetForwardNormal();
		m_velocity += forwardVector * PLAYER_SHIP_ACCELERATION * deltaSeconds;
	}
	
	if(g_app->IsKeyDown('S') && !g_app->IsKeyDown('F'))
	{
		m_orientationDegrees += PLAYER_SHIP_TURN_SPEED * deltaSeconds;
	}
	
	if (g_app->IsKeyDown('F') && !g_app->IsKeyDown('S'))
	{
		m_orientationDegrees -= PLAYER_SHIP_TURN_SPEED * deltaSeconds;
	}
	
	if (g_app->WasKeyJustPressed(VK_SPACE))
	{
		if(m_game->m_bulletSize < MAX_BULLETS)
		{
			m_game->m_bullets[m_game->m_bulletSize] = new Bullet( m_game, m_position + GetForwardNormal());
			m_game->m_bullets[m_game->m_bulletSize]->m_orientationDegrees = m_orientationDegrees;
			m_game->m_bullets[m_game->m_bulletSize]->m_velocity = GetForwardNormal() * BULLET_SPEED;
			m_game->m_bulletSize++;
		}
		else{
			RecoverableWarning(
				__FILE__,
				__FUNCTION__,
				__LINE__,
				Stringf("Cannot fire more bullets! Maximum allowed is %i.", MAX_BULLETS),
				"Size of bullets > MAX_BULLETS"
			);
		}
	}
}

void PlayerShip::BounceOffWalls()
{
	if (IsOffscreen())
	{
		m_velocity = -m_velocity;
	}
}

void PlayerShip::Respawn()
{
	m_position = Vec2(WORLD_CENTER_X, WORLD_CENTER_Y);
	m_isDead = false;
	m_orientationDegrees = 0.f;
	m_velocity = Vec2();
}

