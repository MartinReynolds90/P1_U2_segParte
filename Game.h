#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bloque.h"
#include "Timer.h"
#include "iostream"

using namespace sf;

class Game
{
	RenderWindow* w;   
	Event* e;
	Clock* clock;
	Time* t;

	Sprite* sp_fondo; //SPRITE Y TEXTURA DEL FONDO
	Texture* tx_fondo;
	int fps = 30;

	Player* player;             //DECLARO EL PLAYER
	Timer* temporizador;        //DECLARO EL TEMPORIZADOR
	int arreglo_numeros[10];

	FloatRect rect_bloque;
	Vector2f pos_saltando;      //GUARDA LA POSICION DEL PLAYER MIENTRAS SALTA, TOMANDO COMO REFERENCIA EN EL EJE X EL CENTRO DEL SPRITE, 
	                            //MIENTRAS QUE EN EL EJE Y EL 0 DEL SPRITE. ESTO FACILITA LA DETECCION DE COLISION DEL PUNTO CONTRA EL RECTANGULO DEL BLOQUE
	
	
	bool colision_arriba;       //SE HACE TRUE CUANDO COLISIONA CON UN BLOQUE
	int bloque_colisionado = 0; //GUARDA LA POSICION EN EL ARREGLO DE BLOQUES, DEL BLOQUE GOLPEADO

	int num_anterior;    //GUARDA EL NUMERO DEL BLOQUE QUE SE GOLPEO ANTES
	bool descontar_diez; //SE HACE TRUE CUANDO HAY QUE DESCONTAR 10 SEGUNDOS 

	Bloque* bloque1;
	Bloque* bloque2;
	Bloque* bloque3;
	Bloque* bloque4;
	Bloque* bloque5;
	Bloque* bloque6;
	Bloque* bloque7;
	Bloque* bloque8;
	Bloque* bloque9;
	Bloque* bloque10;
	Bloque* bloque[10];

public:
	Game();
	Game(int, int, String);
	void gameloop();   
	void dibujar();
	void ordenar_arreglo(int[],int);
	
};

