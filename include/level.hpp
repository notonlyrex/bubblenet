#include <M5StickCPlus2.h>
#pragma once

enum LevelResult
{
    Continue,
    GameOver,
    Finished
};

class Level
{
public:
    virtual void setup(std::shared_ptr<LGFX_Sprite> buffer) = 0;
    virtual LevelResult render(bool button) = 0;

protected:
    std::shared_ptr<LGFX_Sprite> buffer;
};