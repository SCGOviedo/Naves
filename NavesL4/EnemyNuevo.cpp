#include "EnemyNuevo.h"
EnemyNuevo::EnemyNuevo(float x, float y, Game* game)
	: EnemyBase(string("res/enemigo_nuevo.png"), string("res/enemigo_nuevo_movimiento.png"), x, y, game) {
	int cual = (rand() % (2));
	vy = 1;
	if (cual == 0)
		vy *= -1;
}

void EnemyNuevo::update() {
	// Actualizar la animación
	animation->update();

	vx = -1.5;
	x = x + vx;
	y = y + vy;

	if (y < 20 || y>300) 
		vy *= -1;

	if (shootTime > 0) {
		shootTime--;
	}
}


