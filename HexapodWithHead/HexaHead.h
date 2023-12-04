#include "Freenove_VK16K33_Lib.h"
#include "Servo.h" 
#include "Otto_sounds.h"

extern int emotion_task_mode;
extern int emotion_count;
class HexaHead
{
public:
  
  Freenove_VK16K33 matrix; 
  
  HexaHead();


  void  Sleep(void);
  void  Wake(void);


  //**********************    DISPLAY   **************************************************
  void Emotion_Setup(int address = 0x70);                 //Initializes the Led Matrix  
  void  Emotion_Show(void);
  void Emotion_SetMode(int mode);

  void clearEmtions(void);                                //clear all
  void complete_emotion(int emotion_current_mode);
  void emoSuprise(int delay_ms);
  void HexaHead::emoGrin(int delay_ms);
  void HexaHead::emoAngry(int delay_ms);
  void HexaHead::emoSad(int delay_ms);
  /*
  void mouthMunch(int delay_ms);   
  void mouthGosh(int delay_ms);   
  void mouthFang(int delay_ms);*/

  //**********************   SERVO   **************************************************
  Servo servoHead;          
  void servo_setup(int pin = 3);
  void servo_scan(void);
  bool servoScanUp = true;
  int servoHeadAngle = 90;
  //**********************    ULTRASONIC   **************************************************
  void Ultrasonic_Setup(void);               //Ultrasonic initialization
  int Ultrasonic_Get_Distance(); //Ultrasonic get distance value  
  
  int dist_left = 0;
  int dist_fwd = 0;
  int dist_right = 0;

  //**********************    Buzzer   **************************************************

  void Buzzer_Setup(int pin = 2);
  void Buzzer_Beep(void);

 //**********************   SOUNDS  ******************************************************
 void _tone (float noteFrequency, long noteDuration, int silentDuration);
 void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
 void sing(int songName);
    
 int pinBuzzer;
private:
  
};
