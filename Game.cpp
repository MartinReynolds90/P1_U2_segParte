#include "Game.h"
#include "iostream"

using namespace std;

Game::Game(int alto_w, int ancho_w, String nombre) {
	fps = 60;
	srand(time(0));
	w = new RenderWindow(VideoMode(800, 600), nombre);
	w->setFramerateLimit(fps);
	e = new Event;

	clock = new Clock(); //INICIO EL TIEMPO DE LA CLASE GAME
	t = new Time();
    *t = clock->getElapsedTime();

	sp_fondo = new Sprite;  //CARGO EL FONDO
	tx_fondo = new Texture;
	tx_fondo->loadFromFile("assets/mundo_fondo.jpg");
	sp_fondo->setTexture(*tx_fondo);

	for (int i = 0; i <= 10; i++) {                 //GENERO LOS VALORES DESORDENADOS DEL ARREGLO Y SE LO ASIGNO A CADA BLOQUE MAS ABAJO
		arreglo_numeros[i] = rand() % 1000;
	}

	temporizador = new Timer(60, w->getSize().x -200,30); //CREO UN TEMPORIZADOR PASANDOLE EL TIEMPO INICIAL Y SU POSICION EN PANTALLA

	player = new Player("assets/spritesheet.png", Vector2i(26, 30), Vector2f(25, 460),5);//CREO UN PLAYER PASANDOLE, EL TAMAÑO DEL RECUADRO DEL PLAYER Y SU POSICION INICIAL, ADEMAS LA VELOCIDAD
	colision_arriba = false;  //SE HACE TRUE SI COLISIONA UN BLOQUE 
	descontar_diez = false;   //SE HACE TRUE SI HAY QUE DESCONTAR 10 SEG POR GOLPEAR UN BLOQUE INCORRECTO. SE USA AL FINAL DEL CICLO DE SUBIDA EN EL SALTO
	num_anterior = 0;         //VA GUARDANDO EL NUMERO QUE SE GOLPEO PARA VER SI ES MENOR QUE EL QUE ESTA GOLPEANDO  
	 
	//CREO LOS BLOQUES Y LE ASIGNO UN NUMERO DE LOS DEL ARREGLO DE NUMEROS DESORDENADOS
	bloque1 = new Bloque("assets/bloque_pared.png", Vector2f(50, 260), arreglo_numeros[0]); //RECIBEN LA POSICION Y EL NUMERO ALEATORIO
	bloque2 = new Bloque("assets/bloque_pared.png", Vector2f(117.5, 260), arreglo_numeros[1]);
	bloque3 = new Bloque("assets/bloque_pared.png", Vector2f(185, 260), arreglo_numeros[2]);
	bloque4 = new Bloque("assets/bloque_pared.png", Vector2f(252.5, 260), arreglo_numeros[3]);
	bloque5 = new Bloque("assets/bloque_pared.png", Vector2f(320, 260), arreglo_numeros[4]);
	bloque6 = new Bloque("assets/bloque_pared.png", Vector2f(387.5, 260), arreglo_numeros[5]);
	bloque7 = new Bloque("assets/bloque_pared.png", Vector2f(455, 260), arreglo_numeros[6]);
	bloque8 = new Bloque("assets/bloque_pared.png", Vector2f(522.5, 260), arreglo_numeros[7]);
	bloque9 = new Bloque("assets/bloque_pared.png", Vector2f(590, 260), arreglo_numeros[8]);
	bloque10 = new Bloque("assets/bloque_pared.png", Vector2f(657.5, 260), arreglo_numeros[9]);

	bloque[0] = bloque1; //AGRUPO LOS BLOQUES EN UN ARREGLO DE BLOQUES 
	bloque[1] = bloque2;
	bloque[2] = bloque3;
	bloque[3] = bloque4;
	bloque[4] = bloque5;
	bloque[5] = bloque6;
	bloque[6] = bloque7;
	bloque[7] = bloque8;
	bloque[8] = bloque9;
	bloque[9] = bloque10;

	gameloop(); //FUNCION GAMELOOP 
}

