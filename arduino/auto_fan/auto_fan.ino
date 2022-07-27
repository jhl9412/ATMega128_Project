#include <Servo.h>
#include <SoftwareSerial.h>

int TX = 2;
int RX = 3;
int trig_r = 4;
int echo_r = 5;
int trig_l = 6;
int echo_l = 7;
int servo_motor = 8;
int motor1EnablePin = 11;
int motor1_1 = 10;
int motor1_2 = 9;

int st = "";

SoftwareSerial soft_Serial(RX, TX);
Servo servo;

int i = 0;
int nSpeed = 0;

void auto_ON();
void auto_OFF();
void distance();
void runMotor(float dis_r, float dis_l);

void setup() {
  soft_Serial.begin(9600);
  Serial.begin(9600);
  pinMode(trig_r, OUTPUT);
  pinMode(echo_r, INPUT);
  pinMode(trig_l, OUTPUT);
  pinMode(echo_l, INPUT);
  servo.attach(servo_motor);

  pinMode(motor1_1, OUTPUT);
  pinMode(motor1_2, OUTPUT);
}

void loop() {
  
  String mode;
  if(soft_Serial.available() > 0)
  {
    mode = soft_Serial.readStringUntil('\n');
    Serial.println(mode);

    if(mode == "auto_ON")
    {
      st = "auto_ON";
    }else if(mode == "auto_OFF")
    {
      st = "auto_OFF";
    }
  }
 
  if(st == "auto_ON")
  {
    auto_ON();
  }
  else if(st == "auto_OFF")
  {
    auto_OFF();
    st="";
  }
}

void auto_ON()
{
  int temp, humi;
  String env;
  do{
    while(soft_Serial.available() == 0){
      if(soft_Serial.available() > 0)
      {
        String off = soft_Serial.readStringUntil('\n');
        Serial.println(off);
        if(off == "auto_OFF")
        {
          st = "auto_OFF";
          break;
        }
      }
    }
    env = soft_Serial.readStringUntil('\n');
// DHT11 추가
    char str_buffer[10];
    strcpy(str_buffer, env.c_str());

    char *ptr = NULL;
    ptr = strtok(str_buffer, ", ");
    temp = atoi(ptr);
    ptr = strtok(NULL, " ");
    humi = atoi(ptr);
//===========================================
    delay(100);

    if (temp >= 20 && humi >= 20)
    {
      distance();
    }
  }while(st == "auto_ON");
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
    
  Serial.print("dis_r = "); 
  Serial.print(dis_r);
  Serial.print(", ");
  Serial.print("dis_l = "); 
  Serial.println(dis_l);

  if(dis_r < 15) {
    for(int j=0; j<50; j++)
    { 
      i = i + j;
      if(i > 180)
      {
        i = 180;
      }
    }
    servo.write(i);
    delay(10);
  }

  if(dis_l < 15) {
    for(int j=0; j<50; j++)
    {
      i = i - j;
      if(i < 0)
      {
        i = 0;
      }
      servo.write(i);
      delay(10);
    }
  }
  runMotor(dis_r, dis_l);
}

void runMotor(float dis_r, float dis_l)
{
  if((dis_r <= 50 && dis_r > 20) || (dis_l <= 50 && dis_l > 20))
  {
    digitalWrite(motor1_1, HIGH);
    digitalWrite(motor1_2, LOW);
    analogWrite(motor1EnablePin, 200);
    Serial.println("speed: 250"); 
    delay(1000);
  }
  else if((dis_r <= 20 && dis_r > 10) || (dis_l <= 20 && dis_l > 10))
  {
    digitalWrite(motor1_1, HIGH);
    digitalWrite(motor1_2, LOW);
    analogWrite(motor1EnablePin, 150);
    Serial.println("speed: 150");
    delay(1000);
  } else {
    digitalWrite(motor1_1, HIGH);
    digitalWrite(motor1_2, LOW);
    analogWrite(motor1EnablePin, 0);
    Serial.println("speed: 0");
    delay(1000);
  }
}

void auto_OFF()
{
  Serial.println("OFF");
  delay(100);
  digitalWrite(motor1_1, HIGH);
  digitalWrite(motor1_2, LOW);
  analogWrite(motor1EnablePin, 0);
}
