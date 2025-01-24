#include <M5StickCPlus2.h>
#pragma once

class Level
{
public:
    Level(LGFX_Sprite &buffer);
    virtual void setup();
    virtual void render();

protected:
    M5GFX display;
    LGFX_Sprite buffer;
};

enum LevelResult
{
    Continue,
    GameOver,
    GameOverWin
};