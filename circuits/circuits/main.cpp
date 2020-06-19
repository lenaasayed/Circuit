#include<iostream>
using namespace std;
#include "Edevice.h"
#include"Current.h"
#include"Resistance.h"
#include"Voltage.h"
#include"capacitor.h"
#include"inductor.h"
#include"voltage_dep.h"
#include<fstream>
#include<string>
#pragma region def
void Read_Data(string ,Current*,Voltage*, Resistance*,capacitor*,inductor*,voltage_dep*,
			   int&,int&,int&,int&,int&,int&);
int get_max(Edevice* e,int c);
void Read_Data(string fname,Current*C,Voltage*V, Resistance*R,capacitor*Cr,inductor*Id,voltage_dep*Vd,int &ci,int &cv,int &cr,int&cap,int&ind,int&vdi )
{
	string str;
	int N1,N2;
	double RV;
	double CV;
	double w;
	ifstream file_read(fname+".txt");
	if(file_read.is_open())
	{
		file_read>>w;
		while (!file_read.eof())
		{
			
			file_read>>str>>N1>>N2>>RV;
			if(str.find("V")!=std::string::npos)
			{
				file_read>>CV;
				V[cv] = Voltage(str,N1,N2,RV,CV);
				cv++;}
			else if(str.find("R")!=std::string::npos)
			{


				R[cr]=  Resistance(str,N1,N2,RV);
				cr++;
			}
			else if(str.find("I")!=std::string::npos)
			{
				file_read>>CV;

				C[ci]=  Current(str,N1,N2,RV,CV);
				ci++;
			}
		
			else if(str.find("C")!=std::string::npos)
			{
				CV=-1/(RV*w);
				Cr[cap]=  capacitor(str,N1,N2,RV,CV);
				cap++;
			}
			
			
			else if(str.find("L")!=std::string::npos)
			{
				CV=w*RV;
				Id[ind]=  inductor(str,N1,N2,RV,CV);
				ind++;
			}			
		
			else{cout<<"NOT valide name"<<endl;}

		}	
		file_read.close();
	}
	else{cout<<"File can't be opened"<<endl;}
}
//////get maximum node
int get_max(Edevice* e,int c)
{
	int maxt;
	int max =(e[0].node_1>e[0].node_2)?e[0].node_1:e[0].node_2;
	for(int i=1;i<c;i++)
	{

		maxt =(e[i].node_1>e[i].node_2)?e[i].node_1:e[i].node_2;
		if(maxt>max)
			max=maxt;
	}

	return max;
}  
#pragma endregion
int main()
{
	//read data from file
	string fnm;
	int c1=0,c2=0,c3=0,c4=0,c5=0,c6=0;
	cout<<"Enter file name"<<endl;
	cin>>fnm;
	Voltage *vv=new Voltage[111];
	Resistance *rr=new Resistance[111];
	Current *ii=new Current[111];
	capacitor *ccr=new capacitor[111];
	inductor *dd=new inductor[111];
	voltage_dep *vd=new voltage_dep[111];
	Read_Data("red",ii,vv,rr,ccr,dd,vd,c1,c2,c3,c4,c5,c6);
#pragma region MyRegion
	
	//fill the edevice
	Edevice* E=new Edevice[111];
	int ce=c1+c2+c3+c4+c5+c6;
	int cecpy=ce;
	int max_node;
	int k=0, k1=0,k2=0,k3=0,k4=0,k5=0;
	//c2=vv,c3=rr,c1=ii,c4=ccr,c5=dd,ce=total(E1,E)
	for(int i=0;i<ce;i++)
	{
		if(k<c2)
		{
			E[i]=vv[k];
			k++;
		}
		else if(k3<c4){
			E[i]=ccr[k3];
			k3++;
		}
		else if(k4<c5)
		{
			E[i]=dd[k4];
			k4++;
		}
		else if(k1<c3)
		{
			E[i]=rr[k1];
			k1++;}
		else if(k2<c1)  
		{
			E[i]=ii[k2];
			k2++;
		}
		else if(k5<c6)
		{
			E[i]=vd[k5];
			k5++;
		}		
	}
	max_node=get_max(E,ce); 
#pragma endregion
	//copy of E
#pragma region MyRegion

	Edevice* E1=new Edevice[111];
	k=0;k1=0;k2=0,k3=0,k4=0,k5=0;
	int ecountcopy1=ce;
	int ecountcopy2=ce;
	for(int i=0;i<ce;i++)
	{
		if(k<c2)
		{
			E1[i]=vv[k];
			k++;
		}
		 else if(k3<c4){
			E1[i]=ccr[k3];
			k3++;
		}
		else if(k4<c5)
		{
			E1[i]=dd[k4];
			k4++;
		}
		else if(k1<c3)
		{
			E1[i]=rr[k1];
			k1++;
		}
		else if(k2<c1)
		{
			E1[i]=ii[k2];
			k2++;
		}
		
		else if(k5<c6)
		{
			E1[i]=vd[k5];
			k5++;
		}		

	}

#pragma endregion
	// global variables
#pragma region MyRegion
	Edevice** branch=new Edevice*[];
	Edevice** loopsarr=new Edevice*[];   
	int ilop=0;
	int* l_device=new int[];
	int lpno=0;
	int rb=0;//number of branches
	int er=0;//number of devices in each branch and set it by zero every cycle  
	int temp;
	bool f=false;
	int trb=0;
	int *arrpnd1=new int[max_node+1];
	int *arrpnd2=new int[max_node+1];
	int* b_node=new int[max_node+1];//number of devices in each branch  
	int *Node=new int[max_node+1];
	int* Arr_Count = new int[max_node+1];//count number of devices have same nodes
	int count=0,p=0;
#pragma endregion
	//get primary nodes number
#pragma region MyRegion

	for(int i=0;i<=max_node;i++)
	{
		for(int j=0;j<ce;j++)//count no of devices connected to node i
		{
			if(E[j].node_1==i||E[j].node_2==i)
			{count++;}
		}
		if(count>=3)//it is a primary node 
		{
			Node[p]=i;
			Arr_Count[p]=count; 
			p++;
		}
		count=0;
	}
	for(int u=0;u<p;u++)
	cout<<"node number = "<<u<<"  "<<Node[u]<<endl;  
#pragma endregion
	//get branches
#pragma region branch
	////////////////////////////////////////////////////////////////////////
	//get branches
	////////////////////////////////////////////////////////////////////////
	//if p==0 no primary nodes one loop
//cecpy	
#pragma region MyRegion
	if(p==0)
	{
		branch[0]=new Edevice[111];
		b_node[0]=0;
		branch[0]=E;
		b_node[0]=ce;
		loopsarr[0]=new Edevice[111];
		l_device[0]=0;
		loopsarr[0]=E;
		l_device[0]=ce;
		ilop++;
		rb++;
		double ztr=0,itr;
		double zti=0,iti;
		Edevice v1;
		for(int i=0;i<ce;i++)
		{
			Resistance* ptr1=dynamic_cast<Resistance*>(&E[i]);
			capacitor* ptr2=dynamic_cast<capacitor*>(&E[i]);
			inductor* ptr3=dynamic_cast<inductor*>(&E[i]);
			Voltage* ptr4=dynamic_cast<Voltage*>(&E[i]);

			if(ptr1)
			{
				ztr=ztr+ptr1->real_value;
			}
			if(ptr2)
			{
				zti=zti+ptr2->complex_value;
			}
			if(ptr3)
			{
				zti=zti+ptr3->complex_value;
			}
			if(ptr4)
			{
			
				v1=*ptr4;
			}
		}

		cout<<"Z = "<<ztr<<" + "<<zti<<"i"<<endl;
		Edevice eobj=Resistance("res",0,0,ztr,zti);
		eobj.transfer_toPhai();
		cout<<"Z = "<<eobj.r<<"<"<<eobj.phai<<">"<<endl;
		Edevice I;
		I=eobj/ v1;
		cout<<"I = "<<I.real_value<<" + "<<I.complex_value<<"i"<<endl;










	}
#pragma endregion
else
{
	for(int i=0;i<p;i++)//through all nodes
	{
		for(int j=0;j<=ce;j++)//if one of its point is the selected node(<=?or<)
		{
			if(Node[i]==E[j].node_1)
			{
				arrpnd1[rb]=Node[i];
				branch[rb]=new Edevice[111];
				temp=E[j].node_2;////////aaaaaaaaaaaaaa
				branch[rb][er]=E[j];//add errrrrrrrrrrrrrr
				er++;
				if(ce>0){
				E[j]=E[ce];//delete
				ce--;}
				//if(ce==0)break;
				/*j--;
				if(j<=0)break;*/
			}
			else if(Node[i]==E[j].node_2)
			{
				arrpnd1[rb]=Node[i];
				branch[rb]=new Edevice[111];
				temp=E[j].node_1;////////aaaaaaaaaaaaaa
				branch[rb][er]=E[j];//add
				er++;
				if(ce>0){
				E[j]=E[ce];//delete
				ce--;}
				//if(ce==0)break;
				/*j--;
				if(j<=0)break;*/
			}
			else 
			{continue;}
			for(int q=0;q<p;q++)//if temp node is a primary node
			{
				if(temp==Node[q])
				{
					f=true;
					break;
				}
			}
			//temp node is not primary
			if(f==false) 
			{
				for(int w=0;w<=ce;w++)
				{
					if(temp==E[w].node_1)
					{
					temp=E[w].node_2;
					branch[rb][er]=E[w];
					er++;
				    if(ce>0){
					E[w]=E[ce];//delete
					ce--;}
					//if(ce==0)break;
					/*w--;
					if(w<=0)w=0;*/
					}
					else if(temp==E[w].node_2)
					{
					temp=E[w].node_1;
					branch[rb][er]=E[w];
					er++;
				    if(ce>0){
					E[w]=E[ce];//delete
					ce--;}
					//if(ce==0)break;
					/*w--;
					if(w<=0)w=0;*/}
					else{continue;}
				}
			}
				arrpnd2[rb]=temp;
			    b_node[rb]=er;		
			    f=false;
			    rb++;	   
			    er=0;
		}// j loop
	}//p loop
	//copy of rb 
	int rbcpy=rb;
#pragma endregion
	//copy of branch
#pragma region MyRegion1
	///////////////////////////////////////////////////////////////////////////////////
	///copy of branch//////////////
	///////////////////////////////////////////////////////////////////////////////////
	Edevice** branch1=new Edevice*[];
	for(int i=0;i<rb;i++)
	{
		branch1[i]=new Edevice[111];
		for(int l=0;l<b_node[i];l++)
		{
			branch1[i][l]=branch[i][l];
		}
	}  
#pragma endregion
//loop happy try 
#pragma region MyRegion
int uu=0;
int t=arrpnd1[0],t1=arrpnd2[0];
for(int yy=1;yy<rb;yy++)
{
	if((t==arrpnd2[yy]||t==arrpnd1[yy])&&(t1==arrpnd2[yy]||t1==arrpnd1[yy]))
	{
		//create and add branches
		loopsarr[ilop]=new Edevice[111];
		l_device[ilop]=0;
	
	loopsarr[ilop]=branch1[uu];
		l_device[ilop]+=b_node[uu];
	for(int ia=0;ia<b_node[yy];ia++)
	{
			loopsarr[ilop][l_device[ilop]]=branch1[yy][ia];	
			l_device[ilop]+=1;
	}

		 ilop++;

	}	

	 uu++;

		 t=arrpnd1[yy];t1=arrpnd2[yy];

}//my for
#pragma endregion
#pragma region looptry2happy
t=arrpnd1[0],t1=arrpnd2[0];
uu=0;int y=1;
for(int yy=1;yy<rb;yy++)
{
	y=yy;
   if(!((t==arrpnd2[yy]||t==arrpnd1[yy])&&(t1==arrpnd2[yy]||t1==arrpnd1[yy])))
	if(t==arrpnd2[yy]){
	t=arrpnd1[uu];
	loopsarr[ilop]= new Edevice[111];
	l_device[ilop]=0;
	loopsarr[ilop]=branch[uu];
	l_device[ilop]+=b_node[uu];
	while(!((t==arrpnd1[y])&&(t==arrpnd2[y])))
	{
	for(int i=0;i<b_node[y];i++)
	{
		loopsarr[ilop][l_device[ilop]]=branch[y][i];
		l_device[ilop]+=1;
	}
     y++;
	 if(y==rb)break;
	}//while
	ilop++;
	uu++;
	if(uu==rb-1)break;
	}//if1
	else if(t1==arrpnd2[yy]){
	t1=arrpnd2[uu];
	loopsarr[ilop]= new Edevice[111];
	l_device[ilop]=0;
	loopsarr[ilop]=branch[uu];
	l_device[ilop]+=b_node[uu];
	while(!((t1==arrpnd1[y])&&(t1==arrpnd2[y])))
	{
	for(int i=0;i<b_node[y];i++)
	{
		loopsarr[ilop][l_device[ilop]]=branch[y][i];
		l_device[ilop]+=1;
	}
     y++;
	 if(y==rb)break;
	}//while
	ilop++;
	uu++;
	if(uu==rb-1)break;
	}//if2
}
	}
#pragma endregion
		for(int i=0;i<rb;i++)
	{
		cout<<"branch no"<<i<<"elements:"<<endl;
		for(int l=0;l<b_node[i];l++)
		{
			cout<<"device name "<<branch[i][l].name<<endl;
		}
	}
	for(int l=0;l<cecpy;l++)
		{
			cout<<"all devices name "<<E1[l].name<<endl;
		}
for(int k=0;k<ilop;k++)
{
	cout<<"loop no"<<k<<endl;
	for(int o=0;o<l_device[k];o++)
		cout<<loopsarr[k][o].name<<",";
	cout<<endl;
}
	//c2=vv,c3=rr,c1=ii,c4=ccr,c5=dd,ce=total(E1,E)
	int x;
	for(int k=0;k<ilop;k++)
	{
		delete[] loopsarr[k];
	}
delete []rr;
delete []vv;
delete []ii;
delete []Node;
delete []Arr_Count;
delete []E1;
delete []arrpnd2;
delete []arrpnd1;
delete []b_node;
	/*//cannot delete a copy second time
     delete []E;
	for(int k=0;k<rb;k++)
	{
		delete[] branch[k];
	}
	//cannot delete a copy second time
	for(int k=0;k<rb;k++)
	{
		delete[] branch1[k];
	}
	//cannot delete a copy second time
//delete []l_device;
*/
//cin>>x;
	return 0;
}