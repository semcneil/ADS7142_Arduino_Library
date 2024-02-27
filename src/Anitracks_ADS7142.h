/*
  This file is a part of the Anitracks ADS7142 library.
  Copyright (c) 2022 Seth McNeill. All rights reserved.

  This software can be redistributed or modified under the MIT license
  that should have been included with this distribution.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
*/

#ifndef ANITRACKS_ADS7142
#define ANITRACKS_ADS7142

#include <Arduino.h>
#include <Wire.h>

#define DEFAULT_I2C_ADDRESS 0x18  // address with neither resistor populated

class ADS7142 {
public:
  ADS7142(uint8_t address = DEFAULT_I2C_ADDRESS, TwoWire &wirePort = Wire);
  virtual ~ADS7142();

  bool begin();
  void end();
  bool write(uint8_t reg, uint8_t val);
  bool write(uint8_t val);
  bool read(uint8_t reg, uint8_t *val);
  bool readFirst(uint16_t *val);
  bool read2Ch(uint16_t *ch0, uint16_t *ch1);

private:
  #define DEBUG_MODE 1
  uint8_t _i2c_address;
  TwoWire& _wire;

  // define registers
  #define WKEY                      0x17
  #define DEVICE_RESET              0x14
  #define OFFSET_CAL                0x15
  #define OPMODE_SEL                0x1C
  #define OPMODE_I2CMODE_STATUS     0x00
  #define CHANNEL_INPUT_CFG         0x24
  #define AUTO_SEQ_CHEN             0x20
  #define START_SEQUENCE            0x1E
  #define ABORT_SEQUENCE            0x1F
  #define SEQUENCE_STATUS           0x04
  #define OSC_SEL                   0x18
  #define nCLK_SEL                  0x19
  #define DATA_BUFFER_OPMODE        0x2C
  #define DOUT_FORMAT_CFG           0x28
  #define DATA_BUFFER_STATUS        0x01
  #define ACC_EN                    0x30
  #define ACC_CH0_LSB               0x08
  #define ACC_CH0_MSB               0x09
  #define ACC_CH1_LSB               0x0A
  #define ACC_CH1_MSB               0x0B
  #define ACCUMULATOR_STATUS        0x02
  #define ALERT_DWC_EN              0x37
  #define ALERT_CHEN                0x34
  #define DWC_HTH_CH0_MSB           0x39
  #define DWC_HTH_CH0_LSB           0x38
  #define DWC_LTH_CH0_MSB           0x3B
  #define DWC_LTH_CH0_LSB           0x3A
  #define DWC_HYS_CH0               0x40
  #define DWC_HTH_CH1_MSB           0x3D
  #define DWC_HTH_CH1_LSB           0x3C
  #define DWC_LTH_CH1_MSB           0x3F
  #define DWC_LTH_CH1_LSB           0x3E
  #define DWC_HYS_CH1               0x41
  #define PRE_ALT_MAX_EVENT_COUNT   0x36
  #define ALERT_TRIG_CHID           0x03
  #define ALERT_LOW_FLAGS           0x0C
  #define ALERT_HIGH_FLAGS          0x0E
};

#endif // ANITRACKS_ADS7142