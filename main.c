#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <curses.h>
#include <math.h>
#include <stdbool.h>

SDL_Texture* text = NULL;
SDL_Window *window = NULL;
SDL_Rect message_rect;
SDL_Renderer *renderer = NULL;
double sine_value = 0;
double sine_step_size;
SDL_AudioDeviceID audio_device;
SDL_AudioSpec audio_spec;
SDL_Event sdl_event;
int sample_rate = 44100;
bool running = true;
double frequency_output = 440;
double phase_double = 0;
double octave = 1.0;
float amplitude = 127.0;

double note = 440.0;
int sample_nr = 0;

void audio_callback(void *data, Uint8 *stream, int length) {
    for (int i = 0; i < length; i++) {
        stream[i] = (Uint8) (amplitude * sin(sine_value))+127;
        sine_value += sine_step_size;
    }
}

int init_sdl_audio() {

    SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec want;
    SDL_zero(want);
    SDL_zero(audio_spec);

    want.freq = 44100;
    want.format = AUDIO_U8;
    want.channels = 1;
    want.samples = 4096;
    want.callback = audio_callback;

    audio_device = SDL_OpenAudioDevice(NULL, 0, &want, &audio_spec, 0);

    if (audio_device == 0) {
        printf("Failed to open audio!\n");
        return 1;
    }
    SDL_PauseAudioDevice(audio_device, 0);

    return 0;
}

int init_sdl_video() {

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("arnSynth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 24);
	SDL_Color color = {120, 200, 100, 0};

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, "Keyboard layout:\n\
		|   |   | |   |   |   |   | |   | |   |   |     | \n\
		|   | W | | E |   |   | T | | Y | | U |   |     | \n\
		|   |___| |___|   |   |___| |___| |___|   |     | \n\
		|     |     |     |     |     |     |     |     | \n\
		|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  | \n\
		|_____|_____|_____|_____|_____|_____|_____|_____| \n\n\
        Octave up: Z\n\
        Octave down: X\n", color);

	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, text_surface);

	message_rect.x = 0;
	message_rect.y = 0;
	message_rect.w = 640;
	message_rect.h = 480;

}

void handle_keydown(SDL_Keysym* key) {
    switch(key->sym) {
        printf("Switching note\n");
        case SDLK_ESCAPE:
            running = false;
            break;
        case SDLK_a:
            note = 261.63;
            break;
        case SDLK_w:
            note = 277.18;
            break;
        case SDLK_s:
            note = 293.66;
            break;
        case SDLK_e:
            note = 311.13;
            break;
        case SDLK_d:
            note = 329.63;
            break;
        case SDLK_f:
            note = 349.23;
            break;
        case SDLK_t:
            note = 369.99;
            break;
        case SDLK_g:
            note = 392.00;
            break;
        case SDLK_y:
            note = 415.30;
            break;
        case SDLK_h:
            note = 440.00;
            break;
        case SDLK_u:
            note = 466.16;
            break;
        case SDLK_j:
            note = 493.88;
            break;
        case SDLK_k:
            note = 523.25;
            break;
        case SDLK_z:
            octave *= 2.0;
            break;
        case SDLK_x:
            octave /= 2.0;
            break;
    }
    sine_step_size = 2 * 3.14159 * note * octave / sample_rate;
}


int main() {

    init_sdl_audio();
    init_sdl_video();

    sine_step_size = 2 * 3.14159 * note * octave / sample_rate;

    while(running) {
        while(SDL_PollEvent(&sdl_event)) {
            switch(sdl_event.type) {
                case SDL_KEYDOWN:
                    handle_keydown(&sdl_event.key.keysym);
            }
        }

        SDL_RenderCopy(renderer, text, NULL, &message_rect);
    }

    SDL_CloseAudioDevice(audio_device);
    SDL_Quit();
}
