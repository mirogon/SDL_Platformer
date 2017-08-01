#include "Player.h"

C_Player::C_Player()
{
    InitObject(_PlayerPath);
    
    velocity = 0;
}

void C_Player::ResetVelocity()
{
	velocity = 0;
}