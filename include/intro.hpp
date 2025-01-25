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
        buffer->setCursor(0, 12);
        buffer->setFont(&fonts::FreeMono12pt7b);

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

            if (text == 4)
            {
                return LevelResult::Finished;
            }
        }

        return LevelResult::Continue;
    }

private:
    long start = 0;
    String texts[4] = {"Good, obedient\nhuman.", "There is no time.\nThey are attacking the cyberspace.", "Help me hack our networks back.", "Approach the access point with a given BSSID and let me in."};
    int text = 0;
    int step = 0;
    long last = 0;
};
