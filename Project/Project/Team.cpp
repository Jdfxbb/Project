#include "Team.h"

Team::Team(){ // default
	this->name = this->city = this->state = this->zip = this->county = this->region = "";
	this->batting = this->defense = this->wins = this->losses = this->next = 0;
	for (int i = 0; i < 5; i++) {
		rotation[i] = 0;
	}

}
Team::Team(const Team& other){ // copy
	this->name = other.name;
	this->city = other.city;
	this->state = other.state;
	this->zip = other.zip;
	this->county = other.county;
	this->region = other.region;
	this->batting = other.batting;
	this->defense = other.defense;
	this->wins = other.wins;
	this->losses = other.losses;
	this->next = 0;
	for (int i = 0; i < 5; i++) {
		rotation[i] = other.rotation[i];
	}
}

Team::Team(string name, string city, string state, string zip, string county, string region) { // assignment
	this->name = name;
	this->city = city;
	this->state = state;
	this->zip = zip;
	this->county = county;
	this->region = region;
	this->batting = this->defense = this->wins = this->losses = 0;
}

const Team& Team:: operator=(const Team& rhs){
	if (this != &rhs){
		this->name = rhs.name;
		this->city = rhs.city;
		this->state = rhs.state;
		this->zip = rhs.zip;
		this->county = rhs.county;
		this->region = rhs.region;
		this->batting = rhs.batting;
		this->defense = rhs.defense;
		this->wins = rhs.wins;
		this->losses = rhs.losses;
		for (int i = 0; i < 5; i++) {
			rotation[i] = rhs.rotation[i];
		}
	}
	return *this;
}

//operators
istream& operator >> (istream& in, Team& other){
	getline(in, other.city);
	getline(in, other.name);
	getline(in, other.state);
	getline(in, other.zip);
	getline(in, other.county);
	getline(in, other.region);
	return in; 
}
ostream& operator << (ostream& out, const Team& other){
	return out << other.city << endl
	<< other.name << endl
	<< other.state << endl
	<< other.zip << endl
	<< other.county << endl
	<< other.region;
}
bool Team::operator ==(const Team& rhs){
	return this->zip == rhs.zip;
}
bool Team::operator <(const Team& rhs){
	if (this->state != rhs.state){
		return this->state < rhs.state;
	}
	if (this->city != rhs.city) {
		return this->city < rhs.city;
	}
	return this->name < rhs.name;
}

