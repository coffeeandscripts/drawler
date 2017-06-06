// windows.h
// version 0.0.1
// classes and functions for window creation and management

#ifndef WINDOWS_H
#define WINDOWS_H

// CLASSES

class WindowData {
    public:
        void setValues(int r, int c, int cr, int cc) {
            rows = r;
            columns = c;
            currentRow = cr;
            currentColumn = cc;
        }
        int returnCurrentRow() {
            return currentRow;
        }
        void incrementRow() {
            if (currentRow < rows) {
                currentRow += 1;
            }
        }
        void decrementRow() {
            if (currentRow > 1) {
                currentRow -= 1;
            }
        }
        WindowData();
    protected:
    int rows;
    int columns;
    int currentRow;
    int currentColumn;
};

class Screen {
    public:
    int escapeCall;
    int height;
    int width;
    int userScreen;
    /* 1 - Home
     * 2 - Characters
     * 3 - Game
     * 4 - Menu
     * 5 - Load
     */
    WINDOW * mainWindow;
    WindowData * mainWindowData;
    WINDOW * gameWindow;
    WindowData * gameWindowData;
    WINDOW * splashWindow;
    int lastKey;
};

// FUNCTIONS

// gets the screen size
void getScreenSize(Screen * scr);
WINDOW * openMainWindow(Screen * scr);
WINDOW * openGameWindow(Screen * scr);
WINDOW * openSplashWindow(Screen * scr);
void drawMainWindow(Screen * scr);
void updateScreen(Screen * scr);

#endif
