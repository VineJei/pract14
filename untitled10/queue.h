#ifndef QUEUE_H
#define QUEUE_H

#include "student.h"

struct QueueNode {
    struct Student* student;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct Queue* create_queue();
void enqueue(struct Queue* queue, struct Student* student);
struct Student* dequeue(struct Queue* queue);
void print_queue(const struct Queue* queue);
void free_queue(struct Queue* queue);

#endif
