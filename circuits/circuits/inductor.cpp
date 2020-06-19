#include "inductor.h"
void inductor::virt(){}

inductor::inductor(void)
{
}
inductor::inductor(string nm,int n1,int n2,double rv,double cv)
{

name=nm;
	node_1=n1;
	node_2=n2;
	real_value=0;
	complex_value=cv;

}

inductor::~inductor(void)
{
}
