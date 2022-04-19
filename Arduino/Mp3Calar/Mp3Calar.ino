#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
bool sesgiris[10] {0};
int girisno = 0;
int toplam = 0;
void printDetail(uint8_t type, int value);
void setup()
{
mySoftwareSerial.begin(9600);
Serial.begin(9600);
Serial.println();
Serial.println(F("DFRobot DFPlayer Mini Demo"));
Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
if(!myDFPlayer.begin(mySoftwareSerial)) {
Serial.println(F("Unable to begin:"));
Serial.println(F("DFPlayer Mini online."));
}
myDFPlayer.setTimeOut(1000);
//----Set volume----
myDFPlayer.volume(30); //Set volume value (0~30).
//----Set different EQ----
myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
pinMode(2, INPUT);

for (int i=0;i<10;i++)
{
  sesgiris[i] = false;
}
}


void loop()
{
if (digitalRead(2)==1) 
{ sesgiris[girisno] = true; }
else
{ sesgiris[girisno] = false; };

for (int i=0;i<10;i++)
{
  if (sesgiris[i]==true)
  {
    toplam = toplam + 1;
  }
}

Serial.println("toplam:"+String(toplam));

if (toplam>2)
{
  for (int i=0;i<10;i++)
  {
    sesgiris[i] = false;
  }
  Serial.println(digitalRead(2));
  Serial.println("Çalma Başladı...");
  myDFPlayer.start();
  myDFPlayer.randomAll(); //Random play all the mp3.
  delay(900000);
  Serial.println("Çalma Durdu...");
  myDFPlayer.stop();
  delay(300000);
  Serial.println("Bekleme Bitti...");  
}
toplam = 0;
girisno = girisno + 1;
if (girisno>9) { girisno=0; }
delay(100);
}
