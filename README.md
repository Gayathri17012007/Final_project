# M24C04 EEPROM Erase and Verification Using NXP S32K144

## 1. Project Overview

This project implements EEPROM block erase emulation and read-back verification using the NXP S32K144 microcontroller and an M24C04 I2C EEPROM. The LPI2C driver is used to communicate with the external EEPROM.

The M24C04 has a storage capacity of 4 Kbit (512 bytes). In this project, the memory is divided into 64 logical blocks, with each block containing 8 bytes. The selected block is erased by writing `0xFF` to each memory location and then reading the data back to verify the operation.

The Watch Expression window in S32 Design Studio is used to inspect memory addresses and data values during debugging. An LED provides a visual indication of the verification status.

This project demonstrates external EEPROM interfacing, memory addressing, embedded C programming, data verification, and debugging using an NXP microcontroller.

## 2. System Architecture

The system uses the NXP S32K144 microcontroller to communicate with the M24C04 EEPROM through the LPI2C interface. The application selects a logical block, calculates its starting address, writes `0xFF` to the selected memory locations, reads the data back, and compares each byte with the expected value.

The Watch Expression window is used to inspect variables during debugging, while the LED indicates the operation status.

### System Flow

```text
       S32K144 Microcontroller
                  |
             LPI2C Driver
                  |
           M24C04 EEPROM
                  |
        Select Logical Block
                  |
          Calculate Address
                  |
          Write 0xFF Data
                  |
           Read Back Data
                  |
          Verify Each Byte
                  |
          +-------+-------+
          |               |
       Success           Failure
          |               |
      LED Status       LED Status

   Watch Expression:
   Inspect addresses and data
   during debugging
```

## 3. Hardware and Software Requirements

### Hardware Requirements

- NXP S32K144 development board
- M24C04 I2C EEPROM (4 Kbit / 512 bytes)
- USB connection for programming and debugging
- LED connected to the configured GPIO pin
- Jumper wires
- Suitable power supply

### Software Requirements

- S32 Design Studio
- S32 SDK and LPI2C driver
- Debugger and Watch Expression window
- Git and GitHub for version control

## 4. Example Configuration

| Parameter | Configuration |
|---|---|
| Microcontroller | NXP S32K144 |
| External EEPROM | M24C04 |
| EEPROM capacity | 512 bytes |
| Logical block size | 8 bytes |
| Number of logical blocks | 64 |
| Base I2C address | `0x50` |
| Example logical block | `2` |
| Starting address | `16` (`0x10`) |
| Erase value | `0xFF` |
| Communication interface | LPI2C |
| Verification method | Watch Expression and LED |

### Example Operation

When `NvM_ErasePage(2U)` is called, the starting address is calculated as:

`StartAddress = PageNum × page_size`

`StartAddress = 2 × 8 = 16 (0x10)`

The program writes eight bytes of `0xFF` to EEPROM addresses 16–23. It then reads the eight bytes back and compares each byte with `0xFF`.

If every byte matches, the verification passes. If any byte differs from `0xFF`, the verification fails.

The Watch Expression window is used to inspect `StartAddress`, `EraseData[]`, and `ReadData[]`. The LED provides a visual indication of the result.

## 5. Build and Run

1. Open the project in S32 Design Studio.
2. Configure the LPI2C peripheral and the GPIO pin used for LED indication.
3. Initialize the system clock, GPIO pins, and LPI2C master driver.
4. Implement the `EEPROM_Write()`, `EEPROM_Read()`, and `NvM_ErasePage()` functions.
5. Build the project and resolve any compilation errors.
6. Connect the M24C04 EEPROM to the configured I2C pins. Ensure the power, ground, and address-pin connections are correct.
7. Flash the program to the NXP S32K144 development board and start debugging.
8. Call `NvM_ErasePage(2U)` from the main function.
9. Set a breakpoint immediately after the `EEPROM_Read()` call inside `NvM_ErasePage()`.
10. Add `StartAddress`, `EraseData[0]` through `EraseData[7]`, and `ReadData[0]` through `ReadData[7]` to the Watch Expression window.
11. Verify that `StartAddress` is `16` (`0x10`) and that all eight bytes in `ReadData[]` equal `0xFF`.
12. Observe the LED indication after the verification process.

### Expected Results

| Variable | Expected value |
|---|---|
| `StartAddress` | `16` (`0x10`) |
| `EraseData[0]` to `EraseData[7]` | `0xFF` |
| `ReadData[0]` to `ReadData[7]` | `0xFF` after successful write and read |
| Verification result | Pass if all eight bytes equal `0xFF` |

The LED's ON/OFF indication depends on whether the configured LED is active-low or active-high and on the status logic implemented in the program.

## 6. Scope and Limitations

### Scope

- Interface an external M24C04 EEPROM with the NXP S32K144 using I2C.
- Implement EEPROM write and read operations using separate C functions.
- Divide EEPROM storage into 8-byte logical blocks.
- Emulate an erase operation by writing `0xFF` to a selected logical block.
- Verify stored data by reading it back and comparing each byte.
- Inspect memory-related variables using the Watch Expression window.
- Use an LED for visual status indication.

### Limitations

- The application processes one selected logical block per function call.
- LPI2C driver return statuses are not yet checked, so communication failures may not be detected reliably.
- A fixed delay is used after writing instead of EEPROM acknowledgement polling.
- UART-based monitoring and runtime user input are not implemented.
- Write-once protection, wear management, and data recovery are not included.
- The LED status is meaningful only when success and failure paths are configured to produce different outputs.
## Verified Output:
<img width="1915" height="1020" alt="Screenshot 2026-10-13 085343" src="https://github.com/user-attachments/assets/1c8ee64b-2957-4ea7-9442-f86a1010cc18" />

## 7. Conclusion

This project demonstrates EEPROM block erase emulation and read-back verification using the NXP S32K144 microcontroller and M24C04 EEPROM. The application divides the 512-byte memory into 64 logical blocks of 8 bytes each. It writes `0xFF` to a selected block and verifies the stored values by reading them back.

The Watch Expression window in S32 Design Studio helps inspect addresses and data values during debugging, while the LED provides a visual indication of the operation status.

Through this project, practical knowledge of I2C communication, embedded C programming, memory addressing, EEPROM operations, and debugging techniques is developed.
