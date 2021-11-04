#include "Shooter.h"


Shooter::Shooter(string foto, float x, float y, int x1, int y1, Game* game)
	: Actor(foto, x, y, x1, y1, game) {
}
Projectile* Shooter::shoot() {

	if (shootTime == 0) {
		audioShoot->play();
		shootTime = shootCadence;
		return new Projectile(x, y, game);
	}
	else {
		return NULL;
	}
}
void Shooter::update() {
	if (shootTime > 0) {
		shootTime--;
	}
}