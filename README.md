# ESP32_VL53L3CX
ESP-IDF componentes for VL53L3CX ranging sensors on ESP32 chips

This component is used to perform the distance reading with the Time-of-Flight ranging sensor VL53L3CX from STMicroelectronics, in this example the official library is used.

## Configuration

Define the channel used in I2C, frequency used in the bus and SCL and SDA pins.

```c

static const I2cDef I2CConfig = {
    .i2cPort            = I2C_NUM_0,
    .i2cClockSpeed      = 400000,
    .gpioSCLPin         = 22,
    .gpioSDAPin         = 21,
    .gpioPullup         = GPIO_PULLUP_ENABLE,
};

```
### Build and Flash firmware

```shell
$ git clone https://github.com/EmotionFly/ESP32_VL53L3CX.git
$ cd ESP32_VL53L3CX
$ . $HOME/esp/esp-idf/export.sh
$ idf.py flash monitor
```

## Resources
- [ESP-IDF Repository ](https://github.com/espressif/esp-idf)
- [ESP-Drone Repository ](https://github.com/espressif/esp-drone)
- [VL53L3CX Full API ](https://www.st.com/en/embedded-software/stsw-img033.html)