// Page btn
void handlePageBtn()
{
    if (curPage == -4)
    {
        if (page_btn_debug == true)
        {
            return;
        }
        page_btn_debug = true;
        tft.fillRect(270, 88, 20, 20, LCD_GREEN);
        return;
    }
    if (curPage < -1 || curPage == 5)
    {
        curPage = -1;
        renderHome();
        return;
    }
    curPage += 1;
    renderButtonPage(curPage);
    return;
}

// Home btn
void handleHomeBtn()
{
    if (curPage == -4)
    {
        if (digitalRead(page_btn) == HIGH)
        {
            activatePartyMode();
        }
        if (home_btn_debug == true)
        {
            return;
        }
        home_btn_debug = true;
        tft.fillRect(270, 68, 20, 20, LCD_GREEN);
        return;
    }
    if (curPage == -1)
    {
        curPage = -2;
        renderSettingsPage();
        return;
    }
    curPage = -1;
    renderHome();
    return;
}

// Nav right btn
void handleNavRightBtn()
{
    if (curPage == -4)
    {
        if (digitalRead(nav_enter_btn) == HIGH && digitalRead(nav_left_btn) == HIGH)
        {
            // Make buttons glow again
            digitalWrite(start_green, HIGH);
            digitalWrite(crisis_red, HIGH);
            rxLEDState = false;
            txLEDState = false;
            curPage = -1;
            renderHome();
            return;
        }
        if (nav_left_btn_debug == true)
        {
            return;
        }
        nav_right_btn_debug = true;
        tft.fillRect(270, 148, 20, 20, LCD_GREEN);
        return;
    }
    handleSelection('m', 1);
    return;
}

// Nav enter btn
void handleNavEnterBtn()
{
    if (curPage == -4)
    {
        if (nav_enter_btn_debug == true)
        {
            return;
        }
        nav_enter_btn_debug = true;
        tft.fillRect(270, 128, 20, 20, LCD_GREEN);
        return;
    }
    handleSelection('u');
    return;
}

// Nav left btn
void handleNavLeftBtn()
{
    if (curPage == -4)
    {
        if (nav_left_btn_debug == true)
        {
            return;
        }
        nav_left_btn_debug = true;
        tft.fillRect(270, 108, 20, 20, LCD_GREEN);
        return;
    }
    handleSelection('m', -1);
    return;
}

// Com led disable btn
void handleComLedDisableBtn()
{
    if (curPage == -4)
    {
        if (com_led_disable_btn_debug == true)
        {
            return;
        }
        lampTest(true);
        com_led_disable_btn_debug = true;
        tft.fillRect(270, 208, 20, 20, LCD_GREEN);
        return;
    }
    if (comLEDDisabled == true)
    {
        comLEDDisabled = false;
    }
    else
    {
        comLEDDisabled = true;
    }
    return;
}

// Start btn
void handleStartBtn()
{
    if (curPage == -4)
    {
        if (digitalRead(crisis_btn) == HIGH)
        {
            witchEmpty = false;
            for (int i = 0; i <= 1; i++)
            {
                btnStatus[arealinking[i] - 'A'] = 'a';
                for (int j = 0; j <= 3; j++)
                {
                    if (portids[j].indexOf(arealinking[i]) != -1)
                    {
                        curPort.end();
                        waitingForAnswer = false;
                        if (j == 0)
                        {
                            curPort = serialPortOne;
                        }
                        else if (j == 1)
                        {
                            curPort = serialPortTwo;
                        }
                        else if (j == 2)
                        {
                            curPort = serialPortThree;
                        }
                        else if (j == 3)
                        {
                            curPort = serialPortFour;
                        }

                        setComLED("tx");
                        curPort.begin(9600);
                        curPort.print(arealinking[i]);
                        curPort.print('s');
                        break;
                    }
                }
            }
        }
        if (digitalRead(nav_left_btn) == HIGH)
        {
            witchEmpty = true;
            sent_area_one_blink = false;
            sent_area_two_blink = false;
        }
        if (start_btn_debug == true)
        {
            return;
        }
        start_btn_debug = true;
        tft.fillRect(270, 188, 20, 20, LCD_GREEN);
        return;
    }

    startShow();
}

