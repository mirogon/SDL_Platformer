#include "Animation.h"

C_Animation::C_Animation(std::string path, int animationLenght, short spriteWidth, short spriteHeight): 
	
	animationLenght(animationLenght), 
	spriteWidth(spriteWidth),
	spriteHeight(spriteHeight),
	currentPosition(1)

{
	Init(path);
}