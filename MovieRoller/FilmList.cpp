#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "FilmList.h"
#include "DiceRoller.h"

using namespace std::literals::chrono_literals;

FilmList::FilmList(std::string filename) {
	file = filename;
	std::ifstream stream(filename);
	std::string buffer;
	std::string film;

	if (!stream.is_open())
	{
		std::cout << "Can't open list: " << filename << std::endl;
		return;
	}

	while (std::getline(stream, buffer)) {
		if (buffer.substr(0, 1) == "#") {
			AddCategory(buffer.substr(5, buffer.length()));
			std::getline(stream, film);
			while (film.substr(0, 1) == "-") {
				AddFilm(buffer.substr(5, buffer.length()), film.substr(2, buffer.length()));
				std::getline(stream, film);
			}
		}
	}
}

int FilmList::SaveToFile() {
	std::ofstream stream;
	stream.open(file, std::ios::trunc);

	if (!stream.is_open()) {
		std::cout << "Can't open list: " << file << std::endl;
		return -1;
	}

	for (int i = 0; i < categories.size(); i++) {
		stream << "#### " + categories[i].categoryName;
		if (categories[i].categoryName.size() >= 1) {
			stream << "\n";
			for (int j = 0; j < categories[i].films.size(); j++)
				stream << "- " + categories[i].films[j] + "\n";

		}
		stream << "\n";
	}
	return 0;
}

void FilmList::PrintLists() {
	std::string emptyLine = "             ";
		int maxSize = 0;

		std::cout << "\n\n\t";

		for (int i = 0; i < categories.size(); i++) {
			std::cout << "################";
		}
	std::cout << "#\n\t";

	for (int i = 0; i < categories.size(); i++) {
		if (categories[i].categoryName.size() >= 13) {
			std::cout << "# " << categories[i].categoryName.substr(0, 11) + ".. ";
		}
		else {
			std::cout << "# " << categories[i].categoryName << emptyLine.substr(categories[i].categoryName.length() - 1);
		}
		//std::cout << categories[i].films.size();
		if (maxSize < categories[i].films.size())
			maxSize = categories[i].films.size();
	}
	std::cout << "#\n\t";


	for (int i = 0; i < categories.size(); i++) {
		std::cout << "################";
	}
	std::cout << "#\n\t";

	for (int i = 0; i < maxSize; i++) {
		for (int j = 0; j < categories.size(); j++) {
			std::cout << "# " << categories[j].PrintFilm(i) << " ";
		}
		std::cout << "#\n\t";
	}

	for (int i = 0; i < categories.size(); i++) {
		std::cout << "################";
	}

	std::cout << "#\n\n";
	//categories[i].PrintCategory();
}

void FilmList::PrintOptions() {

	std::cout << "\n\tWould you like to:\n" << std::endl;
	std::cout << "\t1) Add a category" << std::endl;
	std::cout << "\t2) Add a film" << std::endl;
	std::cout << "\t3) Roll a film" << std::endl;
	std::cout << "\t4) Save list" << std::endl;
}

int FilmList::AddCategory(std::string categoryName)
{
	int size = categories.size();
	Category category(categoryName);
	categories.push_back(category);
	if (size < categories.size()) //TODO: Any other way to detect a succesfull change?
		return 0;
	return -1;
}

int FilmList::AddFilm(std::string category, std::string film)
{
	int tempS = 0;
	int tempS2 = tempS;

	for (int i = 0; i < categories.size(); i++)
		if (categories[i].categoryName == category) {
			std::vector<std::string> temp = categories[i].films;
			tempS = temp.size();
			temp.push_back(film);
			categories[i].films = temp;
			tempS2 = categories[i].films.size();
			break;
		}

	if (tempS < tempS2)
		return 0;
	else for (int i = 0; i < categories.size(); i++)
		if (categories[i].categoryName.substr(0, 5) == category.substr(0, 5)) {
			std::vector<std::string> temp = categories[i].films;
			tempS = temp.size();
			temp.push_back(film);
			categories[i].films = temp;
			tempS2 = categories[i].films.size();
			break;
		}

	if (tempS < tempS2)
		return 0;
	else for (int i = 0; i < categories.size(); i++)
		if (categories[i].categoryName.substr(0, 4) == category.substr(0, 4)) {
			std::vector<std::string> temp = categories[i].films;
			tempS = temp.size();
			temp.push_back(film);
			categories[i].films = temp;
			tempS2 = categories[i].films.size();
			break;
		}

	if (tempS < tempS2)
		return 0;
	else for (int i = 0; i < categories.size(); i++)
		if (categories[i].categoryName.substr(0, 3) == category.substr(0, 3)) {
			std::vector<std::string> temp = categories[i].films;
			tempS = temp.size();
			temp.push_back(film);
			categories[i].films = temp;
			tempS2 = categories[i].films.size();
			break;
		}

	if (tempS < tempS2)
		return 0;
	return -1;
}

