/*
Copyright (c) 2025 Tayyab Zafar

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


/*
 * AFEVANGOV9360.h
 *
 * Interface library for the  version of AFEVANGOV9360 v1.0
 * Based on the v9360 Metering AFE by Vango
 *
 * Author: Tayyab Zafar https://github.com/tayyabxfr
 *
 *
*/
#ifndef AFEVANGOV9360_H
#define AFEVANGOV9360_H

#include <Arduino.h>

// Enable Debugging
#define DEBUG  // Comment this line to disable debug messages

// Serial Communication Configuration
constexpr uint32_t AFE_BAUD_RATE = 4800;
constexpr uint8_t RX_PIN = 16;
constexpr uint8_t TX_PIN = 17;

// Header Byte & Checksum Base
constexpr uint8_t AFE_HEADER = 0x7D;
constexpr uint8_t CHECKSUM_BASE = 0x33;


// AFE Commands
enum AFECommand : uint8_t {
    AFE_CMD_READ = 0x01,
    AFE_CMD_01 = 0x02
};

// AFE Registers
enum AFERegister :  uint8_t {
    VOLTAGE_REG = 0x19,
    CURRENT_REG = 0x1B,
    POWER_REG = 0x16,
    DSP_CTRL0 = 0x02
};

class AFEVANGOV9360 {
public:
    AFEVANGOV9360();
    void begin();
    
    uint32_t voltage();
    uint32_t current();
    int32_t power();
    
    friend void accessWritedata(AFEVANGOV9360& afe, uint32_t data, AFERegister reg);

private:
    uint32_t readdata(AFECommand CMD, AFERegister REG);
    bool writedata(uint32_t DATA, AFERegister ADDR);
    bool validateChecksum(uint8_t received, uint8_t expected);
    void debugPrint(const char* MESSAGE);  // Debugging function
};

#endif  // AFEVANGOV9360_H
