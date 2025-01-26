#include "level.hpp"

class InstructionScreen : public Level
{
public:
    InstructionScreen(String text)
    {
        this->text = text;
    }

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
        buffer->setTextColor(WHITE);
        buffer->setFont(&fonts::efontJA_24_b);

        for (int i = 0; i < step; i++)
        {
            buffer->print(text[i]);
        }

        if (millis() - last > 50)
        {
            if (step < text.length())
                step++;

            last = millis();
        }

        if (step == text.length() && button)
        {

            return LevelResult::Finished;
        }

        return LevelResult::Continue;
    }

private:
    long start = 0;
    String text;
    int step = 0;
    long last = 0;
};
