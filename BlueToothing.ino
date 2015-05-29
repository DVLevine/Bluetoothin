// Bluetooth Pallette message sending based off base structure used in Redbear HelloWorld demo.
// Sends chars in charbuffer to phone app.

#include <SPI.h>
#include <boards.h>
#include <RBL_nRF8001.h>

const int xOut = A5;
const int yOut = A4;
const int zOut = A3;

int sensorReadingX = 0;
int sensorReadingY = 0;
int sensorReadingZ = 0;

void setup()
{
  ble_set_name("Pallette");  
  ble_begin();
}

char b[3] = {0};
String str;
int length = 0;

void loop()
{
  if ( ble_connected() )
  {
    sensorReadingX = analogRead(xOut);
    sensorReadingY = analogRead(yOut);
    sensorReadingZ = analogRead(zOut);
    
    b[0] = 0;
    b[1] = 0;
    
    ble_write('X');
    ble_write(':');
    str = String(sensorReadingX);
    prepAndWrite(str,b);
  
    ble_write('Y');
    ble_write(':');
    str = String(sensorReadingY);
    prepAndWrite(str,b);
    
    ble_write('Z');
    ble_write(':');
    str = String(sensorReadingZ);
    prepAndWrite(str,b);
  }

  //takes care of low level bluetooth stuff. A Redbear special function.
  ble_do_events();
  
 
 // Processor is 8 Mhz
 // Reduce time to sensor 16 kHz
 // calc diff 0.000062375 sec => 62.375 milsec
  delay(62.375);  
}

// A Dan function. preps input ints as chars and writes them to the bluetooth line.
void prepAndWrite(String str, char * b){
  length = str.length(); 
  str.toCharArray(b,3);
    if (length == 0)
    {  
      b[0] = '0';
      b[1] = '0';
      b[2] = '0';
    }
    
     if (length == 1)
    { 
      b[2] = b[0];
      b[1] = '0';
      b[0] = '0';
    }
    
     if (length == 2)
    {  
      b[2] = b[1];
      b[1] = b[0];
      b[0] = '0';
    }
    
    ble_write((unsigned char)b[0]);
    ble_write((unsigned char)b[1]);
    ble_write((unsigned char)b[2]);
    ble_write(' ');
}

