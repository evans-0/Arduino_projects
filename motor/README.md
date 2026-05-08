# motor.ino

A simple Arduino sketch to control a DC motor using an H-Bridge motor driver (e.g., L298N or L293D). The motor alternates between forward and reverse directions every 2 seconds.

## Hardware Requirements

- Arduino board (Uno, Nano, etc.)
- H-Bridge motor driver module (L298N / L293D or similar)
- DC motor
- Power supply suitable for your motor

## Pin Configuration

| Pin | Arduino Pin | Description |
|-----|-------------|-------------|
| EN  | 4           | Enable pin — activates the motor driver |
| DIR1 | 5          | Direction control input 1 |
| DIR2 | 9          | Direction control input 2 |

## Wiring

Connect the Arduino pins to the corresponding input pins on your H-Bridge module. Connect the motor to the output terminals of the H-Bridge, and power the driver with an appropriate voltage for your motor.

## How It Works

1. The enable pin (`EN`) is set `HIGH` to activate the motor driver.
2. The motor spins **forward** for 2 seconds (`DIR1=HIGH`, `DIR2=LOW`).
3. The motor spins **reverse** for 2 seconds (`DIR1=LOW`, `DIR2=HIGH`).
4. This cycle repeats indefinitely.

## Usage

1. Wire the circuit as described above.
2. Open `motor.ino` in the Arduino IDE.
3. Select your board and port under **Tools**.
4. Click **Upload**.

## Notes

- To control motor speed, replace `digitalWrite(en, HIGH)` with `analogWrite(en, value)` where `value` is between `0–255`. Make sure `EN` is connected to a PWM-capable pin.
- Setting both `DIR1` and `DIR2` to the same state (`HIGH/HIGH` or `LOW/LOW`) will brake the motor.
