# ir_remote

An Arduino sketch that listens for IR remote signals and prints the decoded raw data to the Serial Monitor. Useful for mapping the hex codes of an unknown remote before using them in a larger project.

## What it does

When an IR remote button is pressed, the receiver captures the signal, decodes it, and prints the raw hex value over Serial. This lets you identify what code each button on a remote sends.

## Hardware

| Component | Details |
|-----------|---------|
| Microcontroller | Arduino Uno (or compatible) |
| IR Receiver | VS1838B or similar 38kHz receiver module |
| Data pin | Digital pin 7 |

## Wiring

```
IR Receiver OUT  →  Pin 7
IR Receiver VCC  →  5V
IR Receiver GND  →  GND
```

> The built-in LED will blink on each received signal (`ENABLE_LED_FEEDBACK`). Disable this by replacing it with `DISABLE_LED_FEEDBACK` if it causes interference.

## Dependencies

Install via Arduino Library Manager:

- [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote) — **version 3.x or higher**

> This sketch uses `IRremote.hpp` and the v3+ API. It is **not compatible** with IRremote v2.x, which uses `IRremote.h` and a different decode syntax. Many online tutorials still show the old API — ignore them.

## Usage

1. Upload the sketch to your Arduino.
2. Open the Serial Monitor at **9600 baud**.
3. Point your IR remote at the receiver and press a button.
4. The raw hex code for that button will be printed.

**Example output:**
```
FF629D
FFA25D
FFE21D
```

Record these values — they can then be used with `IrSender.sendNEC()` (or the relevant protocol) to replicate remote signals from a transmitter.

## Limitations & next steps

- Only `decodedRawData` (the raw value) is printed. IRremote also decodes **protocol**, **address**, and **command** separately, which gives you more structured and reliable data:

  ```cpp
  Serial.print(IrReceiver.decodedIRData.protocol);  // e.g. NEC
  Serial.print(IrReceiver.decodedIRData.address);
  Serial.print(IrReceiver.decodedIRData.command);
  ```

- No filtering for repeat codes (`IRDATA_FLAGS_IS_REPEAT`). Holding a button will flood the Serial output with repeated values.
- This sketch is a **diagnostic/mapping tool**, not a controller. The logical next step is to use the captured codes in a `switch` statement to trigger actions.
