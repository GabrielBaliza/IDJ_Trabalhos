#include "EndState.h"

EndState::EndState(){
    if(GameData::playerVictory){
        GameObject* win = new GameObject();
        Sprite* winSprite = new Sprite(*win, YOUWIN_BG);
        win->AddComponent(winSprite);
        AddObject(win);
        backgroundMusic.Open(YOUWIN_MUSIC);
    }
    else{
        GameObject* lose = new GameObject();
        Sprite* loseSprite = new Sprite(*lose, YOULOSE_BG);
        lose->AddComponent(loseSprite);
        AddObject(lose);
        backgroundMusic.Open(YOULOSE_MUSIC);
    }
    
    instructionText = new GameObject();
    Text* text = new Text(*instructionText, FONT, 30, Text::TextStyle::SOLID, "Press spacebar to play again! Press esc to close...", {0, 0, 0, 255});
    instructionText->AddComponent(text);
    instructionText->box.x = 1024/2 - instructionText->box.w/2;
    instructionText->box.y = 500;
    AddObject(instructionText);

}

EndState::~EndState(){}

void EndState::LoadAssets(){}

void EndState::Update(float dt){
    if(InputManager::GetInstance().KeyPress(SPACE_BAR)){
		popRequested = true;
	}
    if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested = true;
	}
    UpdateArray(dt);
    instructionTimer.Update(dt);
}

void EndState::Render(){
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

void EndState::Start(){
	StartArray();
    backgroundMusic.Play(-1);
}

void EndState::Pause(){}

void EndState::Resume(){
    Camera::pos = {0, 0};
}
