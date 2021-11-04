#pragma once 

#include "EnemyBase.h" 
#include "Animation.h"  

class Enemy : public EnemyBase 
{ 
public: 
	Enemy(float x, float y, Game* game); 
	void update() override; 
}; 
