#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
	printf("Enter a list of grades below where each grade is separated by a newline character.\n");
	printf("After the last grade is entered, enter a negative value to end the list.\n");

	int allocs = 0;
	int frees = 0;
	int bytes = 0;

	double * container = NULL;
	int space = 0;
	int offset = 0;

	// First value
	double grade = 0;
	double average = 0;
	scanf("%lf", &grade);
	if (grade >= 0) {
		average = grade;
		container = malloc(sizeof(double) * 5);
		allocs++;
		bytes += 40;
		if (container == NULL) {
			printf("Could not allocate memory!\n");
			exit(-1);
		}
		space = 40;
		printf("Allocated 40 bytes to the heap at %p\n", (void *)container);
		*container = grade;
		printf("Stored %lf in the heap at %p\n", grade, (void *)container);
		space -= 8;
		offset = 1;
	}

	// Following values
	int exp = 1; // - # of expansions
	while (grade >= 0) {
		scanf("%lf", &grade);
		if (grade >= 0) {
			average += grade;
			*(container + offset) = grade;
			space -= 8;
			printf("Stored %lf in the heap at %p.\n", grade, (void *)(container + offset++));
		}
		if (space == 0) {
			printf("Stored %d grades (%d bytes) to the heap at %p.\n", exp * 5,  8 * 5 * exp, (void *)container);
			printf("Heap at %p is full.\n", (void *)container);
			double * temp = container;
			container = malloc(sizeof(double) * 5 * ++exp);
			allocs++;
			bytes += 8 * 5 * exp;
			if (container == NULL) {
				printf("Could not allocate memory!\n");
				exit(-1);
			}
			space = 40;
			printf("Allocated %d bytes to the heap at %p\n", 8 * 5 * exp, (void *)container);
			for (int i = 0; i < 5 * (exp - 1); i++) {
				*(container + i) = *(temp + i);
			}
			printf("Copied %d grades from %p to %p.\n", 5 * (exp - 1), (void *)temp, (void *)container);
			free(temp);
			frees++;
			printf("Freed %d bytes from the heap at %p.\n", 8 * 5 * (exp - 1), (void *)temp);
		}
	}
	if (space != 0) {
		average = average / offset;
	}
	printf("The average of %d grades is %lf.\n", offset, average);
	for (int i = 0; i < offset; i++) {
		printf("%d. The grade of %lf is %s the average.\n", i + 1, *(container + i), (*(container + i) >= average) ? ">=" : "<");
	}
	if (container != NULL) {
		free(container);
		frees++;
	}
	if (space != 0) {
		printf("Freed %d bytes from the heap at %p.\n", 8 * 5 * exp, (void *)container);
	}
	printf("total heap usage: %d allocs, %d frees, %d bytes allocated\n", allocs, frees, bytes);
	return 0;
}
