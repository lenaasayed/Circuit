#include "Edevice.h"
void Edevice:: virt(){}
double Edevice::getr(){return real_value;}
double Edevice::geti(){return complex_value;}

void Edevice::Print(){
cout<<"( "<<real_value<<","<<complex_value<<" )"<<endl;
}

void Edevice::Print_po(){
cout<<"r= "<<r<<" phase "<<phai<<endl;
}
Edevice Edevice::operator+(Edevice C)
{
	 Edevice p;
p.real_value=real_value+C.getr();
p.complex_value=complex_value+C.geti();
  return p;
}

Edevice Edevice::operator-(Edevice C){
	Edevice p;
p.real_value=real_value-C.getr();
p.complex_value=complex_value-C.geti();
  return p;
}
void Edevice :: transfer_rect ()
{ 
	real_value=r*cos(phai*(3.141592/180));
	complex_value=r*sin (phai*(3.141592/180));
}

void Edevice :: transfer_toPhai ()
{
	phai=atan(complex_value/real_value)*(180/3.141592);
	r=sqrt(real_value*real_value+complex_value*complex_value);
}
Edevice Edevice :: operator*(Edevice c)
{  transfer_toPhai();
   c.transfer_toPhai();
	Edevice p;
	p.phai=phai+c.phai;
	p.r=r*c.r;
	p.transfer_rect();
	return p;

}



Edevice Edevice :: operator/ (Edevice c)
{
   /*transfer_toPhai();
   c.transfer_toPhai();*/
	Edevice p;
	p.phai=phai-c.phai;
	p.r=r/c.r;
	p.transfer_rect();

	return p;
}


Edevice::Edevice(void)
{
}


Edevice::~Edevice(void)
{
}
