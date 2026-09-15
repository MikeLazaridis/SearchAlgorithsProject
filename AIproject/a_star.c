// Created by mlazg on 23-Dec-25.

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "node.h"
#include "best_first.h"

#define MAX_QUEUE 2000000
#define MAX_VALUE 2000000
#define TIMEOUT 1000

static Pointer Queue[MAX_QUEUE] = {NULL};
static int index=0;

int heuristic_a_star(int current, int target){
  return abs(current - target);
}

void addHeuristic_a_star(Pointer node, int target){
  node->h_cost = heuristic_a_star(node->data, target);
  node->f_cost = node->g_cost + node->h_cost;
}

Children sorted_a_star(Children list, int target){
  Children sortedList;
  sortedList.count = list.count;
  int temp_index = 0;

  for(int i=0; i<list.count; i++){
    addHeuristic_a_star(list.children[i], target);
  }

  for (int i = 0; i < list.count - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < list.count; j++) {
      if (list.children[j]->f_cost < list.children[minIndex]->f_cost) {
        minIndex = j;
      }
    }
    if (minIndex != i) {
      Pointer temp = list.children[i];
      list.children[i] = list.children[minIndex];
      list.children[minIndex] = temp;
    }
  }

  for(int k=list.count-1; k>-1; k--){
    sortedList.children[temp_index] = list.children[k];
    temp_index++;
  }
  return sortedList;
}

void addToQueue_a_star(Pointer node){
  if(index < MAX_QUEUE){
    Queue[index] = node;
    index++;
  } else {
    printf("Queue is full\n");
  }
}

Pointer popFromQueue_a_star(){
  Pointer temp;
  if(index == 0){
    return NULL;
  }else{
    index--;
    temp = Queue[index];
    return temp;
  }
}

Pointer A_Star(int start, int end, clock_t start_time){
  printf("A* Search started: %d -> %d\n", start, end);
  if(start >= MAX_VALUE || end >= MAX_VALUE){
    printf("Start or end exceeds MAX_VALUE\n");
    return NULL;
  }
  Pointer root = newNode(start, 0, 0, "start", NULL);
  if(!root){
    printf("Failed to allocate root node\n");
    return NULL;
  }
  addToQueue_a_star(root);
  while(index > 0){
    double time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    if(time >= TIMEOUT){
      printf("Α* Search timeout\n");
      return NULL;
    }
    Pointer current = popFromQueue_a_star();
    if(current != NULL){
      printf("A* visiting node %d\n", current->data);
      if(current->data == end) {return current;}
      else{
        Children kids = expand(current);
        Children sorted_kids = sorted_a_star(kids, end);
        for(int i = 0; i < kids.count; i++){
          Pointer child = sorted_kids.children[i];
           if(!child) continue;
           if(child->data >= MAX_VALUE){
             free(child);
             continue;
           }
          addToQueue_a_star(child);
        }
      }
    }
  }
  return NULL;
}

void freeA_Star(){
    for(int i = 0; i < index; i++){
        if(Queue[i])
          free(Queue[i]);
    }
    index = 0;
}