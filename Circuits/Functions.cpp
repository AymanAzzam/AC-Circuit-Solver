#include "Functions.h"

void intialize (MatrixXcd& arr,int col , int row)
{
	for(int i=0;i<col;i++)
	{
		for(int j=0;j<row;j++)
		{
			arr(i,j)=0;
		}
	}
}

void merge(MatrixXcd &G,MatrixXcd &B,MatrixXcd &C,MatrixXcd &D,MatrixXcd& a,int nodes,int volt)
{
	for(int i=0;i<nodes;i++)
	{
		for(int j=0;j<nodes;j++)
		{
			a(i,j)=G(i,j);
		}
		for(int j=0;j<volt;j++)
		{
			a(i,j+nodes)=B(i,j);
		}
	}		
	for(int i=0;i<volt;i++)
	{
		for(int j=0;j<nodes;j++)
		{
			a(i+nodes,j)=C(i,j);
		}
		for(int j=0;j<volt;j++)
		{
			a(i+nodes,j+nodes)=D(i,j);
		}
	}	
}

void transformation(complex<double> x,double& w,double & m)
{
 	w=real(x);
	m=imag(x);
}


void approx(double& x)
{
	x*=100;
	if(x-int(x)>0.5)
		x+=1;
	x=(int)x;
	x/=100;
}