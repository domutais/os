#include <stdio.h>
#include "students.h"

int main() {
	add_st((Student){"Petrov", 2, {60, 81, 77}});
	add_st((Student){"Sydorchuk", 1, {97, 99, 92}});
	add_st((Student){"Losersky", 1, {40, 51, 60}});
	add_st((Student){"Mazepa", 3, {70, 85, 79}});
	add_st((Student){"ITshnikov", 4, {90, 47, 88}});

	add_st(input_st());

	print_losers();
	good_marks_percent();
	best_discipline();
	worst_group();

	return 0;
}
