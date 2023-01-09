#pragma once

#include <string>
#include <list>
#include <vector>

class Category {
public:
	Category(std::string);

	std::string categoryName;
	std::vector<std::string> films;

	void PrintCategory();
	std::string PrintFilm(int line);
	std::string PrintFilm(int line, bool fullName);
};

