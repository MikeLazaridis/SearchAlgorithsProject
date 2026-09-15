#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "node.h"
#include "bfs.h"
#include "dfs.h"
#include "best_first.h"
#include "a_star.h"

#define MAX_PATH 1000

void solutionExport(Pointer end, const char* file_name, const double time) {
    FILE* file = fopen(file_name, "a+");
    if(!file){
        printf("Could not open file %s\n", file_name);
        return;
    }

    fprintf(file, "\n==============================\n");
    fflush(file);

    Pointer path[MAX_PATH];
    int i = 0;
    Pointer current = end;
    while(current != NULL && i < MAX_PATH){
        path[i++] = current;
        current = current->parent;
    }

    fprintf(file, "%d %d\n", i-1, end->g_cost);
    for(int j = i-1; j >= 0; j--){
        if(path[j]->parent == NULL)
            fprintf(file, "%s %d 0\n", path[j]->action, path[j]->data);
        else
            fprintf(file, "%s %d %d\n", path[j]->action, path[j]->data,
                    path[j]->g_cost - path[j]->parent->g_cost);
    }
    fprintf(file, "### Execution time: %.3f seconds.\n", time);
    fclose(file);
    printf("Solution exported to %s\n", file_name);
}

int main(int argc, char **argv){
    printf("Program started\n");

    if(argc != 5){
        printf("Usage: AIproject.exe breadth/depth/best_first/a_star start end solutions.txt\n");
        return 1;
    }

    char* method = argv[1];
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);
    char* filename = argv[4];

    printf("Method: %s, Start: %d, End: %d, File: %s\n", method, start, end, filename);

    clock_t begin = clock();
    Pointer result = NULL;

    if(strcmp(method, "breadth") == 0){
        result = BFS(start, end, begin);
    } else if(strcmp(method, "depth") == 0){
        result = DFS(start, end, begin);
    } else if (strcmp(method, "best") == 0){
        result = Best_First(start, end, begin);
    } else if (strcmp(method, "astar") == 0){
        result = A_Star(start, end, begin);
    } else {
        printf("Method not recognized\n");
        return 1;
    }

    clock_t finish = clock();
    double execution_time = (double)(finish - begin) / CLOCKS_PER_SEC;

    if(result == NULL){
        printf("No solution found for %d -> %d\n", start, end);
    } else {
        solutionExport(result, filename, execution_time);
    }

    printf("Program finished\n");
    freeBFS();
    freeDFS();
    freeBestFirst();
    freeA_Star();

    return 0;
}