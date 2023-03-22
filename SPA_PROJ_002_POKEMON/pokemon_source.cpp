#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "Pokemon.h"

using namespace std;
using namespace chrono;

string title() {
	stringstream ss;
	ss << "                                  ,'\\"
		<< "\n    _.----.        ____         ,'  _\\   ___    ___     ____"
		<< "\n_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`."
		<< "\n\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |"
		<< "\n \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |"
		<< "\n   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |"
		<< "\n    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |"
		<< "\n     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |"
		<< "\n      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |"
		<< "\n       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |"
		<< "\n        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |"
		<< "\n                                `'                            '-._|";
	
	return ss.str();
}

int to_int(string& s) {
	stringstream ss(s);
	int n;

	if (ss >> n) {
		return n;
	}
	else {
		return 0;
	}
}

string to_string(string& s) {
	if (s.length() == 0) {
		return "";
	}
	else {
		return s;
	}
}

void enter_path() {
	
	string path;
	cout << "Unesite putanju/ime datoteke: ";
	getline(cin, path);

	ofstream dat("path.bin", ios_base::binary);
	if (!dat) {
		throw exception("Greska kod pisanja u binarnu datoteku!");
	}

	int n = path.length();
	dat.write((char*)&n, sizeof(n));
	dat.write(path.c_str(), n);

	dat.close();
}

Pokemon line_to_pokemon(stringstream& ss) {
	string s;
	bool legendary;
	Pokemon p;
	stringstream b;

	getline(ss, s, ',');
	p.set_id(to_string(s));
	getline(ss, s, ',');
	p.set_name(to_string(s));
	getline(ss, s, ',');
	p.set_type1(to_string(s));
	getline(ss, s, ',');
	p.set_type2(to_string(s));
	
	getline(ss, s, ',');
	p.set_total(to_int(s));
	getline(ss, s, ',');
	p.set_hp(to_int(s));
	getline(ss, s, ',');
	p.set_atk(to_int(s));
	getline(ss, s, ',');
	p.set_def(to_int(s));
	getline(ss, s, ',');
	p.set_sp_atk(to_int(s));
	getline(ss, s, ',');
	p.set_sp_def(to_int(s));
	getline(ss, s, ',');
	p.set_speed(to_int(s));
	getline(ss, s, ',');
	p.set_generation(to_int(s));
	
	getline(ss, s, ',');
	b << s;
	b >> legendary;
	p.set_legendary(legendary);

	return p;
}

void parse_file(vector<Pokemon>& vec) {
	
	ifstream bin_dat("path.bin", ios_base::binary);
	if (!bin_dat) {
		throw exception("Greska kod citanja sa binarne datoteke!");
	}

	int n;
	bin_dat.read((char*)&n, sizeof(n));
	char* pchar = new char[n];
	bin_dat.read(pchar, n);
	
	string path = string(pchar, n);
	cout << "Path: " << path << endl;
	bin_dat.close();

	ifstream dat(path + ".csv");
	if (!dat) {
		throw exception("Greska kod citanja popisa pokemona!");
	}

	string junk;
	getline(dat, junk);
	string temp, conv;

	auto begin = high_resolution_clock::now();
	while (getline(dat, temp)) {
		stringstream ss(temp);
		vec.push_back(line_to_pokemon(ss));
	}
	auto end = high_resolution_clock::now();
	cout << "Trajanje citanja datoteke: " << duration_cast<milliseconds>(end - begin).count() << " ms." << endl;
	
	dat.close();
}

void print_pokemon_names(vector<Pokemon>& poks) {
	for (int i = 0; i < poks.size(); i++) {
		cout << i << ") " << poks[i].get_name() << endl;
	}
}

void pokemon_fight(vector<Pokemon>& poks) {

	cout << "Odaberite pokemona za borbu: ";
	print_pokemon_names(poks);

	int c1, c2;
	cout << "\n----- Izbor: "; cin >> c1;
	cout << "\nIzaberite protivnika: ";
	print_pokemon_names(poks);
	cout << "\n----- Izbor: "; cin >> c2;

	poks[c1].fight(poks[c2]);
}

