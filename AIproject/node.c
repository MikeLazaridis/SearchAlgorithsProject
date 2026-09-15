// Created by mlazg on 10-Dec-25.

#include <stdlib.h>
#include <string.h>
#include "node.h"
#include <math.h>

#define MAX_VALUE 2000000

Pointer newNode(int data, int g, int h, const char* action, Pointer parent){
  Pointer node = (Pointer)malloc(sizeof(Node));
  if(node == NULL){
    return NULL;
  } else {
    node->data = data;
    node->g_cost = g;
    node->h_cost = h;
    node->f_cost = g+h;
    strncpy(node->action, action, 19);
    node->action[19] = '\0';
    node->parent = parent;
  }
  return node;
}

Children kidsInitialise(){
  Children kids;
  kids.count = 0;
  return kids;
}

Children expand(Pointer current){
  Children kids = kidsInitialise();
  int temp = current->data;
  //increase
  if(temp < MAX_VALUE){
    Pointer new_node = newNode(temp+1, current->g_cost+2, 0, "increase", current);
    if(new_node != NULL){
      kids.children[kids.count] = new_node;
      kids.count++;
    }
  }
  //decrease
  if(temp > 0){
    Pointer new_node =  newNode(temp-1, current->g_cost+2, 0, "decrease", current);
    if(new_node !=NULL){
      kids.children[kids.count] = new_node;
      kids.count++;
    }
  }
  //double
  if(current->data>0 && 2*current->data<=MAX_VALUE){
    Pointer new_node = newNode(temp*2, current->g_cost + ((temp+1)/2)+1, 0, "double", current);
    if(new_node != NULL){
      kids.children[kids.count] = new_node;
      kids.count++;
    }
  }
  //half
  if(temp>0){
    Pointer new_node = newNode(temp/2, current->g_cost + ((temp+3)/4)+1, 0, "half", current);
    if(new_node != NULL){
      kids.children[kids.count] = new_node;
      kids.count++;
    }

  }
  //square
  if(temp>0 && (long long)(temp)*temp <= MAX_VALUE){
    Pointer new_node = newNode(temp*temp, current->g_cost + (((temp*temp - temp)+3)/4)+1, 0, "square", current);
    if(new_node != NULL){
      kids.children[kids.count] = new_node;
      kids.count++;
    }
  }
  //root
  int x = (int)sqrt(temp);
  if(x*x == temp && temp>1){
    Pointer new_node = newNode(x, current->g_cost + (((temp-x)+3)/4)+1, 0, "root", current);
    if(new_node != NULL){
      kids.children[kids.count] = new_node;
      kids.count++;
    }
  }

  return kids;
}