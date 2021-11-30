#include <LiquidCrystal.h>
#include<Wire.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int tempPin = A0; // the output pin of LM35
int fan = 11; // the pin where fan is
int temp;
int tempMin=0; // the temperature to start the fan 0%
int tempMax = 4; // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD;

int green_led =9;

int motion=7;

#define red_led 8 // led pin: indicates its hot
int blue_led = 13;// led pin: indicates it's cold
 
void setup() {
//Serial.begin(115200);
pinMode(red_led, OUTPUT);
pinMode(blue_led, OUTPUT);
pinMode(green_led, OUTPUT);

pinMode(motion, INPUT);

pinMode(tempPin, INPUT);
lcd.begin(16,2);
digitalWrite(red_led, LOW);
digitalWrite(blue_led, LOW);
lcd.print("Welcome ELG3336!");
lcd.setCursor(0,1); // move cursor to next line
lcd.print("The WindMill! :)");
delay(5000);
lcd.clear();

int motion_value= digitalRead(motion);

if(motion_value== HIGH){

  lcd.print("Motion Detected!");
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("Red light = on!");
  digitalWrite(red_led,HIGH);
  delay(4000);
  lcd.clear();
}

digitalWrite(red_led, LOW);



}
 
void loop(){

temp = readTemp(); // get the temperature
Serial.print( temp );


lcd.clear();

if(temp < tempMin) // if temp is lower than minimum temp
{
 digitalWrite(red_led, LOW);
digitalWrite(blue_led, HIGH);
lcd.print("It's COLD!");
delay(2000);
lcd.clear();
lcd.print("Blue LED = ON!");
delay(2000);
lcd.clear();

}
if((temp >= tempMin) && (temp <= tempMax)) // if temperature is higher than minimum temp
{
lcd.print("Good condition:");
delay(4000);
lcd.setCursor(0,1);
lcd.print("both LEDs=off");
delay(4000);
lcd.clear();
}
if(temp > tempMax) // if temp is higher than tempMax
{
digitalWrite(red_led, HIGH); // turn on led
digitalWrite(blue_led, LOW); // turn off blue led
lcd.print("It's HOT!");
delay(2000);
lcd.clear();
lcd.print("Red LED = ON!");
delay(2000);
lcd.clear();

}

else // else turn of led
{
digitalWrite(red_led, LOW);
digitalWrite(blue_led, LOW);

}
 
lcd.print("    TEMP: ");
lcd.print(temp); // display the temperature
lcd.print("C ");

lcd.setCursor(0,1); // move cursor to next line
lcd.print("   Humidity:");
lcd.print("32%");
delay(3000);
lcd.clear();
lcd.print("    TEMP: ");
lcd.print(temp+1); // display the temperature
lcd.print("C ");

lcd.setCursor(0,1); // move cursor to next line
lcd.print("   Humidity:");
lcd.print("33%");
delay(10000);
lcd.clear();
}
 
int readTemp() { // get the temperature and convert it to celsius
temp = analogRead(tempPin);
return temp-1000;
}
