#include "Current.h"


Current::Current(void)
{
}
Current::Current(string nm,int n1,int n2,double rv,double cv)
{

name=nm;
	node_1=n1;
	node_2=n2;
	real_value=rv;
	complex_value=cv;

}

Current::~Current(void)
{
}
