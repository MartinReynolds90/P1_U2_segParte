#include "Bloque.h"

using namespace sf;

Bloque::Bloque() {}
Bloque::Bloque(String archivo, Vector2i a, Vector2f b, int e) {
	tx_bloque = new Texture;
	sp_bloque = new Sprite;
	tx_bloque->loadFromFile(archivo);
	sp_bloque->setTexture(*tx_bloque);
}
