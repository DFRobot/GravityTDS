/***************************************************
 DFRobot Gravity: Analog TDS Sensor/Meter
 <https://www.dfrobot.com/wiki/index.php/Gravity:_Analog_TDS_Sensor_/_Meter_For_Arduino_SKU:_SEN0244>
 
 ***************************************************
 This sample code shows how to read the tds value and calibrate it with the standard buffer solution.
 707ppm(1413us/cm)@25^c standard buffer solution is recommended.
 
 Created 2018-1-3
 By Jason <jason.ling@dfrobot.com@dfrobot.com>
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution.
 ****************************************************/

#ifndef GRAVITY_TDS_H
#define GRAVITY_TDS_H

#include "Arduino.h"

#define ReceivedBufferLength 15
#define TdsFactor 0.5  // tds = ec / 2

class GravityTDS
{
public:
    GravityTDS();
    ~GravityTDS();

    void begin();  //initialization
    void update(); //read and calculate
    void setPin(int pin); 
    void setTemperature(float temp);  //set the temperature and execute temperature compensation
    void setAref(float value);  //reference voltage on ADC, default 5.0V on Arduino UNO
    void setAdcRange(float range);  //1024 for 10bit ADC;4096 for 12bit ADC
    void setKvalueAddress(int address); //set the EEPROM address to store the k value,default address:0x08
    float getKvalue(); 
    float getTdsValue();
    float getEcValue();

private:
    int pin;
    float aref;  // default 5.0V on Arduino UNO
    float adcRange;
    float temperature;
    int kValueAddress;     //the address of the K value stored in the EEPROM
    char cmdReceivedBuffer[ReceivedBufferLength+1];   // store the serial cmd from the serial monitor
    byte cmdReceivedBufferIndex;
 
    float kValue;      // k value of the probe,you can calibrate in buffer solution ,such as 706.5ppm(1413us/cm)@25^C 
    float analogValue;
    float voltage;
    float ecValue; //before temperature compensation
    float ecValue25; //after temperature compensation
    float tdsValue;

    void readKValues();
    boolean cmdSerialDataAvailable();
    byte cmdParse();
    void ecCalibration(byte mode);
};  

#endif
