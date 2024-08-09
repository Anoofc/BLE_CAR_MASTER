#define DEBUG 0
#define RIGHT_PWM_R  22
#define RIGHT_PWM_L  23
#define LEFT_PWM_R   5
#define LEFT_PWM_L   17

#define RIGHT_EN_R  27   
#define RIGHT_EN_L  26
#define LEFT_EN_R  19
#define LEFT_EN_L  18


#define DIR_R  25
#define DIR_L  33



#include <Arduino.h>
#include "BluetoothSerial.h"

uint8_t speed = 150;
uint8_t prev_speed = 150;
char prev_data = 'U';

BluetoothSerial SerialBT;

void forward(){
    for (int i = 0; i < speed; i++){
        // digitalWrite(RIGHT_EN_R, HIGH);
        // digitalWrite(LEFT_EN_R, HIGH);
        // digitalWrite(RIGHT_EN_L, LOW);
        // digitalWrite(LEFT_EN_L, LOW);

        analogWrite(RIGHT_PWM_R, i);
        analogWrite(RIGHT_PWM_L, 0);
        analogWrite(LEFT_PWM_R, i);
        analogWrite(LEFT_PWM_L, 0);
        delay(4);
    }
}
void backward(){
    for (int i = 0; i < speed; i++){
        // digitalWrite(RIGHT_EN_R, LOW);
        // digitalWrite(RIGHT_EN_L, HIGH);
        // digitalWrite(LEFT_EN_R, LOW);
        // digitalWrite(LEFT_EN_L, HIGH);

        analogWrite(RIGHT_PWM_R, 0);
        analogWrite(RIGHT_PWM_L, i);
        analogWrite(LEFT_PWM_R, 0);
        analogWrite(LEFT_PWM_L, i);
        delay(4);
    }
}

void right(){
  analogWrite(DIR_R, 0);
  analogWrite(DIR_L, 200);  
}

void left(){
    analogWrite(DIR_R, 200);
  analogWrite(DIR_L, 0);  
}
void stop_backward(){
    for (int i = speed; i >0; i--){
        // digitalWrite(RIGHT_EN_R, LOW);
        // digitalWrite(RIGHT_EN_L, HIGH);
        // digitalWrite(LEFT_EN_R, LOW);
        // digitalWrite(LEFT_EN_L, HIGH);
        
        analogWrite(RIGHT_PWM_R, 0);
        analogWrite(RIGHT_PWM_L, i);
        analogWrite(LEFT_PWM_R, 0);
        analogWrite(LEFT_PWM_L, i);
        delay(4);
    }
    
}
void stop_forward(){
    for (int i = speed; i >0; i--){
        // digitalWrite(RIGHT_EN_R, HIGH);
        // digitalWrite(LEFT_EN_R, HIGH);
        // digitalWrite(RIGHT_EN_L, LOW);
        // digitalWrite(LEFT_EN_L, LOW);
        
        analogWrite(RIGHT_PWM_R, i);
        analogWrite(RIGHT_PWM_L, 0);
        analogWrite(LEFT_PWM_R, i);
        analogWrite(LEFT_PWM_L, 0);
        delay(4);
    }
    
}
void stop_left(){
    analogWrite(DIR_R, 0);
    analogWrite(DIR_L, 0);  
    
}   
void stop_right(){
    analogWrite(DIR_R, 0);
    analogWrite(DIR_L, 0);  
    
}


void setup()
{
    Serial.begin(9600);
    pinMode(RIGHT_PWM_R, OUTPUT);
    pinMode(RIGHT_PWM_L, OUTPUT);
    pinMode(LEFT_PWM_R, OUTPUT);
    pinMode(LEFT_PWM_L, OUTPUT);

    pinMode(RIGHT_EN_R, OUTPUT);
    pinMode(RIGHT_EN_L, OUTPUT);
    pinMode(LEFT_EN_R, OUTPUT);
    pinMode(LEFT_EN_L, OUTPUT);

    pinMode(DIR_R, OUTPUT);
    pinMode(DIR_L, OUTPUT);

    digitalWrite(RIGHT_EN_R, HIGH);
    digitalWrite(RIGHT_EN_L, HIGH);
    digitalWrite(LEFT_EN_R, HIGH);
    digitalWrite(LEFT_EN_L, HIGH);

    SerialBT.begin("ESP32_CAR"); // Bluetooth device name
}

void loop()
{

    if (SerialBT.available())
    {
        char data = SerialBT.read();
        if (DEBUG)(Serial.println(data));
        
        if (data == 'F')
        {
            forward();
            prev_data = data;
        }
        else if (data == 'B')
        {
            backward();
            prev_data = data;
        }
        else if (data == 'L')
        {
            left();
        }
        else if (data == 'R')
        {
            right();
        }
        else if (data == 'W')
        {
            stop_forward();
            prev_data = data;
        }
        else if (data == 'X')
        {
            stop_backward();
            prev_data = data;
        }
        else if (data == 'Y')
        {
            stop_right();
        }
        else if (data == 'Z')
        {
            stop_left();
        }
        else if (data == 'M' && speed <= 240)
        {
            speed +=10;
            if (DEBUG)(Serial.println(speed));
            if (prev_data == 'F'){
                for (int i = prev_speed; i < speed; i++){

                analogWrite(RIGHT_PWM_R, i);
                analogWrite(RIGHT_PWM_L, 0);
                analogWrite(LEFT_PWM_R, i);
                analogWrite(LEFT_PWM_L, 0);
                delay(4);
            }           
                
        }
            else if (prev_data == 'B'){
                for (int i = prev_speed; i < speed; i++){
                    analogWrite(RIGHT_PWM_R, 0);
                    analogWrite(RIGHT_PWM_L, i);
                    analogWrite(LEFT_PWM_R, 0);
                    analogWrite(LEFT_PWM_L, i);
                    delay(4);
                }
                
            }
        }
        else if (data == 'N' && speed > 150)
        {
            speed -=10;
            if (DEBUG)(Serial.println(speed));
            if (prev_data == 'F'){
                for (int i = prev_speed; i > speed; i--){
                    analogWrite(RIGHT_PWM_R, i);
                    analogWrite(RIGHT_PWM_L, 0);
                    analogWrite(LEFT_PWM_R, i);
                    analogWrite(LEFT_PWM_L, 0);
                    delay(4);
                }
                
            }
            else if (prev_data == 'B'){
                for (int i = prev_speed; i > speed; i--){
                    analogWrite(RIGHT_PWM_R, 0);
                    analogWrite(RIGHT_PWM_L, i);
                    analogWrite(LEFT_PWM_R, 0);
                    analogWrite(LEFT_PWM_L, i);
                    delay(4);
                }
                
            }
            prev_speed = speed;
        }
    }
}