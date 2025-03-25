
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif



U8G2_ST75256_JLX240160_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 7, /* reset=*/ 6);

// End of constructor list
int sensor_pin = A0;
int output_value ;

void setup(void) {

  Serial.begin(9600);
  u8g2.begin(); 

}

uint8_t m = 24;
int uvolt,buf,d1,d2;
float voltage;
void loop(void) {
  char m_str[20];
  char m_str2[20];
  char m_str3[20];

  output_value= analogRead(sensor_pin);
  Serial.println(output_value);

  voltage=((float)output_value/1023.0)*4.85;
  Serial.println(voltage);
  //==============================================
  // convert to lcd
  //==============================================
  uvolt=(int)(voltage*100.0); //456
  Serial.println(uvolt);
  buf=(int)voltage; //4
  Serial.println(buf);
  d1=buf*100;//400
  Serial.println(d1);
  d2=(int)(voltage*10.0);//56
  d2=uvolt-d1;//456-400
  Serial.println(d2);
  strcpy(m_str, u8x8_u16toa(output_value,4));//m, 2));    // convert m to a string with two digits
  strcpy(m_str2, u8x8_u16toa(buf,1));
  strcpy(m_str3, u8x8_u16toa(d2,2));
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_bubble_tr );
    u8g2.drawStr(0, 40,"MapSens Meter"); 
    u8g2.setFont(u8g2_font_helvB18_tr );
    u8g2.drawStr(0, 106,"Rpm:"); 
    u8g2.setFont(u8g2_font_logisoso42_tn);
    u8g2.drawStr(84,108,m_str);
    u8g2.setFont(u8g2_font_helvB18_tr );  
    u8g2.drawStr(0, 160,"Volt:");
    u8g2.drawStr(84,160,m_str2);
    u8g2.drawStr(94,160," .");
    u8g2.drawStr(108,160,m_str3); 
  } while ( u8g2.nextPage() );
  delay(1000);
  m++;
  if ( m == 60 )
    m = 0;
}

