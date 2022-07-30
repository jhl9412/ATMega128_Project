#include <DFRobot_DHT11.h>
#include <SoftwareSerial.h>

#define DHT11_PIN 12
DFRobot_DHT11 DHT;

int TX = 2;
int RX = 3;
int trig_r = 4;
int echo_r = 5;
int trig_l = 6;
int echo_l = 7;
char data[50];
int temp, humi;
SoftwareSerial soft_Serial(RX, TX);

void setup() {
  // put your setup code here, to run once:
  soft_Serial.begin(9600);
  Serial.begin(9600);
  pinMode(trig_r, OUTPUT);
  pinMode(echo_r, INPUT);
  pinMode(trig_l, OUTPUT);
  pinMode(echo_l, INPUT);
  soft_Serial.println("test");
}

void loop() {
  // put your main code here, to run repeatedly:
  distance();
}

void distance()
{

  unsigned long duration_r;
  float dis_r;
  unsigned long duration_l;
  float dis_l;
    
  digitalWrite(trig_r, LOW);
  digitalWrite(echo_r, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_r, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_r, LOW);
  duration_r = pulseIn(echo_r, HIGH); 
  dis_r = duration_r/29.0/2.0;

  digitalWrite(trig_l, LOW);
  digitalWrite(echo_l, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_l, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_l, LOW);
  duration_l = pulseIn(echo_l, HIGH); 
  dis_l = duration_l/29.0/2.0;

  DHT.read(DHT11_PIN);
  if(DHT.temperature<100){
    temp = DHT.temperature;
    humi = DHT.humidity;
  }
  sprintf(data,"L%dL%dL%dL%dL",(int)dis_r,(int)dis_l,temp,humi);
  soft_Serial.println(data);
  Serial.println(data); 

}
