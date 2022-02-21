#include <FastLED.h>
#define NUM_LEDS 900 
#define VOLTAGE_LEDS 5
#define MAX_mAMPS_LEDS 24000
#define DATA_PIN D4
CRGB leds[NUM_LEDS];

namespace lighteffects{

  void setupFastleds(){
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTAGE_LEDS,MAX_mAMPS_LEDS);
  }
  
 void setZoneLighting(int start, int end,CRGB zonecolors,bool showChange){
    for(int i=start; i<end;i++){
      leds[i]=zonecolors;
    }
    if(showChange){ 
        FastLED.show();
        FastLED.show();
    }
  }

  void windowZoneLights(int numberofLights, CRGB desiredColor){
    setZoneLighting(28,28+numberofLights,desiredColor,false);
    setZoneLighting(873-numberofLights,873,desiredColor,true);
    FastLED.show();
  }


  int lightsnake(int head, int snakesize, CRGB snakecolor ){
    leds[head]=snakecolor;
    if(head<snakesize){ leds[NUM_LEDS-snakesize+head]=CRGB::Black;
    }else{ leds[head-snakesize]=CRGB::Black;  }
    head=(head+1)%NUM_LEDS;
    return head;
  }
}
