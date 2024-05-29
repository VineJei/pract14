#include "student.h"
#include "queue.h"

#define UNIQUE_CONSTANT 42

int main() {
    system("chcp 65001");

    struct Queue* student_queue = create_queue();

    // Load students from file
    load_students_from_file("students.txt", student_queue);

    // New students to add
    struct Student* new_students = NULL;
    new_students = add_student(new_students, create_student("Иванова", "Анна", "female", 20, "ИСП-208", 4, 5, 5));
    new_students = add_student(new_students, create_student("Петрова", "Мария", "female", 21, "ИСП-307", 5, 5, 4));
    new_students = add_student(new_students, create_student("Сидорова", "Елена", "female", 19, "СИС-107", 5, 5, 5));

    // Add new students and save to file
    add_students_to_queue_and_save("students.txt", student_queue, new_students);

    printf("Unique constant value: %d\n", UNIQUE_CONSTANT);
    printf("All students in queue:\n");
    print_queue(student_queue);

    printf("Students with top grades:\n");
    struct QueueNode* current_node = student_queue->front;
    while (current_node != NULL) {
        struct Student* student = current_node->student;
        if (strcmp(student->gender, "female") == 0 && student->physics_grade == 5 && student->chemistry_grade == 5) {
            print_student(student);
        }
        current_node = current_node->next;
    }

    // Free memory
    free_queue(student_queue);

    return 0;
}
