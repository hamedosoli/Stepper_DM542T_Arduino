#define Pul_N 2
#define Dir_N 3
#define En_N 4

inline void pulse_gen(){
    
    digitalWrite(Pul_N, HIGH);
    delay(1);
    digitalWrite(Pul_N, LOW);
    delay(1);

}

struct StepperDMt{
   
   // motion settings
   float speed = 1; // mm/s
   float distance = 1; // mm
   char direction = 'T'; // with T, stage moves Toward the motor, with A, stage moves Away from the motor
   bool Run = false; // with false, stage stopps, with true, stage runs
   
   // hardware 
   int microsteps = 200; // enter 

      struct stage {
         float pitch = 0.5; // pitch in mm of the linear stage actuator
         float travel = 50; // maximum travel possible
         
      };
};

int number_of_pulses (float distance, int microsteps, float pitch, float travel){


}

void manual_move (bool run , char direction){
  if (Serial.available())
  run = Serial.read();
  direction = Serial.read();
  action_run(run, direction);
}

void action_run(bool run, char direction) {

int Enable;
int dir;

if (run)
Enable = HIGH;
else 
Enable = LOW;
digitalWrite (En_N, Enable);
delayMicroseconds(10);

if (direction == 'T')
dir = HIGH;
else 
dir = LOW;
digitalWrite(Dir_N, dir);
pulse_gen();

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Pul_N, OUTPUT);
  pinMode(Dir_N, OUTPUT);
  pinMode(En_N, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   manual_move(true, 'A');
}
