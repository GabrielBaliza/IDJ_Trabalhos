#pragma once

#define TITLE "./assets/img/title.jpg"
#define FONT "./assets/font/Call me maybe.ttf"

#include <vector>
#include <memory>
#include <iostream>

#include "Game.h"
#include "Sprite.h"
#include "Music.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "State.h"
#include "StageState.h"
#include "Camera.h"
#include "Text.h"
#include "Timer.h"

class TitleState : public State {
    private:
        GameObject* instructionText;
        Timer instructionTimer;
    public:
        TitleState();
        ~TitleState();
        void LoadAssets() override;
        void Update(float dt) override;
        void Render() override;
        void Start() override;
        void Pause() override;
        void Resume() override;
};