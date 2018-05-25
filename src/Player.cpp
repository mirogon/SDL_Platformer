#include "Player.h"

Player::Player()
{
    init(_PATH_PLAYER);
    
    velocity = 0;
}

void Player::reset_velocity()
{
	velocity = 0;
}