/*
 *
 *  Display startup
 *
*/

void display_startup()
{

    // Fill screen with Black
    tft.fillScreen(LCD_BLACK);

    // Draw Logo body
    tft.drawBitmap(110, 10, logobody, 110, 159, LCD_WHITE);

    // Draw Left eye
    tft.drawBitmap(149, 53, logoeye, 6, 6, LCD_BLUE);

    // Draw Right eye
    tft.drawBitmap(179, 53, logoeye, 6, 6, LCD_PINK);

    // Text
    tft.setCursor(127, 180);
    tft.setTextSize(3);
    tft.setTextColor(LCD_WHITE);
    tft.print("HWHS");
    tft.setCursor(40, 210);
    tft.print("Showcontroller");

    return;
}

/*
 *
 *  Handle Selection Function
 *
 *  act:
 *
 *  c   =>  Clear (Clear selection on new page reload) [Sets selection to -1]
 *  m   =>  Move (Move the current selection) [Increases or decreases the selection according to dir value]
 *  u   =>  Use (Run the current selections action)
 *
 */

void renderSelection(int id, bool negative = false)
{
    uint16_t selectionColor = LCD_RED;
    if (negative == true)
    {
        selectionColor = LCD_WHITE;
    }

    // Settings page

    if (curPage == -2)
    {
        switch (id)
        {
        case 1:
            tft.drawRect(59, 59, 202, 42, selectionColor);
            return;
        case 2:
            tft.drawRect(59, 109, 202, 42, selectionColor);
            return;
        case 3:
            tft.drawRect(59, 159, 202, 42, selectionColor);
            return;
        case 4:
            tft.drawRect(109, 209, 102, 22, selectionColor);
            return;
        }
    }
    else if (curPage == -1)
    {
        switch (id)
        {
        case 1:
            tft.drawRect(14, 19, 140, 28, selectionColor);
            return;
        case 2:
            tft.drawRect(169, 19, 140, 28, selectionColor);
            return;
        case 3:
            tft.drawRect(14, 75, 140, 28, selectionColor);
            return;
        case 4:
            tft.drawRect(169, 75, 140, 28, selectionColor);
            return;
        case 5:
            tft.drawRect(14, 131, 140, 28, selectionColor);
            return;
        case 6:
            tft.drawRect(169, 131, 140, 28, selectionColor);
            return;
        }
    }
    else if (curPage >= 0 && curPage <= 5)
    {
        switch (id)
        {
        case 1:
            tft.drawRect(4, 74, 152, 77, selectionColor);
            return;
        case 2:
            tft.drawRect(4, 159, 152, 77, selectionColor);
            return;
        case 3:
            tft.drawRect(164, 159, 152, 77, selectionColor);
            return;
        }
    }
}

/*
 *
 *  Display clock
 *
*/

void displayClock(int digit, char number)
{
    if (curPage != -1) {
        return;
    }
    tft.setTextSize(2);
    switch (digit)
    {
    case 0:
        tft.fillRect(228, 210, 10, 15, LCD_WHITE);
        tft.setCursor(228, 210);
        tft.print(String(number));
        break;
    case 1:
        tft.fillRect(240, 210, 10, 15, LCD_WHITE);
        tft.setCursor(240, 210);
        tft.print(String(number));
        // Change digit one
        break;
    case 2:
        tft.fillRect(252, 210, 10, 15, LCD_WHITE);
        tft.setCursor(252, 210);
        tft.print(String(number));
        // Change digit two
        break;
    case 3:
        tft.fillRect(272, 210, 10, 15, LCD_WHITE);
        tft.setCursor(272, 210);
        tft.print(String(number));
        // Change digit three
        break;
    case 4:
        tft.fillRect(284, 210, 10, 15, LCD_WHITE);
        tft.setCursor(284, 210);
        tft.print(String(number));
        // Change digit four
        break;
    }
    return;
}

/*
 *
 *  Display status
 *
*/

