#include "level.hpp"

class BubblePump : public Level
{
public:
    virtual void setup(std::shared_ptr<LGFX_Sprite> buffer) override
    {
        this->buffer = buffer;
        r = 1;
        timeLeft = 500;
        started = false;
    }

    virtual LevelResult render(bool button) override
    {
        unsigned long loopStartTime = millis();

        buffer->clear();
        drawBubble();

        buffer->setCursor(0, 12);
        buffer->setFont(&fonts::efontJA_16_b);
        buffer->printf("残り時間: %.1fs", timeLeft / 100.0f);

        if (button)
        {
            r += bubbleGrowth;
        }

        if (r > 70)
        {
            return LevelResult::GameOver;
        }

        if (r > 40 && r <= 70)
        {
            timeLeft -= millis() - loopStartTime;
        }

        if (r > 45)
        {
            started = true;
            bubbleGrowth = 5;
        }

        if (r < 40 && started)
        {
            return LevelResult::GameOver;
        }

        if (timeLeft <= 0)
        {
            return LevelResult::Finished;
        }

        if (r > 1 && millis() - last > 100)
        {
            r--;
            last = millis();
        }

        return LevelResult::Continue;
    }

private:
    int r;
    bool started;
    long last;
    int timeLeft;
    int bubbleGrowth = 3;

    void drawBubble()
    {
        buffer->drawCircle(120, 72, r, CYAN);

        buffer->drawCircle(120, 72, 70, RED);
        buffer->drawCircle(120, 72, 40, RED);
    }
};