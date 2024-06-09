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

	for (int i = 0; i < 10; i++) {                 //LE CARGO LOS VALORES AL ARREGLO Y SE LO ASIGNO A CADA BLOQUE MAS ABAJO
		arreglo_numeros[i] = rand() % 1000;
	}

	temporizador = new Timer(60, w->getSize().x -200,30); //CREO UN TEMPORIZADOR

	player = new Player("assets/spritesheet.png", Vector2i(26, 30), Vector2f(25, 460));//CREO UN PLAYER
	colision_arriba = false;
	num_anterior = 0;
	descontar_diez = false;
	 

	bloque1 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(50, 260), arreglo_numeros[0]);
	bloque2 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(117.5, 260), arreglo_numeros[1]);
	bloque3 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(185, 260), arreglo_numeros[2]);
	bloque4 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(252.5, 260), arreglo_numeros[3]);
	bloque5 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(320, 260), arreglo_numeros[4]);
	bloque6 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(387.5, 260), arreglo_numeros[5]);
	bloque7 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(455, 260), arreglo_numeros[6]);
	bloque8 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(522.5, 260), arreglo_numeros[7]);
	bloque9 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(590, 260), arreglo_numeros[8]);
	bloque10 = new Bloque("assets/bloque_pared.png", Vector2i(0, 0), Vector2f(657.5, 260), arreglo_numeros[9]);

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

		//cout << "tiempo juego : " << t->asSeconds() << endl;
		//cout << "tiempo del player " << player->get_time() << endl;
		while (w->pollEvent(*e)) {
			
			if (e->type == Event::Closed) {
				w->close();
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player->set_position(player->get_position().x - 5, player->get_position().y);
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
					player->set_position(player->get_position().x + 5, player->get_position().y);
			}
			if (Keyboard::isKeyPressed(Keyboard::O)) {
				ordenar_arreglo(arreglo_numeros, 10);
				for (int i = 0; i < 10; i++) {
					bloque[i]->set_int(arreglo_numeros[i]);  
					cout << "numero ordenados-> " << arreglo_numeros[i] << endl;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {//SI SE PRESIONA ESPACIO
				w->setKeyRepeatEnabled(false);            //BLOQUEO PARA QUE NO VUELVA A TOMAR LA ACCION HASTA TERMINAR EL CICLO
				//CICLO DE SUBIDA DEL SALTO
				for (int i = 0; i <= 12; i++) {//FOR DE SUBIDA
					temporizador->actualizar_temp();
					for(int i=0; i<10; i++){   //FOR QUE RECORRE LOS GLOBAL BOUNDS DE LOS BLOQUES
					    rect_bloque = bloque[i]->get_sprite().getGlobalBounds();//OBTENGO EL RECTANGULO DE CADA LOQUE PARA VER SI COLISIONA EL PLAYER 
					    pos_saltando.x = player->get_position().x + 26;         //EL CENTRO DEL PLAYER EN EL EJE X(PARA QUE COLISIONE CON UN SOLO BLOQUE)
						pos_saltando.y = player->get_position().y;
					    if (rect_bloque.contains(pos_saltando)) {//SI INTERSECTA CON EL BLOQUE i
							colision_arriba = true;              //ACTIVA EL BOOL DE COLISION
							bloque_colisionado = i;              //GUARDA LA POSICION EN EL ARREGLO DEL BLOQUE COLISIONADO
							if (bloque[i]->get_int() >= num_anterior) {
								cout << "numero que tiene el bloque colisionado (" << bloque_colisionado << "), es mayor al anterior : " << bloque[i]->get_int() << ">" << num_anterior << endl;
								bloque[i]->set_color(Color::Green);   //LE CAMBIA EL COLOR DEL NUMERO A VERDE SI ES CORRECTO
								num_anterior = bloque[i]->get_int();  //GUARDA EL NUMERO(texto) DEL BLOQUE GOLPEADO PARA COMPARARLO CON EL NUMERO DEL PROXIMO BLOQUE QUE GOLPEARÁ
							}
							else {
								cout << "numero que tiene el bloque colisionado (" << bloque_colisionado << "), es menor al anterior : " << bloque[i]->get_int() << "<" << num_anterior << endl;
								descontar_diez = true;                //SI ES INCORRECTO ACTIVA EL BOOL DE DESCUNTO DE TIEMPO    
							} 
					    }
					}
					if (t->asSeconds() >= 0.5 && colision_arriba == false) {  //ESPERA MEDIO SEGUNDO Y SI NO HAY COLISION CON BLOQUE 
						player->set_position(player->get_position().x, player->get_position().y - 20);//SE DESPLAZA HACIA ARRIBA
						if (Keyboard::isKeyPressed(Keyboard::D)) {
							player->set_position(player->get_position().x + 5, player->get_position().y);//DESPLAZAMIENTO HORIZONTAL MIENTRAS SALTA
						}
						if (Keyboard::isKeyPressed(Keyboard::A)) {
							player->set_position(player->get_position().x - 5, player->get_position().y);//DESPLAZAMIENTO HORIZONTAL MIENTRAS SALTA
						}
						clock->restart();
						dibujar();
					}
				}
				temporizador->penalizacion_time(descontar_diez);//CONUSULTA SI HAY PENALIZACION DE TIEMPO CUANDO TERMINA EL CICLO DE SUBIDA 
				//CICLO DE CAIDA DEL SALTO
				for (int i = 0; i <= 12; i++) {
					colision_arriba = false; //CUANDO EMPIEZA A CAER DESACTIVA LA COLISION CON EL BLOQUE
					temporizador->actualizar_temp();
					if (t->asSeconds() >= 0.5 && player->get_position().y <= 445) {                    //SI SIGUE POR ENCIMA DEL NIVEL DEL SUELO, SIGUE CAYENDO
						player->set_position(player->get_position().x , player->get_position().y + 20);//SE DESPLAZA HACIA ABAJO(CAE)
						if (Keyboard::isKeyPressed(Keyboard::D)) {
							player->set_position(player->get_position().x + 5, player->get_position().y);//DESPLAZAMIENTO HORIZONTAL MIENTRAS SALTA
						}
						if (Keyboard::isKeyPressed(Keyboard::A)) {
							player->set_position(player->get_position().x - 5, player->get_position().y);//DESPLAZAMIENTO HORIZONTAL MIENTRAS SALTA
						}
						clock->restart();
						dibujar();
					}
				}
			}
			w->setKeyRepeatEnabled(true);  //ACTIVO EL SETKEYREPEATENABLED AL TERMINAR EL CICLO DE SALTO
		}
		dibujar();
	}
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

void Game::ordenar_arreglo(int arr[],int n) {
		int i, j, min;
		for (i = 0; i < n; i++) { 
			for (j = 0; j < n; j++) { 
				if (arr[j] > arr[j + 1]) {
					min = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = min;
				}
			}
		}
}