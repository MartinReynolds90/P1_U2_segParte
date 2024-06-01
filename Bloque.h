#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bloque
{
private:
	Sprite* sp_bloque;
	Texture* tx_bloque;
public:
	Bloque();
	Bloque(String, Vector2i, Vector2f, int);
	Sprite get_sprite();
};
