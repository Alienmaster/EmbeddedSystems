 #include <DueTimer.h>
auto led_pin = 7;
volatile int led_state = 0;
const byte SwitchOne = 31;
const byte SwitchTwo = 43;
DueTimer timer;
DueTimer timerTwo;
int count1 = 0;
int count2 = 0;
volatile int timerCount = 0;
bool SwitchOnePressed = false;
bool SwitchTwoPressed = false;
int MotorPWMInputPin = 5; //Input on H-Bridge
int InputPin2 = 49;
int InputPin1 = 47;
int MotorSpeed = 255;
boolean ValueInputPin1 = LOW;
boolean ValueInputPin2 = HIGH;
int Stepping = 5;

bool stopmode  = false;




// variables for change de mode
bool btm1 ,btm2 = false;
bool mode = false;



void changeLedStateBrighter(void) {  
    led_state = (led_state + 30) % 255;
}

void changeLedStateDarker(void) {
  if(led_state <= 29){
    led_state=+255;   
  }
  led_state = (led_state - 30) % 255;
}

void writeLedState(void) {
  analogWrite(led_pin, led_state);
}

void startTimer(void) {
    timer.start();
}

void changeDirection(int switch_direction){ // switch1 = 1, switch2 = 2
  analogWrite(MotorPWMInputPin, 0);
  delay(50);
  if (stopmode = false){
    if (switch_direction = 1){
    boolean ValueInputPin1 = LOW;
    boolean ValueInputPin2 = HIGH;
  }
  if (switch_direction = 2){
    boolean ValueInputPin1 = HIGH;
    boolean ValueInputPin2 = LOW;
  }
  digitalWrite(InputPin1, ValueInputPin1);
  digitalWrite(InputPin2, ValueInputPin2);
  analogWrite(MotorPWMInputPin, MotorSpeed);
  }
  stopmode = !stopmode;
  
}

void setSpeed(int updown) { //increase Speed = 1, decrease Speed = 2
  
  if (updown == 1){
    if ((MotorSpeed + Stepping) > 255){
      MotorSpeed = 255;
    }
    else {
      MotorSpeed = MotorSpeed + Stepping;
    }
  }
  else {
    if ((MotorSpeed - Stepping) < 0){
      MotorSpeed = 0; 
    }
    else {
      MotorSpeed = MotorSpeed - Stepping;
    }
  }
  analogWrite(MotorPWMInputPin, MotorSpeed);
}

void checkInput(void) {
  ++timerCount;
  if (digitalRead(SwitchOne) == LOW)
    {
    ++count1;
    SwitchOnePressed = true;
  }
  else
  {
    count1 = 0;
  }
  if (timerCount > 1000)
  {
    timer.stop();
    timerCount = 0;
  }

}

void startTimerTwo(void) {
    timerTwo.start();
}

void checkInputTwo(void) {
  ++timerCount;
  if (digitalRead(SwitchTwo) == LOW)
    {
    ++count2;
    SwitchTwoPressed = true;
  }
  else
  {
    count2 = 0;
  }
  if (timerCount > 1000)
  {
    timerTwo.stop();
    timerCount = 0;
  }

}


void setup()
{
  timer.configure(1000, checkInput);
  timerTwo.configure(1000, checkInputTwo);
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(SwitchOne,INPUT);
  pinMode(SwitchTwo,INPUT);
  pinMode(MotorPWMInputPin, OUTPUT);
  pinMode(InputPin1, OUTPUT);
  pinMode(InputPin2, OUTPUT);
  digitalWrite(InputPin1, ValueInputPin1);
  digitalWrite(InputPin2, ValueInputPin2);
  
  attachInterrupt(digitalPinToInterrupt(SwitchOne), startTimer, FALLING);
  attachInterrupt(digitalPinToInterrupt(SwitchTwo), startTimerTwo, FALLING);
  setSpeed(0);
}
void loop() {
    // TestValue = TestValue-1;
    delay(1000);
    //changeDirection();
    //setSpeed(0);


    
    
    if(mode = true) {              //changing direction
      
       if (count1 > 100 or count2 > 100) {
       if(SwitchOnePressed == true){
          changeDirection(1);
       }
       if(SwitchTwoPressed == true){
          changeDirection(2);
      }

        if(count1 > 100 and count2 > 100){
            mode = false;
        }      
        count1 = 0 ;
        count2 = 0;   
         
      }
    }
    else{ 
      if (count1 > 100 or count2 > 100) {
       if(SwitchOnePressed == true){
          setSpeed(1);

       }
       if(SwitchTwoPressed == true){
          setSpeed(2);
      }
    writeLedState();

        if(count1 > 100 and count2 > 100){
            mode = false;
        }      
        count1 = 0 ;
        count2 = 0;   
         
    }               
    }
}
