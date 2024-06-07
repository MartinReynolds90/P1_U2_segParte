#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Player
{
private:
	Sprite* sp_player;
	Texture* tx_player;
	IntRect* rect_player;
	Time* time_player;
	Clock* clock_player;
	int contador_frame;
public:
	Player();
	Player(String, Vector2i, Vector2f);
	Sprite get_sprite();
	Vector2f get_position();
	void set_position(float, float);
	float get_time();
	void restart_clock();
};

