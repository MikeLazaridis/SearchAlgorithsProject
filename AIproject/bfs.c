// Created by mlazg on 15-Dec-25.

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "node.h"

#define MAX_QUEUE 2000000
#define MAX_VALUE 2000000
#define TIMEOUT 1000

static Pointer Queue[MAX_QUEUE] = {NULL};
static bool visited_queue[MAX_VALUE] = {false};
static int front = 0, rear = 0;

void addToQueue(Pointer node){
    if(rear >= MAX_QUEUE){
        printf("Queue full! Cannot add node %d\n", node->data);
        free(node);
        return;
    }
    Queue[rear++] = node;
}

Pointer removeFromQueue(){
    if(front >= rear) {return NULL;}
    return Queue[front++];
}

bool isQueueEmpty(){
    return front == rear;
}

Pointer BFS(int start, int end, clock_t start_time){
    printf("BFS started: %d -> %d\n", start, end);
    if(start >= MAX_VALUE || end >= MAX_VALUE){
        printf("Start or end exceeds MAX_VALUE\n");
        return NULL;
    }
    Pointer root = newNode(start, 0, 0, "start", NULL);
    if(!root){
        printf("Failed to allocate root node\n");
        return NULL;
    }
    addToQueue(root);
    visited_queue[start] = true;
    while(!isQueueEmpty()){
        double time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        if(time >= TIMEOUT){
            printf("BFS timeout\n");
            return NULL;
        }
        Pointer current = removeFromQueue();
        if(!current) continue;
        printf("BFS visiting node %d\n", current->data);
        if(current->data == end) return current;
        Children kids = expand(current);
        for(int i = 0; i < kids.count; i++){
            Pointer child = kids.children[i];
            if(!child) continue;
            if(child->data >= MAX_VALUE){
                free(child);
                continue;
            }
            if(!visited_queue[child->data]){
                addToQueue(child);
                visited_queue[child->data] = true;
            } else {
                free(child);
            }
        }
    }
    return NULL;
}

void freeBFS(){
    for(int i = front; i < rear; i++){
        if(Queue[i]) free(Queue[i]);
    }
    front = rear = 0;
    for(int i = 0; i < MAX_VALUE; i++) visited_queue[i] = false;
}
