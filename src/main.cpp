#include <Arduino.h>
#include <NewPing.h>
#include <DFPlayer.hpp>

boolean isObjectPresent(NewPing sonar);

void setup()
{
  DFPlayer player(11, 10);
  player.begin(9600);

  int triggerPin = 2;
  int echoPin = 3;
  int maxDistance = 200;
  NewPing sonar(triggerPin, echoPin, maxDistance);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  int relay = 4;
  pinMode(relay, OUTPUT);

  // Serial.begin(115200);
  player.setVolume(25);

  unsigned long timer = 0;
  boolean isPlaying = false;
  while (true)
  {
    boolean isPresent = isObjectPresent(sonar);
    // Serial.println(isPresent ? "Present" : "Absent");

    if (isPresent)
    {
      timer = 0;
      if (!isPlaying)
      {
        player.playNext();
        isPlaying = !isPlaying;
        // Serial.println("Start playing...");
      }
    }

    if (isPlaying && !isPresent)
    {
      if (timer == 0)
      {
        timer = millis();
        // Serial.println("Person moved away...");
      }
      if (millis() - timer > 3000)
      {
        player.pause();
        isPlaying = !isPlaying;
        timer = 0;
        // Serial.println("Player stopped...");
      }
    }

    digitalWrite(relay, !isPlaying);
    delay(200);
  }
}

void loop() {}

int readPing(NewPing sonar)
{
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}

boolean isObjectPresent(NewPing sonar)
{
  return readPing(sonar) <= 70;
}