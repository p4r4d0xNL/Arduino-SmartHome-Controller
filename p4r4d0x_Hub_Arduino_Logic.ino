#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  mySwitch.enableTransmit(5);  // An Pin 5

  mySwitch.setProtocol(1);
  mySwitch.setPulseLength(180);

  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  char data;
  if (mySwitch.available()) 
  {
    output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
  }
  if (Serial.available())
  {
    data = Serial.read();
  }
  if (data == '1') // Alle Aktoren einschalten
  {
    mySwitch.sendTriState("0F00FFFF0101");
    delay(1000);
    mySwitch.sendTriState("0F00FFF10001");
    delay(1000);
    mySwitch.sendTriState("0F00FFFF1001");
    delay(1000);
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(8, HIGH);
  }
  else if (data == '0') // Alle Aktoren ausschalten
  {
    mySwitch.sendTriState("0F00FFFF0110");
    delay(1000);
    mySwitch.sendTriState("0F00FFFF1010");
    delay(1000);
    mySwitch.sendTriState("0F00FFF10010");
    delay(1000);
    digitalWrite(7, LOW);
    delay(1000);
    digitalWrite(8, LOW);
  }
  else if (data == '3') // Funk 1 Ein
  {
    mySwitch.sendTriState("0F00FFFF0101"); 
  }
  else if (data == '2') // Funk 1 Aus
  {
    mySwitch.sendTriState("0F00FFFF0110"); 
  }
  else if (data == '5') // Funk 2 Ein
  {
    mySwitch.sendTriState("0F00FFFF1001"); 
  }
  else if (data == '4') // Funk 2 Aus
  {
    mySwitch.sendTriState("0F00FFFF1010"); 
  }
  else if (data == '7') // Funk 3 Ein
  {
    mySwitch.sendTriState("0F00FFF10001"); 
  }
  else if (data == '6') // Funk 3 Aus
  {
    mySwitch.sendTriState("0F00FFF10010"); 
  }
  else if (data == '9') // Relais 1 Ein
  {
    digitalWrite(7, HIGH);
  }
  else if (data == '8') // Relais 1 Aus
  {
    digitalWrite(7, HIGH);
  }
  else if (data == 'B') // Relais 2 Ein
  {
    digitalWrite(8, HIGH);
  }
  else if (data == 'A') // Relais 2 Aus
  {
    digitalWrite(8, HIGH);
  }
}
