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

struct Game { // this can be made smoother
	Team home, away;
	vector<int> boxHome, boxAway; // vectors for box score
	int inning, balance;
	int Hscore, Ascore, Htotal, Atotal, offense, defense;

	Game() {
		Hscore = Ascore = 0;
	}
	Game(Team& home, Team& away) {
		balance = 150; // higher number should mean lower scoring games
		inning = 1;
		this->home = home;
		this->away = away;

	}
	void play() {
		default_random_engine gen(time(NULL));
		uniform_int_distribution<int> off(1, 500);
		uniform_int_distribution<int> def(1, 300);
		auto setO = bind(off, gen);
		auto setD = bind(def, gen);
		Atotal = Htotal = 0;

		while (Htotal == Atotal || inning <= 9) {
			Hscore = Ascore = 0;
			// top
			offense = away.getBatting() + setO();
			defense = home.getPitching() + home.getDefense() + setD();
			if (offense > defense) {
				if (offense - defense < balance) {
					Ascore = 1;
				}
				else {
					Ascore = (offense - defense) / balance;
				}
			}
			// bottom
			offense = home.getBatting() + setO();
			defense = away.getPitching() + home.getDefense() + setD();
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

		if (Atotal > Htotal) {
			away.win();
			home.lose();
			return;
		}
		else {
			home.win();
			away.lose();
			return;
		}
	}


	friend ostream& operator <<(ostream& out, Game& other) { /*use some columns to make this look nicer 
						1	2	3	4	5	6	7	8	9	R	 something like this
		Orlando Bobcats 0	2	0	1	0	0	0	0	0	3
		Lansing Aces    0	0	0	1	0	0	0	1	0	2
															 */
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
