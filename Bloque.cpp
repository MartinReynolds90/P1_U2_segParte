#include "Bloque.h"


using namespace sf;
using namespace std;

Bloque::Bloque() {
}                                                                     
Bloque::Bloque(String archivo, Vector2f posicion_bl,int num_bloque) {
	tx_bloque = new Texture;
	sp_bloque = new Sprite;
	tx_bloque->loadFromFile(archivo); //ARCHIVO DE DONDE SACO LA TEXTURA DEL BLOQUE
	sp_bloque->setTexture(*tx_bloque);
	rect_bloque = new IntRect(0,0, 45, 45);
	sp_bloque->setTextureRect(*rect_bloque);
	sp_bloque->setPosition(posicion_bl.x, posicion_bl.y); //LE ASIGNO LA POSICION QUE LE PASO AL CREARLO
	sp_bloque->setScale(sp_bloque->getScale().x * 1.5, sp_bloque->getScale().y * 1.5); //MODIFICO LA ESCALA DEL SPRITE

	font_num = new Font;
	font_num->loadFromFile("assets/Square.ttf");

	text_num = new Text;
	text_num->setFont(*font_num);

	num_int = num_bloque;
	num_string = " " + to_string(num_bloque);  //CONVIERTO EL ENTERO ALEATORIO QUE RECIBO COMO PARAMETRO, A STRING Y SE LO PASO AL TEXTO 
	text_num->setString(num_string);
	text_num->setPosition(posicion_bl);         //LE ASIGNO AL TEXTO LA MISMA POSICION QUE EL BLOQUE
	text_num->setFillColor(Color::Yellow);

}

Sprite Bloque::get_sprite() {  //DEVUELVE EL SPRITE DEL BLOQUE PARA PODER DIBUJARLO
	return *sp_bloque;
}

Vector2f Bloque::get_position() {
	Vector2f pos;
	pos.x = sp_bloque->getPosition().x;
	pos.y = sp_bloque->getPosition().y;
	return pos;
}

void Bloque::set_color(Color new_color) {   //CAMBIA EL COLOR DEL TEXTO EN EL BLOQUE
	text_num->setFillColor(new_color);
}

Text Bloque::get_texto() { //DEVUELVE EL TEXTO DEL BLOQUE PARA PODER DIBUJARLO
	return *text_num;
}

int Bloque::get_int() { //Devuelve el número ENTERO que corresponde al bloque
	return num_int;
}

void Bloque::set_int(int num_ordenado) { //LE SETEA UN NUEVO NUMERO AL BLOQUE 
    num_int = num_ordenado;
	num_string = " " + to_string(num_ordenado);
	text_num->setString(num_string);
}
