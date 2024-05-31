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
	inicial_y = 0;
	inicial_x = 0;

	
	cout << "tiempo: " << t->asSeconds() << endl;


	sp_fondo = new Sprite;
	tx_fondo = new Texture;
	tx_fondo->loadFromFile("assets/mundo_fondo.jpg");
	sp_fondo->setTexture(*tx_fondo);

	player = new Player("assets/spritesheet.png",Vector2i(26,30),Vector2f(25, 460),5);
	bloque[10] = new Bloque("assets/bloque_pared.png", Vector2i(26, 30), Vector2f(200, 0), 5);

	//bool direccion;
	//Vector2f magnitud_salto;
	//magnitud_salto.y = 10;

	gameloop();
}

void Game::gameloop() {
	while (w->isOpen()) {
		*t= clock->getElapsedTime();
		//cout << "tiempo: " << t->asSeconds() << endl;
		//cout << "tiempo del player " << player->get_time() << endl;
		while (w->pollEvent(*e)) {
			if (e->type == Event::Closed)
				w->close();
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player->set_position(player->get_position().x - 5, player->get_position().y);
				inicial_x = -3;

			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				player->set_position(player->get_position().x + 5, player->get_position().y);
				inicial_x = +3;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {//SI SE PRESIONA ESPACIO
				w->setKeyRepeatEnabled(false);           //BLOQUEO PARA QUE NO VUELVA A TOMAR LA ACCION HASTA TERMINAR EL CICLO
				//clock->restart();
				inicial_y = player->get_position().y;
				//while(player->get_position().y >= inicial_y -100) {
				for (int i = 0; i <= 11; i++) {
					if (t->asSeconds()>=0.3){
					    player->set_position(player->get_position().x + inicial_x, player->get_position().y -12);
					    cout << "subida en y  " << player->get_position().y << "   subida en x  " << player->get_position().x << endl;
					    clock->restart();
					    dibujar();
					}
				}
				//while (player->get_position().y < inicial_y) {
				for (int i = 0; i <= 11; i++) {
					if (t->asSeconds()>=0.3) {
						player->set_position(player->get_position().x + inicial_x, player->get_position().y + 12);
						cout << "caida en y  " << player->get_position().y << "   caida en x  " << player->get_position().x<<endl;
						clock->restart();
						dibujar();
					}
				}
				inicial_x = 0;
			}
			w->setKeyRepeatEnabled(true);  //ACTIVO EL SETKEYREPEATENABLED ANTES DE TERMINAR EL CICLO DE SALTO
		}
		dibujar();
	}
}

void Game::dibujar() {
	w->clear(Color(255, 255, 255, 255));
	w->draw(*sp_fondo);
	w->draw(player->get_sprite());
	
	w->display();
}