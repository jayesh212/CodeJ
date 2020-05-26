#ifndef __$$_NOTEGLOBALVARIABLES_H
#define __$$_NOTEGLOBALVARIABLES_H 7
#define DSCREENWIDTH 800
#define DSCREENHEIGHT 600
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define DELETE_T 8
#define ENTER 13
#define COPY 3
#define PASTE 22 //previously 16
#define SAVE 19
#define SELECTALL 1
#define UNDO 26
#define CUT 24
#define TAB 9
#define NEWFILE 100
#define OPEN 101
#define EXIT 102
#define SAVEAS 103
#define NOTHINGSELECTED 104
#define ABOUT 105
#define HELP 106
#define WORDWRAP 107
#define CHANGEFONT 108
#define ZOOMIN 109
#define ZOOMOUT 110
#define STATUSBAR 111
#define NEWWINDOW 112
//Define these using unicode
#define FIND 154    //Ctrl+F
#define REPLACE 564 //Ctrl+R
#define SCREENSHOT 113
int screenWidth;
int screenHeight;
int currentWindowWidth;
int currentWindowHeight;
sf::Font Textfont;
sf::Font menuFont;
sf::Color titleBarBlack(27,27,27);
sf::Color backgroundBlack(32,32,32);
sf::Color titleBarBlackTransparent(27,27,27,5);
sf::Color backgroundBlackTransparent(32,32,32,3);
sf::Color buttonBlinker(200,200,200,3);
sf::Color buttonTextColor(100,100,100);
sf::Color threeDotsColor(160,160,160);
sf::Color closeColor(170,0,0);
sf::Color minimizeColor(170,170,0);
sf::Color maximizeColor(0,160,0);
const int defaultWidth=800;
const int defaultHeight=600;
#endif