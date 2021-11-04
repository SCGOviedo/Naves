#pragma once
#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"


class Shooter : public Actor
{
public:
	Shooter(string foto, float x, float y, int x1, int y1, Game* game);
	//Projectile* shoot();
	Audio* audioShoot = new Audio("res/efecto_disparo.wav", false);
	int shootTime = 0;
	int shootCadence = 30;
	void update();
	Tipe tipe=Tipe::Player;
};

