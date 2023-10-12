#define Pul_N 2
#define Dir_N 3
#define En_N 4

int Enable = LOW;
int Dir = HIGH ; 

void setup() {
  // put your setup code here, to run once:
pinMode(Pul_N, OUTPUT);
pinMode(Dir_N, OUTPUT);
pinMode(En_N, OUTPUT);

digitalWrite (En_N, Enable);
delayMicroseconds(10);
digitalWrite(Dir_N, Dir);
delayMicroseconds(10);
}

void loop() {
  // put your main code here, to run repeatedly:


  digitalWrite(Pul_N, HIGH);
    delay(1);
    digitalWrite(Pul_N, LOW);
    delay(1);
}
