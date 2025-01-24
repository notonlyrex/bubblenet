#include "level.hpp"

class Test
{
public:
    void setup(std::shared_ptr<LGFX_Sprite> buffer)
    {
        this->buffer = buffer;
    }

    LevelResult render(bool button = false)
    {
        if (!buffer)
        {
            Serial.println("Buffer is null");
            return LevelResult::GameOver;
        }

        buffer->clear();
        buffer->print("Hello");

        return LevelResult::Continue;
    }

private:
    std::shared_ptr<LGFX_Sprite> buffer;
};

class BubblePump // : public Level
{
public:
    void setup(std::shared_ptr<LGFX_Sprite> buffer)
    {
        this->buffer = buffer;
        r = 1;
        timeLeft = 500;
        started = false;
    }

    LevelResult render(bool button = false)
    {
        unsigned long loopStartTime = millis();

        buffer->clear();
        drawBubble();
        buffer->setCursor(10, 10);
        buffer->printf("Time left: %d", timeLeft / 100);

        if (button)
        {
            r += 3;
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
        }

        if (r < 40 && started)
        {
            return LevelResult::GameOver;
        }

        if (timeLeft <= 0)
        {
            return LevelResult::GameOverWin;
        }

        if (r > 1 && millis() - last > 100)
        {
            r--;
            last = millis();
        }

        return LevelResult::Continue;
    }

private:
    std::shared_ptr<LGFX_Sprite> buffer;
    int r;
    bool started;
    long last;
    int timeLeft;

    void drawBubble()
    {
        buffer->drawCircle(120, 72, r, CYAN);

        buffer->drawCircle(120, 72, 70, RED);
        buffer->drawCircle(120, 72, 40, RED);
    }
};