#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Player
{
private:
	Sprite* sp_player;
	Texture* tx_player;
	IntRect* rect_player;
	int contador_frame;
	int velocidad;
public:
	Player();
	Player(String, Vector2i, Vector2f,int);
	Sprite get_sprite();
	Vector2f get_position();
	void set_position(float, float);
	int get_velocidad();
	void set_velocidad(int);

};