void displayStatus()
{
    String statusText = "";

    if (showRunningMillis == 0)
    {
        statusText = "Idle";
    }

    if (controllerStatus == 'f')
    {
        statusText = "Fault";
    }

    if (showRunningMillis != 0)
    {
        statusText = "Show running";
    }

    if (controllerStatus == 'c')
    {
        statusText = "Panik";
    }

    if (statusText != oldStatusText)
    {
        oldStatusText = statusText;
        // Clear current Status
        tft.fillRect(15, 210, 215, 25, LCD_WHITE);

        // Print new Status
        tft.setCursor(15, 210);
        tft.print(statusText);
    }

    return;
}

/*
 *
 *  Display home status
 *
*/

void renderHomeStatus()
{
    uint16_t areacolor;

    if (curPage != -1)
    {
        return;
    }

    // Top Left Status
    areacolor = getLCDColor(btnStatus[arealinking[0] - 'A']);
    tft.fillRect(15, 20, 26, 26, areacolor);

    if (curPage != -1)
    {
        return;
    }

    // Middle Left Status
    areacolor = getLCDColor(btnStatus[arealinking[2] - 'A']);
    tft.fillRect(15, 76, 26, 26, areacolor);

    if (curPage != -1)
    {
        return;
    }

    // Bottom Left Status
    areacolor = getLCDColor(btnStatus[arealinking[4] - 'A']);
    tft.fillRect(15, 132, 26, 26, areacolor);

    if (curPage != -1)
    {
        return;
    }

    // Top Right Status
    areacolor = getLCDColor(btnStatus[arealinking[1] - 'A']);
    tft.fillRect(170, 20, 26, 26, areacolor);

    if (curPage != -1)
    {
        return;
    }

    // Middle Right Status
    areacolor = getLCDColor(btnStatus[arealinking[3] - 'A']);
    tft.fillRect(170, 76, 26, 26, areacolor);

    if (curPage != -1)
    {
        return;
    }

    // Bottom Right Status
    areacolor = getLCDColor(btnStatus[arealinking[5] - 'A']);
    tft.fillRect(170, 132, 26, 26, areacolor);

    return;
}

/*
 *
 *  Render home
 *
*/

void renderHome()
{
    handleSelection('c');
    curPage = -1;
    // Fill screen with White
    tft.fillScreen(LCD_WHITE);

    // uint16_t areacolor;
    //  Top Left Status
    // areacolor = getcolor(btnStatus[arealinking[0] - 'A']);
    // tft.fillRect(15, 20, 26, 26, areacolor);
    tft.setCursor(52, 26);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[0]);

    // Middle Left Status
    // areacolor = getcolor(btnStatus[arealinking[2] - 'A']);
    // tft.fillRect(15, 76, 26, 26, areacolor);
    tft.setCursor(52, 82);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[2]);

    // Bottom Left Status
    // areacolor = getcolor(btnStatus[arealinking[4] - 'A']);
    // tft.fillRect(15, 132, 26, 26, areacolor);
    tft.setCursor(52, 138);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[4]);

    // Top Right Status
    // areacolor = getcolor(btnStatus[arealinking[1] - 'A']);
    // tft.fillRect(170, 20, 26, 26, areacolor);
    tft.setCursor(207, 26);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[1]);

    // Middle Right Status
    // areacolor = getcolor(btnStatus[arealinking[3] - 'A']);
    // tft.fillRect(170, 76, 26, 26, areacolor);
    tft.setCursor(207, 82);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[3]);

    // Bottom Right Status
    // areacolor = getcolor(btnStatus[arealinking[5] - 'A']);
    // tft.fillRect(170, 132, 26, 26, areacolor);
    tft.setCursor(207, 138);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[5]);

    renderHomeStatus();

    // Show Info Line
    tft.drawFastHLine(0, 190, 360, LCD_BLACK);
    tft.drawFastHLine(0, 191, 360, LCD_BLACK);
    tft.drawFastHLine(0, 192, 360, LCD_BLACK);

    // Show Status
    oldStatusText = "";
    displayStatus();

    // Show Run Duration
    displayClock(1, '0');
    displayClock(2, '0');
    tft.setCursor(262, 210);
    tft.print(":");
    displayClock(3, '0');
    displayClock(4, '0');

    return;
}

