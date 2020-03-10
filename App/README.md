# Dust sensor

This is a small program to read information from a dust sensor


## Flashing the program

### ESP32 devkit

To flash the program on the ESP32 devkit, you need to first press and hold the
BOOT button on the board, then press the EN button. This will enter firmware
download mode, and allow the board to be flashed.

You can then flash the board using ```make BOARD=esp32-wroom-32 flash-only```

## Troubleshooting

### ESP32 connectivity

If you ever encounter an IOError when trying to flash an ESP32, unplug the board
for a minute or two, and plug it back in. Be sure to enter firmware download
mode before trying to flash (hold the BOOT button and then press the EN button).