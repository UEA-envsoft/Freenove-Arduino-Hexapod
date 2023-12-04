
#include "HexaHead.h"


HexaHead::HexaHead() {}

int buzzer;
int emotion_time_next = 0;
int emotion_time_now = 0;
int emotion_count = 0;
int servo_time_next = 0;
int servo_time_now = 0;
int headAngleCorrection = 9;
bool asleep = true;

  void  HexaHead::Sleep(void)
{
  Serial.println("SLEEP");
  asleep = true;
}
  void  HexaHead::Wake(void)
{
  
  Serial.println("WAKE");
  asleep = false;
}



//****************** Display  ******************************

//initialize HT16K33
void HexaHead::Emotion_Setup(int address)
{
  matrix.init(address);
  matrix.setBrightness(15);
  matrix.setBlink(VK16K33_BLINK_OFF);
  emotion_time_now = millis();
  //configure matrix as OPEN-SMART 0.8" Inch 16x8 I2C LED Dot Matrix Display
  matrix.openSmart();
  //emotion_time_now = millis();


  HexaHead::Emotion_SetMode(1);
  HexaHead:Emotion_Show();
}


int emotion_task_mode = 0;
int emotion_current_mode = 0;
//Emotion show
void HexaHead::Emotion_Show(void)
{
  if (emotion_task_mode!= emotion_current_mode)
  {
    Serial.print("new emo mode is ");
    Serial.println(emotion_task_mode);
  }
  if (emotion_task_mode == 0)
    HexaHead::clearEmtions();
  else if (emotion_task_mode == 1)
    HexaHead::emoGrin(200);
  else if (emotion_task_mode == 2)
    HexaHead::emoAngry(200);
  else if (emotion_task_mode == 3)
    HexaHead::emoSuprise(200);
  else if (emotion_task_mode == 4)
    HexaHead::emoSad(200);
  else HexaHead::clearEmtions();
}

//Emotion set mode
void  HexaHead::Emotion_SetMode(int mode)
{
  if (mode <= 4) {
    emotion_task_mode = mode;
    emotion_count = 0;
  }
}