/*
 *
 *  Render button page
 *
*/

void renderButtonPage(int number)
{
    handleSelection('c');
    curPage = number;

    tft.fillScreen(LCD_WHITE);
    tft.setCursor(8, 8);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLACK);
    tft.print(areaname[number]);

    tft.drawRect(5, 75, 150, 75, LCD_BLACK);
    tft.setCursor(40, 105);
    tft.print("ID");
    tft.drawRect(78, 95, 32, 32, LCD_BLACK);
    tft.drawRect(79, 96, 30, 30, LCD_BLACK);
    tft.setCursor(89, 104);
    tft.setTextSize(2);
    tft.print(arealinking[number]);

    tft.drawRect(165, 75, 150, 75, LCD_BLACK);
    tft.setCursor(175, 105);
    tft.print("Status");
    tft.drawRect(258, 95, 32, 32, LCD_BLACK);
    tft.drawRect(259, 96, 30, 30, LCD_BLACK);
    tft.setCursor(269, 104);
    tft.setTextSize(2);
    tft.print(btnStatus[arealinking[number] - 'A']);

    tft.drawRect(5, 160, 150, 75, LCD_BLACK);
    tft.drawRect(19, 186, 27, 22, LCD_BLACK);
    if (btnBypass[number] == 1)
    {
        tft.fillRect(20, 187, 25, 20, LCD_GREEN);
    }
    else
    {
        tft.fillRect(20, 187, 25, 20, LCD_RED);
    }
    tft.setCursor(55, 190);
    tft.print("Bypass");

    tft.drawRect(165, 160, 150, 75, LCD_BLACK);
    tft.setCursor(192, 190);
    tft.print("Freigabe");

    return;
}

/*
 *
 *  Render settings page
 *
*/

void renderSettingsPage()
{
    handleSelection('c');
    tft.fillScreen(LCD_WHITE);
    tft.setCursor(90, 20);
    tft.setTextSize(3);
    tft.setTextColor(LCD_BLACK);
    tft.print("Settings");

    tft.setTextSize(2);

    tft.drawRect(60, 60, 200, 40, LCD_BLACK);
    tft.setCursor(118, 72);
    tft.print("Credits");

    tft.drawRect(60, 110, 200, 40, LCD_BLACK);
    tft.setCursor(131, 122);
    tft.print("Debug");

    tft.drawRect(60, 160, 200, 40, LCD_BLACK);
    tft.setCursor(97, 172);
    tft.print("Re-Discover");

    tft.drawRect(110, 210, 100, 20, LCD_BLACK);
    tft.setTextSize(1);
    tft.setCursor(125, 217);
    tft.print("Reset Status");
    return;
}

/*
 *
 *  Render credits page
 *
*/

void renderCreditsPage()
{
    handleSelection('c');
    tft.fillScreen(LCD_WHITE);
    tft.drawBitmap(5, 5, otto_small, 51, 50, LCD_BLACK);
    tft.drawBitmap(25, 19, eye_small, 3, 2, LCD_BLUE);
    tft.drawBitmap(34, 19, eye_small, 3, 2, LCD_PINK);
    /*
    tft.drawBitmap(5, 5, heart, 53, 53, LCD_RED);
    tft.drawBitmap(5, 5, heartout, 53, 53, LCD_BLACK);
    */

    tft.setCursor(75, 14);
    tft.setTextColor(LCD_ORANGE);
    tft.setTextSize(2);
    tft.print("HW");
    tft.setTextColor(LCD_BLACK);
    tft.print("HS Showcontroller");
    tft.setCursor(145, 34);
    tft.print("Credits");

    tft.setCursor(10, 70);
    tft.print("Coding:");

    tft.setCursor(170, 70);
    tft.setTextColor(LCD_BLUE);
    tft.print("Lo");
    tft.setTextColor(LCD_PINK);
    tft.print("is");

    tft.setCursor(10, 110);
    tft.setTextColor(LCD_BLACK);
    tft.print("Konstruktion:");

    tft.setCursor(170, 110);
    tft.setTextColor(LCD_GREEN);
    tft.print("Valentin");

    tft.setCursor(170, 130);
    tft.setTextColor(LCD_BLUE);
    tft.print("Lo");
    tft.setTextColor(LCD_PINK);
    tft.print("is");

    tft.setCursor(170, 150);
    tft.setTextColor(LCD_BLACK);
    tft.print("Timo");

    tft.setCursor(170, 170);
    tft.print("Christof");

    tft.setCursor(170, 190);
    tft.print("Steffen");

    tft.setTextSize(1);
    tft.setCursor(63, 226);
    tft.print("Holz gesponsert von Holzland Wulf");
    return;
}

