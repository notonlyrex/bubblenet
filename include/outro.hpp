#include "level.hpp"

class OutroScreen : public Level
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
        buffer->setCursor(0, 50);

        if (text == 3)
            buffer->setFont(&fonts::lgfxJapanMincho_40);
        else
            buffer->setFont(&fonts::efontJA_24_b);

        for (int i = 0; i < step; i++)
        {
            if (text == 2)
            {
                buffer->print((char)(rand() % 128));
            }
            else
            {
                buffer->print(texts[text][i]);
            }
        }

        if (millis() - last > 50)
        {
            if (step < texts[text].length())
                step++;

            last = millis();
        }

        if (step == texts[text].length() && button)
        {
            text++;
            step = 0;

            if (text == 4)
            {
                return LevelResult::Finished;
            }
        }

        return LevelResult::Continue;
    }

private:
    long start = 0;
    String texts[4] = {"中に", "ハッキングしているよ", "12345678901234567890",
                       "何…！"};
    int text = 0;
    int step = 0;
    long last = 0;
};
