#ifndef __$$__TextSLL_h
#define __$$__TextSLL_h 7

#define DELETE_T 8
#define ENTER 13
#define COPY 3
#define PASTE 22 //previously 16
#define SAVE 19
#define SELECTALL 1
#define UNDO 26
#define CUT 24
#define TAB 9
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "string.hpp"
using namespace sf;
typedef struct TextNode
{
    sf::Text *text;
    struct TextNode *next;
} Node;
class Textbox
{
private:
    int size;
    JString str;
    JString currentWord;
    Vector2i startPos;
    Node *start;
    Node *end;
    int currentPos;
    int currentTextBox;
    sf::Text *textbox;
    sf::Color colorB;
    int lastCharacter;
    sf::Font font;
    int charSize;
    void add()
    {
        Node *textNew;
        textNew = new Node;
        textNew->next=NULL;
        textNew->text=this->textbox;
        if (textNew == NULL)
            return;
        if (this->start == NULL)
        {
            this->start=this->end=textNew;
            return;
        }
        this->end->next=textNew;
        this->end=textNew;
        this->currentTextBox++;
    }
    void pop()
    {
        Node *t,*j;
        t=this->start;
        while(t->next!=NULL)
        {
            j=t;
            t=t->next;
        }
        delete this->end;
        j->next=NULL;
        this->end=j;
    }
    int addCharacter(int charEntered)
    {
        if (charEntered > 31)
        {
           str<<(char)charEntered;
           currentWord<<(char)charEntered;
           char *string;
           string=new char[currentWord.getSize()];
           currentWord.getString(string);
           textbox->setString(string);
           lastCharacter=charEntered;
           lexer();
        }
        else if (charEntered == 8)
        {
            lexer();
            currentWord.pop();
            char *string;
            string=new char[currentWord.getSize()];
            currentWord.getString(string);
            textbox->setString(string);
        }
        /*
        else if (charEntered == 9)
        {
            str<<'t';
        }
        else if (charEntered == ENTER)
        {
            text.insert(currentPos, 1, '\n');
            textbox.setString(text);
            currentPos++;
        }
        else if (charEntered == PASTE)
        {
            int size;
            std::string clip;
            clip = sf::Clipboard::getString().toAnsiString();
            this->lastPos = this->currentPos;
            if (clip.size() != 0)
            {
                text.insert(currentPos, clip);
                currentPos += clip.size();
            }
            lastChange = clip;
            lastChangeType = 2;
            textbox.setString(text);
        }
        else if (charEntered == SAVE)
        {
            saveState = 1;
        }
        else if (charEntered == UNDO)
        {
            std::string changedString;
            if (lastChangeType == 1) //for adding string
            {
                int i;
                for (i = 0; i < this->lastPos; i++)
                {
                    changedString.push_back(text[i]);
                }
                for (int j = 0; j < lastChange.size(); j++)
                {
                    changedString.push_back(lastChange[j]);
                }
                for (; i < text.size(); i++)
                {
                    changedString.push_back(text[i]);
                }
                text = changedString;
                textbox.setString(text);
                lastChangeType = 2;
                currentPos=lastPos+lastChange.size();
                lastChange ="";
                
            }
            else if (lastChangeType == 2) //for deleting last character
            {

                //lastChangeType = 1;
            }
        }
        else if (charEntered == COPY)
        {
            //To Be Handeled --This Copies the whole data
            std::string copiedString;
            for (int i = this->selectionStart; i <= this->selectionEnd; i++)
            {
                copiedString.push_back(text[i]);
            }
            sf::Clipboard::setString(copiedString);
        }
        else if (charEntered == SELECTALL)
        {
            this->selectionStart = 0;
            this->selectionEnd = text.size() - 1;
            isSelectionOn = true;
        }*/
        return charEntered;
    }
public:
    Textbox()
    {
        this->start=NULL;
        this->end=NULL;
        this->currentPos=0;
        this->currentTextBox=1;
        this->colorB.r=180;
        this->colorB.g=20;
        this->colorB.b=20;
        textbox=new sf::Text;
        add();
    }
    int takeInput(sf::Event event)
    {
        int lastCharacter = -1;
        int charEntered = event.text.unicode;
        if (charEntered <= 128)
        {
            lastCharacter = addCharacter(charEntered);
            return lastCharacter;
        }
        return lastCharacter;
    }
    void lexer()
    {
        if(lastCharacter==' ')
        {
            Vector2f pos;
            pos=textbox->findCharacterPos(currentWord.getSize());
            textbox =new sf::Text;
            colorB.g+=50;
            textbox->setColor(colorB);
            textbox->setPosition(pos.x,pos.y);
            textbox->setFont(font);
            textbox->setCharacterSize(charSize);
            textbox->setString("");
            currentWord="";
            add();
        }
        else if(lastCharacter==8)
        {
            if(currentWord.getSize()<=1)
            {
            pop();
            textbox=this->end->text;
            currentWord="";
            int i=textbox->getString().getSize();
            int j;
            for(j=0;j<i;j++)
            {
                currentWord<<textbox->getString().toAnsiString().at(j);
            }
            std::cout<<currentWord<<std::endl;
            }
        }
    }
    void setFont(sf::Font &font)
    {
        textbox->setFont(font);
        this->font=font;
    }
    void setColor(sf::Color color)
    {
        textbox->setFillColor(color);
    }
    void setCharacterSize(int size)
    {
        textbox->setCharacterSize(size);
        charSize=size;
    }
    void draw(sf::RenderWindow &window)
    {
        Node *t = this->start;
        while (t != NULL)
        {
            window.draw(*(t->text));
            t=t->next;
        }
    }
};
#endif