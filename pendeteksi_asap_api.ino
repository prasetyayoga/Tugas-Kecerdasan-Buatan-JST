#define sensorLightPin    A2

int tsensor = A0;
int pump = 7; 
int ldr = A1;
int gas_pin= A2;
float gas_data= A2;
 
void setup() 
{
  pinMode(ldr, INPUT);
  pinMode(tsensor, INPUT);
  pinMode(pump,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
 Serial.println(gas_data);

  if(gas_data<100){
  gas_data=analogRead(gas_pin);
  digitalWrite(led,LOW);
  digitalWrite(pump,LOW);
  }
  
  if((gas_data > 100)&&(gas_data < 400)){
    gas_data=analogRead(gas_pin);
    digitalWrite(led,HIGH);
    digitalWrite(pump,LOW);
  }
  
  float voltage = analogRead(tsensor) * 5; //sensor temp
  voltage /= 1024.0;
  float temp = (voltage - 0.5) * 100;
  Serial.println(temp);
  
  int light = analogRead(ldr);  //sensor cahaya
  Serial.println(light);
  if (light > 600 && temp > 100 && gas_data > 215)
  {
    digitalWrite(pump,HIGH);
    digitalWrite(led,HIGH);
  } 
  }      
