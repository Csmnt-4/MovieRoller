#pragma once
#include <vector>

#include "Category.h"

class FilmList {
public:
	FilmList(std::string filename);

	std::string file;
	std::vector<Category> categories;

	int AddCategory(std::string categoryName);
	int AddFilm(std::string category, std::string film);
	int OptionInput();
	int SaveToFile();

	void PrintLists();
	void PrintOptions();
	void RollingDice();

};
