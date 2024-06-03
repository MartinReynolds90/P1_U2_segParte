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
	//clock_temporizador = new Clock();
	//time_temporizador = new Time();

	*t = clock->getElapsedTime();
	//*time_temporizador = clock_temporizador->getElapsedTime();
    cout << "tiempo animacion : " << t->asSeconds() << endl;
	//cout << "tiempo temporizador: " << time_temporizador->asSeconds() << endl;


	sp_fondo = new Sprite;
	tx_fondo = new Texture;
	tx_fondo->loadFromFile("assets/mundo_fondo.jpg");
	sp_fondo->setTexture(*tx_fondo);

	font_temporizador.loadFromFile("assets/Square.ttf");
	text_temporizador.setFont(font_temporizador);
	temporizador_string = " " + to_string(t->asSeconds());
	text_temporizador.setString(temporizador_string);
	text_temporizador.setPosition(w->getSize().x /2, 30);
	text_temporizador.setFillColor(Color::Black);

	player = new Player("assets/spritesheet.png", Vector2i(26, 30), Vector2f(25, 460), 5);

	bloque1 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(50, 260), rand()%1000);
	bloque2 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(125, 260), rand() % 1000);
	bloque3 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(200, 260), rand() % 1000);
	bloque4 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(275, 260), rand() % 1000);
	bloque5 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(350, 260), rand() % 1000);
	bloque6 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(350, 260), rand() % 1000);
	bloque7 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(425, 260), rand() % 1000);
	bloque8 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(500, 260), rand() % 1000);
	bloque9 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(575, 260), rand() % 1000);
	bloque10 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(650, 260), rand() % 1000);

	//bloque[10] = new Bloque; //{bloque1, bloque2, bloque3, bloque4, bloque5, bloque6, bloque7, bloque8, bloque9, bloque10 }
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


	/*Bloque bloque1("assets/bloque_pared.png", Vector2i(45, 45), Vector2f(50, 200), 5);
	Bloque bloque2("assets/bloque_pared.png", Vector2i(45, 45), Vector2f(80, 200), 5);
	Bloque bloque3("assets/bloque_pared.png", Vector2i(45, 45), Vector2f(110, 200), 5);
	Bloque bloque4("assets/bloque_pared.png", Vector2i(45, 45), Vector2f(140, 200), 5);
	Bloque bloque5("assets/bloque_pared.png", Vector2i(45, 45), Vector2f(170, 200), 5);
	Bloque bloque6("assets/bloque_pared.png", Vector2i(45, 45), Vector2f(200, 200), 5);
	Bloque bloque7("assets/bloque_pared.png", Vector2i(45, 45), Vector2f(230, 200), 5);
	Bloque bloque8("assets/bloque_pared.png", Vector2i(45, 45), Vector2f(260, 200), 5);
	Bloque bloque9("assets/bloque_pared.png", Vector2i(45, 45), Vector2f(290, 200), 5);
	Bloque bloque10("assets/bloque_pared.png", Vector2i(45, 45), Vector2f(320, 200), 5);*/
		
	//Bloque bloque[10]{ bloque1, bloque2, bloque3, bloque4, bloque5, bloque6, bloque7, bloque8, bloque9, bloque10 };


	gameloop();
}

void Game::gameloop() {
	while (w->isOpen()) {
		*t = clock->getElapsedTime();
		//*time_temporizador = clock_temporizador->getElapsedTime();

		temporizador_string = " " + to_string(t->asSeconds()); //Actualiza el tiempo, lo convierte eb String y lo guarda en la variable temporizador_string
		text_temporizador.setString(temporizador_string);      //Le paso la variable temporizador_string actualizada
		cout << "tiempo animacion : " << t->asSeconds() << endl;
		//cout << "tiempo temporizador: " << time_temporizador->asSeconds() << endl;
		//cout << "tiempo: " << t->asSeconds() << endl;
		cout << "tiempo del player " << player->get_time() << endl;
		while (w->pollEvent(*e)) {
			if (e->type == Event::Closed)
				w->close();
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player->set_position(player->get_position().x - 5, player->get_position().y);
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				player->set_position(player->get_position().x + 5, player->get_position().y);
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {//SI SE PRESIONA ESPACIO
				w->setKeyRepeatEnabled(false);           //BLOQUEO PARA QUE NO VUELVA A TOMAR LA ACCION HASTA TERMINAR EL CICLO
				//clock->restart();
				//CICLO DE SUBIDA DEL SALTO
				for (int i = 0; i <= 11; i++) {
					if (t->asSeconds() >= 0.3) {
						player->set_position(player->get_position().x, player->get_position().y - 12);
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
					if (t->asSeconds() >= 0.3) {
						player->set_position(player->get_position().x , player->get_position().y + 12);
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

void Game::dibujar() {
	w->clear(Color(255, 255, 255, 255));
	w->draw(*sp_fondo);
	w->draw(player->get_sprite());
	w->draw(text_temporizador);
	for (int i = 0; i < 10; i++) {
		w->draw(bloque[i]->get_sprite());
		w->draw(bloque[i]->get_texto());
	}
	w->display();
}
