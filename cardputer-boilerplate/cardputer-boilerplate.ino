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
bool menuInput = false;
bool showSplash = false;
bool showTextInput = false;

// String data = "> ";
// unsigned long splashStartTime = 0;


// Splash screen
void drawSplash() {
  M5Cardputer.update();
  M5Cardputer.Display.clear();

  showMenu = false;
  showSplash = true;
  showTextInput = false;

  M5Cardputer.Display.setRotation(1);

  canvas.setColorDepth(8);
  canvas.setTextFont(&fonts::FreeMonoOblique9pt7b);
  canvas.createSprite(240, 135);
  canvas.setTextSize(1);
  canvas.setTextScroll(false);
  canvas.setTextWrap(true);

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
  delay(5000);
  drawMenu();
  // drawUI();
}


// check for menu input
void drawMenu(){
  M5Cardputer.update();
  M5Cardputer.Display.clear();

  showMenu = true;
  menuInput = true;
  showSplash = false;
  showTextInput = false;

  canvas.fillSprite(BLACK);
  canvas.setTextColor(WHITE);
  canvas.setTextDatum(top_left);
  canvas.setTextScroll(false);
  canvas.setTextWrap(true);
  canvas.setTextSize(1);
  int y = 10;

  canvas.drawString("[I] Input text", 10, y); y += 18;
  canvas.drawString("[B] Back to splash screen", 10, y); y += 18;

  canvas.pushSprite(0,0);

  bool listening = true;

  while (listening) {
    M5Cardputer.update();
    // Serial.println("first");
    if (M5Cardputer.Keyboard.isChange()) {
      if (M5Cardputer.Keyboard.isPressed()) {
          Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
      
        bool recognized = false;

        for (auto c : status.word) {
          if (c == 'I' || c == 'i') {
          Serial.println("input");

            // go to text input screen
            drawUI(); recognized = true; showMenu = false; menuInput = false; listening = false;
            return;
          } else if (c == 'B' || c == 'b') {
          Serial.println("input");

            // go back to splash screen
            drawSplash(); recognized = true; showMenu = false; menuInput = false; listening = false;
            return;
          } 
        }
        if (!recognized) {
          showMenu = true; menuInput = true;
          drawMenu();
        } 
        return;
      }    
      // canvas.pushSprite(0,0);
      // return;
    }
  }
    canvas.pushSprite(0,0);
    Serial.println("here");
}
// Main UI

void drawUI() {
  // canvas.fillSprite(BLACK);
  // canvas.setTextColor(YELLOW);
  // canvas.setTextDatum(top_left);
  // canvas.setTextSize(1);

  // canvas.pushSprite(0,0);
  M5Cardputer.update();
  M5Cardputer.Display.clear();

  String data = "> ";
  showMenu = false;
  showSplash = false;
  showTextInput = true;
  
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setTextSize(0.5);
  M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(),
                                M5Cardputer.Display.height() - 28, GREEN);
  M5Cardputer.Display.setTextFont(&fonts::FreeSerifBoldItalic18pt7b);

  M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4,
                                M5Cardputer.Display.width(), 4, GREEN);

  canvas.setTextFont(&fonts::FreeSerifBoldItalic18pt7b);
  canvas.setTextSize(0.5);
  canvas.createSprite(M5Cardputer.Display.width() - 8,
                      M5Cardputer.Display.height() - 36);
  canvas.setTextScroll(true);
  canvas.println("Press Key and Enter to Input Text");
  canvas.pushSprite(4, 4);
  M5Cardputer.Display.drawString(data, 4, M5Cardputer.Display.height() - 24);

  while (true) {
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
            for (auto i : status.word) {
                data += i;
                Serial.println(data);
            }

            if (status.del) {
                data.remove(data.length() - 1);
                Serial.println(data);
            }

            if (status.enter) {
                data.remove(0, 2);
                canvas.println(data);
                canvas.pushSprite(4, 4);
                data = "> ";
                Serial.println(data);
                // break;
            }

            M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 28, M5Cardputer.Display.width(), 25, BLACK);

            M5Cardputer.Display.drawString(data, 4, M5Cardputer.Display.height() - 24);
        }
    }
  }
  return;
}


// * this is the setup which will initialize all the stuff we do in the loop -- 
// * setup runs ONLY ONCE, when the app is first initialized 
// * and will not run again until restart 
void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  Serial.begin(9600);
  M5Cardputer.update();
  M5Cardputer.Display.setRotation(1);

  canvas.setColorDepth(8);
  canvas.setTextFont(&fonts::FreeMonoOblique9pt7b);
  canvas.createSprite(240, 135);
  canvas.setTextSize(1);
  canvas.setTextScroll(false);
  canvas.setTextWrap(true);

  drawSplash();
  
}


// * this is the loop, where we will add functionality
// * this loop will run continuously while the app is running
// * in a larger app with multi functions you may want to leave this empty
void loop() {

}