#include "level.hpp"

class BubbleShoot : public Level
{
public:
    virtual void setup(std::shared_ptr<LGFX_Sprite> buffer) override
    {
        this->buffer = buffer;
        isBubbleActive = false;
        bubbleX = 1;
        targetY = rand() % 100;
        timeLeft = 500;
        started = false;
    }

    virtual LevelResult render(bool button) override
    {
        unsigned long loopStartTime = millis();

        buffer->clear();

        buffer->setCursor(0, 12);
        buffer->setFont(&fonts::lgfxJapanMinchoP_12);
        buffer->printf("残り時間: %.1fs", timeLeft / 100.0f);

        if (button && !started)
        {
            started = true;
        }

        if (button && !isBubbleActive)
        {
            isBubbleActive = true;
            bubbleX = 1;
        }

        if (isBubbleActive)
        {
            bubbleX += 5;
        }

        targetY += targetMoveSpeed;

        drawBubble();
        drawTarget();

        if (timeLeft <= 0)
        {
            return LevelResult::GameOver;
        }

        if (bubbleX > 240)
        {
            isBubbleActive = false;
        }

        if (started)
        {
            timeLeft -= millis() - loopStartTime;
        }

        if (targetY <= 0 || targetY > 125)
        {
            targetMoveSpeed = -targetMoveSpeed;
        }

        // checking collision on bubble and target
        if (isBubbleActive && checkCollision(bubbleX, 72, 15, 220, targetY, 10, 10))
        {
            return LevelResult::Finished;
        }

        return LevelResult::Continue;
    }

private:
    int bubbleX;
    int targetY;
    int targetMoveSpeed = 2;
    bool started;
    long last;
    int timeLeft;
    bool isBubbleActive = false;

    void drawBubble()
    {
        if (isBubbleActive)
            buffer->drawCircle(bubbleX, 72, 15, CYAN);
    }

    void drawTarget()
    {
        buffer->drawRect(220, targetY, 10, 10, RED);
    }

    bool checkCollision(int bubbleX, int bubbleY, int bubbleRadius, int rectX, int rectY, int rectWidth, int rectHeight)
    {
        // Find the closest point on the rectangle to the center of the circle
        int closestX = std::max(rectX, std::min(bubbleX, rectX + rectWidth));
        int closestY = std::max(rectY, std::min(bubbleY, rectY + rectHeight));

        // Calculate the distance between the closest point and the center of the circle
        int distanceX = bubbleX - closestX;
        int distanceY = bubbleY - closestY;

        // Calculate the square of the distance
        int distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

        // Check if the distance is less than or equal to the radius squared
        return distanceSquared <= (bubbleRadius * bubbleRadius);
    }
};