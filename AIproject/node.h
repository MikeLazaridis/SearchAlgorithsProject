// Created by mlazg on 10-Dec-25.

#ifndef NODE_H
#define NODE_H

#define MAX_CHILDREN 6

typedef struct Node *Pointer;
typedef struct Node{
  int data;
  int g_cost, h_cost, f_cost;
  char action[20];
  Pointer parent;
}Node;

typedef struct Children{
  Pointer children[MAX_CHILDREN];
  int count;
}Children;

Pointer newNode(int data, int g, int h, const char* action, Pointer parent);
Children expand(Pointer current);

#endif //NODE_H
