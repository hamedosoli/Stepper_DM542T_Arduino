#define Pul_N 2
#define Dir_N 3
#define En_N 4

inline void pulse_gen(){
    
    digitalWrite(Pul_N, HIGH);
    delay(1);
    digitalWrite(Pul_N, LOW);
    delay(1);

}

struct StepperDM5{
   
   // motion settings
   //float speed = 1; // mm/s not interested in speed yet!
   float distance = 0; // cm
   char direction = 'A'; // with T, stage moves Toward the motor, with A, stage moves Away from the motor
   bool Run = true; // with false, stage stopps, with true, stage runs
   
   // hardware config
   int microsteps = 200; // enter 

  // stage_mechanics
  float pitch = 0.45; // pitch in cm of the linear stage actuator
  float travel = 50; // maximum travel possible

} stepper1;


int number_of_pulses (float distance, int microsteps, float pitch, float travel){

       if (distance < travel)
       {
        
           return (int((distance/pitch)*microsteps));
       }

       else {Serial.println("distance must be less than 50 cm");}

}

void serial_reader (struct StepperDM5* stepper){
  
      stepper->Run  = Serial.parseInt();
      stepper->direction = Serial.read(); 
      stepper->distance = Serial.parseFloat(); 
      //stepper->speed =Serial.parseFloat(); // not interested in speed yet!
  
}

void manual_move(bool run, char direction, float distance, int microsteps, float pitch, float travel) {

int Enable;
int dir;

if (run)
Enable = HIGH;
else 
Enable = LOW;
digitalWrite (En_N, Enable);
delayMicroseconds(10);

if (direction == 'T')
dir = LOW;
else 
dir = HIGH;
digitalWrite(Dir_N, dir);
delayMicroseconds(10);

int pulses = number_of_pulses(distance, microsteps,pitch,travel);

for (int i=0; i< pulses; i++)
{
  pulse_gen();
}

}

void setup() {
  
  Serial.begin(115200);

  pinMode(Pul_N, OUTPUT);
  pinMode(Dir_N, OUTPUT);
  pinMode(En_N, OUTPUT);

}

void loop() {
  
  if (Serial.available() > 0){
   serial_reader(&stepper1);
}
  
  manual_move(stepper1.Run, stepper1.direction,stepper1.distance, stepper1.microsteps, stepper1.pitch, stepper1.travel);
  stepper1.Run = false;
}
