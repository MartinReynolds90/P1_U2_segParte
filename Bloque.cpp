#include "Bloque.h"


using namespace sf;
using namespace std;

Bloque::Bloque() {
}
Bloque::Bloque(String archivo, Vector2i xy_frame, Vector2f posicion_bl,int num_bloque) {
	tx_bloque = new Texture;
	sp_bloque = new Sprite;
	tx_bloque->loadFromFile(archivo);
	sp_bloque->setTexture(*tx_bloque);
	rect_bloque = new IntRect(xy_frame.x, xy_frame.y, 45, 45);
	sp_bloque->setTextureRect(*rect_bloque);
	sp_bloque->setPosition(posicion_bl.x, posicion_bl.y);
	sp_bloque->setScale(sp_bloque->getScale().x * 1.5, sp_bloque->getScale().y * 1.5);

	f_num = new Font;
	f_num->loadFromFile("assets/Square.ttf");

	tx_num = new Text;
	tx_num->setFont(*f_num);

	num_int = num_bloque;
	num_string = " " + to_string(num_bloque);
	tx_num->setString(num_string);
	tx_num->setPosition(posicion_bl);
	tx_num->setFillColor(Color::Yellow);

}

Sprite Bloque::get_sprite() {
	return *sp_bloque;
}
void Bloque::set_sprite(Texture newTexture) {
	sp_bloque->setTexture(newTexture);
}

Vector2f Bloque::get_position() {
	Vector2f pos;
	pos.x = sp_bloque->getPosition().x;
	pos.y = sp_bloque->getPosition().y;
	return pos;
}

void Bloque::set_position(float x,float y) {
	sp_bloque->setPosition(x, y);
}
 
void Bloque::set_color(Color new_color) {   //Cambia el color del texto del bloque
	tx_num->setFillColor(new_color);
}

Text Bloque::get_texto() { 
	return *tx_num;
}

int Bloque::get_int() { //Devuelve el número ENTERO que corresponde al bloque
	return num_int;
}
