#include <main.h>
MPU6050 dynamicIMU(0x68);
MPU6050 staticIMU(0x69);

IMUData dynamicData(&dynamicIMU), staticData(&staticIMU);

void setup(){
    Wire.begin();
    Serial.begin(9600);
    dynamicIMU.initialize(); // Initialize dynamicIMU
    staticIMU.initialize(); // Initialize staticIMU
}
void loop(){
    //update data
    dynamicData.updateData();
    staticData.updateData();
    // print data
    Serial.print("Dynamic IMU: ");
    dynamicData.printData();
    Serial.print(" | Static IMU: ");
    staticData.printData();
    Serial.println();
}

