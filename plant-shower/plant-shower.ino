#define triggerPin D7

int delayOff = 80;  // pwm delay
int startDelay = 20;  // initial delay ('loading dose' of water)
int waterState=0;
// 0 is off
// 1 is just turned on
// 2 is continuously on

int timeTurnedOn;
int loadingThreshold=2500;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin,OUTPUT);
  Particle.function("water",water);
  Particle.function("delay",changeDelay);
  Particle.function("startDelay",changeStartDelay);
  Particle.subscribe("water",waterHandler,MY_DEVICES);
}

void loop() {
  if (waterState==1) {
    timeTurnedOn=millis();
    digitalWrite(triggerPin,HIGH);
  }
  else if (waterState==2) {
    if (millis()-timeTurnedOn>loadingThreshold) {
      digitalWrite(triggerPin,HIGH);
      delay(delayOff);
      digitalWrite(triggerPin,LOW);
      delay(delayOff);
    }
    else {
      digitalWrite(triggerPin,HIGH);
      delay(startDelay);
      digitalWrite(triggerPin,LOW);
      delay(startDelay);
    }
  }
  else {
    digitalWrite(triggerPin,LOW);
  }
}

int water(String command) {
  if (command=="on"||command=="1") {
    digitalWrite(triggerPin,HIGH);
    delay(startDelay);
    waterState=1;
  }
  else if (command=="off"||command=="0") {
    waterState=0;
  }
  else {
    if (waterState==1) {waterState=0;}
    else {waterState=1;}
  }
  return waterState;
}

int changeDelay(String command) {
  char inputStr[64];
  command.toCharArray(inputStr,64);
  delayOff = atoi(inputStr);
  return delayOff;
}

int changeStartDelay(String command) {
  char inputStr[64];
  command.toCharArray(inputStr,64);
  startDelay = atoi(inputStr);
  return startDelay;
}

void waterHandler(const char *event, const char *data) {
  if (data) {
    water(String(data));
    Serial.println("turning "+String(data));
  }
}
