#pragma once

#include "Actor.h"


class Projectile : public Actor
{
public:
	Projectile(float x, float y, Game* game, Tipe tipe);
	void update();
	Tipe tipe = Tipe::Player;
};

