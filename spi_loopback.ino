#include <SPI.h>

// ---- Set your pins here ----
#define SPI_SCK  12
#define SPI_MISO 13
#define SPI_MOSI 11
#define SPI_CS   10

void setup() {
  Serial.begin(115200);
  delay(1500);
  pinMode(SPI_CS, OUTPUT);
  digitalWrite(SPI_CS, HIGH);                    // idle = deselected
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);
}

void loop() {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));  // 1 MHz, MSB first, mode 0
  digitalWrite(SPI_CS, LOW);                     // select
  uint8_t rx = SPI.transfer(0xA5);               // send 0xA5, read what comes back
  digitalWrite(SPI_CS, HIGH);                    // deselect
  SPI.endTransaction();

  Serial.print("Sent 0xA5, received 0x");
  Serial.println(rx, HEX);
  delay(1000);
}
