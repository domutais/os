#include <stdio.h>
#include <stdlib.h>

#define WEB_WEIGHT 0.4
#define UKR_WEIGHT 0.2
#define PROJ_WEIGHT 0.4

typedef struct student {
	char name[13];
	int group;
	struct {
		int web;
		int ukr;
		int proj;
	} marks;
} Student;	

Student st_null = (Student){"UNDEFINED", -1, {0, 0, 0}};

Student studs[30];
int length = 0;

void add_st(Student st) {
	if (length >= 30) return;

	studs[length] = st;
	length++;
}

void delete_st(int id) {
	if (id < 0 && id >= length) return;

	studs[id] = studs[length-1];
	studs[length-1] = st_null;
	length--;
}

Student input_st() {
	Student ret;
	printf("Adding new student.\nSurname: ");
	scanf("%13s", ret.name);
	printf("Group: ");
	scanf("%d", &(ret.group));
	printf("Marks:\n\t- web dev.: ");
	scanf("%d", &(ret.marks.web));
	printf("\t- Ukrainian: ");
	scanf("%d", &(ret.marks.ukr));
	printf("\t- inf. sys. proj.: ");
	scanf("%d", &(ret.marks.proj));

	return ret;
}

void print_losers() {
	int amount = 0;
	printf("Losers:\n");
	for (int i = 0; i < length; i++) {
		if (studs[i].marks.web < 50 || studs[i].marks.ukr < 50 || studs[i].marks.proj < 50) {
			printf(" - %s\n", studs[i].name);
			amount++;
		}
	}

	if (amount == 0) printf("Currently no losers.\n");
}

void good_marks_percent() {
	int good = 0;
	for (int i = 0; i < length; i++) {
		if (studs[i].marks.web >= 70 || studs[i].marks.ukr >= 70 || studs[i].marks.proj >= 70) good++;
	}
	printf("Good & perfect students: %d out of %d (%.1f%%)\n", good, length, (double)good*100.0/length);
}

void best_discipline() {
	double web, ukr, proj;

	for (int i = 0; i < length; i++) {
		web = (web * i + (double)studs[i].marks.web) / (i+1);
		ukr = (ukr * i + (double)studs[i].marks.ukr) / (i+1);
		web = (web * i + (double)studs[i].marks.web) / (i+1);
	}

	printf("The best rated discipline is ");
	if (web >= ukr && web >= proj)  printf("Web development (%.2f)\n", web);
	else if (ukr >= web && ukr >= proj) printf("Ukrainian (%.2f)\n", ukr);
	else printf("Projecting (%.2f)\n", proj);
}

void worst_group() {
	double groups[4+1] = {0.0, 0.0, 0.0, 0.0, 0.0};
	int gr_studs[4] = {0, 0, 0, 0};

	int worst_id = -1;
	double worst_score = 1e308;

	for (int i = 0; i < length; i++) {
		if (studs[i].group < 1 || studs[i].group > 4) continue;
		
		int j = ++gr_studs[studs[i].group];
		groups[studs[i].group] = (groups[studs[i].group] * j + (studs[i].marks.web * WEB_WEIGHT + studs[i].marks.ukr * UKR_WEIGHT + studs[i].marks.proj * PROJ_WEIGHT)/3) / (j+1);

		if (groups[studs[i].group] < worst_score) {
			worst_score = groups[studs[i].group];
			worst_id = studs[i].group;
		}

	}
	printf("Worst group: #%d (avg. score - %.2f).\n", worst_id, worst_score);
}

