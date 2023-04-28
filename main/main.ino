#include<Servo.h>


#define ir_sensor A0
#define buzzer 4
#define servo_motor 3
#define red_led 7
#define green_led 12
#define blue_led 13
#define waiting_interval 10000
#define device_frequency 60000

Servo myServo;




//variables
int gate=0;
bool food_served = false;
unsigned long current_time;




//functions
void serve_food();
bool is_waiting_time_finished(int current_time);
bool is_ir_sensor_detect();
void buzzer_sound();
void open_gate();
void close_gate();
void wait_for_cat_state();
void device_down_state();
void serve_food_state();





void setup() {
    pinMode(ir_sensor,INPUT);
    pinMode(buzzer,OUTPUT);
    pinMode(red_led,OUTPUT);
    pinMode(blue_led,OUTPUT);
    pinMode(green_led,OUTPUT);

    myServo.attach(servo_motor);
    Serial.begin(9600);
}



void loop() {
    current_time=millis();
    food_served=false;
  	buzzer_sound();
    while(!is_waiting_time_finished(current_time) && !food_served){
        wait_for_cat_state();
      if(is_ir_sensor_detect()){

            serve_food_state();
            serve_food();

        }
      delay(5);
    }

    device_down_state();

  	delay(device_frequency);

}




void serve_food(){
    open_gate();
  	delay(500);
    close_gate();
    food_served = true;
}




bool is_waiting_time_finished(int starting_time){
    if(millis()-starting_time>waiting_interval) return true;
    else return false;

}


void serve_food_state(){
    digitalWrite(green_led,HIGH);
    digitalWrite(red_led,LOW);
    digitalWrite(blue_led,LOW);

}

void wait_for_cat_state(){

    digitalWrite(green_led,LOW);
    digitalWrite(red_led,LOW);
    digitalWrite(blue_led,HIGH);
}

void device_down_state(){

    digitalWrite(green_led,LOW);
    digitalWrite(red_led,HIGH);
    digitalWrite(blue_led,LOW);
}

bool is_ir_sensor_detect(){
    if(!digitalRead(ir_sensor)) return true;
    else return false;
}




void buzzer_sound(){
    for(int i=0;i<2;i++){
        digitalWrite(buzzer,1);
        delay(100);
        digitalWrite(buzzer,0);
        delay(100);
    }
}


void close_gate(){
  while(gate>=0){
    myServo.write(gate);
    gate--;
    delay(10);
  }
}



void open_gate(){
  while(gate<80){
    myServo.write(gate);
    gate++;
    delay(20);
  }
}
