#pragma once

#include "Actor.h" 
#include "Animation.h"  

class EnemyBase : public Actor 
{
public:
	EnemyBase(string quieto, string movimiento, float x, float y, Game* game); 
	void draw() override; // Va a sobrescribir 
	Animation* aMoving; 
	Animation* animation; // Referencia a la animación mostrada 
	 
	virtual void update(); 
	int vida = 3;
}; 
 