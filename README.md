# AFEVANGOV9360 Arduino Library
The AFEVANGOV9360 library provides an easy-to-use interface for communicating with the AFEVANGOV9360 analog front-end (AFE) device using UART. With this library, you can initialize the AFE, read voltage, current, and power data, and write configuration commands, all while ensuring data integrity through checksum validation.

# About
This library was developed to simplify communication with the AFEVANGOV9360 device in Arduino-based projects. The library handles the low-level UART communication, including constructing command packets, calculating checksums, and verifying responses from the AFE. It is especially useful for applications that require accurate measurements of electrical parameters.

## Key features include:

- UART Communication: Utilizes Arduino's Serial1 interface for transmitting and receiving data.
- Checksum Validation: Implements robust checksum calculations to ensure data integrity.
- Flexible Data Reading: Provides functions to read voltage, current, and power with proper data conversion.
- Easy-to-Use API: Designed to be straightforward to integrate into your projects.
## Features
- Initialization: Set up the AFE with a single function call.
- Data Acquisition: Read voltage, current, and power measurements.
- Data Integrity: Validate responses using checksums.
- Debugging Support: Optional debug prints to help troubleshoot communication issues.
  
# Installation
- Download or Clone the Repository:

git clone https://github.com/tayyabxfr/AFE_V9360_Library.git
Add to Arduino IDE:

Open the Arduino IDE.
Go to Sketch > Include Library > Add .ZIP Library…
Select the downloaded repository folder (or zip file if you compressed it).
Include in Your Project:

#include "AFEVANGOV9360.h"

Contributions are welcome! Please fork the repository and submit a pull request with your changes. If you find a bug or have a feature request, please open an issue.

# License
This project is licensed under the MIT License. See the LICENSE file for details.

# Acknowledgments
Special thanks to all contributors and the open-source community for their invaluable support and feedback.
