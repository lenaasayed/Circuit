#include "capacitor.h"
void capacitor:: virt(){}


capacitor::capacitor(void)
{
}
capacitor::capacitor(string nm,int n1,int n2,double rv,double cv)
{

    name=nm;
	node_1=n1;
	node_2=n2;
	real_value=0;
	complex_value=cv;

}

capacitor::~capacitor(void)
{
}
