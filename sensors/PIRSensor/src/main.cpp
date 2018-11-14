/** PIR Sensor (Bewegungsmelder)
 */
#include "mbed.h"

DigitalIn pirSensor( A5 );
DigitalOut licht( LED1 );

int main()
{
    while(1) 
    {
        if  ( pirSensor )
        {
            licht = 1;
            wait( 10 );
        }
        else
            licht = 0;
    }
}
