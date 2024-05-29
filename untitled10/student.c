#include "student.h"
#include "queue.h"

struct Student* create_student(const char* surname, const char* name, const char* gender, int age, const char* group, int math_grade, int physics_grade, int chemistry_grade) {
    struct Student* student = malloc(sizeof(struct Student));
    strcpy(student->surname, surname);
    strcpy(student->name, name);
    strcpy(student->gender, gender);
    student->age = age;
    strcpy(student->group, group);
    student->math_grade = math_grade;
    student->physics_grade = physics_grade;
    student->chemistry_grade = chemistry_grade;
    student->next = NULL;
    return student;
}

void print_student(const struct Student* student) {
    printf("Name: %s %s\n", student->surname, student->name);
    printf("Gender: %s\n", student->gender);
    printf("Age: %d\n", student->age);
    printf("Group: %s\n", student->group);
    printf("Math grade: %d\n", student->math_grade);
    printf("Physics grade: %d\n", student->physics_grade);
    printf("Chemistry grade: %d\n \n", student->chemistry_grade);
}

void print_students_with_top_grades(const struct Student* students) {
    while (students != NULL) {
        if (strcmp(students->gender, "female") == 0 && students->physics_grade == 5 && students->chemistry_grade == 5) {
            print_student(students);
        }
        students = students->next;
    }
}

void print_all_students(const struct Student* students) {
    while (students != NULL) {
        print_student(students);
        students = students->next;
    }
}

struct Student* add_student(struct Student* students, struct Student* new_student) {
    if (students == NULL) {
        students = new_student;
    } else {
        struct Student* current = students;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_student;
    }
    return students;
}

void load_students_from_file(const char* filename, struct Queue* queue) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file for reading");
        return;
    }

    char surname[50], name[50], gender[10], group[10];
    int age, math_grade, physics_grade, chemistry_grade;

    while (fscanf(file, "%s %s %s %d %s %d %d %d", surname, name, gender, &age, group, &math_grade, &physics_grade, &chemistry_grade) == 8) {
        struct Student* student = create_student(surname, name, gender, age, group, math_grade, physics_grade, chemistry_grade);
        enqueue(queue, student);
    }

    fclose(file);
}

void save_students_to_file(const char* filename, struct Student* students) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Could not open file for writing");
        return;
    }

    struct Student* current = students;
    while (current != NULL) {
        fprintf(file, "%s %s %s %d %s %d %d %d\n", current->surname, current->name, current->gender, current->age, current->group, current->math_grade, current->physics_grade, current->chemistry_grade);
        current = current->next;
    }

    fclose(file);
}

void add_students_to_queue_and_save(const char* filename, struct Queue* queue, struct Student* new_students) {
    struct Student* current_student = new_students;
    while (current_student != NULL) {
        enqueue(queue, current_student);
        current_student = current_student->next;
    }

    struct QueueNode* current_node = queue->front;
    struct Student* all_students = NULL;
    while (current_node != NULL) {
        struct Student* student = current_node->student;
        all_students = add_student(all_students, student);
        current_node = current_node->next;
    }
    save_students_to_file(filename, all_students);

    while (all_students != NULL) {
        struct Student* next = all_students->next;
        free(all_students);
        all_students = next;
    }
}
