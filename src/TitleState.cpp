#include "TitleState.h"

TitleState::TitleState(){
    GameObject* title = new GameObject();
    Sprite* title_sprite = new Sprite(*title, TITLE);
    title->AddComponent(title_sprite);
    AddObject(title);
    
    instructionText = new GameObject();
    Text* text = new Text(*instructionText, FONT, 30, Text::TextStyle::SOLID, "Press spacebar to play!", {0, 0, 0, 255});
    instructionText->AddComponent(text);
    instructionText->box.x = 1024/2 - instructionText->box.w/2;
    instructionText->box.y = 500;
    AddObject(instructionText);

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
    instructionTimer.Update(dt);
}

void TitleState::Render(){
    if(instructionTimer.Get() > 0.7){
        Text* inst = (Text*)instructionText->GetComponent("Text");
        inst->SetColor({0, 0, 0, 100});
        instructionTimer.Restart();  
    }
    else if(instructionTimer.Get() > 0.3){
        Text* inst = (Text*)instructionText->GetComponent("Text");
        inst->SetColor({0, 0, 0, 255});   
    }
    RenderArray();
}

void TitleState::Start(){
	StartArray();
}

void TitleState::Pause(){}

void TitleState::Resume(){
    Camera::pos = {0, 0};
}
