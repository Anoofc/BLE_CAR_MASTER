#define RIGHT1  27
#define RIGHT2  26
#define LEFT1   25
#define LEFT2   33


#include <Arduino.h>
#include "BluetoothSerial.h"


BluetoothSerial SerialBT;

void backward(){
    digitalWrite(RIGHT1, HIGH);
    digitalWrite(RIGHT2, LOW);
    digitalWrite(LEFT1, HIGH);
    digitalWrite(LEFT2, LOW);
}
void forward(){
    digitalWrite(RIGHT1, LOW);
    digitalWrite(RIGHT2, HIGH);
    digitalWrite(LEFT1, LOW);
    digitalWrite(LEFT2, HIGH);
}

void right(){
    digitalWrite(RIGHT1, HIGH);
    digitalWrite(RIGHT2, LOW);
    digitalWrite(LEFT1, LOW);
    digitalWrite(LEFT2, HIGH);
}

void left(){
    digitalWrite(RIGHT1, LOW);
    digitalWrite(RIGHT2, HIGH);
    digitalWrite(LEFT1, HIGH);
    digitalWrite(LEFT2, LOW);
}
void stop(){
    digitalWrite(RIGHT1, LOW);
    digitalWrite(RIGHT2, LOW);
    digitalWrite(LEFT1, LOW);
    digitalWrite(LEFT2, LOW);
}


void setup()
{
    Serial.begin(9600);
    pinMode(RIGHT1, OUTPUT);
    pinMode(RIGHT2, OUTPUT);
    pinMode(LEFT1, OUTPUT);
    pinMode(LEFT2, OUTPUT);

    SerialBT.begin("ESP32_CAR"); // Bluetooth device name
}



void loop(){

    if (SerialBT.available()){
        char data = SerialBT.read();
        Serial.println(data);
        if (data  == 'F'){
            forward();
        }
         if (data == 'B'){
            backward();
        } 
         if (data == 'L'){
            left();
        }
         if (data == 'R'){
            right();
        }
         if (data == 'S'){
            stop();
        }
    }

}