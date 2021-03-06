#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	points = 0;
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = to_string(points);

	player = new Player(50, 50, game);
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	backgroundPoints = new Actor("res/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);

	backgroundLives =new Actor("res/corazon.png",
			WIDTH * 0.05, HEIGHT * 0.05, 44, 36, game);
	textLives = new Text("3", WIDTH * 0.15, HEIGHT * 0.04, game);
	textLives->content = to_string(player->vidas);

	enemies.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	monedas.clear(); // Vaciar por si reiniciamos el juego

	enemies.push_back(new Enemy(300, 50, game));
	enemies.push_back(new EnemyNuevo(300, 200, game));
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
	//procesar controles
	//procesar controles
	// Disparar
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}

	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}



}

void GameLayer::update() {
	

	background->update();
	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
		if (enemy->shootTime == 0) {
			projectiles.push_back(enemy->shoot());
		}

	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}
	for (auto const& moneda : monedas) {
		moneda->update();
	}
	// Generar enemigos
	newEnemyTime--;
	if (newEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		enemies.push_back(new Enemy(rX, rY, game));
		rX = (rand() % (600 - 500)) + 1 + 500;
		rY = (rand() % (300 - 60)) + 1 + 60;
		monedas.push_back(new Coin(rX, rY, game));
		enemies.push_back(new EnemyNuevo(rX, rY, game));
		newEnemyTime = 110;
	}

	// Colisiones
	bool colision = false;
	EnemyBase* enemigoMuerto;
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			if (player->inmune == 0){
				colision = true;
				enemigoMuerto = enemy;
				player->vidas--;
				player->inmune = 50;
				textLives->content = to_string(player->vidas);
			}
			if (player->vidas == 0) {
				init();
				return; // Cortar el for
			}
		}
	}
	if(colision)
		enemies.remove(enemigoMuerto);//eliminamos el enemigo

	colision = false;
	Projectile* projectileDado;
	for (auto const& projectile : projectiles) {
		if (player->isOverlap(projectile) && projectile->tipe == Tipe::Enemy) {
			if (player->inmune == 0) {
			colision = true;
			player->vidas--;
			player->inmune = 50;
			textLives->content = to_string(player->vidas);
			projectileDado = projectile;
			}
		}
		if (player->vidas == 0) {
			init();
			return; // Cortar el for
		}
	}
	if (colision)
		projectiles.remove(projectileDado);//eliminamos el enemigo

bool colisionMoneda = false;
	Coin* moneda;
	for (auto const& coin : monedas) {
		if (player->isOverlap(coin)) {
			moneda = coin;
			colisionMoneda = true;
			points++;
			textPoints->content = to_string(points);
		}
	}
	if (colisionMoneda)
		monedas.remove(moneda);
	for (auto const& projectile : projectiles) {
		if(player->isOverlap(projectile) && projectile->tipe == Tipe::Enemy) {
			init();
			return; // Cortar el for
		}
	}
	// Colisiones , Enemy - Projectile

	list<EnemyBase*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	for (auto const& projectile : projectiles) {
		if (projectile->isInRender() == false) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}



	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile) && projectile->tipe==Tipe::Player) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
				enemy->vida--;
				if (enemy->vida == 0) {
					bool eInList = std::find(deleteEnemies.begin(),
						deleteEnemies.end(),
						enemy) != deleteEnemies.end();

					if (!eInList) {
						deleteEnemies.push_back(enemy);
					}

					points++;
					textPoints->content = to_string(points);
				}


			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

}

void GameLayer::draw() {
	background->draw();
	for (auto const& projectile : projectiles) {
		projectile->draw();
	}
	for (auto const& moneda : monedas) {
		moneda->draw();
	}
	player->draw();
	for (auto const& enemy : enemies) {
		enemy->draw();
	}

	backgroundPoints->draw();
	backgroundLives->draw();
	textPoints->draw();
	textLives->draw();
	SDL_RenderPresent(game->renderer); // Renderiza
}
void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		}


	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}

	}

}

