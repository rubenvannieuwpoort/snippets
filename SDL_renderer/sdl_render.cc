#include <iostream>
#include <SDL2/SDL.h>

Uint32 *framebuffer;

int width = 640;
int height = 480;

int main() {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL_Init(SDL_INIT_VIDEO) failed\n";
		return 1;
	}
	
	SDL_Window *window = SDL_CreateWindow("Texture streamer",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	// use SDL_TEXTUREACCESS_STREAMING because we will be writing to this texture a lot
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, width, height);
	
	framebuffer = new Uint32[width * height];
	
	bool quit = false, fullscreen = false;
	while (!quit) {
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
				break;
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
					break;
				}
				else if (event.key.keysym.sym == 'f') {
					fullscreen = !fullscreen;
					if (fullscreen)
						SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
					else
						SDL_SetWindowFullscreen(window, 0);
				}
			}
			else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					width = event.window.data1;
					height = event.window.data2;

					// resizing changes texture and buffer size, so need to re-allocate
					// the framebuffer and destroy and re-create the texture
					delete[] framebuffer;
					framebuffer = new Uint32[width * height];
					SDL_DestroyTexture(texture);
					texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
						SDL_TEXTUREACCESS_STREAMING, width, height);
				}
			}
		}

		// render
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				uint8_t r, g, b;
				r = x & 255;
				g = y & 255;
				b = (x ^ y) & 255;
				framebuffer[y * width + x] = (r << 16) + (g << 8) + b;
			}
		}
		
		SDL_UpdateTexture(texture, NULL, framebuffer, width * sizeof(Uint32));
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	
	delete[] framebuffer;
	
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	SDL_Quit();
	
	return 0;
}
