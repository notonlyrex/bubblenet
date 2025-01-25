#include "level.hpp"

class GameOverScreen : public Level
{
public:
    virtual void setup(std::shared_ptr<LGFX_Sprite> buffer) override
    {
        this->buffer = buffer;
        start = millis();
    }

    virtual LevelResult render(bool button) override
    {
        buffer->clear();
        buffer->setTextDatum(middle_center);
        buffer->setCursor(20, 65);
        buffer->setFont(&fonts::FreeMonoBold18pt7b);
        buffer->setTextColor(RED);
        buffer->print("GAME OVER");

        if (millis() - start > 5000 && button)
        {
            return LevelResult::Finished;
        }

        return LevelResult::Continue;
    }

private:
    long start = 0;
};
