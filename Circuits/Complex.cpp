#include "complex.h"
const double pi =3.14159265358;
Complex::Complex(vector<string> n,vector<double> r, vector<double> i ,double W)
{
	Names=n;
	Real=r;
	Imag=i;
	w=(W==0)?0.0000001:W;
	transform();
}


void Complex::transform()
{
	for(int i=0;i<Names.size();i++)
	{
		if((Names[i][0]=='V') || (Names[i][0]=='I') ||(Names[i][0]=='v') || (Names[i][0]=='i'))
		{
			double x=Real[i];
			Real[i]=x*cos(Imag[i]*pi/180);
			Imag[i]=x*sin(Imag[i]*pi/180);
			approx(Real[i]);
			approx(Imag[i]);
		}
		else if((Names[i][0]=='C') || (Names[i][0]=='c'))
		{
			Imag[i]=(-1/(w*Real[i]));
			Real[i]=0;
		}
		else if((Names[i][0]=='L') || (Names[i][0]=='l'))
		{
			Imag[i]=w*Real[i];
			Real[i]=0;
		}
		else if((Names[i][0]=='R') || (Names[i][0]=='r'))
		{
			Imag[i]=0;
		}
		value[i]=complex<double>(Real[i],Imag[i]);
	}
}


Complex::~Complex()
{
	Names.erase(Names.begin(),Names.end());
	Real.erase(Real.begin(),Real.end());
	Imag.erase(Imag.begin(),Imag.end());
}


void Complex::approx(double& x)
{
	x*=10000;
	if(x-int(x)>0.5)
		x+=1;
	x=(int)x;
	x/=10000;
}