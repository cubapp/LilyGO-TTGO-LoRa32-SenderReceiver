# LilyGO-TTGO-LoRa32-SenderReceiver
The LilyGO TTGO LoRa32 Sender/Receiver made really simple. Instead of RTC module and WiFi RSSi it only send counter and a random number. It is feasible for testing the working distance. At the first try I was able the get the signal (or receive LoRa packets) at about 700meters in town area (not in direct sight). 

* The sender sends: Counter and Random number
* The receiver shows: Internal counter, SNR and RSSi for LoRa packets plus received payload (Sender's Counter and Random numer )


The code is derived and simplified from: 
https://github.com/Xinyuan-LilyGO/TTGO-LoRa-Series

## Arduino studio settings: 
**dependency library files**
* arduino-LoRa from https://github.com/sandeepmistry/arduino-LoRa 
* oled-ssd1306 from https://github.com/ThingPulse/esp8266-oled-ssd1306

**Arduino settings**
1. board: "TTGO LoRa32-OLED V1"
2. upload speed:  921600
3. flash frequency: 80MHz
