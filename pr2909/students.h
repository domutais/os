#ifndef STUDENTS_H_INCLUDED
#define STUDENTS_H_INCLUDED

typedef struct student {
	char name[13];
	int group;
	struct {
		int web;
		int ukr;
		int proj;
	} marks;
} Student;

void add_st(Student);
void delete_st(int);
Student input_st();
void print_losers();
void good_marks_percent();
void best_discipline();
void worst_group();

#endif
