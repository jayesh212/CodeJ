#ifndef __$$__Neo_h
#define __$$__Neo_h 7
#define SFML_NO_DEPRECATED_WARNINGS
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <windows.h>
#include <cmath>
#include "String.hpp"
using namespace sf;
class Button // Abstract class for defining the key features of a button
{
public:
    virtual int isClicked(sf::Event event, sf::Window &window) = 0;
    virtual void setPos(int x, int y) = 0;
    virtual void setText(JString string) = 0;
    virtual void setTextSize(int textSize) = 0;
    virtual void getPosition(int &posX, int &posY) = 0;
    virtual void setFillColor(sf::Color color) = 0;
    virtual void setTextColor(sf::Color color) = 0;
    virtual void setFont(sf::Font &font) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};
class RectangleButton : public Button
{
private:
    sf::RectangleShape buttonRect;
    sf::Text text;
    JString string;
    int width;
    int height;
    int posX;
    int posY;
    sf::Color fillColor;
    sf::Color textColor;
    bool blink;
    sf::Texture texture;
    bool blinkRect;
    bool tToggle;

public:
    RectangleButton()
    {
        this->width = 0;
        this->height = 0;
        posX = 0;
        posY = 0;
        buttonRect.setPosition(posX, posY);
        text.setString("");
        text.setPosition(posX, posY);
        this->blink = true;
        this->tToggle = false;
        this->blinkRect = false;
    }
    RectangleButton(int posX, int posY, sf::Color fillColor, int width, int height)
    {
        this->posX = posX;
        this->posY = posY;
        if (width < 0)
            this->width = 0;
        else
            this->width = width;
        if (height < 0)
            this->height = 0;
        else
            this->height = height;
        buttonRect.setPosition(this->posX, this->posY);
        buttonRect.setSize(Vector2f(this->width, this->height));
        buttonRect.setFillColor(fillColor);
        this->fillColor = fillColor;
        text.setString("");
        text.setPosition(posX, posY);
        this->blink = true;
        this->tToggle = false;
        this->blinkRect = false;
    }
    void blinkRectToggle(bool state)
    {
        this->blinkRect = state;
    }
    int isClicked(sf::Event event, sf::Window &window)
    {
        int x = Mouse::getPosition(window).x;
        int y = Mouse::getPosition(window).y;
        int pressed = 0;
        if (event.type == Event::MouseButtonPressed)
        {
            switch (event.key.code)
            {
            case Mouse::Left:
                pressed = 1;
                break;
            case Mouse::Right:
                pressed = 2;
                break;
            default:
                pressed = 0;
                break;
            }
        }
        if ((x > this->posX) && (x < this->posX + this->width) && (y > this->posY) && y < this->posY + this->height)
        {
            if (this->blink)
            {
                sf::Color color;
                if (this->textColor.r > 195)
                    color.r = 255;
                else
                    color.r = this->textColor.r + 60;
                if (this->textColor.b > 195)
                    color.b = 255;
                else
                    color.b = this->textColor.b + 60;
                if (this->textColor.g > 195)
                    color.g = 255;
                else
                    color.g = this->textColor.g + 60;
                color.a = this->textColor.a;
                text.setFillColor(color);
            }
            if (this->blinkRect)
            {
                sf::Color color;
                if (this->fillColor.r > 195)
                    color.r = 255;
                else
                    color.r = this->fillColor.r + 60;
                if (this->fillColor.b > 195)
                    color.b = 255;
                else
                    color.b = this->fillColor.b + 60;
                if (this->fillColor.g > 195)
                    color.g = 255;
                else
                    color.g = this->fillColor.g + 60;
                if ((this->fillColor).a < 200)
                    color.a = this->fillColor.a + 40;
                buttonRect.setFillColor(color);
            }
            if (pressed == 1)
                return 1;
            if (pressed == 2)
                return 2;
        }
        else
        {
            if (!tToggle && this->blink)
                text.setFillColor(this->textColor);
            if (this->blinkRect)
                buttonRect.setFillColor(this->fillColor);
        }
        return 0;
    }
    void setPos(int x, int y)
    {
        this->posX = x;
        this->posY = y;
        buttonRect.setPosition(Vector2f(x, y));
        text.setPosition(posX, posY);
    }
    void setText(JString string)
    {
        int size = string.getSize();
        char *charray = new char[size];
        string.getString(charray);
        text.setString(charray);
        this->string = string;
    }
    void setTextSize(int textSize)
    {
        text.setCharacterSize(textSize);
        Vector2f textPos;
        textPos = text.findCharacterPos(string.getSize());
        if (textPos.x < this->posX + width)
            text.setPosition(this->posX, this->posY + this->height / 2 - textSize / 2);
        else
            text.setPosition(this->posX, this->posY + this->height / 2 - textSize / 2);
    }
    void setTextPos(int posX, int posY)
    {
        Vector2f textPos;
        textPos.x = posX;
        textPos.y = posY;
        text.setPosition(textPos);
    }
    void getPosition(int &posX, int &posY)
    {
        posX = this->posX;
        posY = this->posY;
    }
    void setFillColor(sf::Color color)
    {
        buttonRect.setFillColor(color);
        this->fillColor = color;
    }
    void setTextColor(sf::Color color)
    {
        text.setFillColor(color);
        this->tToggle = false;
        this->textColor = color;
    }
    void setSize(int width, int height)
    {
        this->width = width;
        this->height = height;
        buttonRect.setSize(Vector2f(this->width, this->height));
        text.setPosition(this->posX, this->posY + this->width / 2 - text.getCharacterSize() / 2);
    }
    void setFont(sf::Font &font)
    {
        text.setFont(font);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(buttonRect);
        window.draw(text);
    }
    void setBlink(bool state)
    {
        this->blink = state;
    }
    void setTexture(const char *filePath)
    {
        this->tToggle = true;
        this->texture.loadFromFile(filePath);
        buttonRect.setTexture(&this->texture);
        buttonRect.setSize(Vector2f(this->width, this->height));
        this->blink = false;
    }
};

