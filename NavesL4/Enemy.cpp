#include "Enemy.h" 

Enemy::Enemy(float x, float y, Game* game) 
	: EnemyBase(string("res/enemigo.png"),string("res/enemigo_movimiento.png"), x, y, game) { 
} 

void Enemy::update() { 
	// Actualizar la animaci�n 
	animation->update(); 
	 
	vx = -1; 
	x = x + vx; 
	 
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