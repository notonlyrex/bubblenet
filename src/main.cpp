#include <M5StickCPlus2.h>
#include <WiFi.h>
#include <SPIFFS.h>

int r = 1;
LGFX_Sprite buffer(&StickCP2.Display);

long last = 0;
int timeLeft = 500;

bool started = false;

void setup(void)
{
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    Serial.begin(115200);

    StickCP2.Display.startWrite();
    StickCP2.Display.setRotation(1);
    StickCP2.Display.setTextDatum(top_left);
    StickCP2.Display.setTextColor(GREEN);
    StickCP2.Display.setFont(&fonts::FreeMono9pt7b);

    buffer.setTextDatum(top_left);
    buffer.setTextColor(GREEN);
    buffer.setFont(&fonts::FreeMono9pt7b);
    buffer.createSprite(240, 135);
}

void drawBubble()
{
    buffer.clear();
    buffer.drawCircle(120, 72, r, CYAN);

    buffer.drawCircle(120, 72, 70, RED);
    buffer.drawCircle(120, 72, 40, RED);
}

void gameOver()
{
    buffer.clear();
    buffer.setTextDatum(middle_center);
    buffer.setTextColor(RED);
    buffer.print("YOU DIED");
    buffer.pushSprite(0, 0); // Push the buffer to the display
    delay(5000);
    while (1)
    {
        if (StickCP2.BtnA.wasClicked())
        {
            r = 1;
            timeLeft = 500;
            started = false;
            return;
        }

        StickCP2.update();
    }
}

void gameOverWin()
{
    buffer.setCursor(0, 0);
    buffer.clear();
    buffer.setTextColor(GREEN);
    buffer.print("YOU WIN");
    buffer.pushSprite(0, 0); // Push the buffer to the display
    delay(5000);
    while (1)
    {
        if (StickCP2.BtnA.wasClicked())
        {
            r = 1;
            timeLeft = 500;
            started = false;
            return;
        }

        StickCP2.update();
    }
}

void loop(void)
{
    unsigned long loopStartTime = millis(); // Store the start time of the loop

    drawBubble();
    buffer.setCursor(10, 10);
    buffer.printf("Time left: %d", timeLeft / 100);

    if (StickCP2.BtnA.wasClicked())
    {
        r += 3;
    }

    if (r > 70)
    {
        gameOver();
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
        gameOver();
    }

    if (timeLeft <= 0)
    {
        gameOverWin();
    }

    if (r > 1 && millis() - last > 100)
    {
        r--;
        last = millis();
    }

    buffer.pushSprite(0, 0); // Push the buffer to the display
    StickCP2.update();
}
