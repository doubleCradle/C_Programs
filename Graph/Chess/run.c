
#include<SDL2/SDL.h>
#include<stdio.h>
#include"src/graph2.h"
#include<SDL2/SDL_image.h>

#define BOARD_SIZE 8

void renderBoard(SDL_Renderer* renderer, NP board[BOARD_SIZE][BOARD_SIZE]) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            NP* np = &board[y][x];
            // Set the color based on the square's position
            if ((np->node.x + np->node.y) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255); // Light color
            } else {
                SDL_SetRenderDrawColor(renderer, 96, 59, 42, 255); // Dark color
            }
            // Render the square
            SDL_RenderFillRect(renderer, &np->node.rect);

            // Render the piece if it's not empty
            if (!np->piece.empty && np->piece.texture != NULL) {
                SDL_RenderCopy(renderer, np->piece.texture, NULL, &np->node.rect);
            }
        }
    }
}



int main(int argc, char* argv[]){

NP board[BOARD_SIZE][BOARD_SIZE];
SDL_Init(SDL_INIT_VIDEO); // if this returns 0, all ok. Else some error posted by SDL_GetError().
IMG_Init(IMG_INIT_PNG);
SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN);

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
      return 1;
 }
graph_init(board, renderer);
printNeighbors(&board[1][1]);



int running = 1;
SDL_Event event;
int selectedX = -1, selectedY = -1;

while(running){
	while(SDL_PollEvent(&event) != 0){
		if(event.type == SDL_QUIT) {
			running = 0;
		}else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Calculate the board coordinates
                int boardX = mouseX / 50; // Assuming each square is 50x50
                int boardY = mouseY / 50;

                // Check if the click is within the board boundaries
                if (boardX >= 0 && boardX < BOARD_SIZE && boardY >= 0 && boardY < BOARD_SIZE) {
                    NP* clickedSquare = &board[boardY][boardX];

                    if (!clickedSquare->piece.empty) {
                        // Select the piece
                        if (selectedX == -1 && selectedY == -1) {
                            selectedX = boardX;
                            selectedY = boardY;
                            printf("Selected piece at (%d, %d)\n", selectedX, selectedY);
                        } else {
                            // Move the piece to the new square
                            if (selectedX != boardX || selectedY != boardY) {
                                // Move the piece logic (you may want to add more checks here)
                                board[boardY][boardX].piece = board[selectedY][selectedX].piece;
                                board[selectedY][selectedX].piece.empty = 1; // Mark the old square as empty
                                selectedX = -1; // Reset selection
                                selectedY = -1;
                            }
                        }
                    } else if (selectedX != -1 && selectedY != -1) {
                        // If an empty square is clicked, move the selected piece there
                        board[boardY][boardX].piece = board[selectedY][selectedX].piece;
                        board[selectedY][selectedX].piece.empty = 1; // Mark the old square as empty
                        selectedX = -1; // Reset selection
                        selectedY = -1;
                    }
                }
            }

            //SDL_Delay(16);
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
