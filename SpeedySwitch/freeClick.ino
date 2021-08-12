

boolean freeClickInit(){
  
}

uint16_t free_click_mode_clicks = 0;
unsigned long elaspedTimeSinceFreeClickStart = elaspedTime;

void free_click_mode(){
  if(button_state){
    if(!button_latched){
       free_click_mode_clicks++;
    }
    button_latched = true;
  } else {
    button_latched = false;
  }

  display.setTextSize(3);
  display.setTextColor(WHITE);

  display.setCursor(40, 20);
  display.println(free_click_mode_clicks);
  render_free_click_elasped_time();
  holdIndicator(10,10);
  display.display();
}


void render_free_click_elasped_time(){
    display.setTextSize(2);
    display.setCursor(80, 30);
    display.println(round((elaspedTime - elaspedTimeSinceFreeClickStart)/1000));
}
