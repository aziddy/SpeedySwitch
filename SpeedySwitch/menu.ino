

  uint8_t cursor_pos_state = 0;
  uint8_t cursor_pos_y[] = {20, 30};

  boolean blinkSelectorStateOn = true;
  unsigned long blinkSelectorLastTime = 0;

  
  unsigned long buttonHoldStartTime = 0;
  unsigned long buttonHoldDeltaTime = 0;
  boolean holdCompleted = false;
  int holdIndicatorHeight = 0;
  
  static void menu_init(){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
  
    display.setCursor(25, 0);
    display.println(F("Speedy Switch!"));
  
    display.setTextSize(1);
    display.setCursor(105, 37);
    display.println(F("By:"));
    display.setCursor(95, 47);
    display.println(F("Ziddy"));
    display.setCursor(95, 57);
    display.println(F("Makes"));

    display.setCursor(15, 20);
    display.println(F("CLICK RACE"));
    display.setCursor(15, 30);
    display.println(F("FREE CLICK")); 

    display.setCursor(0, 47);
    display.println(F("Highscore:"));
    display.setCursor(15, 57);
    display.println(highscore);
    
  }

  static void menu_display(){
    display.setTextSize(1);
    toggleBlinkSelector();
    holdIndicator(10, 10);
    display.display();
  }

  static void toggleBlinkSelector(){
    if((elaspedTime - blinkSelectorLastTime) > 500){
      if(!blinkSelectorStateOn){
        blinkSelectorStateOn = true;
      } else {
        blinkSelectorStateOn = false;
      }
      blinkSelectorLastTime = elaspedTime;
    }

    if(blinkSelectorStateOn){
      display.drawChar(75, cursor_pos_y[cursor_pos_state],'<', WHITE, 0, 1);
      display.drawChar(7, cursor_pos_y[cursor_pos_state], '>', WHITE, 0, 1);
    }
    
  }
  
  static void holdIndicator(int holdIndicatorBoxX, int holdIndicatorBoxY){

    if(button_state){
      if(!button_latched){
        buttonHoldStartTime = elaspedTime;
      }
      button_latched = true;  

      buttonHoldDeltaTime = elaspedTime - buttonHoldStartTime;

      if(buttonHoldDeltaTime > 200){
        if(!holdCompleted){
          holdIndicatorHeight = round(buttonHoldDeltaTime/80);
    
          display.fillRect(holdIndicatorBoxX, holdIndicatorBoxY, 5, 10-holdIndicatorHeight, WHITE);
    
          if(holdIndicatorHeight > 9){
            cursor_pos_state++;
            if(cursor_pos_state > 1){
              cursor_pos_state = 0;
            }
            holdIndicatorHeight = 0;
            buttonHoldStartTime = elaspedTime;
            holdCompleted = true;
          }
        }
    }
      
    } else {

     if(button_latched && (buttonHoldDeltaTime < 200)){
        consoleState = 1;
      }
      
      holdCompleted = false;
      button_latched = false;
    }
  }
  

  static void menu_input_handle(){
    if(button_state){
      digitalWrite(LEDPIN, HIGH);
    } else {
      digitalWrite(LEDPIN, LOW);
    }
  }
