/*Echo    - 2
 *Triger  - 3
 *PIR     - 4
 *Buzzer  - 5
 *Alarm   - 6
 *LED WC  - 10
 *LED dpn - 11
 *Garasi  - 12
 *LDR     - A0
 *Api     - A1
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int echopin = 2, trigpin = 3, sensorPIR = 4, buzzer=5;
int ledWC = 10, ledTeras = 11,ledGarasi = 12, saklarAlarm = 6;
int sensorLDR = A0, sensorApi = A1;
int ldr, jarak, waktu, cm, alarm; 

void setup() {
  Serial.begin(9600);
  pinMode(sensorLDR,INPUT);
  pinMode(echopin,INPUT);
  pinMode(saklarAlarm,INPUT);
  pinMode(sensorPIR,INPUT);
  pinMode(sensorApi,INPUT);
  pinMode(ledWC,OUTPUT);
  pinMode(ledTeras,OUTPUT);
  pinMode(ledGarasi,OUTPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,HIGH);
  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("   Persiapan");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Created by :");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Muhammad Raffi");
  lcd.setCursor(0,1);
  lcd.print(" Ibrohim Husain");
  delay(2000);
  lcd.clear();
}

void loop() {
//Sensor PIR
  int pir_input = digitalRead(sensorPIR);
  Serial.println(pir_input);
  delay(500);
  if (pir_input==HIGH){
    digitalWrite(ledWC,HIGH); //Kalo Sensor PIR mendeteksi
  }
  else {
    digitalWrite(ledWC,LOW); //Sensor Pir tidak mendeteksi
  }
//Program Sensor Jarak (Ultrasonik)
  alarm = digitalRead(saklarAlarm);
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  int waktu = pulseIn(echopin,HIGH);
  int jarak = waktu /58;
  if (alarm==HIGH){
    if(jarak<=15){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Ada Orang Diluar!");
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer,HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer,HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer,HIGH);
      delay(10000);
      lcd.clear();
    }
    else {
      digitalWrite(buzzer,HIGH);
      lcd.setCursor(0,0);
      lcd.print("   KELAS 2F");
    } 
  }    
  
//Sensor LDR
  ldr = analogRead(sensorLDR);
  if (ldr<=500){
    digitalWrite(ledTeras,LOW);  
    digitalWrite(ledGarasi,LOW);
  }
  else {
    digitalWrite(ledTeras,HIGH);
    digitalWrite(ledGarasi,HIGH);
  }

//Sensor Api
  int state = digitalRead(sensorApi);
  Serial.print(state);
  if(state==HIGH){
    digitalWrite(buzzer,HIGH);
    delay(200);
    digitalWrite(buzzer,LOW);
    delay(200);
    digitalWrite(buzzer,HIGH);
    delay(200);
    digitalWrite(buzzer,LOW);
    delay(200);
  }else{
    digitalWrite(buzzer, HIGH);
  }
}
