#pragma once
#include "Team.h"
#include <vector>
#include <random>
#include <time.h>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

struct Game {
	Team home, away;
	vector<int> boxHome, boxAway;
	int inning, balance;
	int Hscore, Ascore, Htotal, Atotal, offense, defense;

	Game() {
		Hscore = Ascore = 0;
	}
	Game(Team& home, Team& away) {
		Hscore = Ascore = Htotal = Atotal = 0;
		balance = 150;
		inning = 1;
		this->home = home;
		this->away = away;

	}
	void play() {
		default_random_engine gen(time(NULL));
		uniform_int_distribution<int> dist(1, 700);
		auto set = bind(dist, gen);

		while (Htotal == Atotal || inning <= 9) {
			Hscore = Ascore = 0;
			// top
			offense = away.getBatting() + set();
			defense = home.getPitching()  /1.5 + home.getDefense() / 2 + set();
			if (offense > defense) {
				if (offense - defense < balance) {
					Ascore = 1;
				}
				else {
					Ascore = (offense - defense) / balance;
				}
			}
			// bottom
			offense = home.getBatting() + set();
			defense = away.getPitching() / 1.5 + home.getDefense() / 2 + set();
			if (offense > defense) {
				if (offense - defense < balance) {
					Hscore = 1;
				}
				else {
					Hscore = (offense - defense) / balance;
				}
			}
			boxHome.push_back(Hscore);
			boxAway.push_back(Ascore);
			Htotal += Hscore;
			Atotal += Ascore;
			inning++;
		}

		//if (Atotal > Htotal) {
		//	return away;
		//}
		//return home;
	}
	friend ostream& operator <<(ostream& out, Game& other) {
		out << other.away.getCity() << " @ " << other.home.getCity() << endl;
		for (int i = 0; i < other.boxAway.size(); i++) {
			out << other.boxAway[i] << " ";
		}
		out << other.Atotal << endl;
		for (int i = 0; i < other.boxHome.size(); i++) {
			out << other.boxHome[i] << " ";
		}
		out << other.Htotal << endl;
		return out;
	}
};
