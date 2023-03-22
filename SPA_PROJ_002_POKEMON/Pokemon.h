#pragma once
#include <string>
using namespace std;


class Pokemon
{
private:
	string id, name, type1, type2;
	int total, hp, atk, def, sp_atk, sp_def, speed, generation;
	bool legendary;

	int random(double min, double max);

public:
	Pokemon();
	Pokemon(string id, string name, string type1, string type2, int total);

	void set_id(string id);
	void set_name(string name);
	void set_type1(string type);
	void set_type2(string type);
	void set_total(int total);
	void set_hp(int hp);
	void set_atk(int atk);
	void set_def(int def);
	void set_sp_atk(int sp_atk);
	void set_sp_def(int sp_def);
	void set_speed(int speed);
	void set_generation(int generation);
	void set_legendary(bool legendary);

	string get_id();
	string get_name();
	string get_type1();
	string get_type2();
	int get_total();
	int get_hp();
	int get_atk();
	int get_def();
	int get_sp_atk();
	int get_sp_def();
	int get_speed();
	int get_generation();
	bool is_legendary();

	void print_data();
	void fight(Pokemon p);
};

