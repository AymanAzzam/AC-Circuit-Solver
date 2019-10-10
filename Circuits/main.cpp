#include "file.h"
#include "complex.h"
#include "Functions.h"


int main()
{
	string ask;
	do
	{
		file x;
		double w;
		x.readfiles();  //read the file outside
		cout<<"Enter The Angular Fequency"<<endl;
		cin>>w;
		cout<<endl<<endl;
		Complex y(x.name,x.vec1,x.vec2,w);
		int num_nodes=x.num_nodes();
		int num_volt=x.num_volt();


		MatrixXcd G(num_nodes,num_nodes);
		for(int i=0;i<num_nodes;i++)
			for(int j=0;j<num_nodes;j++)
			{
				complex<double>sum(0,0); 
				if(i==j)
				{
					for(int k=0;k<x.name.size();k++)
					{
						bool flag=(x.name[k][0]!='V')&&(x.name[k][0]!='v')&&(x.name[k][0]!='I')&&(x.name[k][0]!='i');
						if(flag &&(x.node1[k]==i+1 || x.node2[k]==i+1))
						{
							complex<double>s(1,0);
							s/=y.value[k];
							sum+=s;
						}
					}
				}
				else
				{
					for(int k=0;k<x.name.size();k++)
					{
						bool flag=(x.name[k][0]!='V')&&(x.name[k][0]!='v')&&(x.name[k][0]!='I')&&(x.name[k][0]!='i');
						if(flag &&((x.node1[k]==i+1 && x.node2[k]==j+1) || (x.node1[k]==j+1 && x.node2[k]==i+1)))
						{
							complex<double>s(-1,0);
							s/=y.value[k];
							sum+=s;
						}
					}
				}
				G(i,j)=sum;
			}



			MatrixXcd B(num_nodes,num_volt),C(num_volt,num_nodes);
			intialize(B,num_nodes,num_volt);
			intialize(C,num_volt,num_nodes);
			{
				int k=0;
				for(int i=0;i<x.name.size();i++)
				{
					if(x.name[i][0] =='v' || x.name[i][0]=='V' )
					{
						if(x.node1[i]!=0)
						{
							B(x.node1[i]-1,k)=1;
							C(k,x.node1[i]-1)=1;
						}
						if(x.node2[i]!=0)
						{
							B(x.node2[i]-1,k)=-1;
							C(k,x.node2[i]-1)=-1;
						}
						k++;
					}
				}
			}



			MatrixXcd D(num_volt,num_volt);
			intialize(D,num_volt,num_volt);



			MatrixXcd A(num_nodes+num_volt,num_nodes+num_volt);
			merge(G,B,C,D,A,num_nodes,num_volt);


			MatrixXcd Z(num_nodes+num_volt,1);
			intialize(Z,num_nodes+num_volt,1);
			{

				int index=num_nodes;
				for(int i=0;i<x.name.size();i++)
				{
					if(x.name[i][0]=='i'||x.name[i][0]=='I')
					{
						if(x.node1[i]!=0)
							Z(x.node1[i]-1,0)-=y.value[i];
						if(x.node2[i]!=0)
							Z(x.node2[i]-1,0)+=y.value[i];
					}
					if(x.name[i][0]=='V'||x.name[i][0]=='v')
					{
						Z(index,0)=y.value[i];	
						index++;
					}
				}
			}



			MatrixXcd X=A.jacobiSvd(ComputeThinU | ComputeThinV).solve(Z);
			MatrixXcd  Y(num_volt+num_nodes+1,1);
			Y(0,0)=0;
			for(int i=1;i<=num_volt+num_nodes;i++)
				Y(i,0)=X(i-1,0);
			for(int i=0;i<num_nodes;i++)
			{
				double n,m;
				transformation(X(i,0),n,m);
				double angle;
				if(m<0 && n<0)
					angle=atan(m/n)*180/3.1416+180;
				else if(m<0 && n>0)
					angle=360-atan(-m/n)*180/3.1416;
				else if(m>0 && n<0)
					angle=180-atan(-m/n)*180/3.1416;
				else
					angle=atan(m/n)*180/3.1416;
				if(angle>=360)
					angle-=360;
				double result = sqrt(n*n+m*m);
				approx(result);
				approx(angle);
				cout<<"V["<<i+1<<"]  =  "<<result<<"   "<<angle<<endl;
			}

			cout<<endl<<endl;

			int k=num_nodes+1;
			for(int i=0;i<x.name.size();i++){
				if(x.name[i][0]=='v' || x.name[i][0]=='V')
				{
					double n,m;
					transformation(Y(k++,0),n,m);
					double angle;
					if(m<0 && n<0)
						angle=atan(m/n)*180/3.1416+180;
					else if(m<0 && n>0)
						angle=360-atan(-m/n)*180/3.1416;
					else if(m>0 && n<0)
						angle=180-atan(-m/n)*180/3.1416;
					else
						angle=atan(m/n)*180/3.1416;
					if(angle>=360)
						angle-=360;
					double result = sqrt(n*n+m*m);
					approx(result);
					approx(angle);
					cout<<"I("<<x.node1[i]<<","<<x.node2[i]<<")"<<"  "<<x.name[i]<<"  =  "<<result<<"   "<<angle<<endl;
				}
				else if(x.name[i][0]=='i' || x.name[i][0]=='I')
				{
					double n,m;
					transformation(y.value[i],n,m);
					double angle;
					if(m<0 && n<0)
						angle=atan(m/n)*180/3.1416+180;
					else if(m<0 && n>0)
						angle=360-atan(-m/n)*180/3.1416;
					else if(m>0 && n<0)
						angle=180-atan(-m/n)*180/3.1416;
					else
						angle=atan(m/n)*180/3.1416;
					if(angle>=360)
						angle-=360;
					double result = sqrt(n*n+m*m);
					approx(result);
					approx(angle);
					cout<<"I("<<x.node1[i]<<","<<x.node2[i]<<")"<<"  "<<x.name[i]<<"  =  "<<result<<"   "<<angle<<endl;
				}
				else
				{
					double n,m;
					transformation((Y(x.node1[i],0)-Y(x.node2[i],0))/y.value[i],n,m);
					double angle;
					if(m<0 && n<0)
						angle=atan(m/n)*180/3.1416+180;
					else if(m<0 && n>0)
						angle=360-atan(-m/n)*180/3.1416;
					else if(m>0 && n<0)
						angle=180-atan(-m/n)*180/3.1416;
					else
						angle=atan(m/n)*180/3.1416;
					if(angle>=360)
						angle-=360;
					double result = sqrt(n*n+m*m);
					approx(result);
					approx(angle);
					cout<<"I("<<x.node1[i]<<","<<x.node2[i]<<")"<<"  "<<x.name[i]<<"  =  "<<result<<"   "<<angle<<endl;
				}
			}
			cout<<endl<<endl<<"__________________________________________________________________________"<<endl;
			cout<<"do you Want to test another Circuit(y/n)"<<endl;
			cin>>ask;
	}
	while(ask[0]=='y');
}