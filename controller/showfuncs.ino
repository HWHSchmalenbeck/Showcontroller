void statusCheck()
{
    if (millis() - timeSinceReset <= minTimeSinceReset)
    {
        return;
    }
    String allIds = "";
    bool hasFailure = false;
    bool hasCrisis = false;
    int areaTwoBtns = 0;
    int areaTwoBypassBtns = 0;
    for (int i = 0; i <= 3; i++)
    {
        allIds = allIds + String(portids[i]);
    }
    for (int i = 0; i <= (allIds.length() - 1); i++)
    {
        char gotStatus = btnStatus[allIds.charAt(i) - 'A'];
        if (gotStatus == 'c' && millis() - lastCrisisDisable >= minCrisisDisable)
        {
            hasCrisis = true;
            break;
        }
        else if (gotStatus == 'd' || gotStatus == 'e')
        {
            hasFailure = true;
        }
    }

    if (btnStatus[arealinking[0] - 'A'] == 'n')
    {
        area_one_reconnect = true;
    }
    else if (btnStatus[arealinking[0] - 'A'] != 'n' && area_one_reconnect == true)
    {
        sent_area_one_blink = false;
    }
    if (btnStatus[arealinking[1] - 'A'] == 'n')
    {
        area_two_reconnect = true;
    }
    else if (btnStatus[arealinking[1] - 'A'] != 'n' && area_two_reconnect == true)
    {
        sent_area_two_blink = false;
    }

    if ((btnStatus[arealinking[2] - 'A'] == 'n' && btnBypass[2] == false) ||
        (btnStatus[arealinking[3] - 'A'] == 'n' && btnBypass[3] == false) ||
        (btnStatus[arealinking[4] - 'A'] == 'n' && btnBypass[4] == false))
    {
        btn_pressed_reconnect = true;
    }
    else if ((btnStatus[arealinking[2] - 'A'] != 'n' || btnBypass[2] == true) &&
             (btnStatus[arealinking[3] - 'A'] != 'n' || btnBypass[2] == true) &&
             (btnStatus[arealinking[4] - 'A'] != 'n' || btnBypass[2] == true) &&
             btn_pressed_reconnect == true)
    {
        sent_btn_pressed_blink = false;
    }

    if (btnStatus[arealinking[2] - 'A'] == 'b')
    {
        areaTwoBtns += 1;
    }
    if (btnBypass[2] == true)
    {
        areaTwoBypassBtns += 1;
    }

    if (btnStatus[arealinking[3] - 'A'] == 'b')
    {
        areaTwoBtns += 1;
    }
    if (btnBypass[3] == true)
    {
        areaTwoBypassBtns += 1;
    }

    if (btnStatus[arealinking[4] - 'A'] == 'b')
    {
        areaTwoBtns += 1;
    }
    if (btnBypass[4] == true)
    {
        areaTwoBypassBtns += 1;
    }

    if (btnStatus[arealinking[5] - 'A'] == 'b')
    {
        areaTwoBtns += 1;
    }
    if (btnBypass[5] == true)
    {
        areaTwoBypassBtns += 1;
    }

    if (hasCrisis == false && controllerStatus != 'c')
    {
        // Area 1

        if (btnStatus[arealinking[0] - 'A'] == 'b' && witchEmpty == true && millis() - witch_status_sent_millis >= 2000 && btnStatus[arealinking[1] - 'A'] != 'b' && sent_area_two_blink == false)
        {
            sent_area_two_blink = true;
            witch_status_sent_millis = millis();
            for (int i = 0; i <= 3; i++)
            {
                if (portids[i].indexOf(arealinking[1]) != -1)
                {
                    curPort.end();
                    waitingForAnswer = false;
                    if (i == 0)
                    {
                        curPort = serialPortOne;
                    }
                    else if (i == 1)
                    {
                        curPort = serialPortTwo;
                    }
                    else if (i == 2)
                    {
                        curPort = serialPortThree;
                    }
                    else if (i == 3)
                    {
                        curPort = serialPortFour;
                    }

                    setComLED("tx");
                    curPort.begin(9600);
                    curPort.print(arealinking[1]);
                    curPort.print('b');
                    break;
                }
            }
        }
        else if (btnStatus[arealinking[0] - 'A'] != 'b' && witchEmpty == true && millis() - witch_status_sent_millis >= 2000 && btnStatus[arealinking[1] - 'A'] != 'b' && sent_area_one_blink == false)
        {
            witch_status_sent_millis = millis();
            sent_area_one_blink = true;
            sent_area_two_blink = false;
            for (int i = 0; i <= 3; i++)
            {
                if (portids[i].indexOf(arealinking[0]) != -1)
                {
                    curPort.end();
                    waitingForAnswer = false;
                    if (i == 0)
                    {
                        curPort = serialPortOne;
                    }
                    else if (i == 1)
                    {
                        curPort = serialPortTwo;
                    }
                    else if (i == 2)
                    {
                        curPort = serialPortThree;
                    }
                    else if (i == 3)
                    {
                        curPort = serialPortFour;
                    }

                    setComLED("tx");
                    curPort.begin(9600);
                    curPort.print(arealinking[0]);
                    curPort.print('b');
                    break;
                }
            }
        }

        if (btnStatus[arealinking[0] - 'A'] == 'b' && btnStatus[arealinking[1] - 'A'] == 'b' && witchEmpty == true)
        {
            if (witch_wait_millis == 0)
            {
                witch_wait_millis = millis();
            }

            if (millis() - witch_wait_millis >= 10000)
            {
                witch_wait_millis = 0;
                witchEmpty = false;
                sent_area_one_blink = false;
                sent_area_two_blink = false;
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
        }

        // Area 2

        if ((areaTwoBtns + areaTwoBypassBtns) == 4)
        {
            startShow();
        }
        else if (areaTwoBtns >= 1 && areaTwoBtns <= 3 && millis() - lastBtnSentAction >= minLastBtnSentAction && sent_btn_pressed_blink == false)
        {
            sent_btn_pressed_blink = true;
            lastBtnSentAction = millis();
            controllerStatus = 'b';
            for (int i = 2; i <= 5; i++)
            {
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
                        curPort.print('b');
                        break;
                    }
                }
            }
        }
    }

    if (hasFailure == true && controllerStatus != 'c')
    {
        controllerStatus = 'f';
    }
    else if (hasFailure == false && controllerStatus == 'f')
    {
        controllerStatus = 'a';
    }

    if (hasCrisis == true)
    {
        enableCrisis();
    }
}