int FilmList::OptionInput() {
	int choice;
	std::string buffer;
	std::string buffer2;

	do {
		std::cout << "\n\t";

		std::cin >> choice;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		system("cls");
		PrintLists();

		switch (choice) {
		case 1: {
			std::cout << "\n\tPlease, enter a category name:\n\n\t";

			std::getline(std::cin, buffer);		//TODO: Shouldn't be like this.
			std::getline(std::cin, buffer);
			if (AddCategory(buffer) != 0)
				std::cout << "\tSomething went wrong! Please try again\n\t";

		}
			  break;
		case 2: {

			std::cout << "\n\tPlease, enter the category:\n\n\t";
			std::getline(std::cin, buffer);		//TODO: Shouldn't be like this.
			std::getline(std::cin, buffer);
			std::cout << "\n\tPlease, enter the film:\n\n\t";
			std::getline(std::cin, buffer2);

			if (AddFilm(buffer, buffer2) != 0)
				std::cout << "\tSomething went wrong! Please try again\n\t";
		}
			  break;
		case 3: {
			RollingDice();
		}
			  break;
		case 4: {
			SaveToFile();
		}
			  break;
		default: {
			std::cout << "\tThat was an invalid choice! Please try again\n\t";
			PrintOptions();
		}
		}
	} while ((choice < 1) || (choice > 4));
	std::this_thread::sleep_for(1s);
	return 0;
}

void FilmList::RollingDice() {
	DiceRoller die;
	int j = 1;

	for (int i = 0; i < 20; i++) {
		std::this_thread::sleep_for(100ms);
		system("cls");
		PrintLists();

		die.PrintDiceN6(j);

		j++;
		if (j == 7)
			j = 1;

	}

	std::this_thread::sleep_for(100ms);
	system("cls");
	PrintLists();
	die.PrintDiceN6(1);

	std::this_thread::sleep_for(100ms);
	system("cls");
	PrintLists();
	die.PrintDiceN6(3);

	std::this_thread::sleep_for(100ms);
	system("cls");
	PrintLists();
	die.PrintDiceN6(2);

	std::this_thread::sleep_for(200ms);
	system("cls");
	PrintLists();
	die.PrintDiceN6(die.Roll1DN(6));

	std::this_thread::sleep_for(300ms);
	system("cls");
	PrintLists();
	die.PrintDiceN6(3);

	std::this_thread::sleep_for(500ms);
	system("cls");
	PrintLists();
	die.PrintDiceN6(die.Roll1DN(6));

	std::this_thread::sleep_for(700ms);
	system("cls");
	PrintLists();
	die.PrintDiceN6(5);

	std::this_thread::sleep_for(900ms);
	system("cls");
	PrintLists();
	die.PrintDiceN6(die.Roll1DN(6));

	std::this_thread::sleep_for(1300ms);
	system("cls");
	PrintLists();
	die.PrintDiceN6(die.Roll1DN(6));

	std::this_thread::sleep_for(3s);

	std::string film = "";
	do {
		int roll1 = die.Roll1DN(categories.size()) - 1;
		int roll2 = die.Roll1DN(categories[roll1].films.size()) - 1;
		film = categories[roll1].PrintFilm(roll2, true);

	} while (film == "" || film == "             ");

	std::cout << "\n\t" << film << "\n\t";
	system("pause");


}