//clear
byte clearEmotion[][8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
//clear all
void HexaHead::clearEmtions(void)
{
  emotion_time_next = millis();
  if (emotion_time_next - emotion_time_now >= 500)
  {
    emotion_time_now = emotion_time_next;
    emotion_count = 0;
    int count = sizeof(clearEmotion) / sizeof(clearEmotion[0]);
    for (int i = 0; i < count; i++)
      matrix.showStaticArray(clearEmotion[i], clearEmotion[i]);
  }
}


//*************************  GRIN  ***************************
byte grinL[][8] = {
  0x80,0x40,0x8F,0x8F,0x80,0x40,0x38,0x07,
  0x90,0x5C,0x8B,0x88,0x87,0x40,0x38,0x07,
  0xA0,0x5C,0x8B,0x88,0x84,0x43,0x38,0x07,
  0x90,0x5C,0x8B,0x88,0x87,0x40,0x38,0x07,
};

byte grinR[][8] = {
  0x01,0x02,0xF1,0xF1,0x01,0x02,0x1C,0xE0,
  0x09,0x3A,0xD1,0x11,0xE1,0x02,0x1C,0xE0,
  0x05,0x3A,0xD1,0x11,0x21,0xC2,0x1C,0xE0,
  0x09,0x3A,0xD1,0x11,0xE1,0x02,0x1C,0xE0, 
};


void HexaHead::emoGrin(int delay_ms)
{
  emotion_time_next = millis();
  if (emotion_time_next - emotion_time_now >= delay_ms)
  {
    emotion_time_now = emotion_time_next;
    if (emotion_task_mode!= emotion_current_mode)  //we are currently displaying something else
    {
      //display intermediate
      HexaHead::complete_emotion(emotion_current_mode);
      emotion_current_mode = emotion_task_mode;        
      emotion_count = 0;  
    }
    else
    {
      if (emotion_count == 0) sing(S_happy);
      //emotion count 2 is main expression so if we have reached 3 do nowt
      if (emotion_count < 3) 
      {
        matrix.showStaticArray(grinL[emotion_count], grinR[emotion_count]);
        emotion_count++;
      }
    }
  }
}


//*************************  SUPRISE  ***************************
byte suprL[][8] = {
0x80,0x40,0x8F,0x8F,0x80,0x40,0x38,0x07,
0x80,0x47,0x88,0x88,0x87,0x40,0x38,0x07,
0x83,0x44,0x88,0x88,0x84,0x43,0x38,0x07,
0x80,0x47,0x88,0x88,0x87,0x40,0x38,0x07,
};

byte suprR[][8] = {
0x01,0x02,0xF1,0xF1,0x01,0x02,0x1C,0xE0,
0x01,0xE2,0x11,0x11,0xE1,0x02,0x1C,0xE0,
0xC1,0x22,0x11,0x11,0x21,0xC2,0x1C,0xE0,
0x01,0xE2,0x11,0x11,0xE1,0x02,0x1C,0xE0,

};


void HexaHead::emoSuprise(int delay_ms)
{
  emotion_time_next = millis();
  if (emotion_time_next - emotion_time_now >= delay_ms)
  {
    emotion_time_now = emotion_time_next;
    if (emotion_task_mode!= emotion_current_mode)  //we are currently displaying something else
    {
      //display intermediate
      HexaHead::complete_emotion(emotion_current_mode);
      emotion_current_mode = emotion_task_mode;        
      emotion_count = 0;  
    }
    else
    {
      if (emotion_count == 0) sing(S_surprise);
      //emotion count 2 is main expression so if we have reached 3 do nowt
      if (emotion_count < 3) 
      {
        matrix.showStaticArray(suprL[emotion_count], suprR[emotion_count]);
        emotion_count++;
      }
    }
  }
}

//*************************  ANGRY  ***************************
byte angrL[][8] = {
0x80,0x40,0x8F,0x8F,0x80,0x40,0x38,0x07,
0x80,0x47,0x88,0x88,0x87,0x40,0x38,0x07,
0x8F,0x55,0x90,0x94,0x8D,0x47,0x38,0x07,
0x80,0x47,0x88,0x88,0x87,0x40,0x38,0x07,
};

byte angrR[][8] = {
0x01,0x02,0xF1,0xF1,0x01,0x02,0x1C,0xE0,
0x01,0xE2,0x11,0x11,0xE1,0x02,0x1C,0xE0,
0xF1,0xAA,0x09,0x29,0xB1,0xE2,0x1C,0xE0,
0x01,0xE2,0x11,0x11,0xE1,0x02,0x1C,0xE0,
};


void HexaHead::emoAngry(int delay_ms)
{
  emotion_time_next = millis();
  if (emotion_time_next - emotion_time_now >= delay_ms)
  {
    emotion_time_now = emotion_time_next;
    if (emotion_task_mode!= emotion_current_mode)  //we are currently displaying something else
    {
      //display intermediate
      HexaHead::complete_emotion(emotion_current_mode);
      emotion_current_mode = emotion_task_mode;        
      emotion_count = 0;  
    }
    else
    {
      if (emotion_count == 0) sing(S_OhOoh2);
      //emotion count 2 is main expression so if we have reached 3 do nowt
      if (emotion_count < 3) 
      {
        matrix.showStaticArray(angrL[emotion_count], angrR[emotion_count]);
        emotion_count++;
      }
    }
  }
}

//*************************  SAD  ***************************
byte sadL[][8] = {
0x80,0x40,0x8F,0x8F,0x80,0x40,0x38,0x07,
0x80,0x40,0x87,0x8F,0x90,0x40,0x38,0x07,
0x80,0x40,0x87,0x88,0x97,0x58,0x20,0x1F,
0x80,0x40,0x87,0x8F,0x90,0x40,0x38,0x07,
};

byte sadR[][8] = {
0x01,0x02,0xF1,0xF1,0x01,0x02,0x1C,0xE0,
0x01,0x02,0xE1,0xF1,0x09,0x02,0x1C,0xE0,
0x01,0x02,0xE1,0x11,0xE9,0x1A,0x04,0xF8,
0x01,0x02,0xE1,0xF1,0x09,0x02,0x1C,0xE0,
};


void HexaHead::emoSad(int delay_ms)
{
  emotion_time_next = millis();
  if (emotion_time_next - emotion_time_now >= delay_ms)
  {
    emotion_time_now = emotion_time_next;
    if (emotion_task_mode!= emotion_current_mode)  //we are currently displaying something else
    {
      //display intermediate
      HexaHead::complete_emotion(emotion_current_mode);
      emotion_current_mode = emotion_task_mode;        
      emotion_count = 0;  
    }
    else
    {
      if (emotion_count == 0) sing(S_sad);
      //emotion count 2 is main expression so if we have reached 3 do nowt
      if (emotion_count < 3) 
      {
        matrix.showStaticArray(sadL[emotion_count], sadR[emotion_count]);
        emotion_count++;
      }
    }
  }
}

void HexaHead::complete_emotion(int emo_no)
{
   //display intermediate
      switch(emo_no) 
      {
        case 0:
          // code block
          break;
        case 1:  //Grin
          matrix.showStaticArray(grinL[1], grinR[1]);
          break;
        case 2:  //Suprise
          matrix.showStaticArray(suprL[1], suprR[1]);
          break;
        case 3:  //Angry
          matrix.showStaticArray(angrL[1], angrR[1]);
          break;
        case 4:  //Sad
          matrix.showStaticArray(sadL[1], sadR[1]);
          break;
        default:
          // code block
          break;
      }
}

//****************** Servo  ******************************

  void HexaHead::servo_setup(int pin)
  {
  servoHead.attach (pin);      
  servoHead.write (servoHeadAngle); 
  servo_time_now = millis();
  }

  void HexaHead::servo_scan(void)
  {       
    if (asleep)  
    {
      if (servoHeadAngle < 90)  servoHeadAngle++;
      if (servoHeadAngle > 90)  servoHeadAngle--;
      if (servoHeadAngle != 90) servoHead.write (servoHeadAngle + headAngleCorrection);   
    }
    else
    {
      servo_time_next = millis();
      //2ms between movements unless we are at a measuring angle
      //if (servoHeadAngle  < 63 || (servoHeadAngle > 87 && servoHeadAngle < 93 ) || servoHeadAngle > 117 || servo_time_next - servo_time_now >= 10)
      if (servo_time_next - servo_time_now >= 2)
      {
        //Serial.println(servoHeadAngle);
        servo_time_now = servo_time_next;
        if (servoScanUp) servoHeadAngle+=2;
        else servoHeadAngle--;
        if (servoHeadAngle <= 60) servoScanUp = true;
        if (servoHeadAngle >= 120) servoScanUp = false;        
        servoHead.write (servoHeadAngle + headAngleCorrection); 
        //average 3 readings for distances
        if (servoHeadAngle  == 60 ) 
        {
          //Serial.println("RIGHT");
          HexaHead::dist_right =  HexaHead::Ultrasonic_Get_Distance();
        }
        if (servoHeadAngle == 90 ) 
        {          
          //Serial.println("MID");
          HexaHead::dist_fwd = HexaHead::Ultrasonic_Get_Distance();
        }
        if (servoHeadAngle == 120 ) 
        {
          //Serial.println("LEFT");
          HexaHead::dist_left = HexaHead::Ultrasonic_Get_Distance();
        }
      }
    }
  }
//****************** Ultrasonic  ******************************

unsigned int HighByte = 0;
unsigned int LowByte  = 0;
unsigned int Len  = 0;


void HexaHead::Ultrasonic_Setup(void)
{
  Serial3.begin(9600);
}

int HexaHead::Ultrasonic_Get_Distance()
{
  int distance = -1;
   Serial3.flush();
  Serial3.write(0X55);                           // trig US-100 begin to measure the distance
  
  delay(50);                                  
  if (Serial3.available() >= 2)                  // check receive 2 bytes correctly
  {
    HighByte = Serial3.read();
    LowByte  = Serial3.read();
    Len  = HighByte * 256 + LowByte;          // Calculate the distance
    if ((Len > 1) && (Len < 10000))
    {
      distance = Len/10;             
    }
  }
  return distance;
}


  //**********************    Buzzer   **************************************************

void HexaHead::Buzzer_Setup(int pin)
{
  HexaHead::pinBuzzer = pin;
  pinMode(pin, OUTPUT); // Set buzzer - pin as an output
  HexaHead::Buzzer_Beep();
}



void HexaHead::Buzzer_Beep(void)
{
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(100);        // ...for .1 sec
  noTone(buzzer);     // Stop sound...
}

///////////////////////////////////////////////////////////////////
//-- SOUNDS -----------------------------------------------------//

// all of the following sounds code is based on code used in the OttoDIY robots
// https://github.com/OttoDIY/OttoDIYLib
///////////////////////////////////////////////////////////////////

void HexaHead::_tone (float noteFrequency, long noteDuration, int silentDuration){

    // tone(10,261,500);
    // delay(500);
      if(silentDuration==0){silentDuration=1;}

      tone(HexaHead::pinBuzzer, noteFrequency, noteDuration);
      delay(noteDuration);       //milliseconds to microseconds

      noTone(pinBuzzer);
      delay(silentDuration);
}

void HexaHead::bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration){

  //Examples:
  //  bendTones (880, 2093, 1.02, 18, 1);
  //  bendTones (note_A5, note_C7, 1.02, 18, 0);
  if(silentDuration==0){silentDuration=1;}

  if(initFrequency < finalFrequency)
  {
      for (int i=initFrequency; i<finalFrequency; i=i*prop) {
          _tone(i, noteDuration, silentDuration);
      }

  } else{
      for (int i=initFrequency; i>finalFrequency; i=i/prop) {
          _tone(i, noteDuration, silentDuration);
      }
  }
}

