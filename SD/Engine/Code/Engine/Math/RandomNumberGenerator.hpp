#pragma once

class RandomNumberGenerator;
extern RandomNumberGenerator* g_rng;

class RandomNumberGenerator
{
public:
	int RollRandomIntLessThan(int maxNotInclusive);
	int RollRandomIntInRange(int minInclusive, int maxInclusive);
	float RollRandomFloatZeroToOne();
	float RollRandomFloatInRange(float minInclusive, float maxInclusive);

private:
	//	unsigned int		m_seed = 0;
	//	int					m_position = 0;
};