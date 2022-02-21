# Individually wifi adressable RGB LED strips
This is a project i started to replace the normal lighting I have in my room. 
A ESP8266 is set to connect to a named wifi network based on SSID and password. Once connected the router gives the ESP a dedicated static ip, that will also be used to redirect requests on the network if they match certain keywords.
![Project component structure](https://user-images.githubusercontent.com/35771181/154945298-2cc1fb18-5868-42b4-981b-8bc8f7bad0a8.png)

The ESP hosts the webpage files in its EEPROM (see "/data" folder), which it reads as a bitstream and sends to the requester.

The user opens their device and goes to the website (in this case "http://esp8266"), where they can control the lights.
![Website example](https://user-images.githubusercontent.com/35771181/154938757-79b21571-8329-4e16-8fd5-35351955dd6e.png)


