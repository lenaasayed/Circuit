#pragma once
#include "Edevice.h"
class capacitor:public Edevice
{
public:
	void virt();

	capacitor(string ,int n1,int n2,double rv,double cv=0);
	capacitor(void);
	~capacitor(void);
};

