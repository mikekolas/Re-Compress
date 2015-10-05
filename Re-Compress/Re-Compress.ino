#include <Servo.h>

Servo claw,arm;

#define echoPin 2 // Echo Pin
#define trigPin 4 // Trigger Pin

long duration,distance;

const int servoc=6; //claw
const int servoa=5; //dagkana

int posa=105;
int posc=80;

const int pir_pin = 7;
int state=LOW;

void setup()
{
	Serial.begin(9600);
	claw.attach(servoc);
	arm.attach(servoa);

  	pinMode(12, OUTPUT);  //A motor=piestiras
  	pinMode(9, OUTPUT);   //A motor=piestiras
	//============================================
  	pinMode(13, OUTPUT);  //B motor=katapakti
	pinMode(8, OUTPUT);   //B motor=katapakti

	pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

	pinMode(pir_pin,INPUT); // pir

  	Serial.println("Warming up...");
	 for (int i=0; i<10;i++)
	 {
	   Serial.print("second :");
	   Serial.println(i);
	   delay(1000);
  	 }
  	 Serial.println("Sensor Active!");
  	 delay(50);
}

void loop()	//kiriws programma
{
	 int pir=vraxionas();

	 Serial.print("Signal = ");
	 Serial.println(pir);

	 delay(100);

  	 if(pir == HIGH)	//elegxos skoupidiwn ston kouva
  	 {
  	 	Serial.println("Initializing trash can operation.");
  	 	delay(1000);
	 	moveP();
   	 	moveK();
  	 }
  	 else
  	 {
     	Serial.println("The trash can is empty.");
  	 }
     delay(1000);

}

//=============Kiniseis Piestira================================
  void frontP()
  {
    digitalWrite(12, HIGH); //kinisi mprosta gia piestira
    digitalWrite(9, LOW);   //bgazei to freno
    analogWrite(3,255);  //taxitita motor A
  }//frontP

  void backP()
  {
    digitalWrite(12, LOW);  //kinisi pisw piestira
    digitalWrite(9, LOW);  // bgazei freno
    analogWrite(3,255);  //taxitita motor A
  }//backP

  void haltP()
  {
    digitalWrite(12, HIGH);
    digitalWrite(9, LOW);
    analogWrite(3, 0);      //taxitita motor A=0
  }//haltP
//==============Kiniseis katapaktis==================
  void frontK()
  {
    digitalWrite(13, HIGH);  //kinisi mprosta gia katapakti
    digitalWrite(8, LOW);  //bgazei to freno
    analogWrite(11,180);  //taxitita katapaktis
  }//frontK
  void backK()
  {
    digitalWrite(13, LOW);  //kinisi pisw katapaktis
    digitalWrite(8, LOW);  // bgazei freno
    analogWrite(11,180);  //taxitita katapaktis
  }//backK
  void haltK()
  {
    digitalWrite(13, HIGH);
    digitalWrite(8, LOW);
    analogWrite(11, 0);  //STOP katapaktis
  }//haltK

void moveK()
{
    frontK();
    delay(600);
    haltK();
    delay(1000);
    backK();
    delay(600);
    haltK();
    delay(3000);
}

void moveP()
{

    frontP();
    delay(400);
    haltP();
    delay(1000);
    backP();
    delay(400);
    haltP();
    delay(1000);
}

//======================Braxionas====================

int vraxionas()
{
	int trash=LOW;
	for(posa=105;posa>9;posa--)
	{
		arm.write(posa);//thesi paralavis
		delay(17);
	}
	delay(2000);
 	for(posc=90;posc>3;posc--)
	{
		claw.write(posc);//kleinei to claw
		delay(15);
	}
	delay(2000);
	for(posa=10;posa<171;posa++)
	{
		arm.write(posa);//thesi apostolis
		delay(17);
	}
	delay(2000);
	for(posc=3;posc<91;posc++)
	{
		claw.write(posc);//anigei to claw
		state=digitalRead(pir_pin);
		Serial.print("State of PIR : ");
		Serial.println(state);

		 digitalWrite(trigPin, LOW);
  		 delayMicroseconds(2);
  		 digitalWrite(trigPin, HIGH);
  		 delayMicroseconds(10);
  		 digitalWrite(trigPin, LOW);
  		 duration = pulseIn(echoPin, HIGH);
		 distance = duration/58.2;  //convert it to centimeters
		 Serial.print("Distance ");
  		 Serial.print(distance);
  		 Serial.println(" cm");
		/*if(digitalRead(pir_pin) == HIGH)
		Sei
		{
			trash=HIGH;
		}*/
		if(state == HIGH ||distance <= 6)
		{
			trash=HIGH;
		}
		delay(15);
	}
	delay(3000); //kouvas
	for(posa=170;posa>=105;posa--)
	{
		arm.write(posa);//thesi default
		delay(17);
	}
	delay(1000);
	return trash;
}
