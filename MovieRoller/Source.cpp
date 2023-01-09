#include "FilmList.h"

int main() {
	FilmList list("List.md");
	while (true) {
		system("cls");
		list.PrintLists();
		list.PrintOptions();
		list.OptionInput();
	}
	return 0;
};
