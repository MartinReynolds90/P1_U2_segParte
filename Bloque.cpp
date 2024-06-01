#include "Bloque.h"

using namespace sf;

Bloque::Bloque() {}
Bloque::Bloque(String archivo, Vector2i a, Vector2f b, int e) {
	tx_bloque = new Texture;
	sp_bloque = new Sprite;
	tx_bloque->loadFromFile(archivo);
	sp_bloque->setTexture(*tx_bloque);
}

Sprite get_sprite() {
    
}
void Bloque::set_sprite(Texture newTexture) {
	sp_bloque->setTexture(newTexture);
}
void Bloque::set_position(float x,float y) {
	sp_bloque->setPosition(x, y);
}
Vector2f Bloque::get_position() {
	Vector2f pos;
	pos.x = sp_bloque->getPosition().x;
	pos.y = sp_bloque->getPosition().y;
	return pos;
}



}
