#include <ESP8266WebServer.h>
// #include <perpareHTML.h>
#include <LittleFS.h>
#include <lighteffects.h>
ESP8266WebServer serverHTTP(80);

File file;
String htmlIndex;
String styleSheet;
String jsScript;

int maxMilliAmps = 2400;
int currentPerLamp = 20;

/*
todo change server calls to be start, end, color and showBool
ignore if the parameters are missing

*/

namespace myServerCommands{
    String retreiveFromFS(String filePath){
        LittleFS.begin();
        String myFileString;
        File file = LittleFS.open(filePath, "r");
        if (!file) {
            return "hey d00fus theres no such file "+filePath;
        } else{
            while(file.available()){
                myFileString += file.readString();
            };
            file.close();
            return myFileString;
        }
    }
    void setupPageResources(){
        styleSheet = retreiveFromFS("/style.css");
        htmlIndex = retreiveFromFS("/index.html");
        jsScript = retreiveFromFS("/script.js");
    }
    void sendPage(){ serverHTTP.send(200,"text/html", htmlIndex);}
    void sendScript(){ serverHTTP.send(200, "text/javascript", jsScript);}
    void sendStyle(){ serverHTTP.send(200, "text/css", styleSheet);} 


    void sendDefaultSettings(String sendcontent){
        serverHTTP.sendHeader("Access-Control-Allow-Headers", "*");
        serverHTTP.sendHeader("Access-Control-Allow-Origin", "*");
        serverHTTP.send(200, "text/html",sendcontent);
    }
    
    
    void handleNotFound(){ 
        serverHTTP.sendHeader("Location", "/",true); //Redirect to our html web page 
        serverHTTP.send(302, "text/plane",""); 
    }

    void handleLightRequest(){
        int lightStart = 100;
        int lightEnd = 200;
        long lightColor = 0;
        bool lightShow=false;
        String recievedData = "";
        for (int i = 0; i < serverHTTP.args(); i++) {
            recievedData += " "+ serverHTTP.argName(i) + " "+ serverHTTP.arg(i).c_str();
            if ( serverHTTP.argName(i)==(String) "start"){
                lightStart = atoi(serverHTTP.arg(i).c_str());
                continue;
            }else if (serverHTTP.argName(i)==(String) "end"){
                lightEnd = atoi(serverHTTP.arg(i).c_str());
                continue;
            }  else if (serverHTTP.argName(i)==(String) "showBool"){
                lightShow=true;
                continue;
            }else if (serverHTTP.argName(i)==(String) "color"){
                lightColor = strtol(serverHTTP.arg(i).c_str(), NULL, 16);
                continue;
            } 
        }
        lighteffects::setZoneLighting(lightStart,lightEnd, lightColor,lightShow);
        sendDefaultSettings(recievedData);
    }

    void sendParameters(){
        String ledParameters = "{\"maxLeds\":"+(String) NUM_LEDS;
    
        String ledValues = "[["
                +(String) leds[0].red+","
                +(String) leds[0].green+","
                +(String) leds[0].blue+"]";
        for( int i=1; i<NUM_LEDS;i++){
            //ledValues +=(String) leds[i] +",";
            ledValues += ",["
                +(String) leds[i].red+","
                +(String) leds[i].green+","
                +(String) leds[i].blue+"]";
        }
        ledValues+="]";
        if(ledValues.length()>3){
            ledParameters+=",\"ledValues\":"+ (String) ledValues;
        }
        ledParameters+="}";
        serverHTTP.sendHeader("Access-Control-Allow-Headers", "*");
        serverHTTP.sendHeader("Access-Control-Allow-Origin", "*");
        serverHTTP.send(200, "application/json",ledParameters);
        
    }   

 
    void setupRouting(){
        serverHTTP.on("/style.css",sendStyle);
        serverHTTP.on("/script.js",sendScript);
        serverHTTP.on("/",sendPage);
        serverHTTP.on("/lights",handleLightRequest);
        serverHTTP.on("/getParameters", sendParameters);
        serverHTTP.onNotFound(handleNotFound); 
        
    }
};

