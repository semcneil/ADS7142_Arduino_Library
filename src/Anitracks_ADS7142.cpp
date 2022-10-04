/*
  This file is a part of the Anitracks ADS7142 library.
  Copyright (c) 2022 Seth McNeill. All rights reserved.

  This software can be redistributed or modified under the MIT license
  that should have been included with this distribution.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
*/

#include <Anitracks_ADS7142.h>

ADS7142::ADS7142(uint8_t address, TwoWire &wirePort) :
  _i2c_address(address),
  _wire(wirePort)
{
}

ADS7142::~ADS7142() {
}

bool ADS7142::begin() {
  _wire.begin();
  uint8_t regVal;
  if(!read(OPMODE_I2CMODE_STATUS, &regVal)) {
    return(false);
  }
  if(!read(AUTO_SEQ_CHEN, &regVal)) {
    return(false);
  }
  return(true);
}

void ADS7142::end() {
    _wire.end();
}

bool ADS7142::write(uint8_t val) {
  _wire.beginTransmission(_i2c_address);
  _wire.write(val);
  return(_wire.endTransmission() == 0);
}

bool ADS7142::write(uint8_t reg, uint8_t val) {
  _wire.beginTransmission(_i2c_address);
  if(!_wire.write(0x08))
    return(false); // write single register command write failed
  if(!_wire.write(reg))
    return(false); // write register value failed
  if(!_wire.write(val))
    return(false); // write register value failed
  return(_wire.endTransmission() == 0);
}

bool ADS7142::read(uint8_t reg, uint8_t *val) {
  _wire.beginTransmission(_i2c_address);
  if(!_wire.write(0x10))
    return(0); // read single register command write failed
  if(!_wire.write(reg))
    return(0); // register write failed
  _wire.endTransmission();
  _wire.requestFrom(_i2c_address, 1);
  if(!_wire.available())
    return(false);  // request failed
  *val = _wire.read();
  return(_wire.endTransmission() == 0);
}

// Reads AIN0
bool ADS7142::readFirst(uint16_t *ch0) {
  _wire.requestFrom(_i2c_address, 2);
  if(!_wire.available())
    return(false);  // request failed
  *ch0 = _wire.read() << 8;  // read upper byte
  *ch0 += _wire.read();      // read lower byte
  return(true);
}

bool ADS7142::read2Ch(uint16_t *ch0, uint16_t *ch1) {
  // select both channels for auto sequencing
  if(!write(AUTO_SEQ_CHEN, 0x03)) {
      return(false);
  }
  // change to auto sequence mode
  if(!write(OPMODE_SEL, 0x04)) {
    return(false);
  }
  // start sequence
  if(!write(START_SEQUENCE, 0x01)) {
    return(false);
  }
  _wire.requestFrom(_i2c_address, 4);
  if(!_wire.available())
    return(false);  // request failed
  // need to check that 4 bytes came back
  // read ch0
  *ch0 = _wire.read() << 8; // read upper byte
  *ch0 += _wire.read();     // read lower byte
  // read ch1
  *ch1 = _wire.read() << 8; // read upper byte
  *ch1 += _wire.read();     // read lower byte
  // write SEQ_ABORT bit to stop Manual mode to allow 
  // it to be changed to another mode
  if(!write(ABORT_SEQUENCE, 0x01)) {
    return(false);
  }
  return(true);
}
