#include "level.hpp"
#include <WiFi.h>

class WifiBubble : public Level
{
public:
    virtual void setup(std::shared_ptr<LGFX_Sprite> buffer) override
    {
        this->buffer = buffer;
        r = 1;
        timeLeft = 500;
        started = false;

        int n = WiFi.scanNetworks(false, true);

        if (n == 0)
        {
            buffer->println("No networks found");
            targetSignal = 0;
        }
        else
        {
            for (int i = 0; i < n; ++i)
            {
                Serial.printf("%d %s %s \n", i, WiFi.SSID(i).c_str(), WiFi.BSSIDstr(i).c_str());
            }

            int targetId = rand() % n;
            target = WiFi.BSSIDstr(targetId);
            // target = "C6:97:85:3C:02:1C"; // selene
            // target = "60:22:32:72:2F:CE"; // WSEI
            Serial.println(WiFi.SSID(targetId));
            Serial.println(target);

            for (int i = 0; i < n; ++i)
            {
                if (WiFi.BSSIDstr(i) == target)
                {
                    targetSignal = -WiFi.RSSI(i);
                    Serial.printf("\n  Signal: %d\n", targetSignal);
                    break;
                }
            }
        }
    }

    virtual LevelResult render(bool button) override
    {
        unsigned long loopStartTime = millis();

        buffer->clear();
        drawBubble();

        buffer->setCursor(0, 65);
        buffer->setFont(&fonts::FreeMonoBold18pt7b);
        buffer->setTextColor(CYAN);
        buffer->drawCenterString("BUBBLENET", 120, 65);
        buffer->setFont(&fonts::FreeMono9pt7b);
        buffer->setTextColor(GREEN);

        if (button && !scanInProgress)
        {
            WiFi.scanDelete();
            int n = WiFi.scanNetworks(true, true);
            scanInProgress = true;

            last = millis();
        }

        if (scanInProgress)
        {
            buffer->fillRect(0, 100, 240, 50, RED);
        }
        buffer->drawCenterString(target, 120, 110);

        int n = WiFi.scanComplete();
        if (n > 0)
        {
            // for (int i = 0; i < n; ++i)
            // {
            //     Serial.printf("%d %s %s\n", i, WiFi.SSID(i).c_str(), WiFi.BSSIDstr(i).c_str());
            // }

            for (int i = 0; i < n; ++i)
            {
                if (WiFi.BSSIDstr(i) == target)
                {
                    targetSignal = -WiFi.RSSI(i);
                    Serial.printf("\n  Signal: %d\n", targetSignal);
                    break;
                }
            }

            if (targetSignal <= 50)
            {
                return LevelResult::Finished;
            }

            scanInProgress = false;
        }
        else if (n == 0)
        {
            return LevelResult::Finished;
        }

        buffer->drawCircle(120, 67, 100 - targetSignal, CYAN);
        buffer->drawCircle(120, 67, 100 - 40, RED);

        return LevelResult::Continue;
    }

private:
    int r;
    bool started;
    long last = 0;
    int targetSignal = 100;
    String target;
    int timeLeft;
    bool scanInProgress = false;

    void drawBubble()
    {
    }
};