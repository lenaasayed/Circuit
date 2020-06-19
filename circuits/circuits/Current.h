#pragma once
#include "Edevice.h"

class Current:public Edevice
{
public:
	Current(string nm,int n1,int n2,double rv,double cv=0);
	Current(void);
	~Current(void);
};

