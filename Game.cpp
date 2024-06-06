#include "Game.h"
#include "iostream"

using namespace std;

Game::Game(int alto_w, int ancho_w, String nombre) {
	fps = 60;
	srand(time(0));
	w = new RenderWindow(VideoMode(800, 600), nombre);
	w->setFramerateLimit(fps);
	e = new Event;

	clock = new Clock();
	t = new Time();

	*t = clock->getElapsedTime();
    cout << "tiempo animacion : " << t->asSeconds() << endl;

	sp_fondo = new Sprite;
	tx_fondo = new Texture;
	tx_fondo->loadFromFile("assets/mundo_fondo.jpg");
	sp_fondo->setTexture(*tx_fondo);

	temporizador = new Timer(60, w->getSize().x -200,30);
	player = new Player("assets/spritesheet.png", Vector2i(26, 30), Vector2f(25, 460), 5);

	bloque1 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(50, 260), rand()%1000);
	bloque2 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(125, 260), rand() % 1000);
	bloque3 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(200, 260), rand() % 1000);
	bloque4 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(275, 450), rand() % 1000);
	bloque5 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(350, 260), rand() % 1000);
	bloque6 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(350, 260), rand() % 1000);
	bloque7 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(425, 260), rand() % 1000);
	bloque8 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(500, 260), rand() % 1000);
	bloque9 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(575, 260), rand() % 1000);
	bloque10 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(650, 260), rand() % 1000);

	bloque[0] = bloque1;
	bloque[1] = bloque2;
	bloque[2] = bloque3;
	bloque[3] = bloque4;
	bloque[4] = bloque5;
	bloque[5] = bloque6;
	bloque[6] = bloque7;
	bloque[7] = bloque8;
	bloque[8] = bloque9;
	bloque[9] = bloque10;

	gameloop();
}

void Game::gameloop() {
	while (w->isOpen()) {
		*t = clock->getElapsedTime();
		temporizador->actualizar_temp();//ACTUALIZA EL TEMPORIZADOR
		//for (int i = 0; i < 10; i++) {
			//if (bloque[i]->get_sprite().getGlobalBounds().intersects(player->get_sprite().getGlobalBounds()));
			//cout << "colision con bloque" << endl;
		//}
		//cout << "tiempo juego : " << t->asSeconds() << endl;
		//cout << "tiempo del player " << player->get_time() << endl;
		while (w->pollEvent(*e)) {
			if (e->type == Event::Closed)
				w->close();
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player->set_position(player->get_position().x - 5, player->get_position().y);
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				for (int i = 0; i < 10; i++) {
					if (bloque[i]->get_sprite().getGlobalBounds().intersects(player->get_sprite().getGlobalBounds()));
					cout << "colision con bloque" << endl;
				}
				player->set_position(player->get_position().x + 5, player->get_position().y);
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {//SI SE PRESIONA ESPACIO
				w->setKeyRepeatEnabled(false);           //BLOQUEO PARA QUE NO VUELVA A TOMAR LA ACCION HASTA TERMINAR EL CICLO
				//CICLO DE SUBIDA DEL SALTO
				for (int i = 0; i <= 11; i++) {
					temporizador->actualizar_temp();
					if (t->asSeconds() >= 0.5) {
						for (int i = 0; i < 10; i++) {
							if (bloque[i]->get_sprite().getGlobalBounds().intersects(player->get_sprite().getGlobalBounds()));
							cout << "colision con bloque" << endl;
						}
						player->set_position(player->get_position().x, player->get_position().y - 20);
						if (Keyboard::isKeyPressed(Keyboard::D)) {
							player->set_position(player->get_position().x + 5, player->get_position().y);
						}
						if (Keyboard::isKeyPressed(Keyboard::A)) {
							player->set_position(player->get_position().x - 5, player->get_position().y);
						}
						cout << "subida en y  " << player->get_position().y << "   subida en x  " << player->get_position().x << endl;
						clock->restart();
						dibujar();
					}
				}
				//CICLO DE CAIDA DEL SALTO
				for (int i = 0; i <= 11; i++) {
					temporizador->actualizar_temp();
					if (t->asSeconds() >= 0.5) {
						player->set_position(player->get_position().x , player->get_position().y + 20);
						if (Keyboard::isKeyPressed(Keyboard::D)) {
							player->set_position(player->get_position().x + 5, player->get_position().y);
						}
						if (Keyboard::isKeyPressed(Keyboard::A)) {
							player->set_position(player->get_position().x - 5, player->get_position().y);
						}
						cout << "caida en y  " << player->get_position().y << "   caida en x  " << player->get_position().x << endl;
						clock->restart();
						dibujar();
					}
				}
			}
			w->setKeyRepeatEnabled(true);  //ACTIVO EL SETKEYREPEATENABLED ANTES DE TERMINAR EL CICLO DE SALTO
		}
		dibujar();
	}
}

bool colision(Player pj, Bloque b[], int n) {
	bool colision = false;;
	for (int i = 0; i < n; i++) {
		if (b[n].get_sprite().getGlobalBounds().intersects(pj.get_sprite().getGlobalBounds()));
		colision = true;
	}
	return colision;
}

void Game::dibujar() {
	w->clear(Color(255, 255, 255, 255));
	w->draw(*sp_fondo);
	w->draw(player->get_sprite());
	w->draw(temporizador->get_text());
	for (int i = 0; i < 10; i++) {
		w->draw(bloque[i]->get_sprite());
		w->draw(bloque[i]->get_texto());
	}
	w->display();
}
