# Individually wifi adressable RGB LED strips
This is a project i started to replace the normal lighting I have in my room. 
A ESP8266 is set to connect to a named wifi network based on SSID and password. Once connected the router gives the ESP a dedicated static ip, that will also be used to redirect requests on the network if they match certain keywords.

The ESP hosts the webpage files in its EEPROM (see "/data" folder), which it reads as a bitstream and sends to the requester.

The user opens their device and goes to the website (in this case "http://esp8266"), where they can control the lights.