// Crisis btn
void handleCrisisBtn()
{
    if (curPage == -4)
    {
        if (crisis_btn_debug == true)
        {
            return;
        }
        crisis_btn_debug = true;
        tft.fillRect(270, 168, 20, 20, LCD_GREEN);
        return;
    }

    if (controllerStatus == 'c')
    {
        resetStatus();
    }
    else
    {
        enableCrisis();
        ;
    }
}

// Check btns
void checkForBtnActive()
{
    if (digitalRead(page_btn) == HIGH && (page_btn_millis == 0 || millis() - page_btn_millis >= 500))
    {
        page_btn_millis = millis();
        handlePageBtn();
    }

    if (digitalRead(home_btn) == HIGH && (home_btn_millis == 0 || millis() - home_btn_millis >= 500))
    {
        home_btn_millis = millis();
        handleHomeBtn();
    }

    if (digitalRead(nav_right_btn) == HIGH && (nav_right_btn_millis == 0 || millis() - nav_right_btn_millis >= 500))
    {
        nav_right_btn_millis = millis();
        handleNavRightBtn();
    }

    if (digitalRead(nav_enter_btn) == HIGH && (nav_enter_btn_millis == 0 || millis() - nav_enter_btn_millis >= 500))
    {
        nav_enter_btn_millis = millis();
        handleNavEnterBtn();
    }

    if (digitalRead(nav_left_btn) == HIGH && (nav_left_btn_millis == 0 || millis() - nav_left_btn_millis >= 500))
    {
        nav_left_btn_millis = millis();
        handleNavLeftBtn();
    }

    if (digitalRead(com_led_disable_btn) == HIGH && (com_led_disable_btn_millis == 0 || millis() - com_led_disable_btn_millis >= 500))
    {
        com_led_disable_btn_millis = millis();
        handleComLedDisableBtn();
    }

    if (digitalRead(start_btn) == HIGH && (start_btn_millis == 0 || millis() - start_btn_millis >= 1000))
    {
        start_btn_millis = millis();
        handleStartBtn();
    }

    if (digitalRead(crisis_btn) == HIGH && (crisis_btn_millis == 0 || millis() - crisis_btn_millis >= 1000))
    {
        crisis_btn_millis = millis();
        handleCrisisBtn();
    }

    // Debug page handling

    if (curPage == -4)
    {
        if (digitalRead(page_btn) == LOW)
        {
            if (page_btn_debug == true)
            {
                page_btn_debug = false;
                tft.fillRect(270, 88, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(home_btn) == LOW)
        {
            if (home_btn_debug == true)
            {
                home_btn_debug = false;
                tft.fillRect(270, 68, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(nav_right_btn) == LOW)
        {
            if (nav_right_btn_debug == true)
            {
                nav_right_btn_debug = false;
                tft.fillRect(270, 148, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(nav_enter_btn) == LOW)
        {
            if (nav_enter_btn_debug == true)
            {
                nav_enter_btn_debug = false;
                tft.fillRect(270, 128, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(nav_left_btn) == LOW)
        {
            if (nav_left_btn_debug == true)
            {
                nav_left_btn_debug = false;
                tft.fillRect(270, 108, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(com_led_disable_btn) == LOW)
        {
            if (com_led_disable_btn_debug == true)
            {
                com_led_disable_btn_debug = false;
                tft.fillRect(270, 208, 20, 20, LCD_RED);
                lampTest(false);
            }
        }

        if (digitalRead(start_btn) == LOW)
        {
            if (start_btn_debug == true)
            {
                start_btn_debug = false;
                tft.fillRect(270, 188, 20, 20, LCD_RED);
            }
        }

        if (digitalRead(crisis_btn) == LOW)
        {
            if (crisis_btn_debug == true)
            {
                crisis_btn_debug = false;
                tft.fillRect(270, 168, 20, 20, LCD_RED);
            }
        }
    }
    return;
}


