#include "Player.h"

C_Player::C_Player()
{
    Init(_PlayerPath);
    
    velocity = 0;
}

void C_Player::ResetVelocity()
{
	velocity = 0;
}