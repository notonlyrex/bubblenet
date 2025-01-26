#include "level.hpp"

class YouWinScreen : public Level
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
        buffer->setTextColor(GREEN);
        buffer->drawCenterString("YOU WIN!", 120, 65);

        buffer->setFont(&fonts::efontJA_16_b);
        buffer->drawCenterString("ハッキングは完了した", 120, 95);

        if (millis() - start > 5000 && button)
        {
            return LevelResult::Finished;
        }

        return LevelResult::Continue;
    }

private:
    long start = 0;
};
