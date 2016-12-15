
#include "Dagger.h"

#define SPEED_X 0.5f

Dagger::Dagger(void) : Weapon()
{
}

Dagger::Dagger(float x, float y, float _huong) : Weapon(x, y, _huong, EnumID::Dagger_ID)
{

}

Dagger::~Dagger(void)
{
}
