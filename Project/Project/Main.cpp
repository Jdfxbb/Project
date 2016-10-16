#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <functional>
#include <algorithm>
#include "Team.h"
#include "Game.h"
#include "League.h"
#include <Windows.h>
#include <SDL/SDL.h>
#include <GL/glew.h>
using namespace std;

void renameTeams(vector<Team>& teams); // assigns random team names
void saveTeams(vector<Team> teams, string output); // puts current team dat in output file
void getTeams(vector<Team>& teams, string input); // populates team list from input file
vector<vector<Team>> organize(vector<Team>& teams); // assigns team to region, populates list of regions, not sure how to handle this data yet, probably needs to be split up into a few functions
void generateStats(vector<Team>& team); // randomizes stats 
void test(vector<Team>& teams, vector<League>& leagues);


int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);

	//vector<Team> teams;
	//vector<League> leagues;

	//getTeams(teams, "TeamClassData.txt");
	//generateStats(teams);


	system("pause");
	return 0;
}

void getTeams(vector<Team>& teams, string input) {
	ifstream fin(input);
	Team team;

	if (!fin.good()) {
		cerr << "bad input" << endl;
		return;
	}

	fin >> team;
	while (fin.good()) {
		if (team.getCounty() != "") {
			teams.push_back(team);
		}
		fin >> team;
	}
}

void renameTeams(vector<Team>& teams) { // random numbers not working
	string temp;
	Team team;

	// team names
	vector<string> names;

	// populate team name array
	ifstream tin("teams.txt");
	getline(tin, temp);
	while (tin.good()) {
		names.push_back(temp);
		getline(tin, temp);
	}

	//random number generator
	default_random_engine gen(time(NULL));
	uniform_int_distribution<int> dist(0, names.size() - 1);
	auto assign = bind(dist, gen);

	for (vector<Team>::iterator it = teams.begin(); it != teams.end(); it++) {
		it->setName(names[assign()]);
	}
}

void saveTeams(vector<Team> teams, string output) {
	ofstream fout(output);
	vector<Team>::iterator it;

	for (it = teams.begin(); it != teams.end(); it++) {
		if (it->getCity() != "" && it->getCity() != " ") {
			fout << *it << endl;
		}
	}
	fout.close();
}

vector<vector<Team>> organize(vector<Team>& teams) {
	vector<Team>::iterator it;
	vector<string>::iterator strit;
	vector<vector<string>>::iterator stringit;

	vector<Team> W, N, MW, GL, C, NE, SE, SW;
	vector<vector<Team>> RegionLists = { W, N, MW, GL, C, NE, SE, SW };

	vector<string> West, North, Midwest, GreatLakes, Coastal, Northeast, Southeast, Southwest;
	
	West = { "AK", "CA", "NV", "OR", "WA", "HI", "ID", "UT" };
	North = { "CO", "MN", "MT", "ND", "NE", "SD", "WY" };
	Midwest = { "AR", "IA", "KS", "MO", "MS" };
	GreatLakes = { "IN", "MI", "OH", "WI", "IL" };
	Coastal = { "DC", "DE", "MD", "NC", "NJ", "VA", "WV", "CT" };
	Northeast = { "MA", "ME", "PA", "NH", "NY", "RI", "VT" };
	Southeast = { "AL", "FL", "GA", "SC", "TN", "KY" };
	Southwest = { "AZ", "LA", "NM", "TX", "OK" };
	vector<vector<string>> RegionStrings = { West, North, Midwest, GreatLakes, Coastal, Northeast, Southeast, Southwest };
	

	for (it = teams.begin(); it != teams.end(); it++) { // for teams
		for (stringit = RegionStrings.begin(); stringit != RegionStrings.end(); stringit++) { //for region strings
			for (strit = stringit->begin(); strit != stringit->end(); strit++) { // for states in string
				if (it->getState() == *strit) {
					if (*stringit == West) {
						it->setRegion("West");
						W.push_back(*it);
						break;
					}
					if (*stringit == North) {
						it->setRegion("North");
						N.push_back(*it);
						break;
					}
					if (*stringit == Midwest) {
						it->setRegion("Midwest");
						MW.push_back(*it);
						break;
					}
					if (*stringit == GreatLakes) {
						it->setRegion("GreatLakes");
						GL.push_back(*it);
						break;
					}
					if (*stringit == Coastal) {
						it->setRegion("Coastal");
						C.push_back(*it);
						break;
					}
					if (*stringit == Northeast) {
						it->setRegion("Northeast");
						NE.push_back(*it);
						break;
					}
					if (*stringit == Southeast) {
						it->setRegion("Southeast");
						SE.push_back(*it);
						break;
					}
					if (*stringit == Southwest) {
						it->setRegion("Southwest");
						SW.push_back(*it);
						break;
					}
					break;
				}
			}
		}
	}
	return RegionLists;
}

void generateStats(vector<Team>& teams) {
	default_random_engine gen(time(NULL));
	uniform_int_distribution<int> bat(100, 500);
	uniform_int_distribution<int> def(50, 200);
	uniform_int_distribution<int> pit(50, 500);
	auto setB = bind(bat, gen);
	auto setD = bind(def, gen);
	auto setP = bind(pit, gen);

	for (vector<Team>::iterator it = teams.begin(); it != teams.end(); it++) {
		it->setBatting(setB());
		it->setDefense(setD());
		for (int i = 0; i < 5; i++) {
			it->setPitching(setP(), i);
		}
		it->setNext(0);
	}
}

void test(vector<Team>& teams, vector<League>& leagues) {
	bool exists = false;
	for (vector<Team>::iterator it = teams.begin(); it != teams.end(); it++) {
		for (vector<League>::iterator lt = leagues.begin(); lt != leagues.end(); lt++) {
			if (lt->getName() == it->getCounty() && lt->getState() == it->getState()) {
				lt->add(*it);
				exists = true;
				break;
			}

		}
		if (!exists) {
			League league(it->getCounty(), it->getState());
			league.add(*it);
			leagues.push_back(league);
			
		}
		exists = false;
	}
	sort(leagues.begin(), leagues.end());
	ofstream fout("counties.txt");
	for (vector<League>::iterator lt = leagues.begin(); lt != leagues.end(); lt++) {
		fout << lt->getName() << " " << lt->getState() <<" "<< lt->size() << endl;
	}

}