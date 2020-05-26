#include "Neo.h"
#include "NoteGlobalVariables.h"
//To Compile
//g++ Neo.cpp -Ic:\sfml\include -Lc:\sfml\lib -lsfml-graphics -lsfml-window -lsfml-system -o Neo.exe
using namespace sf;
int main(int argc, char *argv[])
{
    //Removing the allocated Console
    FreeConsole();
    //Getting the Screen Dimensions
    RECT screenRes;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRes, 0);
    screenWidth = screenRes.right - screenRes.left;
    screenHeight = screenRes.bottom - screenRes.top;
    //Creating a Window
    currentWindowHeight = 600;
    currentWindowWidth = 800;
    ContextSettings windowSettings;
    windowSettings.antialiasingLevel = 8;
    VideoMode defaultMode(currentWindowWidth, currentWindowHeight);
    RenderWindow window(defaultMode, "", Style::None, windowSettings);
    HWND windowHandle = window.getSystemHandle();
   // window.setFramerateLimit(60);
    int closeFlag = 0, minimizeFlag = 0, maximizeFlag = 0;
    int menuFlag = 0;
    int mouseX, mouseY, dragged;
    int i;
    int fileFlag,editFlag,viewFlag,settingsFlag,openFlag,runFlag;
    View fullscreenView;
    fullscreenView.setSize(screenWidth, screenHeight);
    fullscreenView.setCenter(screenWidth / 2, screenHeight / 2);
    View defaultView;
    defaultView.setSize(defaultWidth, defaultHeight);
    defaultView.setCenter(defaultWidth / 2, defaultHeight / 2);
    CircleButton close, minimize, maximize, threeDots[3];
    close.setPos(currentWindowWidth - 20, 4);
    close.setSize(8);
    close.setFillColor(closeColor);
    maximize.setPos(currentWindowWidth - 40, 4);
    maximize.setSize(8);
    maximize.setFillColor(maximizeColor);
    minimize.setPos(currentWindowWidth - 60, 4);
    minimize.setSize(8);
    minimize.setFillColor(minimizeColor);
    for (i = 0; i <= 2; i++)
    {
        threeDots[i].setPos(5 + 10 * i, 8);
        threeDots[i].setSize(3);
        threeDots[i].setFillColor(threeDotsColor);
    }
    RectangleButton menu;
    menu.setPos(0, 0);
    menu.setSize(32, 20);
    menu.setFillColor(titleBarBlack);
    menu.setBlink(false);
    bool menuShown = false;
    RectangleButton menuBackLayer;
    menuBackLayer.setPos(0, 0);
    menuBackLayer.setBlink(false);
    menuBackLayer.setFillColor(titleBarBlack);
    menuBackLayer.setSize(150, currentWindowHeight);
    //Title Bar : for making title bar of a different color
    RectangleButton titleBar;
    titleBar.setPos(0, 0);
    titleBar.setSize(currentWindowWidth, 20);
    titleBar.setFillColor(titleBarBlack);
    //Loading the menu Font
    menuFont.loadFromFile("resources/fonts/arial.ttf");
    //Check if the font is correctly opened
    //Creating three dot Menu Buttons
    JString buttonStr;
    RectangleButton menuButton[8];
    for (i = 0; i <= 7; i++)
    {
        menuButton[i].setPos(0, 40 + 45 * i);
        menuButton[i].setSize(150, 40);
        menuButton[i].setFillColor(titleBarBlack);
        menuButton[i].setFont(menuFont);
        menuButton[i].setTextSize(20);
        menuButton[i].setTextColor(buttonTextColor);
        menuButton[i].setTextPos(40,40+45*i);
    }
    buttonStr = "File";
    menuButton[0].setText(buttonStr);
    buttonStr = "Edit";
    menuButton[1].setText(buttonStr);
    buttonStr = "View";
    menuButton[2].setText(buttonStr);
    buttonStr = "Open";
    menuButton[3].setText(buttonStr);
    buttonStr="Run";
    menuButton[4].setText(buttonStr);
    int menuButtonFlag[8];
    Vector2i draggingOffset;
    CircleButton logo;
    logo.setPos(currentWindowWidth / 2 - 10, 0);
    logo.setSize(10);
    logo.setTexture("resources/logo.png");
    //fileIcon
    RectangleButton fileIcon;
    fileIcon.setPos(5, 40);
    fileIcon.setSize(24, 24);
    fileIcon.setTexture("resources/file.png");
    RectangleButton fileIconB;
    fileIconB.setPos(5, 40);
    fileIconB.setSize(24, 24);
    fileIconB.setFillColor(buttonBlinker);
    //Settings Icon
    RectangleButton settingsIcon;
    settingsIcon.setPos(5, currentWindowHeight - 32);
    settingsIcon.setSize(24, 24);
    settingsIcon.setTexture("resources/settings.png");
    RectangleButton settingsIconB;
    settingsIconB.setPos(5, currentWindowHeight - 32);
    settingsIconB.setSize(24, 24);
    settingsIconB.setFillColor(buttonBlinker);
    //Edit Icon
    RectangleButton editIcon;
    editIcon.setPos(5, 85);
    editIcon.setSize(24, 24);
    editIcon.setTexture("resources/eraser.png");
    RectangleButton editIconB;
    editIconB.setPos(5, 85);
    editIconB.setSize(24, 24);
    editIconB.setFillColor(Color(200,200,200,3));
    RectangleButton viewIcon;
    viewIcon.setPos(5, 130);
    viewIcon.setSize(24, 24);
    viewIcon.setTexture("resources/telescope.png");
    RectangleButton viewIconB;
    viewIconB.setPos(5, 130);
    viewIconB.setSize(24, 24);
    viewIconB.setFillColor(buttonBlinker);
    RectangleButton openIcon;
    openIcon.setPos(5, 175);
    openIcon.setSize(24, 24);
    openIcon.setTexture("resources/package.png");
    RectangleButton openIconB;
    openIconB.setPos(5, 175);
    openIconB.setSize(24, 24);
    openIconB.setFillColor(buttonBlinker);
    fileIconB.blinkRectToggle(true);
    openIconB.blinkRectToggle(true);
    viewIconB.blinkRectToggle(true);
    editIconB.blinkRectToggle(true);
    settingsIconB.blinkRectToggle(true);
    RectangleButton runIcon;
    runIcon.setPos(5, 220);
    runIcon.setSize(24, 24);
    runIcon.setTexture("resources/run.png");
    RectangleButton runIconB;
    runIconB.setPos(5, 220);
    runIconB.setSize(24, 24);
    runIconB.setFillColor(buttonBlinker);
    runIconB.blinkRectToggle(true);
    while (window.isOpen())
    {
        Event event;
        //Event Handeling
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
                closeFlag = close.isClicked(event, window);
                maximizeFlag = maximize.isClicked(event, window);
                minimizeFlag = minimize.isClicked(event, window);
                menuFlag = menu.isClicked(event, window);
                fileFlag=fileIconB.isClicked(event,window);
                viewFlag=viewIconB.isClicked(event,window);
                editFlag=editIconB.isClicked(event,window);
                openFlag=openIconB.isClicked(event,window);
                settingsFlag=settingsIconB.isClicked(event,window);
                runFlag=runIconB.isClicked(event,window);
                mouseX = Mouse::getPosition(window).x;
                mouseY = Mouse::getPosition(window).y;
                for (i = 0; i <= 2; i++)
                    threeDots[i].isClicked(event, window);
                if (menuShown)
                {
                    for (i = 0; i <= 7; i++)
                        menuButtonFlag[i] = menuButton[i].isClicked(event, window);
                }
                if (mouseY < 20 && closeFlag == 0 && minimizeFlag == 0 && maximizeFlag == 0 && menuFlag == 0)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        dragged = 1;
                        draggingOffset = window.getPosition() - Mouse::getPosition();
                    }
                }
                break;
            case Event::MouseButtonReleased:
                if (event.mouseButton.button == Mouse::Left)
                {
                    dragged = 0;
                }
                break;
            case Event::MouseMoved:
                close.isClicked(event, window);
                maximize.isClicked(event, window);
                minimize.isClicked(event, window);
                menu.isClicked(event, window);
                fileIconB.isClicked(event,window);
                viewIconB.isClicked(event,window);
                editIconB.isClicked(event,window);
                openIconB.isClicked(event,window);
                settingsIconB.isClicked(event,window);
                runIconB.isClicked(event,window);
                for (i = 0; i <= 2; i++)
                    threeDots[i].isClicked(event, window);
                for (i = 0; i <= 7; i++)
                    menuButton[i].isClicked(event, window);
                if (menuShown)
                {
                    for (i = 0; i <= 7; i++)
                        menuButton[i].isClicked(event, window);
                }
                if (dragged == 1)
                {
                    window.setPosition(Mouse::getPosition() + draggingOffset);
                }
                break;
            }
        }
        // Updating the Scene
        if (closeFlag == 1)
        {
            window.close();
            closeFlag = 0;
        }
        else if (minimizeFlag == 1)
        {
            ShowWindow(windowHandle, SW_MINIMIZE);
            minimizeFlag = 0;
        }
        else if (maximizeFlag == 1)
        {
            if (currentWindowWidth == defaultWidth)
            {
                currentWindowHeight = screenHeight;
                currentWindowWidth = screenWidth;
                window.setSize(Vector2u(currentWindowWidth, currentWindowHeight));
                window.setPosition(Vector2i(0, 0));
                window.setView(fullscreenView);
                maximize.setPos(currentWindowWidth - 40, 4);
                minimize.setPos(currentWindowWidth - 60, 4);
                close.setPos(currentWindowWidth - 20, 4);
                for (i = 0; i <= 2; i++)
                    threeDots[i].setPos(5 + i * 10, 8);
                menuBackLayer.setSize(150, currentWindowHeight);
                logo.setPos(currentWindowWidth / 2 - 10, 0);
                titleBar.setSize(currentWindowWidth, 20);
                settingsIcon.setPos(5, currentWindowHeight - 32);
                settingsIconB.setPos(5, currentWindowHeight - 32);
            }
            else
            {
                window.setSize(Vector2u(defaultWidth, defaultHeight));
                window.setPosition(Vector2i(100, 100));
                window.setView(defaultView);
                currentWindowWidth = defaultWidth;
                currentWindowHeight = defaultHeight;
                maximize.setPos(currentWindowWidth - 40, 4);
                minimize.setPos(currentWindowWidth - 60, 4);
                close.setPos(currentWindowWidth - 20, 4);
                for (i = 0; i <= 2; i++)
                    threeDots[i].setPos(5 + i * 10, 8);
                menuBackLayer.setSize(150, currentWindowHeight);
                logo.setPos(currentWindowWidth / 2 - 10, 0);
                titleBar.setSize(currentWindowWidth, 20);
                settingsIcon.setPos(5, currentWindowHeight - 32);
                settingsIconB.setPos(5, currentWindowHeight - 32);
            }
            maximizeFlag = 0;
        }
        else if (menuFlag == 1)
        {
            if (menuShown)
                menuShown = false;
            else
                menuShown = true;
            menuFlag = 0;
        }
        if (menuShown)
        {
            if (menuButtonFlag[0] == 1)
            {
            }
            else if (menuButtonFlag[1] == 1)
            {
            }
            else if (menuButtonFlag[2] == 1)
            {
            }
            else if (menuButtonFlag[3] == 1)
            {
            }
            else if (menuButtonFlag[4] == 1)
            {
            }
            else if (menuButtonFlag[5] == 1)
            {
            }
            else if (menuButtonFlag[6] == 1)
            {
            }
            else if (menuButtonFlag[7] == 1)
            {
            }
        }
        //Clearing the old Scene
        window.clear(backgroundBlack);
        //window draw calls
        titleBar.draw(window);
        minimize.draw(window);
        maximize.draw(window);
        close.draw(window);
        menu.draw(window);
        logo.draw(window);
        if (menuShown)
        {
            menuBackLayer.draw(window);
            for (i = 0; i <= 7; i++)
                menuButton[i].draw(window);
        }
        for (i = 0; i <= 2; i++)
            threeDots[i].draw(window);
            
        fileIcon.draw(window);
        settingsIcon.draw(window);
        editIcon.draw(window);
        viewIcon.draw(window);
        openIcon.draw(window);
        runIcon.draw(window);
        fileIconB.draw(window);
        settingsIconB.draw(window);
        editIconB.draw(window);
        viewIconB.draw(window);
        openIconB.draw(window);
        runIconB.draw(window);
        //Displaying the content
        window.display();
    }
    return 0;
}