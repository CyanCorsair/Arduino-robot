#include <NewPing.h>
#include <Ardumoto.h>

Ardumoto Moto;

#define TRIGGER_PIN 14
#define ECHO_PIN 15
#define MAX_DISTANCE 300

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int LED = 13;

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  Moto.begin();
}

void loop()
{
  delay(75);
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm (0 = outside set distance range)
  Serial.println("cm");
  
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
  
  Moto.setSpeed('A',-30);
}
