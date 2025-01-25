#include <M5StickCPlus2.h>
#include <WiFi.h>
#include <SPIFFS.h>

#include "bubblepump.hpp"
#include "gameover.hpp"

LGFX_Sprite buffer(&StickCP2.Display);
GameOverScreen level;

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

    level.setup(std::make_shared<LGFX_Sprite>(buffer));
}

void gameOver()
{
    buffer.clear();
    buffer.setTextDatum(middle_center);
    buffer.setTextColor(RED);
    buffer.print("YOU DIED");
    buffer.pushSprite(0, 0); // Push the buffer to the display
    delay(5000);
    while (1)
    {
        if (StickCP2.BtnA.wasClicked())
        {
            return;
        }

        StickCP2.update();
    }
}

void gameOverWin()
{
    buffer.setCursor(0, 0);
    buffer.clear();
    buffer.setTextColor(GREEN);
    buffer.print("YOU WIN");
    buffer.pushSprite(0, 0);
    delay(5000);
    while (1)
    {
        if (StickCP2.BtnA.wasClicked())
        {
            return;
        }

        StickCP2.update();
    }
}

void loop(void)
{
    LevelResult result = level.render(StickCP2.BtnA.wasClicked());

    if (result == LevelResult::GameOver)
    {
        gameOver();
    }
    else if (result == LevelResult::GameOverWin)
    {
        gameOverWin();
    }

    if (StickCP2.BtnB.wasClicked())
    {
        ESP.restart();
    }

    buffer.pushSprite(0, 0); // Push the buffer to the display
    StickCP2.update();
}
