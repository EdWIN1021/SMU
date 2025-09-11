#pragma once

/* Engine */
#include "Engine/Math/Vec2.hpp"

/* Game */
#include "Entity.hpp"
#include "Engine/Core/Vertex.hpp"


constexpr int NUM_SHIP_TRIS = 5;
constexpr int NUM_SHIP_VERTS = 3 * NUM_SHIP_TRIS;

class PlayerShip : public Entity
{
public:
	PlayerShip( Game* owner, Vec2 const& startPos );
	~PlayerShip();

	void Update(float deltaSeconds) override;
	void Render() const override;

private:
	void InitializeLocalVerts();
	void UpdateFromKeyboard( float deltaSeconds );
	void BounceOffWalls();
	void Respawn();


public:
	Vertex  m_localVerts[NUM_SHIP_VERTS];
	bool    m_isTurningLeft     = false;
	bool    m_isTurningRight    = false;
	bool    m_isThrusting       = false;
};