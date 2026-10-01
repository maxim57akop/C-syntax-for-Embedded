#include <stdio.h>
#include <stdint.h>

enum DroneStatus
{
    IDLE,
    FLYING,
    LANDING
};

struct Drone
{
    int id;
    float battery_level;
    float temperature;
    int speed;
    enum DroneStatus status;
    uint8_t errors;
};
enum DroneError
{
    LOW_BATTERY = 1 << 0,
    HIGH_TEMPERATURE = 1 << 1,
    SENSOR_ERROR = 1 << 2
};

int battery_check(struct Drone *drone)
{
    if (drone->battery_level <= 20.0f)
    {
        drone->errors |= LOW_BATTERY;
        return -1; 
    }
    return 0; 
}

int temperature_check(struct Drone *drone)
{
    if (drone->temperature > 60.0f)
    {
        drone->errors |= HIGH_TEMPERATURE;
        return -1; 
    }
    return 0; 
}

void errorsBitmask(struct Drone *drone)
{
    for (int bit = 5; bit >= 0; bit--)
    {
        putchar((drone->errors & (1u << bit)) ? '1' : '0');
    }
}


void sensor_check(struct Drone *drone)
{
    if (drone->speed < 0)
    {
        drone->errors |= SENSOR_ERROR;
    }
}


void errorsName(struct Drone *drone)
{
    if (drone->errors & LOW_BATTERY)
    {
        printf("LOW_BATTERY ");
    }
    if (drone->errors & HIGH_TEMPERATURE)
    {
        printf("HIGH_TEMPERATURE ");
    }
    if (drone->errors & SENSOR_ERROR)
    {
        printf("SENSOR_ERROR ");
    }
}
int temperature_max(struct Drone *drone, int *temperature_array, size_t size)
{
    if (size == 0)
    {
        return -1; 
    }

    int max_temp = temperature_array[0];
    for (size_t i = 1; i < size; i++)
    {
        if (temperature_array[i] > max_temp)
        {
            max_temp = temperature_array[i];
        }
    }

   

    return max_temp; 
}

int main()
{
    int temperature_array[5] = {25, 30, 35, 40, 45};
    struct Drone myDrone = {1, 19.0f, 30.0f, 10, FLYING, 0};
    myDrone.temperature = temperature_max(&myDrone, temperature_array, 5);
    printf("Drone ID: %d\n", myDrone.id);
    printf("Drone Battery Level: %.2f\n", myDrone.battery_level);
    printf("Drone Temperature: %.2f\n", myDrone.temperature);
    printf("Drone Speed: %d\n", myDrone.speed);
    printf("Drone Status: %d\n", myDrone.status);
    printf("Drone Errors: ");
    errorsBitmask(&myDrone);
    putchar('\n');
    battery_check(&myDrone);
    temperature_check(&myDrone);
    temperature_max(&myDrone, temperature_array, 5);
    printf("Drone Errors after checks: ");
    errorsBitmask(&myDrone);
    putchar('\n');

    return 0;
}
