/*
  * This is a basic boilplate for the m5stack cardputer
  * Author: limemangler 
  * Github: https:github.com/limemangler/bp-app
  * 
  * date: July 5, 2025
  * Version: 1.0
  *
  * FEATURES:
  * + basic loading to cardputer device
  * + basic setup 
  * + basic loop
  * + splash screen with basic text
  * + prepopulated, basic menu on welcome screen
  * + documented code for quick customizing
  * + beginner friendly
*/

// These libraries must be included to run this basic app on a cardputer
#include "M5Cardputer.h" // compatible with esp-32 architecture 
#include "M5GFX.h" // graphics library

// -------- //

// adds the  canvas variable 
M5Canvas canvas(&M5Cardputer.Display);

bool showMenu = false;
bool showSplash = true;
unsigned long splashStartTime = 0;


// Splash screen
void drawSplash() {
    // Fill background with COLOR
    canvas.fillSprite(0x0451); //TFT_DARKCYAN2 0x0451
    
    // Draw "text" in big COLOR font
    canvas.setTextDatum(middle_center);
    canvas.setTextSize(1.75);
    canvas.setTextColor(0x18CE);  // TFT_MIDNIGHTBLUE 0x18CE
    canvas.drawString("BOILERPLATE", canvas.width() / 2, canvas.height() / 2 - 20);
    
    // Draw GitHub URL in small COLOR font
    canvas.setTextSize(1);
    canvas.setTextColor(0x07E0);  // TFT_LIME 0x07E0
    canvas.drawString("by limemangler", canvas.width() / 2, canvas.height() / 2 + 30);
    //github.com/limemangler

    // Draw version number in COLOR or 0x0000
    canvas.setTextSize(0.75);
    canvas.setTextColor(0xFFD9); // TFT_LEMONCHIFFON  0xFFD9
    canvas.drawString("Version 0.1", canvas.width() / 2, canvas.height() / 2 + 50);
    
    canvas.pushSprite(0, 0);
}


// MENU UI
void drawMenu() {
  canvas.fillSprite(RED);
  canvas.setTextColor(WHITE);
  canvas.setTextDatum(top_left);
  canvas.setTextSize(1);
  int y = 10;

  canvas.drawString("[I] Input text", 10, y); y += 18;
  canvas.drawString("[B] Back to splash screen", 10, y); y += 18;

  canvas.pushSprite(0,0);
 
}

// Main UI

void drawUI() {
  canvas.fillSprite(BLACK);
  canvas.setTextColor(YELLOW);
  canvas.setTextDatum(top_left);
  canvas.setTextSize(1);

  canvas.pushSprite(0,0);
}


// * this is the setup which will initialize all the stuff we do in the loop -- 
// * setup runs ONLY ONCE, when the app is first initialized 
// * and will not run again until restart 
void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);

    canvas.setColorDepth(8);
    canvas.setTextFont(&fonts::FreeMonoOblique9pt7b);
    canvas.createSprite(240, 135);
    canvas.setTextSize(1);
    canvas.setTextScroll(false);
    canvas.setTextWrap(true);

    splashStartTime = millis();
    drawSplash();
}


// * this is the loop, where we will add functionality
// * this loop will run continuously while the app is running
void loop() {
  M5Cardputer.update();

  // splash screen timeout 3 seconds
  if (showSplash && millis() - splashStartTime > 3000) {
    showSplash = false;
    drawMenu();
  }

  if (showSplash) {
    // Skip any other steps while the Splash is active
    delay(100);
    return;
  }

  if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
    auto keys = M5Cardputer.Keyboard.keysState();

    if (showMenu) {
      showMenu = false;
      return;
    }

    bool recognized = false;

    for (auto c : keys.word) {
      if (c == 'I' || c == 'i') {
        // go to text input screen
        drawUI(); recognized = true;
      } else if (c == 'B' || c == 'b') {
        // go back to splash screen
        drawSplash(); recognized = true;
      }
    }
    if (!recognized) {
      showSplash = true;
      drawMenu();
    }
  }

}