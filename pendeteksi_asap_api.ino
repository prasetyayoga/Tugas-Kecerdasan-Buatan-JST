#include <LiquidCrystal.h>
#include <Servo.h>
#define sensorLightPin    A2

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo window;

int servo = 9;
int tsensor = A0;
int pump = 7; 
int buzzer = 8; 
int led = 6;
int ldr = A1;
int state = 0;
int gas_pin= A2;
float gas_data= A2;
 
void setup() 
{
  window.attach(servo);
  pinMode(ldr, INPUT);
  pinMode(tsensor, INPUT);
  pinMode(pump,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  window.write(0);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(2,0);
  lcd.print("PENDETEKSI");
  lcd.setCursor(2,1);
  lcd.print("Asap & Api");
  delay(1000);
  lcd.clear();
  
}

void loop()
{
 Serial.println(gas_data);
  lcd.setCursor(1, 0);
  lcd.print("Mendeteksi Asap");
  lcd.setCursor(0,2);
    lcd.print("Tebal: ");
    lcd.setCursor(6, 1);
    lcd.print(gas_data);
    delay(500);
    lcd.clear();

  if(gas_data<100){
  gas_data=analogRead(gas_pin);
  window.write(0);
  digitalWrite(buzzer,LOW);
  digitalWrite(led,LOW);
  digitalWrite(pump,LOW);
  
  }
  
  
  if((gas_data > 100)&&(gas_data < 400)){
    gas_data=analogRead(gas_pin);
    window.write(45);
    digitalWrite(buzzer,HIGH);
    digitalWrite(led,HIGH);
    digitalWrite(pump,LOW);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
   
  }
  
  float voltage = analogRead(tsensor) * 5; //sensor temp
  voltage /= 1024.0;
  float temp = (voltage - 0.5) * 100;
  Serial.println(temp);
  
  int light = analogRead(ldr);  //sensor cahaya
  Serial.println(light);
  if (light > 600 && temp > 100 && gas_data > 215)
  {
    window.write(90); //memutar servo ke 90 derajat
    digitalWrite(pump,HIGH);
    digitalWrite(buzzer,HIGH);
    digitalWrite(led,HIGH);
    delay(100);   
    lcd.setCursor(0,0);
    lcd.print("KONDISI DARURAT");
    lcd.setCursor(0,1);
    lcd.print("HUBUNGI PEMADAM");
    delay(1000);
    lcd.clear();
   
  } 
  }      
