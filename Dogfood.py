import RPi.GPIO as GPIO
import atexit
import time
import datetime as dt


#MODELS

class PressEvent:

  def __init__(self):
    self.time = dt.datetime.now()

  def today(self):
    if dt.datetime.now().day == self.time.day:
      return 1 
    else:
      return 0 

class Led:
  gpio_index = 0
  state = 0 # 0=off, 1=blink, 2=steady
  currentOnState = 0 # 0=off, 1=on
  def updateState(self, updatedState):
    self.state = updatedState
  def updatePinOutput(self):
    if self.state == 0:
      GPIO.output(self.index,GPIO.LOW) 
    elif self.state == 1:
      if self.currentOnState == 0:
        self.currentOnState = 1              
        GPIO.output(self.index,GPIO.HIGH) 
      else:
        self.currentOnState = 0            
        GPIO.output(self.index,GPIO.LOW) 
    elif self.state == 2:
      GPIO.output(self.index,GPIO.HIGH) 



pressEvents = []

def currentHourIndex():
  return dt.datetime.now().hour

def idealCompletedFeedingsNow():
  currentHour = currentHourIndex()
  if currentHour > 0 and currentHour < 5:
    return 0 #Early Morning - no feeding
  elif currentHour < 12:
    return 1 #Morning
  elif currentHour < 18:
    return 2 #Afternoon
  else:
    return 3 #Midnight

def completedFeedingsNow():
  total = 0
  for event in pressEvents:
    if event.today() == 1:
      total = total + 1
  return total        

led1 = Led()
led1.index = 18 
  
led2 = Led()
led2.index = 22 

top = 20 
topLeft = 24
topRight = 23
middle = 16 
bottomLeft = 17
bottomRight = 19
bottom = 21
dot = 26 

def exit_handler():
  GPIO.output(led1.index,GPIO.LOW) 
  GPIO.output(led2.index,GPIO.LOW) 
  #GPIO.output(top, GPIO.LOWTrue)
  #GPIO.output(topLeft, GPIO.LOW)
  #GPIO.output(topRight, GPIO.LOW)
  #GPIO.output(middle, GPIO.LOW)
  #GPIO.output(bottomLeft, GPIO.LOW)
  #GPIO.output(bottomRight, GPIO.LOW)
  #GPIO.output(bottom, GPIO.LOW)
  #GPIO.output(dot, GPIO.LOW)
  GPIO.cleanup()

def updatePins():

  completed = completedFeedingsNow()
  ideal = idealCompletedFeedingsNow()
  dueFeedings = ideal - completed
  
  showNumber(completed % 10)

  doorOpened = 0
  if GPIO.input(25):
    doorOpened = 1

  if doorOpened == 1:
    led1.updateState(1) #blinking for open door
  elif dueFeedings > 0:
    led1.updateState(2) #solid for feeding due
  else:
    led1.updateState(0) #off for all good

  led1.updatePinOutput()

def doorOpened(channel):
  daClass = PressEvent()
  pressEvents.append(daClass)

def buttonPressed(channel):
  del pressEvents[-1]
  updatePins() 

def showNumber(number):

  GPIO.output(top, False)
  GPIO.output(topLeft, False)
  GPIO.output(topRight, False)
  GPIO.output(middle, False)
  GPIO.output(bottomLeft, False)
  GPIO.output(bottomRight, False)
  GPIO.output(bottom, False)
  GPIO.output(dot, False)

  #top
  if number == 0 or number == 2 or number == 3 or number == 5 or number == 6 or number == 7 or number == 8 or number == 9:
    GPIO.output(top, True)

  #top left
  if number == 0 or number == 4 or number == 5 or number == 6 or number == 7 or number == 8 or number == 9:
    GPIO.output(topLeft, True)

  #top right 
  if number == 0 or number == 1 or number == 2 or number == 3 or number == 4 or number == 7 or number == 8 or number == 9:
    GPIO.output(topRight, True)

  #middle 
  if number == 2 or number == 3 or number == 4 or number == 5 or number == 6 or number == 8 or number == 9:
    GPIO.output(middle, True)

  #bottom left 
  if number == 0 or number == 2 or number == 6 or number == 8:
    GPIO.output(bottomLeft, True)

  #bottom right 
  if number == 0 or number == 1 or number == 3 or number == 4 or number == 5 or number == 6 or number == 7 or number == 8 or number == 9:
    GPIO.output(bottomRight, True)

  #bottom 
  if number == 0 or number == 2 or number == 3 or number == 5 or number == 6 or number == 8:
    GPIO.output(bottom, True)

  #if 0 == 1:
#      GPIO.output(topLeft, True)
#      GPIO.output(topRight, True)
#      GPIO.output(middle, True)
#      GPIO.output(bottomLeft, True)
#      GPIO.output(bottomRight, True)
#      GPIO.output(bottom, True)
#      GPIO.output(dot, True)
  
  
atexit.register(exit_handler)
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

#Setup LEDs
GPIO.setup(led1.index, GPIO.OUT)
GPIO.setup(led2.index, GPIO.OUT)

#Setup Hall Sensor 
GPIO.setup(25, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.add_event_detect(25, GPIO.RISING, callback=doorOpened, bouncetime=200)

#Setup Hall Sensor 
GPIO.setup(6, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.add_event_detect(6, GPIO.RISING, callback=buttonPressed, bouncetime=200)

#Seting digits
GPIO.setup(top, GPIO.OUT)
GPIO.setup(topLeft, GPIO.OUT)
GPIO.setup(topRight, GPIO.OUT)
GPIO.setup(middle, GPIO.OUT)
GPIO.setup(bottomLeft, GPIO.OUT)
GPIO.setup(bottomRight, GPIO.OUT)
GPIO.setup(bottom, GPIO.OUT)
GPIO.setup(dot, GPIO.OUT)

while True:
  updatePins() 
  time.sleep(1)

