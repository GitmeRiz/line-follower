#include <ros.h>
#include <std_msgs/Empty.h> // Include any ROS message types you want to use

ros::NodeHandle nh;

#define enA 9 // Enable1
#define in1 10 // Motor1  
#define in2 11 // Motor1  
#define in3 5 // Motor2  
#define in4 6 // Motor2  
#define enB 3 // Enable2 

#define RightIR A0 // ir sensor Right
#define LeftIR A1 // ir sensor Left

std_msgs::Empty msg; // Create the message object
ros::Publisher pub("move_forward", &msg); // Declare the publisher with the topic name and message object

void setup() {
  nh.initNode();
  pinMode(RightIR, INPUT);
  pinMode(LeftIR, INPUT);

  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  pinMode(enB, OUTPUT); 

  analogWrite(enA, 150); // Motor1 Speed
  analogWrite(enB, 150); // Motor2 Speed

  nh.advertise(pub); // Initialize the publisher
  delay(1000);
}

void loop() {
  // Handle ROS communication
  nh.spinOnce();

  if ((digitalRead(RightIR) == 0) && (digitalRead(LeftIR) == 0)) {
    forward();
    publishForwardMsg(); // Publish ROS message when moving forward
  }

  if ((digitalRead(RightIR) == 1) && (digitalRead(LeftIR) == 0)) {
    turnRight();
  }

  if ((digitalRead(RightIR) == 0) && (digitalRead(LeftIR) == 1)) {
    turnLeft();
  }

  if ((digitalRead(RightIR) == 1) && (digitalRead(LeftIR) == 1)) {
    Stop();
  }
}

void forward() {
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);  
}

void Stop() {
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
}

void publishForwardMsg() {
  pub.publish(&msg);
}
