
#include <Servo.h> 
#include <SoftwareSerial.h>

SoftwareSerial BT(0, 1); //TX, RX respetively
String readvoice;
Servo myservo;  // create servo object to control a servo 
float val;
float ran;
int  ans;
int distanceCm;
int duration;
//int const LED=13;
int const MOTOR1=4;
int const MOTOR2=5;
int const MOTOR3=6;
int const MOTOR4=7;
const int trigPin = 11;
const int echoPin = 10;
int disleft;
int disright;
int pirsin;
int count;
int i;
int smallright=300;
int smallleft=300;
int pirSensor = 2;
int led = 13;

void setup() {
 BT.begin(9600);
 //Serial.begin(9600);
  pinMode(MOTOR1,OUTPUT);
pinMode(MOTOR2,OUTPUT);
pinMode(MOTOR3,OUTPUT);
pinMode(MOTOR4,OUTPUT);
Serial.begin(9600); // Starting Serial Terminal
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
myservo.attach(9);
pinMode(pirSensor, INPUT);
  pinMode(led, OUTPUT);  
}
//-------------------------------------------------------------------------------YOGESH_JADHAV-----------------------------------------------------------------------------------// 
void left()
{
    digitalWrite(MOTOR1,LOW);
    digitalWrite(MOTOR2,HIGH);   //LEFT turn
    digitalWrite(MOTOR3,LOW);
    digitalWrite(MOTOR4,LOW);
    delay(500);
}

void right()
{
  digitalWrite(MOTOR1,LOW);
  digitalWrite(MOTOR2,LOW);   //RIGHT turn
  digitalWrite(MOTOR3,HIGH);
  digitalWrite(MOTOR4,LOW);
  delay(500);
}

void back()
{
  digitalWrite(MOTOR1,HIGH);
  digitalWrite(MOTOR2,LOW);  //backward
  digitalWrite(MOTOR3,LOW);
  digitalWrite(MOTOR4,HIGH);
  delay(400);
  digitalWrite(MOTOR1,LOW);
  digitalWrite(MOTOR2,LOW);  //backward
  digitalWrite(MOTOR3,LOW);
  digitalWrite(MOTOR4,LOW);
}

void front()
{
  digitalWrite(MOTOR1,LOW);
  digitalWrite(MOTOR2,HIGH);
  digitalWrite(MOTOR3,HIGH); //forward
  digitalWrite(MOTOR4,LOW);
}

void stand()
{
  digitalWrite(MOTOR1,LOW);
  digitalWrite(MOTOR2,LOW);   //stop
  digitalWrite(MOTOR3,LOW);
  digitalWrite(MOTOR4,LOW);
  delay(100);
}

int check_leftRight()
{
  myservo.write(80);
  for(i=80;i<=170;i++)
  {
    myservo.write(i);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    disright= duration*0.034/2;
    if(disright<smallright)
    {
        smallright=disright;
    }
    delay(50);
  } 
  for(i=80;i>=0;i--)
  {
    myservo.write(i);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    disright= duration*0.034/2;
    if(disleft<smallleft)
    {
        smallleft=disleft;
    }
    delay(50);
  }
  Serial.println(smallleft);
   Serial.println(smallright);
  myservo.write(80);
 if(disleft>disright)
 {
     return 0;
 }
 if(disright>disleft)
 {
     return 1;
 }
  
}

int check_distance()
{
  myservo.write(80);
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  return distanceCm;
}

void pir()
{
  int sensorValue = digitalRead(pirSensor);
  if (sensorValue == 1) {
    digitalWrite(led, HIGH); // The Relay Input works Inversly
  }
  else
  {
  digitalWrite(led,LOW);
  }
}




void loop() 
{
  while (BT.available())
  {  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readvoice += c; //build the string- "forward", "reverse", "left" and "right"
  } 
  if (readvoice.length() > 0) {
   Serial.println(readvoice);
  } 
  pir();
  myservo.write(80);
  val=check_distance();
   if(val<50)
{
   stand();
   ans=check_leftRight();
   if(ans==1)
   {
   myservo.write(80);
   left();
   front();
   Serial.println("left");
   }
   if(ans==0)
   {
   myservo.write(80);
   right();
   front();
   Serial.println("right");
   }
   
}

if(readvoice == "*forward#")
  {
   myservo.write(80);
   val=check_distance();
   if(val<50)
{
   stand();
   ans=check_leftRight();
   if(ans==1)
   {
     myservo.write(80);
   left();
   front();
   }
   if(ans==0)
   {
     myservo.write(80);
   right();
   front();
   }
}

else
{
  front();
  myservo.write(80);
}
  }

  else if(readvoice == "*back#")
  {
    myservo.write(80);
  back();
  }

  else if (readvoice == "*right#")
  {
    right();
    myservo.write(80);
    val=check_distance();
   if(val<50)
{
   stand();
   ans=check_leftRight();
   if(ans==1)
   {
     myservo.write(80);
   left();
   front();
   }
   if(ans==0)
   {
     myservo.write(80);
   right();
   front();
   }
}

else
{
  front();
  myservo.write(80);
}
  }

 else if ( readvoice == "*left#")
 {
   left();
   myservo.write(80);
   val=check_distance();
   if(val<50)
{
   stand();
   ans=check_leftRight();
   if(ans==1)
   {
     myservo.write(80);
   left();
   front();
   }
   if(ans==0)
   {
     myservo.write(80);
   right();
   front();
   }
}

else
{
  front();
  myservo.write(80);
}
 }

 else if (readvoice == "*stop#")
 {
   stand();
   myservo.write(80);
 }


readvoice="";
 } //Reset the variable
 