void Game::gameloop() {
	while (w->isOpen()) {
		*t = clock->getElapsedTime();                                                                
		temporizador->actualizar_temp();//ACTUALIZA EL TEMPORIZADOR      
		if (temporizador->get_time() <0){  //SI EL TEMPORIZADOR LLEGA A CERO
			ordenar_arreglo(arreglo_numeros, 10); //ORDENA EL ARREGLO
			for (int i = 0; i < 10; i++) {        //SE LO ASIGNA A LOS BLOQUES DE FORMA ORDENADA
				bloque[i]->set_int(arreglo_numeros[i]);
			}
			player->set_velocidad(0);    //LE SETEA VELOCIDAD CERO AL PLAYER PARA QUE NO PUEDA MOVERSE NI SALTAR
		}
		while (w->pollEvent(*e)) {

			if (e->type == Event::Closed) {
				w->close();
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {   //DESPLAZAMIENTO A LA IZQUIERDA, AFECTADO POR EL PARAMETRO VELOCIDAD
				player->set_position(player->get_position().x - player->get_velocidad(), player->get_position().y); 
			}    
			if (Keyboard::isKeyPressed(Keyboard::D)) {   //DESPLAZAMIENTO A LA DERECHA, AFECTADO POR EL PARAMETRO VELOCIDAD
				player->set_position(player->get_position().x + player->get_velocidad(), player->get_position().y);
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {//SI SE PRESIONA ESPACIO
				w->setKeyRepeatEnabled(false);            //BLOQUEO PARA QUE NO VUELVA A TOMAR LA ACCION HASTA TERMINAR EL CICLO
				//CICLO DE SUBIDA DEL SALTO ///////////////////////////////////////////////////////////////////////////////////
				for (int i = 0; i <= 12; i++) {//FOR DE SUBIDA
					temporizador->actualizar_temp();
					for(int i=0; i<10; i++){   //FOR QUE RECORRE LOS RECTANGULOS DE LOS BLOQUES
					    rect_bloque = bloque[i]->get_sprite().getGlobalBounds();//OBTENGO EL RECTANGULO DE CADA LOQUE PARA VER SI COLISIONA EL PLAYER 
					    pos_saltando.x = player->get_position().x + 26;         //EL CENTRO DEL PLAYER EN EL EJE X(PARA QUE COLISIONE CON UN SOLO BLOQUE)
						pos_saltando.y = player->get_position().y;
					    if (rect_bloque.contains(pos_saltando)) {//SI INTERSECTA CON EL BLOQUE i
							colision_arriba = true;              //ACTIVA EL BOOL DE COLISION ->colision_arriba
							bloque_colisionado = i;              //GUARDA LA POSICION QUE OCUPA EL BLOQUE COLISIONADO EN EL ARREGLO 
							if (bloque[i]->get_int() >= num_anterior) {
								bloque[i]->set_color(Color::Green);   //LE CAMBIA EL COLOR DEL NUMERO A VERDE SI ES CORRECTO
								num_anterior = bloque[i]->get_int();  //GUARDA EL NUMERO(texto) DEL BLOQUE GOLPEADO PARA COMPARARLO CON EL NUMERO DEL PROXIMO BLOQUE QUE GOLPEARÁ
							}
							else {
								descontar_diez = true;                //SI ES INCORRECTO ACTIVA EL BOOL DE DESCUNTO DE TIEMPO  -> descontar_diez  
							} 
					    }
					}
					if (t->asSeconds() >= 0.5 && colision_arriba == false) {  //ESPERA MEDIO SEGUNDO Y SI NO HAY COLISION CON BLOQUE MUEVE EL PLAYER
						player->set_position(player->get_position().x, player->get_position().y - (player->get_velocidad()*4));//SE DESPLAZA HACIA ARRIBA (VELOCIDAD * -4)
						if (Keyboard::isKeyPressed(Keyboard::D)) {
							player->set_position(player->get_position().x + player->get_velocidad(), player->get_position().y);//DESPLAZAMIENTO HORIZONTAL MIENTRAS SALTA
						}
						if (Keyboard::isKeyPressed(Keyboard::A)) {
							player->set_position(player->get_position().x - player->get_velocidad(), player->get_position().y);//DESPLAZAMIENTO HORIZONTAL MIENTRAS SALTA
						}
						clock->restart();
						dibujar();
					}
				}
				temporizador->penalizacion_time(descontar_diez);//CONUSULTA SI HAY PENALIZACION DE TIEMPO CUANDO TERMINA EL CICLO DE SUBIDA 
				//CICLO DE CAIDA DEL SALTO//////////////////////////////////////////////////////////////////////////////////////////////////
				for (int i = 0; i <= 12; i++) { 
					colision_arriba = false; //CUANDO EMPIEZA A CAER DESACTIVA LA COLISION CON EL BLOQUE
					temporizador->actualizar_temp();
					if (t->asSeconds() >= 0.5 && player->get_position().y <= 445) {       //CADA 0.5 SEGUNDO, SI ESTA POR ENCIMA DEL NIVEL DEL SUELO(445 EN EL EJE Y), SIGUE CAYENDO
						player->set_position(player->get_position().x , player->get_position().y + (player->get_velocidad() * 4));//SE DESPLAZA HACIA ABAJO(CAE)(VELOCIDAD * 4)
						if (Keyboard::isKeyPressed(Keyboard::D)) {
							player->set_position(player->get_position().x + player->get_velocidad(), player->get_position().y);//DESPLAZAMIENTO HORIZONTAL MIENTRAS SALTA
						}
						if (Keyboard::isKeyPressed(Keyboard::A)) {
							player->set_position(player->get_position().x - player->get_velocidad(), player->get_position().y);//DESPLAZAMIENTO HORIZONTAL MIENTRAS SALTA
						}
						clock->restart();
						dibujar();
					}
				}
			}
			w->setKeyRepeatEnabled(true);  //ACTIVO EL SETKEYREPEATENABLED AL TERMINAR EL CICLO DE SALTO
		}
		dibujar();   //llamo a la funcion dibujar al final de cada ciclo del gameloop
	}
}


void Game::dibujar() {   //funcion dibujar
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

void Game::ordenar_arreglo(int arr[],int n) { //ORDENA EL ARREGLO DE NUMEROS DE MENOR A MAYOR UTILIZANDO EL METODO BURBUJA
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