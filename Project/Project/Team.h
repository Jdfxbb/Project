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
	// identifiers - zip is only unique ID; all others will have duplicates
	string name, city, state, zip, county, region;

	// game stats
	int batting, defense, next;
	int rotation[5] = { 0 };
	int wins, losses;

public:
	Team();
	Team(const Team& other); 
	Team(string name, string city, string state, string zip, string county, string region); // probably only used if someone wants to create a new team, not a priority right now
	const Team& operator=(const Team& rhs);
	
	//getters for identifiers
	string getName() { return this->name; }
	string getCity() { return this->city; }
	string getState() { return this->state; }
	string getZip() { return this->zip; }
	string getCounty() { return this->county; }
	string getRegion() { return this->region; }

	// getters for game and league processes
	int getPitching() { return this->rotation[next]; }
	int getBatting() { return this->batting; }
	int getDefense() { return this->defense; }
	int getWins() { return this->wins; }
	int getLosses() { return this->losses; }

	//setters 
	void setName(string name) { this->name = name; }
	void setCity(string city) { this->city = city; }
	void setState(string state) { this->state = state; }
	void setZip(string zip) { this->zip = zip; }
	void setCounty(string county) { this->county = county; }
	void setRegion(string region) { this->region = region; }
	void setPitching(int n, int p) { this->rotation[p] = n; }
	void setBatting(int n) { this->batting = n; }
	void setDefense(int n) { this->defense = n; }
	void setNext(int n) { this->next = n; }

	// game operations
	void win() { this->wins++; }
	void lose() { this->losses++; }
	void rotate() { next++;	if (next == 5)	next = 0; } // move to next pitcher

	//operators
	friend istream& operator >>(istream& in, Team& other);
	friend ostream& operator <<(ostream& out, const Team& other);
	bool operator ==(const Team& rhs);
	bool operator <(const Team& rhs);
};

