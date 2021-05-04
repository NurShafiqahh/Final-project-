//Library code for LCD
#include <LiquidCrystal.h>

//Initialize the variables
LiquidCrystal lcd = LiquidCrystal(13,12,11,10,9,8); 

int distance = 0;	//declare variable for containing distance sensor
int inches   = 0;   //for Ultrasonic Sensor
float cm       = 0;   // for Ultrasonic Sensor
int i	  	 = 0;	//for Ultrasonic Sensor

 
 void setup()
{  
  Serial.begin(9600);	 	//Send the data rate in bits per second for serial data
 
  pinMode(4, OUTPUT); 		//set LED (green) as output
  pinMode(5, OUTPUT); 		//set LED (yellow) as output
  pinMode(6, OUTPUT); 		//set LED (red) as output
  pinMode(3,  OUTPUT); 		//set the trigger pin as output
  pinMode(2,  INPUT); 		//set the echo pin as input  
  
    lcd.begin(16,2);			//setup the LCDs number of columns and rows
  //For LCD Display  
  lcd.setCursor(0,0);
  lcd.write("Initializing...");
  
}


void loop()
{
  int pulse1;
  distance = 333;	           // The maximum distance for sensor
  digitalWrite(3, HIGH);	   //Set the trigger pin on
  delay(1000);                 // Wait for 1000 millisecond(s)
  digitalWrite(3,LOW);		   //Set the trigger pin off
  pulse1 = pulseIn(2,HIGH);	   //Echo pin turn on to give pulse before the program start 
  cm = 0.01723 * pulse1;	   // convert to cm
  inches = ((cm *50)/127);     // convert to inches
  Serial.print(inches);
  Serial.print ("in,");
  Serial.print(cm);
  Serial.println("cm");
  
  //For LCD Display  
  lcd.setCursor(0,0);
  lcd.print("Distance in CM"); //print current distance setting on lcd		
  lcd.setCursor(0,1);
  lcd.print(cm);

    if (cm > distance) 
  {
    lcd.setCursor(7,1);
    lcd.print("BOOM!!!!");
    digitalWrite(4, LOW);  //Green LED turn OFF
    digitalWrite(5, LOW);	//Yellow LED turn OFF
    digitalWrite(6, LOW);	//Red LED turn OFF
    noTone(7);

  }
  
  else if (cm <= distance - 10 && cm > distance - 149) // cm <= 273 && cm > 184
  {
    lcd.setCursor(7,1);
    lcd.print("LETSGO :D");
    digitalWrite(4, HIGH);	//Green LED turn ON
    digitalWrite(5,  LOW);	//Yellow LED turn OFF
    digitalWrite(6,  LOW);	//Red LED turn OFF
       i=1;
    while (i==1)
    {
      tone(7,350);
      delay(75);
      noTone(7);
      delay(500);
      i=0;
    }

    
  }
  else if (cm <= distance - 150 && cm > distance - 249 )  // cm <= 183 && cm > 84
  {
    lcd.setCursor(7,1);
    lcd.print("Careful<3");
    digitalWrite(4, LOW);	//Green LED turn OFF
    digitalWrite(5, HIGH);	//Yellow LED turn ON
    digitalWrite(6,  LOW);	//Red LED turn OFF
      i=1;
    while (i==1)
    {
      tone(7,350);
      delay(250);
      noTone(7);
      delay(100);
      i=0;
    }

  }
  else if (cm <= distance - 250 && cm > distance - 310)  // cm <= 83 && cm > 23 
  {
    lcd.setCursor(7,1);
    lcd.print("DANGERR!!");
    digitalWrite(4, LOW);	//Green LED turn OFF
    digitalWrite(5, LOW);	//Yellow LED turn OFF
    digitalWrite(6, HIGH);	//Red LED turn ON
     i=1;
    while (i==1)
    {
      tone(7,350);
      delay(500);
      noTone(7);
      delay(100);
      i=0;
    }
  
  }
    else if (cm<= distance)
  {
    digitalWrite(4, LOW);	//Green LED turn OFF
    digitalWrite(5, LOW);	//Yellow LED turn OFF
    digitalWrite(6, LOW);	//Red LED turn ON
     i=1;
    while (i==1)
    {
    tone(7,350);
    delay(500);
    i=0;
    }
  }

  delay(1000);             // Wait for 1000 millisecond(s)

}