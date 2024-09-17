#include <dht11.h>
#define DHT11PIN 8
dht11 DHT11;
int t, h;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27, 16, 2);
int buzz = 13;
int mq2 = A0;
int mq135 = A1;
int mq2_value = 0;
int mq135_value = 0;

void setup()
{
Serial.begin(9600);
pinMode(buzz, OUTPUT);
digitalWrite(buzz, LOW);
pinMode(mq2, INPUT);
pinMode(mq135, INPUT);
lcd.init();
lcd.backlight();
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("  TOXIC GASES ");
lcd.setCursor(0, 1);
lcd.print("MONITORING SYSTEM ");
delay(3000);
lcd.clear();
}
void loop()
{
  mq2_value = analogRead(mq2);
  mq135_value = analogRead(mq135);
  int chk = DHT11.read(DHT11PIN);
  h = (float)DHT11.humidity;
  t = (float)DHT11.temperature;
lcd.setCursor(0, 0);
lcd.print("M2:   ");
lcd.setCursor(3, 0);
lcd.print(mq2_value);
lcd.setCursor(7, 0);
lcd.print("M135:    ");
lcd.setCursor(0x0C, 0);
lcd.print(mq135_value);
lcd.setCursor(0, 1);
lcd.print("TEMP:");
lcd.setCursor(5, 1);
lcd.print(t);
lcd.setCursor(7, 1);
lcd.print("C");
lcd.setCursor(9, 1);
lcd.print("HUM:");
lcd.setCursor(0X0D, 1);
lcd.print(h);
lcd.setCursor(0X0F, 1);
lcd.print("%");
delay(3000);
  if (mq2_value >= 200)
  {
digitalWrite(buzz, HIGH);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("FLAMMABLE GAS");
lcd.setCursor(0, 1);
lcd.print("    DETECTED   ");
Serial.println();
Serial.print("AT+CMGS=");     // Send the SMS number. To whome message to send.
Serial.print("\"+917416355929\"");// paste your number
Serial.println();
delay(500);
digitalWrite(buzz, LOW);
delay(2000);
Serial.print("ALERT! FLAMMABLE GAS DETECTED...."); // SMS-Message body
delay(4000);
Serial.println();
Serial.write(26);
lcd.clear();
  }
  if (mq135_value >= 400)
  {
digitalWrite(buzz, HIGH);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(" TOXIC GASES ");
lcd.setCursor(0, 1);
lcd.print("   DETECTED   ");
Serial.println();
Serial.print("AT+CMGS=");     // Send the SMS number. To whome message to send.
Serial.print("\"+917416355929\"");// paste your number
Serial.println();
delay(500);
digitalWrite(buzz, LOW);
delay(2000);
Serial.print("ALERT! TOXIC GASES DETECTED...."); // SMS-Message body
delay(4000);
Serial.println();
Serial.write(26);
lcd.clear();
  }
  if (t >= 35)
  {
digitalWrite(buzz, HIGH);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("  TEMPERATURE ");
lcd.setCursor(0, 1);
lcd.print("   EXCEEDS...   ");
Serial.println();
Serial.print("AT+CMGS=");     // Send the SMS number. To whome message to send.
Serial.print("\"+917416355929\"");// paste your number
Serial.println();
delay(500);
digitalWrite(buzz, LOW);
delay(2000);
Serial.print("ALERT! TEMPERATURE EXCEEDS...."); // SMS-Message body
Serial.println();
Serial.print("TEMPERATURE:");
Serial.println(t);
delay(4000);
Serial.println();
Serial.write(26);
lcd.clear();
  }}

