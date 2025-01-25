#include <M5StickCPlus2.h>
#include <WiFi.h>
#include <SPIFFS.h>

#include "bubblepump.hpp"
#include "gameover.hpp"
#include "youwin.hpp"

LGFX_Sprite buffer(&StickCP2.Display);

std::shared_ptr<Level> level;

void setup(void)
{
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    Serial.begin(115200);

    StickCP2.Display.startWrite();
    StickCP2.Display.setRotation(1);
    StickCP2.Display.setTextDatum(top_left);
    StickCP2.Display.setTextColor(GREEN);
    StickCP2.Display.setFont(&fonts::FreeMono9pt7b);

    buffer.setTextDatum(top_left);
    buffer.setTextColor(GREEN);
    buffer.setFont(&fonts::FreeMono9pt7b);
    buffer.createSprite(240, 135);

    // level.setup(std::make_shared<LGFX_Sprite>(buffer));

    level = std::make_shared<BubblePump>();
    level->setup(std::make_shared<LGFX_Sprite>(buffer));
}

void loop(void)
{
    LevelResult result = level->render(StickCP2.BtnA.wasClicked());

    if (result == LevelResult::GameOver)
    {
        level = std::make_shared<GameOverScreen>();
        level->setup(std::make_shared<LGFX_Sprite>(buffer));
    }
    else if (result == LevelResult::Finished)
    {
        level = std::make_shared<YouWinScreen>();
        level->setup(std::make_shared<LGFX_Sprite>(buffer));
    }

    if (StickCP2.BtnB.wasClicked())
    {
        ESP.restart();
    }

    buffer.pushSprite(0, 0); // Push the buffer to the display
    StickCP2.update();
}
