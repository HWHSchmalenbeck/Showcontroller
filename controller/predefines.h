// Pre-defines

void activatePartyMode();
void blinkError();
void checkConnector();
void checkForBtnActive();
void checkTime();
void communicationUtil();
void display_startup();
void displayClock(int digit, char number);
void displayStatus();
void enableCrisis();
uint16_t getLCDColor(char status);
void handleComLedDisableBtn();
void handleCrisisBtn();
void handleDebugInterfaceInputs(char input);
void handleHomeBtn();
void handleNavEnterBtn();
void handleNavLeftBtn();
void handleNavRightBtn();
void handlePageBtn();
void handleSelection(char act, int dir = 0);
void handleStartBtn();
void lampTest(bool mode);
void renderButtonPage(int number);
void renderCreditsPage();
void renderDebugPage();
void renderHome();
void renderHomeStatus();
bool renderMessage(char msgid, int severity, char activator = '0');
void renderSelection(int id, bool negative = false);
void renderSettingsPage();
void resetStatus();
void sendDebugInterfacePage();
void sendSerialMessage(String msg);
void setComLED(String led);
void setStatusLEDColor();
void startShow();
void statusCheck();
void renderSettingsShowTypes();