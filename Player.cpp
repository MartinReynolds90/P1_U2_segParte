#include "Player.h"

using namespace sf;

Player::Player() {
}

//ARCHIVO(el arcivo que usa),XY_FRAME(coordenadas para pasarle al IntRect, sobre que recuadro usar)POSITION_PJ(la posicion con que inicia en pantalla) 
Player::Player(String archivo, Vector2i xy_frame, Vector2f position_pj) {
	sp_player = new Sprite;
	tx_player = new Texture;
	tx_player->loadFromFile(archivo);
	sp_player->setTexture(*tx_player);
	rect_player = new IntRect(xy_frame.x, xy_frame.y, 32, 32);
	sp_player->setTextureRect(*rect_player);
	sp_player->setPosition(position_pj.x, position_pj.y);
	sp_player->setScale(sp_player->getScale().x * 2, sp_player->getScale().y * 2);

	//contador_frame = 0;
	clock_player = new Clock(); 
	time_player = new Time();

}

Sprite Player::get_sprite() {
	return *sp_player;
}

Vector2f Player::get_position() {
	Vector2f pos_pj;
	pos_pj.x = sp_player->getPosition().x;
	pos_pj.y = sp_player->getPosition().y;
	return pos_pj;
}

void Player::set_position(float new_posX, float new_posY) {
	sp_player->setPosition(new_posX, new_posY);
}

float Player::get_time() {
	*time_player = clock_player->getElapsedTime();
	float time_float = time_player->asSeconds();
	return time_float;
}

void Player::restart_clock() {
	clock_player->restart();
}

void Player::animar() {

}
