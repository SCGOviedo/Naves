#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 36, 40, game) {
	audioShoot = new Audio("res/efecto_disparo.wav", false);

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, game);
	animation = aMoving;

	vx = 1;
}

void Enemy::update() {
	// Actualizar la animación
	animation->update();

	vx = -1;
	x = x + vx;

	if (shootTime > 0) {
		shootTime--;
	}
}


Projectile* Enemy::shoot() {

	if (shootTime == 0) {
		audioShoot->play();
		shootTime = shootCadence;
		return  new Projectile(x, y, game, Tipe::Enemy);
		
	}
	else {
		return NULL;
	}
}