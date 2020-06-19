#pragma once
#include<iostream>
using namespace std;
class Edevice
{
public:
	string name;
	int id;
	int node_1,node_2;
	double real_value,complex_value;
	double phai,r;
	double getr();
	double geti();
	void Print();
	Edevice operator+(Edevice C);
	Edevice operator- (Edevice C);
	void transfer_toPhai ();
	void transfer_rect ();
	

	Edevice  operator*(Edevice c);
	Edevice operator/ (Edevice c);
	void Print_po();
	virtual void virt();
	Edevice(void);
	~Edevice(void);
};

