#pragma once
#include "Edevice.h"
class Resistance:public Edevice
{
public:
	void virt();
	Resistance(string,int n1,int n2,double rv,double cv=0);
	Resistance(void);
	~Resistance(void);
};

