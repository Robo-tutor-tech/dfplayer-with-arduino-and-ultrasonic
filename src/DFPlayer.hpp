#ifndef DF_PLAYER_HPP
#define DF_PLAYER_HPP
#include <Arduino.h>
#include <SoftwareSerial.h>

class DFPlayer
{
private:
  void execute_CMD(byte CMD, byte Par1, byte Par2);
  SoftwareSerial serial;

public:
  DFPlayer(int rxPin, int txPin);
  void begin(int baudrate);
  void setVolume(int volume);
  void playFirst();
  void play();
  void pause();
  void playNext();
  void playPrevious();
};

#endif