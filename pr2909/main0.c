#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 8

typedef struct point {
	double x;
	double y;

	double mass;
} Point;

int main(void) {
	Point array[N];
	Point deleted_point = {.x=-1, .y=-1, .mass=0.0};
	int length = N;
	srand(time(NULL));

	for (int i = 0; i < N; i++) {
		array[i] = (Point){.x=(double)(rand() % (N*N*100))/100, .y=(double)(rand() % (N*N*100))/100, .mass=((double)(rand() % 1000) / 100)};
	}
	
	while (length > 0) {
		int smallest_id = -1;
		double smallest_mass = 1e308;
		printf("%d points left.\n", length);
		for (int i = 0; i < length; i++) {
			printf(" Point (%.2f, %.2f), %.2f kg\n", array[i].x, array[i].y, array[i].mass);
			if (array[i].mass < smallest_mass) {
				smallest_id = i;
				smallest_mass = array[i].mass;
			}
		}
		
		
		printf("Point (%.2f, %.2f) (%.2f kg) will be deleted.\n", array[smallest_id].x, array[smallest_id].y, array[smallest_id].mass);

		int closest_id = -1;
		double closest_dist = 1e308;
		double dist;
		for (int i = 0; i < length; i++) {
			if (i == smallest_id) continue;

			dist = sqrt(powf(array[i].x - array[smallest_id].x, 2) + powf(array[i].y - array[smallest_id].y, 2));
			if (dist < closest_dist) {
				closest_dist = dist;
				closest_id = i;
			}
		}
		printf("Its mass will be transferred to (%.2f, %.2f): before %.2f kg, after %.2f kg.\n", array[closest_id].x, array[closest_id].y, array[closest_id].mass, array[closest_id].mass + array[smallest_id].mass);

		array[closest_id].mass += array[smallest_id].mass;
		array[smallest_id] = array[length-1];
		array[length-1] = deleted_point;
		length--;
		printf("\n");
	}
	return 0;
}


