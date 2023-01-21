// write a program that dectect the tilt of adxl 345 accelerometer and print forward backward left right
#include <VirtualWire.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

char *data;


void setup()
{
    Serial.begin(9600);
    Serial.println("Accelerometer Test");
    Serial.println("");
    vw_set_tx_pin(12);
    vw_setup(2000);

    if (!accel.begin())
    {
        /* There was a problem detecting the ADXL345 ... check your connections */
        Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
        while (1)
            ;
    }

    /* Set the range to whatever is appropriate for your project */
}

void loop()
{
    /* Get a new sensor event */
    sensors_event_t event;
    accel.getEvent(&event);
    // Display no tilt forward back left right according to tilt in axis
    
    if (event.acceleration.y >= 4.5)
    {
        data = "f"; 
        vw_send((uint8_t *)data, strlen(data));
        vw_wait_tx();
        delay(100);
        Serial.println("Forward");
    }
    else if (event.acceleration.y <= -4.5)
    { 
        data = "b";
        vw_send((uint8_t *)data, strlen(data));
        vw_wait_tx();
        delay(100);
        Serial.println("Backward");
    }
    else if (event.acceleration.x <= -5.15)
    {   
        data = "l";
        vw_send((uint8_t *)data, strlen(data));
        vw_wait_tx();
        delay(100);
        Serial.println("Left");
    }
    else if (event.acceleration.x >= 5.5)
    {
        data = "r";
        vw_send((uint8_t *)data, strlen(data));
        vw_wait_tx();
        delay(100);
        Serial.println("Right");
    }
    else 
    {  
        data = "s";
        vw_send((uint8_t *)data, strlen(data));
        vw_wait_tx();
        delay(100);
        Serial.println("No tilt");
    }
 

    delay(50);
}
