#include "Category.h"
#include <iostream>

Category::Category(std::string name) {
	categoryName = name;
}

void Category::PrintCategory() {	// TODO: Do I still need it?
	for (int i = 0; i < films.size(); i++)
		std::cout << films[i];
};

std::string Category::PrintFilm(int line) {
	std::string emptyLine = "             ";	// TODO: That's ugly, change it.
	if (line < films.size()) {
		if (films[line].size() > 13)
			return films[line].substr(0, 10) + "...";
		else
			return films[line] + emptyLine.substr(films[line].length());
	}
	return emptyLine;	//
}

std::string Category::PrintFilm(int line, bool fullName) {
	std::string emptyLine = "             ";
	if (fullName) {
		if (line < films.size())
			return films[line];
		return emptyLine;	//
	}
	if (line < films.size()) {
		if (films[line].size() > 13)
			return films[line].substr(0, 10) + "...";
		else
			return films[line] + emptyLine.substr(films[line].length());
	}
	return emptyLine;	//
}
