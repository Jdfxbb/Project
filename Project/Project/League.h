#pragma once
#include "Team.h"
#include "Game.h"
#include <vector>
#include <string>

class League {
private:
	vector<Team> teams;
	string name, state;
public:
	League() { state = name = ""; }
	League(string name, string state) { this->name = name; this->state = state; }
	
	void add(Team& team) { this->teams.push_back(team); }
	int size() { return teams.size(); }

	string getName() { return this->name; }
	string getState() { return this->state; }

	bool operator < (const League& rhs) { return teams.size() < rhs.teams.size(); }

};