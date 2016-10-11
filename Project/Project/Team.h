#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Team{

private:
	string name, city, state, region, txt;
	int pitching, batting, defense, average;

public:
	Team();
	Team(const Team& other);
	Team(string name, string city, string state, string region);
	const Team& operator=(const Team& rhs);

	//get
	string getName();
	string getCity();
	string getRegion();
	string getState();
	string getOutput();
	int getPitching();
	int getBatting();
	int getDefense();
	int getAverage();

	//set
	void setName(string name);
	void setCity(string city);
	void setState(string state);
	void setRegion(string region);

	//modify
	void modPitching(int n);
	void modBatting(int n);
	void modDefense(int n);

	//operators
	friend istream& operator >>(istream& in, Team& other);
	friend ostream& operator <<(ostream& out, const Team& other);
	bool operator ==(const Team& rhs);
	bool operator <(const Team& rhs);
};

