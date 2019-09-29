#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdbool.h>

// Video
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font* font = NULL;
SDL_Surface* surface = NULL;
SDL_Texture* texture = NULL;
SDL_Rect texture_rect;

// Audio
SDL_AudioDeviceID audio_device;
SDL_AudioSpec audio_spec;
double sine_value = 0;
double sine_step_size;
int sample_rate = 44100;
double phase_double = 0;
double octave = 1.0;
float amplitude = 127.0;
double note = 0.0;
bool sustain = true;

// Events
SDL_Event sdl_event;
bool running = true;


void audio_callback(void *data, Uint8 *stream, int length) {
    for (int i = 0; i < length; i++) {
        stream[i] = (Uint8) (amplitude * sin(sine_value));
        sine_value += sine_step_size;
    }
}

int init_sdl_audio() {

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        return 1;
    }

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
        return 1;
    }

    SDL_PauseAudioDevice(audio_device, 0);

    return 0;
}

int init_sdl_video() {

    if (SDL_Init(SDL_INIT_VIDEO) || TTF_Init() != 0) {
        return 1;
    }

    window = SDL_CreateWindow("arnSynth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

	font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20);

	SDL_Color color = {255, 255, 255};

	surface = TTF_RenderText_Blended_Wrapped(font, "Keyboard layout:\n\
		|   |   | |   |   |   |   | |   | |   |   |     | \n\
		|   | W | | E |   |   | T | | Y | | U |   |     | \n\
		|   |___| |___|   |   |___| |___| |___|   |     | \n\
		|     |     |     |     |     |     |     |     | \n\
		|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  | \n\
		|_____|_____|_____|_____|_____|_____|_____|_____| \n\n\
        Octave up: X\n\
        Octave down: Z\n\
        Toggle sustain: C\n", color, 10000);


	texture = SDL_CreateTextureFromSurface(renderer, surface);

    int texture_width = 0;
    int texture_height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);
    texture_rect = (SDL_Rect){0, 0, texture_width, texture_height};

    return 0;
}

int quit() {
    SDL_CloseAudioDevice(audio_device);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void handle_keydown(SDL_Keysym* key) {
    switch(key->sym) {
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
            octave /= 2.0;
            break;
        case SDLK_x:
            octave *= 2.0;
            break;
        case SDLK_c:
            sustain = !sustain;
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
                    break;
                case SDL_KEYUP:
                    if (!sustain) {
                        note = 0;
                    }
                    sine_step_size = 2 * 3.14159 * note * octave / sample_rate;
                    break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
        SDL_RenderPresent(renderer);
    }

    quit();
}
