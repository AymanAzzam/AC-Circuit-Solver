#include "file.h"


file::~file()
{
	name.erase(name.begin(),name.end());
	vec1.erase(vec1.begin(),vec1.end());
	vec2.erase(vec2.begin(),vec2.end());
	node1.erase(node1.begin(),node1.end());
	node2.erase(node2.begin(),node2.end());
}
void file:: readfiles(){
	string x;
	int l,y;
	double	z,o;
	ifstream inputfile;
	string read;
	cout<<"please Enter The input file name"<<endl;
	do
	{
		cin>>read;
		inputfile.open(read+".txt");
		if(inputfile.is_open()){
			while(!inputfile.eof()){
				inputfile>>x;
				if(x[0]=='v' ||x[0]=='i' || x[0]=='I' || x[0]=='V'){
					inputfile >> l>>y>>z>>o;
					name.push_back(x);
					node1.push_back(l);
					node2.push_back(y);
					vec1.push_back(z);
					vec2.push_back(o);}
				else
				{
					inputfile >> l>>y>>z;
					name.push_back(x);
					node1.push_back(l);
					node2.push_back(y);
					vec1.push_back(z);
					vec2.push_back(0);
				}
			}
		}
		else
		{
			cout<<"File Name not Found , try again"<<endl;
		}
	}
	while(!inputfile.is_open());
}


int file::num_nodes()const
{
	int x=0;
	for(int i=0;i<name.size();i++)
	{
		if(node1[i]>x)
			x=node1[i];
		if(node2[i]>x)
			x=node2[i];
	}
	return x;
}


int file::num_volt()const
{
	int x=0;
	for(int i=0;i<name.size();i++)
		if(name[i][0]=='V' || name[i][0]=='v')
			x++;
	return x;
}