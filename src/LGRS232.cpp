#include "LGRS232.h"

void LGRS232::connect(HardwareSerial *serial, byte setID, int rxPin, int txPin){
    _serial = serial;
    _serial->begin(9600, SERIAL_8N1, rxPin, txPin);
    _serial->setTimeout(500);

    this->setID   = setID;
    this->buf     = (char *)malloc(16);

    if(this->buf == NULL) {
        Serial.print("MALLOC FAILED\n");
    }
}

byte LGRS232::sendCmd(byte cmd1, byte cmd2, byte data){
    int bytesRead;
    char ackCmd;
    byte ackSetID;
    byte ackR1;
    byte ackR2;
    byte ackData;

    _serial->printf("%c%c %02X %02X\r", cmd1, cmd2, this->setID, data);
    _serial->flush();

    memset(this->buf, 0, 16);
    bytesRead = _serial->readBytesUntil('x', this->buf, 16);

    if(bytesRead == 9) {
        if(debugPrint){
            Serial.printf("GETCMD: %s\n", this->buf);
        }

        sscanf((char *)this->buf, "%c %02d %c%c%02d", &ackCmd, &ackSetID, &ackR1, &ackR2, &ackData);

        if(ackCmd == cmd2){
            if(ackR1 == 'O' && ackR2 == 'K') {
                if(debugPrint){
                    Serial.printf("  RET: %d\n", ackData);
                }
                return ackData;
            } else if(ackR1 == 'N' && ackR2 == 'G') {
                return 0xFF;
            }
        }

    } else if(debugPrint){
        Serial.printf("FAILED TO READ: %s\n", this->buf);
    }

    return 0xFF;
}

byte LGRS232::setPower(bool onOff){
    return sendCmd('k', 'a', onOff ? 0x01 : 0x00);
}

byte LGRS232::getPower(){
    return sendCmd('k', 'a', 0xFF);// == 0x01 ? true : false;
}

bool LGRS232::setVolume(byte v){
    return sendCmd('k', 'f', v*64/100);
}

byte LGRS232::getVolume(){
    return min((sendCmd('k', 'f', 0xFF) * 100) / 64, 0);
}

byte LGRS232::setMute(bool m){
    return sendCmd('k', 'e', m ? 0x00 : 0x01);
}

byte LGRS232::getMute(){
    return sendCmd('k', 'e', 0xFF);// 0x01 = volume on, 0x00 = muted
}

bool LGRS232::setInput(byte v){
    return sendCmd('x', 'b', v);
}

byte LGRS232::getInput(){
    return sendCmd('x', 'b', 0xFF);
}
