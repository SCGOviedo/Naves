#include "Enemy.h" 

Enemy::Enemy(float x, float y, Game* game) 
	: EnemyBase(string("res/enemigo.png"),string("res/enemigo_movimiento.png"), x, y, game) { 
} 

void Enemy::update() { 
	// Actualizar la animación 
	animation->update(); 
	 
	vx = -1; 
	x = x + vx; 
	 
} 
  

