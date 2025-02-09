#include<stdio.h>
#include <SDL.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define AGENTS_COUNT 5

#define CELL_WIDTH ((float)SCREEN_WIDTH / BOARD_WIDTH)
#define CELL_HEIGHT ((float)SCREEN_HEIGHT / BOARD_HEIGHT)

typedef enum {
	DIR_RIGHT = 0,
	DIR_UP,
	DIR_LEFT,
	DIR_DOWN,
} Dir;

typedef struct {
	int pos_x, pos_y;
	Dir dir;
	int hunger;
	int health;
} Agent;

typedef enum {
	ACTION_NOP = 0,
	ACTION_STEP,
	ACTION_EAT,
	ACTION_ATTACK,
} Action;

Agent agents[AGENTS_COUNT];

int scc(int code) {
	if(code < 0) {
		fprintf(stderr, "SDL error: %s\n", SDL_GetError());
		exit(1);
	}
	return 0;
}

void *scp(void *ptr) {
	if(ptr == NULL) {
		fprintf(stderr, "SDL error: %s\n", SDL_GetError());
		exit(1);
	}	
	return ptr;
}

void render_grid(SDL_Renderer *renderer) {
	scc(SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255));
	// * Draw Columns
	for (int x = 1; x < BOARD_WIDTH; ++x) {
		scc(SDL_RenderDrawLine(
				renderer,
				x * CELL_WIDTH,
				0,
				x * CELL_WIDTH,
				SCREEN_HEIGHT));
	}

	// * Draw Rows
	for(int y = 1; y < BOARD_HEIGHT; ++y) {
		scc(SDL_RenderDrawLine(
				renderer,
				0,
				y * CELL_HEIGHT,
				SCREEN_WIDTH,
				y * CELL_HEIGHT));
	}
}

int random_int_range(int low, int high) {
	return rand() % (high - low) + low;
} 

int random_dir(void) {
	return (Dir) random_int_range(0, 4);
} 

Agent random_agent(void) {
	Agent agent = {0};
	agent.pos_x = random_int_range(0, BOARD_WIDTH);
	agent.pos_y = random_int_range(0, BOARD_HEIGHT);
	agent.dir = random_dir();
	agent.hunger = 100;
	agent.health = 100;
	return agent;
}

void init_agents(void) {
	for (size_t i = 0; i < AGENTS_COUNT; ++i) {
		agents[i] = random_agent();
	}
}

int main() {
	printf("Genetic Programming\n");
	scc(SDL_Init(SDL_INIT_VIDEO));

	// * Create SDL window
	SDL_Window *const window = scp(SDL_CreateWindow(
			"Hunger Games",
			0, 0,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE));

	// * Create SDL Renderer
	SDL_Renderer *const renderer = scp(SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED));

	scc(SDL_RenderSetLogicalSize(
			renderer,
			(int)SCREEN_WIDTH,
			(int)SCREEN_HEIGHT));

	int quit = 0;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: {
				quit = 1;
			} break;
			}
		}

		scc(SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255));
		scc(SDL_RenderClear(renderer));

		render_grid(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	return 0;
}
