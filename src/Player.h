#include "Object.h"

const float maxVelocity = 20.0f;
const float velocityChangeFall = 0.075;
const float playerWalkSpeed = 7.5f;


class C_Player : public C_Object{
    
public:
    
	//Player class constructor
    C_Player();

	//Player class deconstructor
    ~C_Player() = default;
    
	//Return the current velocity
    float GetVelocity()
	{
        return velocity;
    }
    
	//Check if a walk key is pressed and walk
	void PlayerWalk();

	//Let the player jump
    void Jump();

	//Let the player fall
    void Fall(Uint32 deltaTime);

	//Reset the current velocity
	void ResetVelocity();
    
private:
    
    float velocity;
    
};

inline void C_Player::Jump()
{   
    velocity = -maxVelocity;
}
    

inline void C_Player::Fall(Uint32 deltaTime)
{
        if(velocity > maxVelocity)
        {
            velocity = maxVelocity;
        }
        
        MoveObject(0, velocity * SCALE_H );
        velocity += float( deltaTime*velocityChangeFall );
}

inline void C_Player::PlayerWalk()
{
	if (m1::KeyIsPressed(SDL_SCANCODE_A))
	{
		MoveObject(-playerWalkSpeed * SCALE_W, 0);
	}

	if (m1::KeyIsPressed(SDL_SCANCODE_D))
	{
		MoveObject(playerWalkSpeed * SCALE_W, 0);
	}
}