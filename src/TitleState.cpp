#include "TitleState.h"

TitleState::TitleState(){
    GameObject* title = new GameObject();
    Sprite* title_sprite = new Sprite(*title, TITLE);
    title->AddComponent(title_sprite);
    AddObject(title);
}

TitleState::~TitleState(){

}

void TitleState::LoadAssets(){}

void TitleState::Update(float dt){
    if(InputManager::GetInstance().KeyPress(SPACE_BAR)){
		Game::GetInstance().Push(new StageState);
	}
    if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested = true;
	}
    UpdateArray(dt);
}

void TitleState::Render(){
    RenderArray();
}

void TitleState::Start(){
	StartArray();
}

void TitleState::Pause(){}

void TitleState::Resume(){
    Camera::pos = {0, 0};
}
