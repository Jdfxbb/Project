#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <random>
#include <functional>
#include <algorithm>
using namespace std;

class Team{

private:
	string name, city, state, zip, county, region;
	int next, pitcher1, pitcher2, pitcher3, pitcher4, pitcher5;
	int batting, defense;
	int rotation[5] = { pitcher1, pitcher2, pitcher3, pitcher4, pitcher5 };
	int wins, losses;

public:
	Team();
	Team(const Team& other);
	Team(string name, string city, string state, string zip, string county, string region);
	const Team& operator=(const Team& rhs);
	
	void rotate() {
		next++;
		if (next == 5) {
			next = 0;
		}
	}


	//get
	string getName() { return this->name; }
	string getCity() { return this->city; }
	string getState() { return this->state; }
	string getZip() { return this->zip; }
	string getCounty() { return this->county; }
	string getRegion() { return this->region; }


	int getPitching() { return this->rotation[next]; }
	int getBatting() { return this->batting; }
	int getDefense() { return this->defense; }
	int getWins() { return this->wins; }
	int getLosses() { return this->losses; }

	//set
	void setName(string name) { this->name = name; }
	void setCity(string city) { this->city = city; }
	void setState(string state) { this->state = state; }
	void setZip(string zip) { this->zip = zip; }
	void setCounty(string county) { this->county = county; }
	void setRegion(string region) { this->region = region; }
	void setPitching(int n, int p) { this->rotation[p] = n; }
	void setBatting(int n) { this->batting = n; }
	void setDefense(int n) { this->defense = n; }
	void setStats();

	void win() { this->wins++; }
	void lose() { this->losses++; }

	//operators
	friend istream& operator >>(istream& in, Team& other);
	friend ostream& operator <<(ostream& out, const Team& other);
	bool operator ==(const Team& rhs);
	bool operator <(const Team& rhs);
};