void write_in_same_order(vector<string>& lines) {
	ofstream dat("novi_pokemoni_popis.csv");
	if (!dat) throw exception("Greska kod pisanja u novu datoteku!");
	
	for (int i = 0; i < lines.size(); i++) {
		dat << lines[i] << endl;
	}

	dat.close();
}

void write_in_reversed_order(vector<string>& lines) {
	vector<string> lines_r(lines.rbegin(), lines.rend());
	ofstream dat("novi_pokemoni_popis.csv");
	if (!dat) throw exception("Greska kod pisanja u novu datoteku!");

	for (int i = 0; i < lines.size(); i++) {
		dat << lines_r[i] << endl;
	}

	dat.close();
}

void create_file() {
	int choice;
	cout << "Kopiraj datoteku u \n1) Istom redosljedu\nili\n2) Obrnutom redosljedu\nIzbor: ";
	cin >> choice;

	ifstream read("pokemoni_popis.csv");
	if (!read) {
		throw exception("Greska kod citanja datoteke!");
	}

	string line;
	vector<string> lines;
	while (getline(read, line)) {
		lines.push_back(line);
	}
	read.close();

	switch (choice) {
	case 1:
		try {
			write_in_same_order(lines);
		}
		catch (exception& er) {
			cout << er.what() << endl;
		}
		break;

	case 2:
		write_in_reversed_order(lines);
		break;

	default:
		throw exception("Invalid choice!");
	}
}

void multiply_hp(Pokemon& p) {
	int hp = p.get_hp();
	hp *= 1.5;
	p.set_hp(hp);
}

void print_vector(vector<Pokemon> p) {
	for (int i = 0; i < p.size(); i++) {
		cout << p[i].get_name() << endl;
	}
}

void poison_pokemon_processing(vector<Pokemon>& p) {
	vector<Pokemon> p_pokemons;

	cout << "Procesing pokemons..." << endl;
	for (int i = 0; i < p.size(); i++) {
		if (p[i].get_type1() == "Poison") {
			p_pokemons.push_back(p[i]);
		}
	}

	for (int i = 0; i < p_pokemons.size(); i++) {
		if (p_pokemons[i].get_total() < 300) {
			p_pokemons.erase(p_pokemons.begin() + i);
		}
	}
	
	for_each(p_pokemons.begin(), p_pokemons.end(), multiply_hp);
	vector<Pokemon>reversed(p_pokemons.rbegin(), p_pokemons.rend());
	p_pokemons = reversed;

	print_vector(p_pokemons);
}

void main_menu() {
	
	int choice;
	bool dalje;
	vector<Pokemon> pokemons;

	do {
		cout << "\n\t---------- 1) Unos putanje\n\t---------- 2) Unos podataka iz datoteke\n\t---------- 3) Borba pokemona" << 
				"\n\t---------- 4) Kopiranje datoteke\n\t---------- 5) Obrada otrovnih pokemona\n\t---------- Izbor: ";
		cin >> choice; cin.ignore();

		switch (choice)
		{
		case 1:
			try {
				enter_path();
			}
			catch (exception& err) {
				cout << err.what() << endl;
			}
			break;

		case 2:
			try {
				parse_file(pokemons);
			}
			catch (exception& err) {
				cout << err.what() << endl;
			}
			break;

		case 3:
			pokemon_fight(pokemons);
			break;

		case 4:
			try {
				create_file();
			}
			catch (exception& err) {
				cout << err.what() << endl;
			}
			break;

		case 5:
			poison_pokemon_processing(pokemons);
			break;

		default:
			cout << "Invalid choice!" << endl;
			break;
		}

		cout << "\nZelite li nastaviti? (1/da, 0/ne): ";
		cin >> dalje;
	} while (dalje);
}

int main() {

	cout << title() << endl;

	main_menu();

	return 0;
}