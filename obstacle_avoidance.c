#include<Servo.h>

int counter=0;

Servo myservo;

int trigPin=2;

int echoPin=3;

long duration;

int distance;

void forwardcar()

{

digitalWrite(8,HIGH);

digitalWrite(7,LOW);

digitalWrite(12,HIGH);

digitalWrite(13,LOW);


}


void stopcar()

{

digitalWrite(8,LOW);

digitalWrite(7,LOW);

digitalWrite(12,LOW);

digitalWrite(13,LOW);

}


void left()

{

digitalWrite(8,LOW);

digitalWrite(7,LOW);

digitalWrite(12,HIGH);

digitalWrite(13,LOW);

}

void back_right(){

digitalWrite(8,LOW);

digitalWrite(7,LOW);

digitalWrite(12,LOW);

digitalWrite(13,HIGH);

}

void right()

{

digitalWrite(8,HIGH);

digitalWrite(7,LOW);

digitalWrite(12,LOW);

digitalWrite(13,LOW);

}

void back_left()

{

digitalWrite(8,LOW);

digitalWrite(7,HIGH);

digitalWrite(12,LOW);

digitalWrite(13,LOW);

}

void backward()

{

digitalWrite(8,LOW);

digitalWrite(7,HIGH);

digitalWrite(12,LOW);

digitalWrite(13,HIGH);

}

int checkdistance()

{


digitalWrite(2, LOW);

delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds

digitalWrite(2, HIGH);

delayMicroseconds(10);

digitalWrite(2, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds

duration = pulseIn(3,HIGH);

// Calculating the distance

distance= duration*0.034/2;

// Prints the distance on the Serial Monitor

Serial.print("Distance: \n");

// delay(2000);

Serial.println(distance);

return distance;

}

int checkobject(){

int pos;

Serial.println("I am in check object");

stopcar();

myservo.write(60);

delay(2000);

int l_angled = checkdistance();

delay(2000);

if(l_angled >30)

pos = 60;

Serial.print("r_angled distance ");

Serial.println(l_angled);

myservo.write(120);

delay(2000);

int r_angled = checkdistance();

delay(2000);

if(r_angled >30)

pos = 120;

Serial.println("l_angled distance ");

Serial.print(r_angled);


if(l_angled < 40 && r_angled < 40 )

return 1;

else

return pos;

}


int checkleft()

{

Serial.println("i have to check left");

myservo.write(180);

delay(2000);

int left_distance = checkdistance();


myservo.write(90);

return left_distance;

}


int checkright()

{

Serial.println("i have to check right");


myservo.write(0);

delay(2000);


int right_distance = checkdistance();

myservo.write(90);

return right_distance;

}


int smallobject(int a){

  backward();

  delay(800);

      if(a==60)

  {

        right();

        delay(1000);

        forwardcar();

        delay(1000);

        stopcar();

        int l_distance = checkleft();

        delay(1000); 

        if(l_distance > 50  )

        {

          left();

          delay(800);

          forwardcar();

          delay(2300);

          stopcar();

          int l_distance2 = checkleft();

          delay(2000);

            if(l_distance2 > 30)

              {

                left();

                delay(800);

                forwardcar();

                delay(1000);

                right();

                delay(900);

                return 10;    

              }

             else

              {

                return 0;

              }

          

        } 

       

        else

        {

         backward();

         delay(1000);

         back_left();

         delay(1000); 

         return 1;

        } 

  }


  

  else

  {

        left();

        delay(1000);

        forwardcar();

        delay(1000);

        stopcar();

        int r_distance = checkright();

        delay(1000);

       

      

        if(r_distance > 50 )

        {

          right();

          delay(1000);

          forwardcar();

          delay(2300);

          stopcar();

          int r_distance2 = checkright();

          delay(1000);

            if(r_distance2 > 30)

              {

                right();

                delay(1200);

                forwardcar();

                delay(1000);

                left();

                delay(700);  

                return 10;  

              }

             else

              {

                return 0;

              }

          

        } 

       

        else

        {

         backward();

         delay(1000);

         back_right();

         delay(1000); 

         return 1;

        }   

  }




  

}

  



int wallobject()

{

Serial.println("i am in wall object");

stopcar();

if(counter%2 == 0 )

{

int right_distance = checkright();

if(right_distance >20)

{

right();

delay(1900);

counter++;

return 1;

}

}


if(counter%2 == 1)

{

int left_distance = checkleft();

if(left_distance > 20)

{

left();

delay(19

00);

counter++;

return 1;

}

}

counter++;

return 2;

}



void setup() {

pinMode(7,OUTPUT);

pinMode(8,OUTPUT);

pinMode(9,OUTPUT);

pinMode(11,OUTPUT);

pinMode(12,OUTPUT);

pinMode(13,OUTPUT);

pinMode(trigPin,OUTPUT);

pinMode(echoPin,INPUT);

myservo.attach(5);

Serial.begin(9600);   

}


char ch;

void loop() {

// put your main code here, to run repeatedly:

if(Serial.available()>0){

 ch = Serial.read();

Serial.println(ch);

}

if(ch=='o'){

  Serial.println("i am auto mode");

  while(1){

    

analogWrite(9,255);

analogWrite(11,255);

myservo.write(90);

int distance=checkdistance();


Serial.println(distance);

//delay(5000);

if(distance >20)

forwardcar();

else

{

stopcar();

delay(2000);

int o_status = checkobject();

Serial.print("status: ");

Serial.println(o_status);

if(o_status == 1 )

{

int w_status = wallobject();

if(w_status == 1)

forwardcar();

}

else

{

Serial.println("small object");

int s_status = smallobject(o_status);

if(s_status == 1)

wallobject();

}

}

  }

}

if(ch=='m'){

  Serial.println("i am menual");

  while(1){

  analogWrite(9,255);

  analogWrite(11,250);

    if(Serial.available()>0){

 ch = Serial.read();

Serial.println(ch);

}

  if(ch=='f'){

  forwardcar();

  }

  if(ch=='b'){

    backward();


  }

  if(ch=='l'){

    digitalWrite(8,LOW);

digitalWrite(7,LOW);

digitalWrite(12,HIGH);

digitalWrite(13,LOW);

  }

  if(ch=='r'){

    digitalWrite(8,HIGH);

digitalWrite(7,LOW);

digitalWrite(12,LOW);

digitalWrite(13,LOW);

    }

  if(ch=='s'){

    digitalWrite(8,LOW);

digitalWrite(7,LOW);

digitalWrite(12,LOW);

digitalWrite(13,LOW);

  }

}

}

}
