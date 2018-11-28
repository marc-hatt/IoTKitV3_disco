/** Beispiel Abfrage Cloud Dienst Sunrise / Sunset
 */
#include "mbed.h"
#include "http_request.h"
#include "network-helper.h"
#include "OLEDDisplay.h"

OLEDDisplay oled;

AnalogIn hallSensor( A3 );
DigitalOut led1( LED1 );
DigitalOut led2( LED2 );
DigitalIn reset( USER_BUTTON );

// HTTP Hilfsklassen
char *finishMsg = "http://maker.ifttt.com/trigger/hallsensoralarm/with/key/ge6H2PIYtdpW0D6SY3w9xu38_1SkvKWIP6C9if4WyRb";
// I/O Buffer
char message[256];

int main()
{
    oled.clear();
    oled.printf( "Hall Sensor Alarm\n" );
    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface* network = connect_to_default_network_interface();
    
    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }

    led1 = 0;
    led2 = 1;
    oled.clear();
    oled.printf( "Hall Sensor Alarm" );
        
    while(1) 
    {
        // Alarm scharf
        if  ( led1 == 0 )
        {
            oled.cursor( 1, 0 );
            oled.printf( "scharf      " );
            float value = hallSensor.read();
            if  ( value < 0.4f || value > 0.6f )
            {
                oled.cursor( 1, 0 );
                oled.printf( "ALARM !!!" );
                HttpRequest* get_req = new HttpRequest( network, HTTP_GET, finishMsg );

                HttpResponse* get_res = get_req->send();
                // Error
                if ( !get_res )
                {
                    printf("HttpRequest failed (error code %d)\n", get_req->get_error());
                    return 1;
                }
                else
                    printf("\nBody (%d bytes):\n\n%s\n", get_res->get_body_length(), get_res->get_body_as_string().c_str());
                delete get_req;
                led1 = 1;
                led2 = 0;
            }
        }
        else
        {
            if  ( reset == 0 )
            {
                oled.cursor( 1, 0 );
                oled.printf( "reset       " );                
                led1 = 0;
                led2 = 1;
            }
        }
        wait( 0.2f );
    }
}
