#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game, Tipe tip) :
	Actor("res/disparo_jugador.png", x, y, 18, 6, game) {
	tipe = tip;
	if (tipe == Tipe::Player)
		vx = 9;
	else
		vx = -4;
}

void Projectile::update() {
	x = x + vx;
}
