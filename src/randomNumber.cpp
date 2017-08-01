#include "randomNumber.h"


int C_Random::randomNumber(int min, int max){

    return (  rand()  % (max-min) ) + min  ;
}

C_Random::C_Random(){

    srand(time(NULL));

}

C_Random::~C_Random(){}


