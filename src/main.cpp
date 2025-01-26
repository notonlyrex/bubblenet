#include <M5StickCPlus2.h>
#include <WiFi.h>
#include <SPIFFS.h>

#include "bubblepump.hpp"
#include "shoot.hpp"
#include "gameover.hpp"
#include "youwin.hpp"
#include "bubblesort.hpp"
#include "wifigame.hpp"
#include "intro.hpp"
#include "outro.hpp"
#include "titlescreen.hpp"
#include "instruction.hpp"

LGFX_Sprite buffer(&StickCP2.Display);

std::vector<std::shared_ptr<Level>> levels = {
    std::make_shared<TitleScreen>(),
    std::make_shared<IntroScreen>(),
    std::make_shared<InstructionScreen>("ボタンを押してスキャンして\nBSSID を持つ WAP に近づく"),
    std::make_shared<WifiBubble>(),
    std::make_shared<InstructionScreen>("俺をネットワークに注入して"),
    std::make_shared<BubbleShoot>(),
    std::make_shared<InstructionScreen>("俺のサイズをぴったりになる"),
    std::make_shared<BubblePump>(),
    std::make_shared<InstructionScreen>("もうすぐそこ。\n数字を小さい順に並べる"),
    std::make_shared<BubbleSort>(),
    std::make_shared<YouWinScreen>(),
    std::make_shared<OutroScreen>(),
    // std::make_shared<GameOverScreen>()};
};

int currentLevel = 0;

void setup(void)
{
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    Serial.begin(115200);

    srand(StickCP2.Rtc.getDateTime().time.seconds);

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
    currentLevel = 0;
    levels[currentLevel]->setup(std::make_shared<LGFX_Sprite>(buffer));
}

void loop(void)
{
    LevelResult result = levels[currentLevel]->render(StickCP2.BtnA.wasClicked());

    if (result == LevelResult::GameOver)
    {
        levels[currentLevel] = std::make_shared<GameOverScreen>();
        levels[currentLevel]->setup(std::make_shared<LGFX_Sprite>(buffer));
    }
    else if (result == LevelResult::Finished)
    {
        currentLevel++;
        if (currentLevel >= levels.size())
        {
            ESP.restart();
        }
        levels[currentLevel]->setup(std::make_shared<LGFX_Sprite>(buffer));
    }

    if (StickCP2.BtnB.wasClicked())
    {
        ESP.restart();
    }

    buffer.pushSprite(0, 0); // Push the buffer to the display
    StickCP2.update();
}
