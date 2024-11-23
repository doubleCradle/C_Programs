typedef struct Node {
    char name;
    int x; 
    int y; 
    SDL_Rect rect;
    struct Node* neighbors[8]; 
} Node;