class CircleButton
{
private:
    sf::CircleShape buttonCircle;
    int radius;
    int posX;
    int posY;
    int centerX, centerY;
    sf::Color fillColor;
    bool blink;
    sf::Texture texture;
    bool tToggle;

public:
    CircleButton()
    {
        this->radius = 0;
        posX = 0;
        posY = 0;
        buttonCircle.setPosition(posX, posY);
        buttonCircle.setPointCount(30);
        this->blink = true;
        this->tToggle = false;
    }
    CircleButton(int posX, int posY, sf::Color fillColor, int radius)
    {
        this->tToggle = false;
        this->posX = posX;
        this->posY = posY;
        if (radius < 0)
            this->radius = 0;
        else
            this->radius = radius;
        this->centerX = this->posX + this->radius;
        this->centerY = this->posY + this->radius;
        buttonCircle.setPosition(this->posX, this->posY);
        buttonCircle.setRadius(this->radius);
        buttonCircle.setFillColor(fillColor);
        this->fillColor = fillColor;
        buttonCircle.setPointCount(30);
        this->blink = true;
    }
    int isClicked(sf::Event event, sf::Window &window)
    {
        int x = Mouse::getPosition(window).x;
        int y = Mouse::getPosition(window).y;
        int pressed = 0;
        if (event.type == Event::MouseButtonPressed)
        {
            switch (event.key.code)
            {
            case Mouse::Left:
                pressed = 1;
                break;
            case Mouse::Right:
                pressed = 2;
                break;
            default:
                pressed = 0;
                break;
            }
        }
        double distFromCenter = pow(x - this->centerX, 2) + pow(y - this->centerY, 2);
        distFromCenter = sqrt(distFromCenter);
        if (distFromCenter < this->radius)
        {
            if (this->blink)
            {
                sf::Color color;
                color.r = this->fillColor.r + 60;
                color.b = this->fillColor.b + 60;
                color.g = this->fillColor.g + 60;
                buttonCircle.setFillColor(color);
            }
            if (pressed == 1)
                return 1;
            if (pressed == 2)
                return 2;
        }
        else
        {
            if (!tToggle)
                buttonCircle.setFillColor(this->fillColor);
        }
        return 0;
    }
    void setPos(int x, int y)
    {
        this->posX = x;
        this->posY = y;
        this->centerX = this->posX + this->radius;
        this->centerY = this->posY + this->radius;
        buttonCircle.setPosition(Vector2f(x, y));
    }
    void setPointCount(int points)
    {
        buttonCircle.setPointCount(points);
    }
    void getPosition(int &posX, int &posY)
    {
        posX = this->posX;
        posY = this->posY;
    }
    void setFillColor(sf::Color color)
    {
        buttonCircle.setFillColor(color);
        this->tToggle = false;
        this->fillColor = color;
    }
    void setSize(int radius)
    {
        this->radius = radius;
        this->centerX = this->posX + this->radius;
        this->centerY = this->posY + this->radius;
        buttonCircle.setRadius(this->radius);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(buttonCircle);
    }
    void setBlink(bool state)
    {
        this->blink = state;
    }
    void setTexture(const char *filePath)
    {
        (this->texture).loadFromFile(filePath);
        buttonCircle.setTexture(&this->texture);
        buttonCircle.setRadius(this->radius);
        this->tToggle = true;
        this->blink = false;
    }
};

#endif