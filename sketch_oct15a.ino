//identifying pin 2 as constant trigger pin input, and pin 3 as constant echo pin input 
const int trigPin = 2;  
const int echoPin = 3; 

int ledR=10; //identifying pin 10 LED 1 (named R to signal red LED) 
int ledY=11; //identifying pin 11 LED 2 (named Y to signal yellow LED)

//setting the distance for the LEDs to light up - height of the bowl in inches 
//added own measurement values 
int a=2.5; 
int b=1.875; 
int c=1.25;
int d=0;

int max_distance = 5;

void setup() {
  // put your setup code here, to run once:


Serial.begin(9600); //opens serial port, sets data rate to 9600 bps 
//setting LEDs as output - receiving an output signal 
pinMode (ledR,OUTPUT); 
pinMode (ledY,OUTPUT);

//initialising as LOW (off)
//5V is HIGH (connected to 5V port on ardino) and 0 is LOW 
digitalWrite(ledR, LOW);
digitalWrite(ledY, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

long duration, inches, cm; 
pinMode(trigPin,OUTPUT);
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(trigPin, LOW); 
pinMode(echoPin, INPUT); 
duration = pulseIn(echoPin, HIGH); 

//cm = ( duration / 29 ) / 2;
//inches = cm * 0.393701;
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);

if (inches <max_distance){
Serial.print(inches);
Serial.print(" in");
Serial.print(cm);
Serial.print(" cm");
Serial.println();
delay(100);
}
//digitalWrite (ledA,HIGH);
if (inches >=a) {digitalWrite (ledR,HIGH);digitalWrite (ledY,LOW); }  
else if (inches >=b){digitalWrite (ledR,LOW);digitalWrite (ledY,HIGH);  } 
else if (inches >=c){digitalWrite (ledR,LOW);digitalWrite (ledY,LOW); } 
else if (inches >=d){digitalWrite (ledR,LOW);digitalWrite (ledY,LOW); } 
//else {digitalWrite (ledA,HIGH);digitalWrite (ledB,HIGH); } 

}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return (microseconds / 74) / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return (microseconds / 29) / 2;
}

