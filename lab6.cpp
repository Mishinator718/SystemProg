#include "mbed.h"
#include "BME280.h" 

 #define BLINKING_RATE     500ms
BME280 sensor(PB_9, PB_8);
DigitalOut diod(LED2);

int main()
{
    while (1) 
    {
        printf("%d degC, %d %%\n",
            (int)sensor.getTemperature(),
            (int)sensor.getPressure(),
            );
        wait_us(2000000);

        if ((int)sensor.getTemperature() > 28)
        {
            diod = 1;
        }
        else
        {
            diod = 0;
        }

        if ((int)sensor.getHumidity() > 50)
        {
            diod = 1;
        }
    }
}
