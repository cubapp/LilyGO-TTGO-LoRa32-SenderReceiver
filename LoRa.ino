#include <SPI.h>
#include <LoRa.h>
#include "board_def.h"

OLED_CLASS_OBJ display(OLED_ADDRESS, OLED_SDA, OLED_SCL);

//display size for better string placement
int width;
int height;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  if (OLED_RST > 0) {
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, HIGH);
    delay(100);
    digitalWrite(OLED_RST, LOW);
    delay(100);
    digitalWrite(OLED_RST, HIGH);
  }

  display.init();
  width = display.getWidth() / 2;
  height = display.getHeight() / 2;
  display.flipScreenVertically();
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(width - 50, height, LORA_SENDER ? "LoRa++ Sender" : "LoRa++ Receiver");
  display.display();
  delay(2000);



  SPI.begin(CONFIG_CLK, CONFIG_MISO, CONFIG_MOSI, CONFIG_NSS);
  LoRa.setPins(CONFIG_NSS, CONFIG_RST, CONFIG_DIO0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  if (!LORA_SENDER) {
    display.clear();
    display.drawString(width - 50, height, "LoraRecv++ Ready");
    display.display();
  }
}

int count = 0;
void loop()
{


#if LORA_SENDER
//  LORA SENDER PART -
//  sending random number and counter to the LoRa Receiver
  int32_t rssi;
  count++;
  rssi = random(1, 100);
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(width - 50, height, String(count) + ". RandNum: " + String(rssi));
  display.display();
  LoRa.beginPacket();
  LoRa.print(count);
  LoRa.print(". Rnd= ");
  LoRa.print(rssi);
  LoRa.endPacket();
  delay(500);

#else
//  LORA RECEIVER PART -
//  displaying random number and counter from the LoRa Sender
  if (LoRa.parsePacket()) {
    String recv = "";
    while (LoRa.available()) {
      recv += (char)LoRa.read();
    }
    count++;
    display.clear();
    display.drawString(width - 50, height, recv);
    String info = "[" + String(count) + "]" + "RSSI " + String(LoRa.packetRssi());
    String snr = "[" + String(count) + "]" + "SNR: " + String(LoRa.packetSnr());
    display.drawString(width - 50, height - 16, info);
    display.drawString(width - 50, height - 24, snr);
    display.display();
  }
#endif
}

