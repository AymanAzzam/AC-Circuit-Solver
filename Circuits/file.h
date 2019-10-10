#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class file
{
	
public:
	vector<string>name;  //vector of string
	vector<int>node1;  //vector of node in 1st coloumn 
	vector<int>node2;  //vector of node in 2nd coloumn 
	vector<double>vec1;     //first input of the complex nom.
	vector<double>vec2;     //phase
	~file();
	int num_nodes()const;
	int num_volt()const;
	void readfiles();
};

