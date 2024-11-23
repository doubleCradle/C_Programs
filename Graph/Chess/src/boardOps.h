#include <stdio.h>
#include <stdlib.h>
#include<SDL2/SDL.h>
#define BOARD_SIZE 8
#include"graph.h"



void printNeighbors(Node* node) {
    //printf("Neighbors of (%d, %d):\n", node->x, node->y);
    printf("\nNeighbors of (%c%d):\n", node->name, node->y+1);
    for (int i = 0; i < 8; i++) {
        if (node->neighbors[i] != NULL) {
           /* printf("  (%d, %d, %c)\n", node->neighbors[i]->x, node->neighbors[i]->y, node->neighbors[i]->name); */
	      printf("(%c%d)\n", node->neighbors[i]->name, (node->neighbors[i]->y+1));
        }
    }
}
