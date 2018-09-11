const int trigPin = 3;
const int echoPin = 2;
const int MotVib=10; //Vibrating motor control pin
const int Mod1Pin=5; //Distance selector control pin
const int Dmax1=70; //The maximum distance on "short distance mode"
const int Dmin1=25; //The minimum distance on "short distance mode" 
const int Dmax2=200;//The maximum distance on "long distance mode"
const int Dmin2=25; //The minimum distance on "long distance mode"
const int Pauza=30; //Time between two Trig's
long duration, duration_last;
int distance;
int frecventa;



void setup() {

pinMode(trigPin, OUTPUT); // Trig pin set for output
pinMode(echoPin, INPUT); // Echo pin set for input
pinMode(MotVib, OUTPUT); // Vibration Motor pin set for output
pinMode(Mod1Pin, INPUT); // Distance Selector Mode pin for input

//Serial.begin(9600);  //To be used only for diagnostic purposes
}

void loop() {

if(digitalRead(Mod1Pin)==HIGH)
{
  //If the distance selector is set to short distance: 
duration_last=8000;
for(int i=0;i<6;i++)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Trig pin is set to HIGH for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
//Echo pin is read. It returns the time between the emision and the reception of the ultrasonic wave in microseconds
//If 7000 microseconds are passing and there is no pulsein, the function returns 0 (timeout).
duration = pulseIn(echoPin, HIGH, 7000);
if(duration!=0)
{
  if(duration<duration_last)
  {
    duration_last=duration;
  }
}

}

 //distance calculation using sound speed 0.034 cm/us:
distance= ( duration_last*0.034)/2;  
//Serial.println(distance); //To be used only for diagnostic

//Send pulses to the vibration motor, with a frequency inversely proportional to the distance  
if(distance<Dmax1)
{
 if(distance>Dmin1)
 {
 frecventa=100+155*(Dmax1-distance)/(Dmax1-Dmin1);
  analogWrite(MotVib, frecventa);

 }
 else
 {
  //If the distance selector is set to long distance:
  analogWrite(MotVib,255);
 }
}
else
{
  analogWrite(MotVib, 0);
}
}

else
{
  duration_last=16000;
for(int i=0;i<12;i++)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Trig pin is set to HIGH for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
//Echo pin is read. It returns the time between the emision and the reception of the ultrasonic wave in microseconds
//If 15000 microseconds are passing and there is no pulsein, the function returns 0 (timeout).
duration = pulseIn(echoPin, HIGH, 15000);
if(duration!=0)
{
  if(duration<duration_last)
  {
    duration_last=duration;
  }
}

}

 //distance calculation using sound speed 0.034 cm/us:
distance= ( duration_last*0.034)/2;
//Serial.println(distance); //To be used only for diagnostic purposes

if(distance<Dmax2)
{
 if(distance>Dmin2)
 {
 frecventa=100+155*(Dmax2-distance)/(Dmax2-Dmin2);
 analogWrite(MotVib, frecventa);
 }
 else
 {
 analogWrite(MotVib,255);
 }
}
else
{
  analogWrite(MotVib, 0);
}
}

}

