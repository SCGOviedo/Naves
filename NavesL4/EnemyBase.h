#pragma once

#include "Actor.h" 
#include "Animation.h"  

#include "Projectile.h" 
#include "Audio.h"
class EnemyBase : public Actor 
{
public:
	EnemyBase(string quieto, string movimiento, float x, float y, Game* game); 
	void draw() override; // Va a sobrescribir 
	Animation* aMoving; 
	Animation* animation; // Referencia a la animación mostrada 
	 
	virtual void update(); 
	int vida = 3;

	Projectile* shoot();
	Audio* audioShoot;
	int shootCadence = 90;
	int shootTime = 0;
}; 
 