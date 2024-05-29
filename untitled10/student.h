#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

struct Student {
    char surname[50];
    char name[50];
    char gender[10];
    int age;
    char group[10];
    int math_grade;
    int physics_grade;
    int chemistry_grade;
    struct Student* next;
};

struct Student* create_student(const char* surname, const char* name, const char* gender, int age, const char* group, int math_grade, int physics_grade, int chemistry_grade);
void print_student(const struct Student* student);
void print_students_with_top_grades(const struct Student* students);
void print_all_students(const struct Student* students);
struct Student* add_student(struct Student* students, struct Student* new_student);
void load_students_from_file(const char* filename, struct Queue* queue);
void save_students_to_file(const char* filename, struct Student* students);
void add_students_to_queue_and_save(const char* filename, struct Queue* queue, struct Student* new_students);

#endif
