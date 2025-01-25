#include "level.hpp"

class BubbleShoot : public Level
{
public:
    virtual void setup(std::shared_ptr<LGFX_Sprite> buffer) override
    {
        this->buffer = buffer;
        isBubble = false;
        x = 1;
        y = 50;
        timeLeft = 500;
        started = false;
    }

    virtual LevelResult render(bool button = false) override
    {
        unsigned long loopStartTime = millis();

        buffer->clear();

        buffer->setCursor(0, 10);
        buffer->printf("Time left: %.1fs", timeLeft / 100.0f);

        if (button && !started)
        {
            started = true;
        }

        if (button && !isBubble)
        {
            isBubble = true;
            x = 1;
        }

        if (isBubble)
        {
            x += 5;
        }

        y += move;

        drawBubble();
        drawTarget();

        if (timeLeft <= 0)
        {
            return LevelResult::GameOver;
        }

        if (x > 240)
        {
            isBubble = false;
        }

        if (started)
        {
            timeLeft -= millis() - loopStartTime;
        }

        if (y <= 0 || y > 125)
        {
            move = -move;
        }

        // checking collision on bubble and target
        if (isBubble && checkCollision(x, 72, 15, 220, y, 10, 10))
        {
            return LevelResult::Finished;
        }

        return LevelResult::Continue;
    }

private:
    int x;
    int y;
    int move = 2;
    bool started;
    long last;
    int timeLeft;
    bool isBubble = false;

    void drawBubble()
    {
        if (isBubble)
            buffer->drawCircle(x, 72, 15, CYAN);
    }

    void drawTarget()
    {
        buffer->drawRect(220, y, 10, 10, RED);
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