/*
 *
 *  Render debug page
 *
*/

void renderDebugPage()
{
    handleSelection('c');

    page_btn_debug = false;
    home_btn_debug = false;
    nav_left_btn_debug = false;
    nav_enter_btn_debug = false;
    nav_right_btn_debug = false;
    com_led_disable_btn_debug = false;
    crisis_btn_debug = false;
    start_btn_debug = false;

    tft.fillScreen(LCD_WHITE);
    tft.setCursor(105, 5);
    tft.setTextSize(2);
    tft.setTextColor(LCD_BLUE);
    tft.print("Debug ");
    tft.setTextColor(LCD_PINK);
    tft.print("Page");

    tft.setCursor(60, 25);
    tft.setTextSize(1);
    tft.setTextColor(LCD_BLACK);
    tft.print("Zum ");
    tft.setTextColor(LCD_RED);
    tft.print("Verlassen");
    tft.setTextColor(LCD_BLACK);
    tft.print(": Left + Enter + Right");
    tft.setCursor(69, 35);
    tft.print("Activate ");
    tft.setTextColor(LCD_RED);
    tft.print("p");
    tft.setTextColor(LCD_YELLOW);
    tft.print("a");
    tft.setTextColor(LCD_GREEN);
    tft.print("r");
    tft.setTextColor(LCD_BLUE);
    tft.print("t");
    tft.setTextColor(LCD_PINK);
    tft.print("y");
    tft.setTextColor(LCD_BLACK);
    tft.print(" mode: Page + Home");
    tft.setCursor(4, 45);
    tft.print("WitchEmpty ");
    tft.setTextColor(LCD_RED);
    tft.print("false");
    tft.setTextColor(LCD_BLACK);
    tft.print(": Panik + Start / ");
    tft.setTextColor(LCD_GREEN);
    tft.print("true");
    tft.setTextColor(LCD_BLACK);
    tft.print(": Left + Start");
    tft.setCursor(104, 55);
    tft.print("Lamptest: Comdisable");

    tft.setCursor(10, 70);
    tft.setTextSize(2);
    tft.print("Buttons:");

    tft.setCursor(140, 70);
    tft.print("Home");
    tft.fillRect(270, 68, 20, 20, LCD_RED);

    tft.setCursor(140, 90);
    tft.print("Page");
    tft.fillRect(270, 88, 20, 20, LCD_RED);

    tft.setCursor(140, 110);
    tft.print("Left");
    tft.fillRect(270, 108, 20, 20, LCD_RED);

    tft.setCursor(140, 130);
    tft.print("Enter");
    tft.fillRect(270, 128, 20, 20, LCD_RED);

    tft.setCursor(140, 150);
    tft.print("Right");
    tft.fillRect(270, 148, 20, 20, LCD_RED);

    tft.setCursor(140, 170);
    tft.print("Panic");
    tft.fillRect(270, 168, 20, 20, LCD_RED);

    tft.setCursor(140, 190);
    tft.print("Start");
    tft.fillRect(270, 188, 20, 20, LCD_RED);

    tft.setCursor(140, 210);
    tft.print("Comdisable");
    tft.fillRect(270, 208, 20, 20, LCD_RED);
    return;
}

/*
 *
 *  Render quick select
 *
*/

void renderQuickSelect() {
    return;
}