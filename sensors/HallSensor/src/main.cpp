/** Hall Sensor 
*/
#include "mbed.h"

AnalogIn hallSensor( A3 );
DigitalOut led1( LED1 );
DigitalOut led2( LED2 );

int main()
{
    while(1) 
    {
        led1 = led2 = 0;
        
        float value = hallSensor.read();
        if  ( value < 0.4f )
            led1 = 1;
        else if ( value > 0.6f )
            led2 = 1;
        wait(1.0);
    }
}                                       
    
