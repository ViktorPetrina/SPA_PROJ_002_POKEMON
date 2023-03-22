#include <iostream>
#include <sstream>
#include "Pokemon.h"
#include <ctime>

using namespace std;

int Pokemon::random(double min, double max)
{
	srand(time(nullptr));
	int min_ = 100 * min;
	int max_ = 100 * max;

	double random = rand() % (max_ - min_ + 1) + min_;

	random /= 100;

	return random;
}

Pokemon::Pokemon()
{
	set_id("");
	set_name("");
	set_type1("");
	set_type2("");
	set_total(0);
	set_hp(0);
	set_atk(0);
	set_def(0);
	set_sp_atk(0);
	set_sp_def(0);
	set_speed(0);
	set_generation(0);
	set_legendary(0);
}

Pokemon::Pokemon(string id, string name, string type1, string type2, int total) : Pokemon()
{
	set_id(id);
	set_name(name);
	set_type1(type1);
	set_type2(type2);
	set_total(total);

}

void Pokemon::set_id(string id)
{
	this->id = id;
}

void Pokemon::set_name(string name)
{
	this->name = name;
}

void Pokemon::set_type1(string type)
{
	this->type1 = type;
}

void Pokemon::set_type2(string type)
{
	this->type2 = type;
}

void Pokemon::set_total(int total)
{
	this->total = total;
}

void Pokemon::set_hp(int hp)
{
	this->hp = hp;
}

void Pokemon::set_atk(int atk)
{
	this->atk = atk;
}

void Pokemon::set_def(int def)
{
	this->def = def;
}

void Pokemon::set_sp_atk(int sp_atk)
{
	this->sp_atk = sp_atk;
}

void Pokemon::set_sp_def(int sp_def)
{
	this->sp_def = sp_def;
}

void Pokemon::set_speed(int speed)
{
	this->speed = speed;
}

void Pokemon::set_generation(int generation)
{
	this->generation = generation;
}

void Pokemon::set_legendary(bool legendary)
{
	this->legendary = legendary;
}

string Pokemon::get_id()
{
	return id;
}

string Pokemon::get_name()
{
	return name;
}

string Pokemon::get_type1()
{
	return type1;
}

string Pokemon::get_type2()
{
	return type2;
}

int Pokemon::get_total()
{
	return total;
}

int Pokemon::get_hp()
{
	return hp;
}

int Pokemon::get_atk()
{
	return atk;
}

int Pokemon::get_def()
{
	return def;
}

int Pokemon::get_sp_atk()
{
	return sp_atk;
}

int Pokemon::get_sp_def()
{
	return sp_def;
}

int Pokemon::get_speed()
{
	return speed;
}

int Pokemon::get_generation()
{
	return generation;
}

bool Pokemon::is_legendary()
{
	return legendary;
}

void Pokemon::print_data()
{
	cout << "---- Pokemon data ----" << endl;
	cout << "Name: " << get_name() << "\nType 1: " << get_type1() << "\nType 2: " << get_type2() << "\nTotal: " << get_total();
}

void Pokemon::fight(Pokemon p)
{
	int hp1 = this->hp;
	int hp2 = p.hp;

	while (true) {

		hp1 -= (p.get_atk() / (double)this->def) * random(0.75, 1.00);
		cout << p.get_name() << " napada!\n" << this->name << " HP: " << this->hp << endl;

		hp2 -= (this->atk / (double)p.get_def()) * random(0.75, 1.00);
		cout << this->name << " napada!\n" << p.get_name() << " HP: " << p.get_hp() << endl;


		if (hp1 <= 0) {
			cout << this->name << " pobjeduje!" << endl;
			break;
		}
		else {
			cout << p.get_name() << " pobjeduje!" << endl;
			break;
		}
	}

}
