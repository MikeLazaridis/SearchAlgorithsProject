// Created by mlazg on 15-Dec-25.

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "node.h"

#define MAX_STACK 2000000
#define MAX_VALUE 2000000
#define TIMEOUT 1000

static Pointer stack[MAX_STACK];
static Pointer processed[MAX_STACK];
static bool visited_stack[MAX_VALUE] = {false};
static int top_stack = -1;
static int top_processed = -1;

void pushNode(Pointer node){
    if(top_stack >= MAX_STACK-1){
        printf("DFS stack full! Cannot push node %d\n", node->data);
        free(node);
        return;
    }
    if(node->data >= MAX_VALUE){
        printf("DFS node exceeds MAX_VALUE: %d\n", node->data);
        free(node);
        return;
    }
    if(!visited_stack[node->data]){
        stack[++top_stack] = node;
        visited_stack[node->data] = true;
    } else {
        free(node);
    }
}

Pointer popNode(){
    if(top_stack < 0) return NULL;
    return stack[top_stack--];
}

bool isStackEmpty(){
    return top_stack == -1;
}

void pushProcessed(Pointer node){
    if(top_processed >= MAX_STACK-1){
        printf("Processed stack full! Node %d cannot be saved\n", node->data);
        return;
    }
    processed[++top_processed] = node;
}

Pointer DFS(int start, int end, clock_t start_time){
    Pointer endNode = NULL;
    printf("DFS started: %d -> %d\n", start, end);
    if(start >= MAX_VALUE || end >= MAX_VALUE){
        printf("Start or end exceeds MAX_VALUE\n");
        return NULL;
    }
    Pointer root = newNode(start, 0, 0, "start", NULL);
    if(!root){
        printf("Failed to allocate root node\n");
        return NULL;
    }
    pushNode(root);
    while(!isStackEmpty()){
        double time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        if(time >= TIMEOUT){
            printf("DFS timeout\n");
            return NULL;
        }
        Pointer current = popNode();
        if(!current) continue;
        printf("DFS visiting node %d\n", current->data);
        pushProcessed(current);
        if(current->data == end) {
            endNode = current;
            break;
        }
        Children kids = expand(current);
        for(int i = kids.count-1; i >= 0; i--){
            Pointer child = kids.children[i];
            if(!child) continue;
            if(child->data >= MAX_VALUE){
                free(child);
                continue;
            }
            if(!visited_stack[child->data]){
                pushNode(child);
            } else {
                free(child);
            }
        }
    }
    return endNode;
}

void freeDFS(){
    for(int i = 0; i <= top_stack; i++){
        if(stack[i]) free(stack[i]);
    }
    for(int i = 0; i <= top_processed; i++){
        if(processed[i]) free(processed[i]);
    }
    top_stack = top_processed = -1;
    for(int i = 0; i < MAX_VALUE; i++) visited_stack[i] = false;
}
