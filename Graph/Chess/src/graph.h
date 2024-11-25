#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#define BOARD_SIZE 8

//typedef struct Piece;

typedef struct Piece {
    char type;
    int color;
    int empty;
    char* path;
    SDL_Texture* texture;
} Piece;

typedef struct Node {
    char name;
    int x; 
    int y; 
    SDL_Rect rect;
    //Piece* piece;
    struct Node* neighbors[8]; 
} Node;

typedef struct NP {
    Node node;
    Piece piece;
} NP;



void graph_init(NP board[BOARD_SIZE][BOARD_SIZE], SDL_Renderer* renderer) {
 char alphabet[] = {'a','b','c','d','e','f','g','h'};
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            board[y][x].node.x = x;
            board[y][x].node.y = y;

	    board[y][x].node.rect.x = x*50;
	    board[y][x].node.rect.y = y*50;
	    board[y][x].node.rect.w = 50;
	    board[y][x].node.rect.h = 50;
	    board[y][x].node.name = alphabet[x];
        board[y][x].piece.empty = 1;

	    board[1][x].piece.empty = 0;
	    board[1][x].piece.color = 0;
	    board[1][x].piece.path = "bishop.png";

        if(!board[y][x].piece.empty){

            SDL_Surface* imageSurface = IMG_Load(board[y][x].piece.path);
            if (imageSurface == NULL) {
                fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());
                continue; // Skip if the image fails to load
            }
            board[y][x].piece.texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
            SDL_FreeSurface(imageSurface);
        }
            // Initialize neighbors
            int neighborCount = 0;

            // Up
            if (y > 0) {
                board[y][x].node.neighbors[neighborCount++] = &board[y - 1][x].node; // North
            }
            // Down
            if (y < BOARD_SIZE - 1) {
                board[y][x].node.neighbors[neighborCount++] = &board[y + 1][x].node; // South
            }
            // Left
            if (x > 0) {
                board[y][x].node.neighbors[neighborCount++] = &board[y][x - 1].node; // West
            }
            // Right
            if (x < BOARD_SIZE - 1) {
                board[y][x].node.neighbors[neighborCount++] = &board[y][x + 1].node; // East
            }
            // Top-Left
            if (x > 0 && y > 0) {
                board[y][x].node.neighbors[neighborCount++] = &board[y - 1][x - 1].node; // Northwest
            }
            // Top-Right
            if (x < BOARD_SIZE - 1 && y > 0) {
                board[y][x].node.neighbors[neighborCount++] = &board[y - 1][x + 1].node; // Northeast
            }
            // Bottom-Left
            if (x > 0 && y < BOARD_SIZE - 1) {
                board[y][x].node.neighbors[neighborCount++] = &board[y + 1][x - 1].node; // Southwest
            }
            // Bottom-Right
            if (x < BOARD_SIZE - 1 && y < BOARD_SIZE - 1) {
                board[y][x].node.neighbors[neighborCount++] = &board[y + 1][x + 1].node; // Southeast
            }

            // Set remaining neighbors to NULL
            for (int i = neighborCount; i < 8; i++) {
                board[y][x].node.neighbors[i] = NULL;
            }
        }
    }
}


void printNeighbors(NP* np) {
    //printf("Neighbors of (%d, %d):\n", node->x, node->y);
    printf("\nNeighbors of (%c%d):\n", np->node.name, np->node.y+1);
    for (int i = 0; i < 8; i++) {
        if (np->node.neighbors[i] != NULL) {
           /* printf("  (%d, %d, %c)\n", node->neighbors[i]->x, node->neighbors[i]->y, node->neighbors[i]->name); */
	      printf("(%c%d)\n", np->node.neighbors[i]->name, (np->node.neighbors[i]->y+1));
        }
    }
}
