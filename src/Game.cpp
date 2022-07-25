#include "Game.h"

#define TITLE "Gabriel Baliza Rocha - 17/0103293"
#define WIDTH 1024
#define HEIGHT 600
#define DELAYTIME 33 //ms

Game *Game::instance = nullptr;

void Game::Run(){
    while(!state->QuitRequested()){
        InputManager::GetInstance().Update();
        state->Update(DELAYTIME);
        state->Render();
        SDL_RenderPresent(renderer);
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSound();
}

Game::Game(std::string title, int width, int height){
    srand(time(NULL));
    if(instance != nullptr){        
        std::cout << "Logical error. Game Error" << std::endl;
    }
    else{
        instance = this;
        
    }
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        std::cout << "SDL initialization error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0){
        std::cout << "Image initialization error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    if(Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3) == 0){
        std::cout << "Mix inicialization error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
        std::cout << "Audio opening error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    Mix_AllocateChannels(32);

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(this->window == nullptr){
        std::cout << "Window creation error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if(this->renderer == nullptr){
        std::cout << "Window creation error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    
    state = new State();

}

Game::~Game(){

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();    
    SDL_Quit();

}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}
    
State& Game::GetState(){
    return *state;
}

Game& Game::GetInstance(){
    if(instance != nullptr){
        return *instance;
    }
    else{
        instance = new Game(TITLE, WIDTH, HEIGHT);
        return *instance;
    }
}