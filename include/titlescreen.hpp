#include "level.hpp"

class TitleScreen : public Level
{
public:
    virtual void setup(std::shared_ptr<LGFX_Sprite> buffer) override
    {
        this->buffer = buffer;
        start = millis();
    }

    virtual LevelResult render(bool button) override
    {
        unsigned long loopStartTime = millis();

        // buffer->clear();
        if (millis() - last > 10)
        {
            buffer->fillSmoothCircle(rand() % 240, rand() % 135, rand() % 30, CYAN);

            last = millis();
        }

        buffer->setCursor(0, 65);
        buffer->setFont(&fonts::FreeMonoBold18pt7b);
        buffer->setTextColor(BLACK);
        buffer->drawCenterString("BUBBLENET", 120, 65);
        buffer->setFont(&fonts::efontJA_16_b);
        buffer->drawCenterString("ボタンを押してください", 120, 110);

        if (button && (millis() - start > 1000))
        {
            return LevelResult::Finished;
        }

        return LevelResult::Continue;
    }

private:
    long last = 0;
    String target;
    long start;
};