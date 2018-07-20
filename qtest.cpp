#include <iostream>
#include <ctime>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>
class Digit {
  public:
    int top = 20;
    int topLeft = 24;
    int topRight = 23;
    int middle = 16;
    int bottomLeft = 17;
    int bottomRight = 19;
    int bottom = 21;
    int dot = 26;
    void showNumber(int num);
};

void myInterrupt(void) {
  puts("Interrupt called"); 
}

class PressEvent {
  public:
    bool today();
    time_t pressTime = time(0);
    int minute();
};

class Led {
  public:
    int gpioIndex = 0;
    int state = 0; // 0=off, 1=blink, 2=steady
    int currentOnState = 0; // 0=off, 1=on
    void updateState(int updatedState);
    void updatePinOutput();
};

class Input {
  public:
    int gpioIndex = 0;
    bool lastHigh;

    bool high();
    void setHigh(bool high);

};

class FeedingScheduler {
  public:
    std::vector<PressEvent> events;
    int idealFeedingCountNow();
    int completedFeedingsNow();
    void updatePins();
    Led led1;    
    Input door;    
    Digit digit;
};

//Time Utilities

int dayFromTime(time_t timeVal){
  struct tm* tm_info = localtime(&timeVal);
  return tm_info->tm_mday;
}

int hourFromTime(time_t timeVal){
  struct tm* tm_info = localtime(&timeVal);
  return tm_info->tm_hour;
}

int currentHourIndex(){
  return hourFromTime(time(0));
}

void Digit::showNumber(int number){
  printf("Show number called with %d\n", number);
  fflush(stdout); 
      //digitalWrite (gpioIndex, HIGH);
  digitalWrite(top, LOW);
  digitalWrite(topLeft, LOW);
  digitalWrite(topRight, LOW);
  digitalWrite(middle, LOW);
  digitalWrite(bottomLeft, LOW);
  digitalWrite(bottomRight, LOW);
  digitalWrite(bottom, LOW);
  digitalWrite(dot, LOW);

  //top
  if ((number == 0) || (number == 2) || (number == 3) || (number == 5) || (number == 6) || (number == 7) || (number == 8) || (number == 9)){
    digitalWrite(top, HIGH);
  }

  //top left
  if ((number == 0) || (number == 4) || (number == 5) || (number == 6) || (number == 7) || (number == 8) || (number == 9)){
    digitalWrite(topLeft, HIGH);
  }

  //top right 
  if ((number == 0) || (number == 1) || (number == 2) || (number == 3) || (number == 4) || (number == 7) || (number == 8) || (number == 9)){
    digitalWrite(topRight, HIGH);
  }

  //middle 
  if ((number == 2) || (number == 3) || (number == 4) || (number == 5) || (number == 6) || (number == 8) || (number == 9)){
    digitalWrite(middle, HIGH);
  }

  //bottom left 
  if ((number == 0) || (number == 2) || (number == 6) || (number == 8)){
    digitalWrite(bottomLeft, HIGH);
  }

  //bottom right 
  if ((number == 0) || (number == 1) || (number == 3) || (number == 4) || (number == 5) || (number == 6) || (number == 7) || (number == 8) || (number == 9)){
    digitalWrite(bottomRight, HIGH);
  }

  //bottom 
  if ((number == 0) || (number == 2) || (number == 3) || (number == 5) || (number == 6) || (number == 8)){
    digitalWrite(bottom, HIGH);
    }
}

bool Input::high(){
  return (digitalRead (gpioIndex) == 1);
}

bool PressEvent::today(){
  return dayFromTime(time(0)) == dayFromTime(pressTime); 
}

int PressEvent::minute(){
  struct tm* tm_info;
  tm_info = localtime(&pressTime);
  return tm_info->tm_sec;
}


void Led::updateState(int updatedState){
  state = updatedState;
}

void Led::updatePinOutput(){
  if (state == 0){
    digitalWrite (gpioIndex, LOW);
  } else if (state == 1){
    if (currentOnState == 0){
      currentOnState = 1;
      digitalWrite (gpioIndex, HIGH);
    } else {
      currentOnState = 0;
      digitalWrite (gpioIndex, LOW);
    }
  } else if (state == 2){
    digitalWrite (gpioIndex, HIGH);
  }
}

void Input::setHigh(bool high){
  if (high == true){
    digitalWrite (gpioIndex, HIGH);
  } else {
    digitalWrite (gpioIndex, LOW);
  }
}

//General schedule methods
int FeedingScheduler::idealFeedingCountNow(){
  int currentHour = currentHourIndex();
  if (currentHour > 0 && currentHour < 5){
    return 0; //Early Morning - no feeding
  } else if (currentHour < 12){
    return 1; //Morning
  } else if (currentHour < 18){
    return 2; // Afternoon
  } else {
    return 3; //Midnight
  }
}

int FeedingScheduler::completedFeedingsNow(){
  int total = 0;
  for (auto event: events) {
    if (event.today() == true) {
      total++;
    }
  }
  return total;
}

void FeedingScheduler::updatePins(){
  int completed = completedFeedingsNow();
  int ideal = idealFeedingCountNow();
  int dueFeedings = ideal = completed;
  digit.showNumber(completed % 10);


  bool doorOpened = door.high();
  if (doorOpened && door.lastHigh == false){
    //Door has been opened. Record the event.
    PressEvent classTest = PressEvent(); 
    events.push_back(classTest);
  }

  door.lastHigh = doorOpened;

  if(doorOpened){
    led1.updateState(1); //blinking for open door
  } else if (dueFeedings > 0) {
    led1.updateState(2); //solid for feeding due
  } else {
    led1.updateState(0); //off for all good
  }

  led1.updatePinOutput();
}


int main (void)
{
  printf("***Starting Feeding Scheduler***\n");
  wiringPiSetupGpio ();

  std::vector<PressEvent> pressEvents; 

  FeedingScheduler scheduler = FeedingScheduler();
  scheduler.led1 = Led();
  scheduler.led1.gpioIndex = 18;
  scheduler.door = Input();
  scheduler.door.gpioIndex = 25;

  if ( wiringPiISR (25, INT_EDGE_RISING, &myInterrupt) < 0 ) {
      printf("returning");
  }

  scheduler.digit = Digit();
  pinMode(scheduler.digit.top, OUTPUT);
  pinMode(scheduler.digit.topLeft, OUTPUT);
  pinMode(scheduler.digit.topRight, OUTPUT);
  pinMode(scheduler.digit.middle, OUTPUT);
  pinMode(scheduler.digit.bottomLeft, OUTPUT);
  pinMode(scheduler.digit.bottomRight, OUTPUT);
  pinMode(scheduler.digit.bottom, OUTPUT);
  pinMode(scheduler.digit.dot, OUTPUT);


  while(true) {
    if(scheduler.door.high() == true){
      puts("Door open\n");
    } else {
      puts("Door closed\n");
    }
    
    scheduler.updatePins();
    delay(1000);
  }

  return 0;

}
