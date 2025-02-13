#include "AFEVANGOV9360.h"
//frirend function
void accessWritedata(AFEVANGOV9360& afe, uint32_t data, AFERegister reg) {
    afe.writedata(data, reg);  // Can access private method
}
// Constructor
AFEVANGOV9360::AFEVANGOV9360() {}

// Initialization function
void AFEVANGOV9360::begin() {
    Serial1.begin(AFE_BAUD_RATE, SERIAL_8O1, RX_PIN, TX_PIN);
}

// Read data function
uint32_t AFEVANGOV9360::readdata(AFECommand cmd, AFERegister reg) {
    uint8_t cmd1 = reg & 0x7F;
    uint8_t checksum = CHECKSUM_BASE + ~(cmd + cmd1);

    Serial1.write(AFE_HEADER);
    Serial1.write(cmd);
    Serial1.write(cmd1);
    Serial1.write(checksum);
    Serial1.flush();  // Ensure all bytes are transmitted

    unsigned long startTime = millis();
    while (Serial1.available() < 5 && (millis() - startTime) < 100) {
        delay(1);
    }

    if (Serial1.available() < 5) {
        debugPrint("Timeout or no response from AFE");
        return 0;
    }

    uint8_t data_bytes[4];
    uint32_t complete_data = 0;
    int32_t power_data = 0;

    for (int i = 0; i < 4; i++) {
        data_bytes[i] = Serial1.read();
        if (reg == POWER_REG)
            power_data |= ((uint32_t)data_bytes[i] << (i * 8));
        else
            complete_data |= ((uint32_t)data_bytes[i] << (i * 8));
    }

    uint8_t received_cksum = Serial1.read();
    uint8_t expected_cksum = CHECKSUM_BASE + ~(cmd + cmd1 + data_bytes[0] + data_bytes[1] + data_bytes[2] + data_bytes[3]);

    if (validateChecksum(received_cksum, expected_cksum)) {
        return (reg == POWER_REG) ? power_data : complete_data;
    } else {
        debugPrint("Checksum error - Data may be corrupted");
        return 0;
    }
}

// Write data function
bool AFEVANGOV9360::writedata(uint32_t data, AFERegister reg) {
    uint8_t cmd4 = reg & 0x007F;
    uint8_t data_bytes[4] = {
        (uint8_t)(data & 0xFF),
        (uint8_t)((data >> 8) & 0xFF),
        (uint8_t)((data >> 16) & 0xFF),
        (uint8_t)((data >> 24) & 0xFF)
    };

    uint8_t checksum = CHECKSUM_BASE + ~(AFE_CMD_01 + cmd4 + data_bytes[0] + data_bytes[1] + data_bytes[2] + data_bytes[3]);

    Serial1.write(AFE_HEADER);
    Serial1.write(AFE_CMD_01);
    Serial1.write(cmd4);
    Serial1.write(data_bytes, 4);
    Serial1.write(checksum);
    Serial1.flush();

    unsigned long startTime = millis();
    while (Serial1.available() < 1 && (millis() - startTime) < 100) {
        delay(1);
    }

    if (Serial1.available() < 1) {
        debugPrint("Timeout or no acknowledgment from AFE");
        return false;
    }

    uint8_t received_cksum = Serial1.read();
    return validateChecksum(received_cksum, checksum);
}
// Checksum validation function
bool AFEVANGOV9360::validateChecksum(uint8_t received, uint8_t expected) {
    return received == expected;
}

// Debug print function
void AFEVANGOV9360::debugPrint(const char* message) {
#ifdef DEBUG
    Serial.println(message);
#endif
}

//  Get Voltage
uint32_t AFEVANGOV9360::voltage() {
    return readdata(AFE_CMD_READ, VOLTAGE_REG);
}

//  Get Current
uint32_t AFEVANGOV9360::current() {
    return readdata(AFE_CMD_READ, CURRENT_REG);
}

//  Get Power
int32_t AFEVANGOV9360::power() {
    return readdata(AFE_CMD_READ, POWER_REG);
}
