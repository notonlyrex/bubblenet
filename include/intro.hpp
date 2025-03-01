#include "level.hpp"

class IntroScreen : public Level
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
        buffer->setFont(&fonts::efontJA_24_b);

        for (int i = 0; i < step; i++)
        {
            buffer->print(texts[text][i]);
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

            if (text == 3)
            {
                return LevelResult::Finished;
            }
        }

        return LevelResult::Continue;
    }

private:
    long start = 0;
    String texts[3] = {"よかった\n良い人間だ", "時間がない\ncyberspaceが攻撃されている", "networksをハッキングしてのを手伝って"};
    int text = 0;
    int step = 0;
    long last = 0;
};
