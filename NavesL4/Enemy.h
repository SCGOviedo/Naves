#pragma once

#include "Actor.h"
#include "Animation.h" 

#include "Projectile.h" 
#include "Audio.h"

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	void draw() override; // Va a sobrescribir
	void update();
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
	Projectile* shoot();
	Audio* audioShoot;
	int shootCadence = 90;
	int shootTime = 0;
};
