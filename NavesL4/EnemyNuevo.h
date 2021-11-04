#pragma once

#include "EnemyBase.h"
#include "Animation.h" 

class EnemyNuevo : public EnemyBase
{
public:
	EnemyNuevo(float x, float y, Game* game);
	void update() override;
};
