#include <DFPlayer.hpp>

#define Start_Byte 0x7E
#define Version_Byte 0xFF
#define Command_Length 0x06
#define End_Byte 0xEF
#define Acknowledge 0x00 // Returns info with command 0x41 [0x01: info, 0x00: no info]
#define ACTIVATED LOW

DFPlayer::DFPlayer(int rxPin, int txPin) : serial(rxPin, txPin) {}

void DFPlayer::execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
  // Calculate the checksum (2 bytes)
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
  // Build the command line
  byte Command_line[10] = {Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
                           Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
  // Send the command line to the module
  for (byte k = 0; k < 10; k++)
  {
    this->serial.write(Command_line[k]);
  }
}

void DFPlayer::begin(int baudrate)
{
  this->serial.begin(baudrate);
}

void DFPlayer::setVolume(int volume)
{
  execute_CMD(0x06, 0, volume);
  delay(2000);
}

void DFPlayer::playFirst()
{
  this->execute_CMD(0x3F, 0, 0);
  delay(500);
  this->setVolume(20);
  delay(500);
  this->execute_CMD(0x11, 0, 1);
  delay(500);
}

void DFPlayer::pause()
{
  this->execute_CMD(0x0E, 0, 0);
  delay(500);
}

void DFPlayer::play()
{
  this->execute_CMD(0x0D, 0, 1);
  delay(500);
}

void DFPlayer::playNext()
{
  this->execute_CMD(0x01, 0, 1);
  delay(500);
}

void DFPlayer::playPrevious()
{
  this->execute_CMD(0x02, 0, 1);
  delay(500);
}
