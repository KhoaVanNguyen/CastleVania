#ifndef _DAGGER_H_
#define _DAGGER_H_

#include "Weapon.h"

class Dagger : public Weapon
{
public:
	Dagger(void);
	Dagger(float x, float y, float _huong);
	~Dagger(void);
};

#endif