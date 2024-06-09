#include "Player.h"

using namespace sf;

Player::Player() {
}

//ARCHIVO(el arcivo que usa),XY_FRAME(coordenadas para pasarle al IntRect, sobre que recuadro usar)POSITION_PJ(la posicion con que inicia en pantalla) 
Player::Player(String archivo, Vector2i xy_frame, Vector2f position_pj,int vel) {
	velocidad = vel;
	sp_player = new Sprite;
	tx_player = new Texture;
	tx_player->loadFromFile(archivo);
	sp_player->setTexture(*tx_player);
	rect_player = new IntRect(xy_frame.x, xy_frame.y, 32, 32);
	sp_player->setTextureRect(*rect_player);
	sp_player->setPosition(position_pj.x, position_pj.y);
	sp_player->setScale(sp_player->getScale().x * 2, sp_player->getScale().y * 2);

}

Sprite Player::get_sprite() { //OBTIENE EL SPRITE DEL PLAYER
	return *sp_player;
}

Vector2f Player::get_position() {  //OBTIENE LA POSICION DEL PLAYER
	Vector2f pos_pj;
	pos_pj.x = sp_player->getPosition().x;
	pos_pj.y = sp_player->getPosition().y;
	return pos_pj;
}

void Player::set_position(float new_posX, float new_posY) { //LE SETEA UNA NUEVA POSICION AL JUGADOR
	sp_player->setPosition(new_posX, new_posY);
}

int Player::get_velocidad() { //OBTIENE LA VELOCIDAD
	return velocidad;
}
void Player::set_velocidad(int new_velocity) { //PARA CAMBIARLE LA VELOCIDAD AL JUGADOR
	velocidad = new_velocity;
}


