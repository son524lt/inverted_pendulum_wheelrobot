#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

#define gyroScale 131.0
#define accelScale 16384.0
struct IMUData {
    int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
    float accelX, accelY, accelZ, temp, gyroX, gyroY, gyroZ;
    MPU6050 *imu;
    IMUData(MPU6050 *_imu) {
        imu = _imu;
        AcX = AcY = AcZ = Tmp = GyX = GyY = GyZ = 0;
        accelX = accelY = accelZ = temp = gyroX = gyroY = gyroZ = 0;
    }
    void updateData() {
        imu->getMotion6(&AcX, &AcY, &AcZ, &GyX, &GyY, &GyZ);
        accelX = AcX / accelScale;
        accelY = AcY / accelScale;
        accelZ = AcZ / accelScale;
        gyroX = GyX / gyroScale;
        gyroY = GyY / gyroScale;
        gyroZ = GyZ / gyroScale;
    }
    void printRawData() {
        Serial.print("AcX = "); Serial.print(AcX);
        Serial.print(" | AcY = "); Serial.print(AcY);
        Serial.print(" | AcZ = "); Serial.print(AcZ);
        Serial.print(" | GyX = "); Serial.print(GyX);
        Serial.print(" | GyY = "); Serial.print(GyY);
        Serial.print(" | GyZ = "); Serial.print(GyZ);
    }
    void printData() {
        Serial.print("AcX = "); Serial.print(accelX);
        Serial.print(" | AcY = "); Serial.print(accelY);
        Serial.print(" | AcZ = "); Serial.print(accelZ);
        Serial.print(" | GyX = "); Serial.print(gyroX);
        Serial.print(" | GyY = "); Serial.print(gyroY);
        Serial.print(" | GyZ = "); Serial.print(gyroZ);
    }
};