#include "level.hpp"

class BubbleSort : public Level
{
public:
    virtual void setup(std::shared_ptr<LGFX_Sprite> buffer) override
    {
        this->buffer = buffer;

        timeLeft = 1000;
        started = false;
        last = millis();

        values[0] = rand() % 10;
        values[1] = rand() % 10;
        values[2] = rand() % 10;
        values[3] = rand() % 10;

        for (int i = 0; i < 4; i++)
        {
            moves[i] = moves[i] - rand() % 20;
        }

        if (checkWin())
        {
            std::sort(values, values + 4);
            std::reverse(values, values + 4);
        }
    }

    virtual LevelResult render(bool button) override
    {
        unsigned long loopStartTime = millis();
        buffer->clear();

        buffer->setTextColor(GREEN);
        buffer->setFont(&fonts::FreeMono9pt7b);
        buffer->setCursor(0, 10);
        buffer->printf("Time left: %.1fs", timeLeft / 100.0f);

        if (started)
        {
            timeLeft -= millis() - loopStartTime;
        }

        if (button && !started)
        {
            started = true;
        }

        if (button)
        {
            std::swap(values[active], values[active + 1]);
        }

        if (millis() - last > 1000)
        {
            active++;
            if (active > 2)
            {
                active = 0;
            }
            last = millis();
        }

        drawBubbles();

        if (checkWin())
        {
            return LevelResult::Finished;
        }

        if (timeLeft <= 0)
        {
            return LevelResult::GameOver;
        }

        return LevelResult::Continue;
    }

private:
    bool started;
    int timeLeft;

    int active = 0;
    long last = 0;

    int values[4] = {4, 3, 2, 1};

    int moves[4] = {65, 60, 70, 65};

    void drawBubbles()
    {
        buffer->setCursor(20, 65);
        buffer->setFont(&fonts::FreeMonoBold18pt7b);
        buffer->setTextColor(CYAN);

        for (int i = 0; i < 4; i++)
        {
            if (active == i || (active + 1) == i)
            {
                buffer->drawCircle(20 + i * 60, moves[i], 20, RED);
            }
            else
            {
                buffer->drawCircle(20 + i * 60, moves[i], 20, CYAN);
            }

            buffer->drawNumber(values[i], 20 + i * 60, moves[i]);
        }
    }

    bool checkWin()
    {
        return (values[0] <= values[1] && values[1] <= values[2] && values[2] <= values[3]);
    }
};