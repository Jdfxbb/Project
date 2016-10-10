#include "Team.h"

Team::Team(){ // default
	this->name = this->city = this->region = this->state = "";
	this->pitching = this->batting = this->defense = 0;
}
Team::Team(const Team& other){ // copy
	this->name = other.name;
	this->city = other.city;
	this->state = other.state;
	this->region = other.region;
	this->pitching = other.pitching;
	this->batting = other.batting;
	this->defense = other.defense;
}

Team::Team(string name, string city, string state, string region){ // construct
	this->name = name;
	this->city = city;
	this->state = state;
	this->region = region;
	this->pitching = this->batting = this->defense = 0;
}

const Team& Team:: operator=(const Team& rhs){
	if (this != &rhs){
		this->name = rhs.name;
		this->city = rhs.city;
		this->state = rhs.state;
		this->region = rhs.region;
		this->batting = rhs.batting;
		this->pitching = rhs.pitching;
		this->defense = rhs.defense;
	}
	return *this;
}

//get
string Team::getName(){
	return this->name;
}
string Team::getCity(){
	return this->city;
}
string Team::getRegion(){
	return this->region;
}
string Team::getState(){
	return this->state;
}
string Team::getOutput(){
	return txt;
}
double Team::getPitching(){
	return this->pitching;
}
double Team::getBatting(){
	return this->batting;
}
double Team::getDefense(){
	return this->defense;
}

// set
void Team::setName(string name){
	this->name = name;
}
void Team::setCity(string city){
	this->city = city;
}
void Team::setState(string state){
	this->state = state;
}
void Team::setRegion(string region){
	this->region = region;
}
void Team::modPitching(double n){
	this->pitching += n; 
}
void Team::modBatting(double n){
	this->batting += n;
}
void Team::modDefense(double n){
	this->defense += n;
}

//operators
istream& operator >> (istream& in, Team& other){
	getline(in, other.city);
	getline(in, other.name);
	in >> other.state >> other.region;
	in.ignore();
	return in; 
}
ostream& operator << (ostream& out, const Team& other){
	return out << other.city << endl << other.name << endl << other.state << " " << other.region;
}
bool Team::operator ==(const Team& rhs){
	return this->city == rhs.city;
}
bool Team::operator <(const Team& rhs){
	if (this->state == rhs.state){
		return this->city < rhs.city;
	}
	return this->state < rhs.state;
}