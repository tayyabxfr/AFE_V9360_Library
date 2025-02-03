AFEVANGOV9360 Arduino Library
The AFEVANGOV9360 library provides an easy-to-use interface for communicating with the AFEVANGOV9360 analog front-end (AFE) device using UART. With this library, you can initialize the AFE, read voltage, current, and power data, and write configuration commands, all while ensuring data integrity through checksum validation.

About
This library was developed to simplify communication with the AFEVANGOV9360 device in Arduino-based projects. The library handles the low-level UART communication, including constructing command packets, calculating checksums, and verifying responses from the AFE. It is especially useful for applications that require accurate measurements of electrical parameters.

Key features include:

UART Communication: Utilizes Arduino's Serial1 interface for transmitting and receiving data.
Checksum Validation: Implements robust checksum calculations to ensure data integrity.
Flexible Data Reading: Provides functions to read voltage, current, and power with proper data conversion.
Easy-to-Use API: Designed to be straightforward to integrate into your projects.
Features
Initialization: Set up the AFE with a single function call.
Data Acquisition: Read voltage, current, and power measurements.
Data Integrity: Validate responses using checksums.
Debugging Support: Optional debug prints to help troubleshoot communication issues.
Installation
Download or Clone the Repository:

git clone https://github.com/yourusername/AFEVANGOV9360.git
Add to Arduino IDE:

Open the Arduino IDE.
Go to Sketch > Include Library > Add .ZIP Library…
Select the downloaded repository folder (or zip file if you compressed it).
Include in Your Project:


#include "AFEVANGOV9360.h"
Usage
Below is a simple example demonstrating how to use the library:


#include "AFEVANGOV9360.h"

// Create an instance of the AFEVANGOV9360 class
AFEVANGOV9360 afe;

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(115200);

  // Begin communication with the AFE
  afe.begin();

  // Optionally, you can write initial configuration
  // For example: write some register settings (if needed)
  // afe.writedata(0x00000007, DSP_CTRL0);
}

void loop() {
  // Read voltage, current, and power from the AFE
  uint32_t voltage = afe.voltage();
  uint32_t current = afe.current();
  int32_t power = afe.power();

  // Print the values to the Serial Monitor
  Serial.print("Voltage: ");
  Serial.println(voltage);
  Serial.print("Current: ");
  Serial.println(current);
  Serial.print("Power: ");
  Serial.println(power);

  // Wait before next reading
  delay(1000);
}
API Reference
Class: AFEVANGOV9360
Constructor

AFEVANGOV9360(): Creates an instance of the AFEVANGOV9360 class.
Initialization

void begin(): Initializes UART communication and sets up the AFE device.
Data Reading

uint32_t voltage(): Reads the voltage register.
uint32_t current(): Reads the current register.
int32_t power(): Reads the power register.
Data Writing

bool writedata(uint32_t data, AFERegister reg): Writes a 32-bit data value to a specified AFE register.
Checksum Validation

bool validateChecksum(uint8_t received, uint8_t expected): Checks if the received checksum matches the expected checksum.
Debugging

void debugPrint(const char* message): Prints debug messages if DEBUG is defined.
Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes. If you find a bug or have a feature request, please open an issue.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgments
Special thanks to all contributors and the open-source community for their invaluable support and feedback.
