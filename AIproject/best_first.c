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
static bool visited[MAX_VALUE] = {false};
static int index=0;

int heuristic(int current, int target){
  return abs(current - target);
}

void addHeuristic(Pointer node, int target){
  node->h_cost = heuristic(node->data, target);
}

Children sorted(Children list, int target){
  Children sortedList;
  sortedList.count = list.count;
  int temp_index = 0;

  for(int i=0; i<list.count; i++){
    addHeuristic(list.children[i], target);
  }

  for (int i = 0; i < list.count - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < list.count; j++) {
      if (list.children[j]->h_cost < list.children[minIndex]->h_cost) {
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

void addToQueue_bf(Pointer node){
  if(visited[node->data] == false && index < MAX_QUEUE){
    Queue[index] = node;
    visited[node->data] = true;
    index++;
  } else {
    printf("Queue is full\n");
  }
}

Pointer popFromQueue_bf(){
  Pointer temp;
  if(index == 0){
    return NULL;
  }else{
    index--;
    temp = Queue[index];
    return temp;
  }
}

Pointer Best_First(int start, int end, clock_t start_time){
  printf("Best-First Search started: %d -> %d\n", start, end);
  if(start >= MAX_VALUE || end >= MAX_VALUE){
    printf("Start or end exceeds MAX_VALUE\n");
    return NULL;
  }
  Pointer root = newNode(start, 0, 0, "start", NULL);
  if(!root){
    printf("Failed to allocate root node\n");
    return NULL;
  }
  addToQueue_bf(root);
  visited[root->data] = true;
  while(index > 0){
    double time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    if(time >= TIMEOUT){
      printf("Best-First Search timeout\n");
      return NULL;
    }
    Pointer current = popFromQueue_bf();
    if(current != NULL){
      printf("Best-First visiting node %d\n", current->data);
      if(current->data == end) {return current;}
      else{
        Children kids = expand(current);
        Children sorted_kids = sorted(kids, end);
        for(int i = 0; i < kids.count; i++){
          Pointer child = sorted_kids.children[i];
           if(!child) continue;
           if(child->data >= MAX_VALUE){
             free(child);
             continue;
           }
           if(!visited[child->data]){
             addToQueue_bf(child);
           } else {
             free(child);
           }
        }
      }
    }
  }
  return NULL;
}

void freeBestFirst(){
    for(int i = 0; i < index; i++){
        if(Queue[i])
          free(Queue[i]);
    }
    index = 0;
    for(int i = 0; i < MAX_VALUE; i++)
      visited[i] = false;
}