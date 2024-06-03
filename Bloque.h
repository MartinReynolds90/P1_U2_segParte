#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bloque
{
private:
	Sprite* sp_bloque;
	Texture* tx_bloque;
	IntRect* rect_bloque;

	Font* f_num;
	Text* tx_num;

	int num_int;
	String num_string;
public:
	Bloque();
	Bloque(String, Vector2i, Vector2f,int);
	Sprite get_sprite();
	void set_sprite(Texture);
	void set_position(float,float);
	Vector2f get_position();
	void set_color();
	Text get_texto();
	int get_int();
};
