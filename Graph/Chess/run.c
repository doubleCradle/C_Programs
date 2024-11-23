
#include<SDL2/SDL.h>
#include<stdio.h>
#include"src/boardOps.h"
#include"src/graph.h"

void renderBoard(SDL_Renderer* renderer, Node board[BOARD_SIZE][BOARD_SIZE]) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            Node* node = &board[y][x];
            // Set the color based on the square's position
            if ((node->x + node->y) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255); // Light color
            } else {
                SDL_SetRenderDrawColor(renderer, 96, 59, 42, 255); // Dark color
            }
            // Render the square
            SDL_RenderFillRect(renderer, &node->rect);
        }
    }
}



int main(int argc, char* argv[]){

Node board[8][8];
initializeBoard(board);
//printNeighbors(&board[1][1]);
SDL_Init(SDL_INIT_VIDEO); // if this returns 0, all ok. Else some error posted by SDL_GetError().
SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN);

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
      return 1;
 }

int running = 1;
SDL_Event event;

while(running){
	while(SDL_PollEvent(&event) != 0){
		if(event.type == SDL_QUIT) {
			running = 0;
		}
	}

	
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        renderBoard(renderer, board);

	/*SDL_Rect rect = { 0, 0, 50, 50 };
        SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); */
	SDL_RenderPresent(renderer);
}

SDL_DestroyWindow(window);
SDL_Quit();

return 0;

}
