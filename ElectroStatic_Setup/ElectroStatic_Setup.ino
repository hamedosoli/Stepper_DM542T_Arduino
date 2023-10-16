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
   float speed = 1; // mm/s
   float distance = 2; // mm
   char direction = 'T'; // with T, stage moves Toward the motor, with A, stage moves Away from the motor
   bool Run = true; // with false, stage stopps, with true, stage runs
   
   // hardware config
   int microsteps = 200; // enter 

  // stage_mechanics
  float pitch = 0.5; // pitch in mm of the linear stage actuator
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
  if (Serial.available() > 0){

      stepper->Run  = Serial.parseInt();
      stepper->direction = Serial.read(); 
      stepper->distance = Serial.parseFloat(); 
      stepper->speed =Serial.parseFloat();

  }
  
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
dir = HIGH;
else 
dir = LOW;
digitalWrite(Dir_N, dir);
delayMicroseconds(10);

int pulses = number_of_pulses(distance, microsteps,pitch,travel);

for (int i=0; i< pulses; i++)
{
  pulse_gen();
}

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
  
  //serial_reader(&stepper1);
  //  Serial.print("Run = ");
  //  Serial.println(stepper1.Run);
  //  Serial.print("direction = ");
  //  Serial.println(stepper1.direction);
  //  Serial.print("distance = ");
  //  Serial.println(stepper1.distance);
  //  Serial.print("speed = ");
  //  Serial.println(stepper1.speed);
  
  manual_move(stepper1.Run, stepper1.direction,stepper1.distance, stepper1.microsteps, stepper1.pitch, stepper1.travel);
  stepper1.Run = false;
}
