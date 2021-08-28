#include <HardwareSerial.h>
#include <Arduino.h>


class LGRS232
{
  private:
    HardwareSerial *_serial;
    char           *buf;
    byte            setID;
    
    byte sendCmd(byte cmd1, byte cmd2, byte data);
  public:
    void connect(HardwareSerial *serial, byte setID=0, int rxPin=-1, int =-1);
    byte setPower(bool onOff);
    byte getPower();
    bool setVolume(byte v);
    byte getVolume();
    bool setInput(byte v);
    byte getInput();
    byte getMute();
    byte setMute(bool m);
    bool debugPrint = false;
    
};


