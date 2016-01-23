/***************************************************************************************

Tutorial:http://www.toptechboy.com/arduino/lesson-15-super-cool-arduino-color-sensor-project/

S0 S1 OUTPUT FREQUENCY SCALING           S2 S3 PHOTODIODE TYPE
L L Power down                            L L Red
L H 2%                                    L H Blue
H L 20%                                   H L Clear (no filter)
H H 100%                                  H H Green

s0=Gnd
s1=VCC


RGB
RBG
GRB
GBR
BRG
BGR

tunned for most of the colors 
******************************************************************************************/
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define wsled 6
Adafruit_NeoPixel ring = Adafruit_NeoPixel(16, wsled, NEO_GRB + NEO_KHZ800);
int s2 = 8;  //color sensor
int s3 = 7;  //color sensor
int out =4;  //color sensor

unsigned long int pulseWidth;

int rColor;
int gColor;
int bColor;

void setup() 
{
 Serial.begin(9600);
 ring.begin();
 ring.show();
 ring.setBrightness(75);

 pinMode(s2,OUTPUT);
 pinMode(s3,OUTPUT);
 pinMode(out,INPUT);
}

void loop() 
{

  //read red color
   digitalWrite(s2,LOW);
   digitalWrite(s3,LOW);
   pulseWidth=pulseIn(out,LOW);
   rColor = (pulseWidth/400) - 1;
   rColor = (255 -rColor);

   //read green color
   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   pulseWidth=pulseIn(out,LOW);
   gColor = (pulseWidth/400) - 1;
   gColor = (255 -gColor);

   //read blue color
   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   pulseWidth=pulseIn(out,LOW);
   bColor = (pulseWidth/400) - 1;
   bColor = (255 -bColor);
  // taking out orignal colors

 /*  Serial.print(rColor);
   Serial.print(",");
   Serial.print(gColor);
   Serial.print(",");
   Serial.println(bColor);
   
   delay(100);
*/

////////////////////////////////////////// TUNE THE BELOW GIVEN rColor,gColor,bColor for accurate results.//////////////////////////////////////////
   
  //White Color
  if (rColor >=251 && gColor >=251 && bColor >=251)
 {
 rColor = 255;
 bColor = 255; 
 gColor = 255;
  }
  
  //red color
else  if(rColor > gColor && gColor > bColor)
  {
   rColor = rColor;
   gColor=gColor/1.5;  // gColor = gColor   ;
   bColor=bColor * 0.05;     //bColor = bColor * 0.1;
  }
  else if(rColor > bColor && bColor > gColor)
  {
   rColor = rColor;
   bColor = bColor /  8;
   gColor = gColor *0.5;  //0.50
  }

// green color   
   else  if(gColor > rColor && rColor > bColor)
  {
   gColor = 255;
   rColor = rColor/1.5;
   bColor = bColor * 0.5;
  }
  else if(gColor > bColor && bColor > rColor)
  
  {
   gColor = 255;
   bColor = bColor/2;
   rColor = rColor * 0.50;
  }
  
  //blue color
  else if(bColor > rColor && rColor > gColor)
  
  {
   bColor = 255;
   rColor = rColor/1.5;
   gColor = gColor* 0.5;
  }
 else if(bColor > gColor && gColor > rColor)
  {
   bColor = 255;
   gColor = gColor/2;
   rColor = rColor * 0.50;
  }
  
  // no Color(black out)
  else
  {
rColor=0;
gColor=0;
bColor=0;
  }

  // correcting red,blue,green color
bColor =bColor * .6;
gColor =gColor * .95;
//rColor =rColor * .002; 

   Serial.print(rColor);
   Serial.print(",");
   Serial.print(gColor);
   Serial.print(",");
   Serial.println(bColor);
   
   delay(100);
   
//ADD ANY RGB LED CODE in this case it is neopixel

  for(int i=0;i<=16;i++)
  {  // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    ring.setPixelColor(i, ring.Color(rColor,gColor,bColor)); 
    ring.show(); // This sends the updated pixel color to the hardware.
    delay(50);
  } 

}
