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
using namespace std;

void assignTeams(list<Team>& teams);
void saveTeams(list<Team> teams, string output);
void getTeams(list<Team>& teams, string input);
list<list<Team>> organize(list<Team>& teams);
list<Team> setStats(list<Team>& teams);

void main() {
	list<Team> teams;

	getTeams(teams, "NewClassData.txt");

	teams.unique();
	teams.sort();

	assignTeams(teams);

	list<list<Team>> Regions = organize(teams);

	saveTeams(teams, "TeamClassData.txt");

	system("pause");
}

void getTeams(list<Team>& teams, string input) {
	ifstream fin(input);
	Team team;

	if (!fin.good()) {
		cerr << "bad input" << endl;
		return;
	}

	fin >> team;
	while (fin.good()) {
		teams.push_back(team);
		fin >> team;
	}
}

void assignTeams(list<Team>& teams) {
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

	for (list<Team>::iterator it = teams.begin(); it != teams.end(); it++) {
		it->setName(names[assign()]);
	}
}

void saveTeams(list<Team> teams, string output) {
	ofstream fout(output);
	list<Team>::iterator it;

	for (it = teams.begin(); it != teams.end(); it++) {
		if (it->getCity() != "" && it->getCity() != " ") {
			fout << *it << endl;
		}
	}
	fout.close();
}

list<list<Team>> organize(list<Team>& teams) {
	list<Team>::iterator it;
	list<string>::iterator strit;
	list<list<string>>::iterator stringit;

	list<Team> W, N, MW, GL, C, NE, SE, SW;
	list<list<Team>> RegionLists = { W, N, MW, GL, C, NE, SE, SW };

	list<string> West, North, Midwest, GreatLakes, Coastal, Northeast, Southeast, Southwest;
	
	West = { "AK", "CA", "NV", "OR", "WA", "HI", "ID", "UT" };
	North = { "CO", "MN", "MT", "ND", "NE", "SD", "WY" };
	Midwest = { "AR", "IA", "KS", "MO", "MS" };
	GreatLakes = { "IN", "MI", "OH", "WI", "IL" };
	Coastal = { "DC", "DE", "MD", "NC", "NJ", "VA", "WV", "CT" };
	Northeast = { "MA", "ME", "PA", "NH", "NY", "RI", "VT" };
	Southeast = { "AL", "FL", "GA", "SC", "TN", "KY" };
	Southwest = { "AZ", "LA", "NM", "TX", "OK" };
	list<list<string>> RegionStrings = { West, North, Midwest, GreatLakes, Coastal, Northeast, Southeast, Southwest };
	

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

list<Team> setStats(list<Team>& teams) {

	default_random_engine gen(time(NULL));
	uniform_int_distribution<int> dist(300, 999);
	auto set = bind(dist, gen);

	ofstream fout("stats.txt");

	list<Team>::iterator it;
	for (it = teams.begin(); it != teams.end(); it++) {
		it->setBatting(set());
		it->setDefense(set());
		it->setPitching(set());
		fout << it->getCity() << " " << it->getName() << it->getState() << " " << it->getAverage() << endl;
	}
	fout.close();
	return teams;
}