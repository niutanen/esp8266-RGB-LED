# Individually wifi adressable RGB LED strips
This is a project i started to replace the normal lighting I have in my room. 
A ESP8266 is set to connect to a named wifi network based on SSID and password. Once connected the router gives the ESP a dedicated static ip, that will also be used to redirect requests on the network if they match certain keywords.
![Project component structure](https://user-images.githubusercontent.com/35771181/154945385-33feac73-09eb-4d1b-ada6-1de6b79f88e7.png)

The ESP hosts the webpage files in its EEPROM (see "/data" folder), which it reads as a bitstream and sends to the requester.

## The website

The user opens their device and goes to the website (in this case "http://esp8266"), where they can control the lights. This website is saved as three different files in the ESP8266, and are retrieved by using littleFS. 
The site is optimised to resize with the width of the window, thus making the experience on all platforms similar. Currently the colorpicker (the button in the middle at the bottom), uses the default colorpicker of each browser, and requires more clicks than what I find convenient. Eventually this will be changed to a faster color picker.
![Website example](https://user-images.githubusercontent.com/35771181/154938757-79b21571-8329-4e16-8fd5-35351955dd6e.png)


## The ESP8266
The ESP8266 is powered by a usb wall charger, and is out of reach for the most part. Thus having OTA updates significantly simplifies the development process. 

