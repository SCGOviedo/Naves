#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "EnemyBase.h"
#include "EnemyNuevo.h"
#include "Projectile.h"
#include "Text.h"
#include "Audio.h" 
#include <list>

using namespace std;
class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);

	Audio* audioBackground;
	Text* textPoints;
	Text* textLives;
	int points;
	int newEnemyTime = 0;
	Player* player;
	Background* background;
	Actor* backgroundPoints;
	Actor* backgroundLives;
	list<EnemyBase*> enemies;
	list<Projectile*> projectiles;

	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;


};

