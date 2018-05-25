#pragma once
#include "Button.h"


class Player : public Object{
    
public:
    
	//Player class constructor
    Player();

	//Player class deconstructor
    ~Player() = default;
    
	//Return the current velocity
    float get_velocity()
	{
        return velocity;
    }
    
	//Check if a walk key is pressed and walk
	void player_walk();

	//Let the player jump
    void jump();

	//Let the player fall
    void fall(Uint32 delta_time);

	//Reset the current velocity
	void reset_velocity();
    
private:
    
    float velocity;
    
};

inline void Player::jump()
{   
    velocity = -MAX_VELOCITY;
}
    

inline void Player::fall(Uint32 delta_time)
{
        if(velocity > MAX_VELOCITY)
        {
            velocity = MAX_VELOCITY;
        }
        
        move_object(0, velocity * _SCALE_H );
        velocity += float( delta_time*VELOCITY_CHANGE_FALL );
}

inline void Player::player_walk()
{
	if (m1::key_is_pressed(SDL_SCANCODE_A))
	{
		move_object(-PLAYER_WALKSPEED * _SCALE_W, 0);
	}

	if (m1::key_is_pressed(SDL_SCANCODE_D))
	{
		move_object(PLAYER_WALKSPEED * _SCALE_W, 0);
	}
}