void HexaHead::sing(int songName){
  switch(songName){

    case S_connection:
      _tone(note_E5,50,30);
      _tone(note_E6,55,25);
      _tone(note_A6,60,10);
    break;

    case S_disconnection:
      _tone(note_E5,50,30);
      _tone(note_A6,55,25);
      _tone(note_E6,50,10);
    break;

    case S_buttonPushed:
      bendTones (note_E6, note_G6, 1.03, 20, 2);
      delay(30);
      bendTones (note_E6, note_D7, 1.04, 10, 2);
    break;

    case S_mode1:
      bendTones (note_E6, note_A6, 1.02, 30, 10);  //1318.51 to 1760
    break;

    case S_mode2:
      bendTones (note_G6, note_D7, 1.03, 30, 10);  //1567.98 to 2349.32
    break;

    case S_mode3:
      _tone(note_E6,50,100); //D6
      _tone(note_G6,50,80);  //E6
      _tone(note_D7,300,0);  //G6
    break;

    case S_surprise:
      bendTones(800, 2150, 1.02, 10, 1);
      bendTones(2149, 800, 1.03, 7, 1);
    break;

    case S_OhOoh:
      bendTones(880, 2000, 1.04, 8, 3); //A5 = 880
      delay(200);

      for (int i=880; i<2000; i=i*1.04) {
           _tone(note_B5,5,10);
      }
    break;

    case S_OhOoh2:
      bendTones(1880, 3000, 1.03, 8, 3);
      delay(200);

      for (int i=1880; i<3000; i=i*1.03) {
          _tone(note_C6,10,10);
      }
    break;

    case S_cuddly:
      bendTones(700, 900, 1.03, 16, 4);
      bendTones(899, 650, 1.01, 18, 7);
    break;

    case S_sleeping:
      bendTones(100, 500, 1.04, 10, 10);
      delay(500);
      bendTones(400, 100, 1.04, 10, 1);
    break;

    case S_happy:
      bendTones(1500, 2500, 1.05, 20, 8);
      bendTones(2499, 1500, 1.05, 25, 8);
    break;

    case S_superHappy:
      bendTones(2000, 6000, 1.05, 8, 3);
      delay(50);
      bendTones(5999, 2000, 1.05, 13, 2);
    break;

    case S_happy_short:
      bendTones(1500, 2000, 1.05, 15, 8);
      delay(100);
      bendTones(1900, 2500, 1.05, 10, 8);
    break;

    case S_sad:
      bendTones(880, 669, 1.02, 20, 200);
    break;

    case S_confused:
      bendTones(1000, 1700, 1.03, 8, 2); 
      bendTones(1699, 500, 1.04, 8, 3);
      bendTones(1000, 1700, 1.05, 9, 10);
    break;

    case S_fart1:
      bendTones(1600, 3000, 1.02, 2, 15);
    break;

    case S_fart2:
      bendTones(2000, 6000, 1.02, 2, 20);
    break;

    case S_fart3:
      bendTones(1600, 4000, 1.02, 2, 20);
      bendTones(4000, 3000, 1.02, 2, 20);
    break;

  }
}
