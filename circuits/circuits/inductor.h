#pragma once
#include "Edevice.h"
class inductor:public Edevice
{
public:
	void virt();
	inductor(string,int n1,int n2,double rv,double cv=0);
	inductor(void);
	~inductor(void);
};

