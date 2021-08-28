# LGRS232

Allows you to control your LG Television via its RS232 port (DB9 or Headphone jack)

## Quick start

### Controlling the TV

```c++
LGRS232       tv;

tv.connect(&Serial2, 0x01, 22, 19);
tv.setPower(true); // turn the TV on
tv.setVolume(50);  // set volume to 50%
tv.setInput(0x90); // set input to 0x90 (HDMI1)
tv.setInput(0x91); // set input to 0x91 (HDMI2)
tv.setInput(0x92); // set input to 0x92 (HDMI3)
tv.setInput(0x93); // set input to 0x93 (HDMI4)
tv.setMute(true); // mute the tv

tv.getPower(); // retrieve the current power state of the tv - will return false while the tv is turning on
tv.getInput(); // retrieve the current input on the tv
tv.getMute(); // retrieve the current mute status on the tv

tv.sendCmd('x', 'b', 0x90); // send custom command - see LG manuals for other commands
```

## Installation

- PULL or download zip.
- Move contents into Arduino library directory

## Notes

- Tested with ESP32
- Only limited commands are implemented, but you can use the `sendCmd()` method to send them
- See LG manuals for additional commands that can be sent (brightness, contrast, other inputs, etc)
  - see https://www.lg.com/us/business/download/resources/BT00001837/UV340C-U_Install_Manual_170825.pdf pg 28 for example
