typedef struct Node {
    char name;
    int x; 
    int y; 
    SDL_Rect rect;
    struct Node* neighbors[8]; 
} Node;

void graph_init(Node board[BOARD_SIZE][BOARD_SIZE]) {
 char alphabet[] = {'a','b','c','d','e','f','g','h'};
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            board[y][x].x = x;
            board[y][x].y = y;

	    board[y][x].rect.x = x*50;
	    board[y][x].rect.y = y*50;
	    board[y][x].rect.w = 50;
	    board[y][x].rect.h = 50;
	    board[y][x].name = alphabet[x];

            // Initialize neighbors
            int neighborCount = 0;

            // Up
            if (y > 0) {
                board[y][x].neighbors[neighborCount++] = &board[y - 1][x]; // North
            }
            // Down
            if (y < BOARD_SIZE - 1) {
                board[y][x].neighbors[neighborCount++] = &board[y + 1][x]; // South
            }
            // Left
            if (x > 0) {
                board[y][x].neighbors[neighborCount++] = &board[y][x - 1]; // West
            }
            // Right
            if (x < BOARD_SIZE - 1) {
                board[y][x].neighbors[neighborCount++] = &board[y][x + 1]; // East
            }
            // Top-Left
            if (x > 0 && y > 0) {
                board[y][x].neighbors[neighborCount++] = &board[y - 1][x - 1]; // Northwest
            }
            // Top-Right
            if (x < BOARD_SIZE - 1 && y > 0) {
                board[y][x].neighbors[neighborCount++] = &board[y - 1][x + 1]; // Northeast
            }
            // Bottom-Left
            if (x > 0 && y < BOARD_SIZE - 1) {
                board[y][x].neighbors[neighborCount++] = &board[y + 1][x - 1]; // Southwest
            }
            // Bottom-Right
            if (x < BOARD_SIZE - 1 && y < BOARD_SIZE - 1) {
                board[y][x].neighbors[neighborCount++] = &board[y + 1][x + 1]; // Southeast
            }

            // Set remaining neighbors to NULL
            for (int i = neighborCount; i < 8; i++) {
                board[y][x].neighbors[i] = NULL;
            }
        }
    }
}
