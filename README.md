# C-syntax-for-Embedded

## Drone Status and Error Checks

A small C program that stores basic drone data, finds the maximum value in a temperature array, and tracks detected errors with a bitmask.

### Drone data

The `struct Drone` contains:

- ID
- Battery level
- Temperature
- Speed
- Status (`IDLE`, `FLYING`, or `LANDING`)
- Error flags

### Error checks

- `battery_check` sets `LOW_BATTERY` when the battery level is 20% or lower.
- `temperature_check` sets `HIGH_TEMPERATURE` when the temperature is above 60.
- `sensor_check` sets `SENSOR_ERROR` when the speed is negative.
- `errorsBitmask` prints the lowest six bits of the error mask, including leading zeroes (for example, `000001`).
- `errorsName` prints the names of any set error flags.

The error flags are stored as bit values: `LOW_BATTERY` is bit 0, `HIGH_TEMPERATURE` is bit 1, and `SENSOR_ERROR` is bit 2. The current `main` function calls the battery and temperature checks; `sensor_check` and `errorsName` are implemented but not called.

### Temperature maximum

`temperature_max` returns the largest value in an integer array. It returns `-1` if the array size is zero. The example program uses the array `{25, 30, 35, 40, 45}`, so the displayed temperature is `45`.

### Build and run

With Clang installed, run:

```sh
clang main.c -o main
./main
```

The program prints the drone data and its error mask before and after the checks. With the initial battery level of 19%, the mask after checks is `000001` (`LOW_BATTERY`).
