#include <String.h>
#include <SoftwareSerial.h>
#include <Keypad.h>
SoftwareSerial mySerial(52, 53);

int greenLED = 12;


//set our code
char* ourCode = "1234";
int currentPosition = 0;

//define the keypad
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );




void setup()
{
  mySerial.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);    // the GPRS baud rate 
  delay(500);
  
 
  pinMode(greenLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  
}

void loop()
{
  int l;
  
  char key = keypad.getKey();
  
  if (int(key) != 0) {
    
    
    for (l=0; l<=currentPosition; ++l)
    {
      //lcd.print("*");
    }
    
    if (key == ourCode[currentPosition])
      {
        ++currentPosition;
        if (currentPosition == 4)
        {
          unlockDoor();
          currentPosition = 0;
        }
      } else {
        invalidCode();
        currentPosition = 0;
      }
    }
}

void invalidCode()
{ DialVoiceCall(); 
 }

void unlockDoor()
{
  digitalWrite(greenLED, HIGH);
  delay(1000);
  digitalWrite(greenLED, LOW);
 }
void DialVoiceCall()
{
  mySerial.println("ATD + +880XXXXXXXXXX;");//dial the number
  delay(100);
  mySerial.println();
}


