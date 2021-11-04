#include "EnemyBase.h" 
 
EnemyBase::EnemyBase(string quieto, string movimiento, float x, float y, Game* game) 
	: Actor(quieto, x, y, 36, 40, game) { 
	 
	aMoving = new Animation(movimiento, width, height, 
		108, 40, 6, 3, game); 
	animation = aMoving; 
	 
	vx = 1; 
	audioShoot = new Audio("res/efecto_disparo.wav", false);

} 
void EnemyBase::draw() { 
	animation->draw(x, y); 
} 

void EnemyBase::update() 
{ 
} 

Projectile* EnemyBase::shoot() {

	if (shootTime == 0) {
		audioShoot->play();
		shootTime = shootCadence;
		return  new Projectile(x, y, game, Tipe::Enemy);

	}
	else {
		return NULL;
	}
}