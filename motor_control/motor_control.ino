#include "pitches.h"

#define MOTOR_FL_PIN_A 4
#define MOTOR_FL_PIN_B 5
#define MOTOR_FR_PIN_A 6
#define MOTOR_FR_PIN_B 7
#define MOTOR_RL_PIN_A 14
#define MOTOR_RL_PIN_B 15
#define MOTOR_RR_PIN_A 16
#define MOTOR_RR_PIN_B 17
#define BUZZER_PIN 10

static int chargeNotes[] = { NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4 };
static unsigned int chargeDuration[] = { 125, 125, 125, 240, 112, 480 };
static unsigned int chargeGap[] = { 50, 50, 50, 50, 50, 60 };

enum MotorId {
  FL = 1, FR, RL, RR
};

enum MotorDirection {
  REV = LOW, FWD = HIGH, OFF = 2
};

enum MotorMotions {
  STRAIGHT = 1, TURN, STRAFE
};

// function declarations
void motorCommand(unsigned int motion, unsigned int dir, unsigned int duration); // duration in milliseconds
void motorControl(unsigned int id, unsigned int dir);
void hardStopMotors();

void setup() {
  pinMode(MOTOR_FL_PIN_A, OUTPUT);
  pinMode(MOTOR_FL_PIN_B, OUTPUT);
  pinMode(MOTOR_FR_PIN_A, OUTPUT);
  pinMode(MOTOR_FR_PIN_B, OUTPUT);
  pinMode(MOTOR_RL_PIN_A, OUTPUT);
  pinMode(MOTOR_RL_PIN_B, OUTPUT);
  pinMode(MOTOR_RR_PIN_A, OUTPUT);
  pinMode(MOTOR_RR_PIN_B, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  hardStopMotors();
}

void loop() {
  /* CHARGE!!! */
  delay(3000);
  buzzerCharge();
  
  /* DEMO */
  motorCommand(STRAIGHT, FWD, 700);
  delay(500);
  motorCommand(STRAIGHT, REV, 700);
  delay(1000);

  motorCommand(TURN, FWD, 700); // CW
  delay(500);
  motorCommand(TURN, REV, 700); // CCW
  delay(1000);

  motorCommand(STRAFE, FWD, 700); // RIGHT
  delay(500);
  motorCommand(STRAFE, REV, 700); // LEFT

  /* TRAP THE LOOP */
  hardStopMotors();
  while (true) { delay(1000); }
}

void motorCommand(unsigned int motion, unsigned int dir, unsigned int duration) {
  unsigned int oppo = (dir == FWD) ? REV : FWD;
  
  switch (motion) {
    case STRAIGHT:
      motorControl(FL, dir);
      motorControl(FR, dir);
      motorControl(RL, dir);
      motorControl(RR, dir);
      break;

    case TURN:
      motorControl(FL, dir);
      motorControl(FR, oppo);
      motorControl(RL, dir);
      motorControl(RR, oppo);
      break;

    case STRAFE:
      motorControl(FL, oppo);
      motorControl(FR, dir);
      motorControl(RL, dir);
      motorControl(RR, oppo);
      break;

    default:
      break;
  }
  
  delay(duration);
  
  motorControl(FL, OFF);
  motorControl(FR, OFF);
  motorControl(RL, OFF);
  motorControl(RR, OFF);
}

void motorControl(unsigned int id, unsigned int dir) {
  switch (id) {
    case FL:
      digitalWrite(MOTOR_FL_PIN_A, dir);
      digitalWrite(MOTOR_FL_PIN_B, dir == OFF ? dir : !dir);
      break;
      
    case FR:
      digitalWrite(MOTOR_FR_PIN_A, dir);
      digitalWrite(MOTOR_FR_PIN_B, dir == OFF ? dir : !dir);
      break;
      
    case RL:
      digitalWrite(MOTOR_RL_PIN_A, dir);
      digitalWrite(MOTOR_RL_PIN_B, dir == OFF ? dir : !dir);
      break;
      
    case RR:
      digitalWrite(MOTOR_RR_PIN_A, dir);
      digitalWrite(MOTOR_RR_PIN_B, dir == OFF ? dir : !dir);
      break;
      
    default:
      break;
  }
}

void hardStopMotors() {
  digitalWrite(MOTOR_FL_PIN_A, LOW);
  digitalWrite(MOTOR_FL_PIN_B, LOW);
  digitalWrite(MOTOR_FR_PIN_A, LOW);
  digitalWrite(MOTOR_FR_PIN_B, LOW);
  digitalWrite(MOTOR_RL_PIN_A, LOW);
  digitalWrite(MOTOR_RL_PIN_B, LOW);
  digitalWrite(MOTOR_RR_PIN_A, LOW);
  digitalWrite(MOTOR_RR_PIN_B, LOW);
}

void buzzerCharge() {
  for (unsigned int i = 0; i < sizeof(chargeNotes) / sizeof(chargeNotes[0]); i++) {
    tone(BUZZER_PIN, chargeNotes[i], chargeDuration[i]);
    delay(chargeDuration[i]);
    noTone(BUZZER_PIN);
    delay(chargeGap[i]);
  }
}
