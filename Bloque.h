#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bloque
{
private:
	Sprite* sp_bloque;
	Texture* tx_bloque;
	IntRect* rect_bloque;

	Font* font_num;
	Text* text_num;

	int num_int;
	String num_string;
public:
	Bloque();
	Bloque(String, Vector2f,int);
	Sprite get_sprite();
	void set_sprite(Texture);
	Vector2f get_position();
	void set_color(Color);
	Text get_texto();
	int get_int();
	void set_int(int);
}; 
