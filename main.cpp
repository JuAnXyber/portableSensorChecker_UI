// Learn about the ESP32 WiFi simulation in
// https://docs.wokwi.com/guides/esp32-wifi
// btn means the button

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

#define btn1 16 //define your button pins here
#define btn2 17 //define your button pins here
#define btn3 18 //define your button pins here
#define btn4 2  //define your button pins here
#define btn5 4  //define your button pins here

int page=0;
String pilihanSensor = "";
// int tempSlaveId = 0;
int tempSlaveId = 0;
int humidSlaveId = 0;

void page_pilihSensor() {
  LCD.setCursor(0, 1);
  LCD.println("<Back Next>   OK");
  if(digitalRead(btn1)==1)
  {
    LCD.setCursor(0, 0);
    LCD.println("<   humidity   >");
    pilihanSensor = "humidity";
    Serial.println(pilihanSensor);
  }
  else if(digitalRead(btn2)==1)
  {
    LCD.setCursor(0, 0);
    LCD.println("< temperature  >");
    pilihanSensor = "temperature";
    Serial.println(pilihanSensor);
  }
  else if(digitalRead(btn5)==1)
  {
    Serial.println("OK");
    Serial.println(pilihanSensor);
    if(pilihanSensor=="humidity")
    {
      page=1;
    }
    else if(pilihanSensor=="temperature")
    {
      page=2;
    }
  }
  Serial.println(page);
}


void page_rwSensorHumidity() {
  LCD.setCursor(0,0);
  LCD.println("   (humidity)   ");
  LCD.setCursor(0,1);
  LCD.println("<Back Write>    ");
  if(digitalRead(btn1)==1)
  {
    page=0;
  }
  else if(digitalRead(btn2)==1)
  {
    page=3;
  }
  Serial.println(page);
}

void page_rwSensorTemperature() {
  LCD.setCursor(0,0);
  LCD.println("  (temperature) ");
  LCD.setCursor(0,1);
  LCD.println("<Back Write>    ");
  if(digitalRead(btn1)==1)
  {
    page=0;
    LCD.setCursor(0, 0);
    LCD.println("< PILIH SENSOR >");
  }
  else if(digitalRead(btn2)==1)
    {
    page=4;
    Serial.println(page);
  }
  Serial.println(page);
}

void page_writeSensorHumidity() {
  LCD.setCursor(0,0);
  LCD.println("INPUT SLAVE ID:");
  LCD.setCursor(15,0);
  LCD.println(humidSlaveId);
  LCD.setCursor(0,1);
  LCD.println("<Back  -  +   OK");
  if(digitalRead(btn1)==1)
  {
    page=0;
    LCD.setCursor(0, 0);
    LCD.println("< PILIH SENSOR >");
  }
  else if(digitalRead(btn3)==1)
  {
    humidSlaveId=humidSlaveId-1;
    Serial.println(humidSlaveId);
  }
  else if(digitalRead(btn4)==1)
  {
    humidSlaveId=humidSlaveId+1;
    Serial.println(humidSlaveId);
  }
  else if(digitalRead(btn5))
  {
    LCD.setCursor(0,0);
    LCD.println("Write ID Success");
    LCD.setCursor(0,1);
    LCD.println("Wait 5 Second...");
    delay(5000);
    page=1;
  }
  if(humidSlaveId<=0)
  {
    humidSlaveId=0;
  }
  else if(humidSlaveId>=9)
  {
    humidSlaveId=9;
  }
}

void page_writeSensorTemperature() {
  LCD.setCursor(0,0);
  LCD.println("INPUT SLAVE ID:");
  LCD.setCursor(15,0);
  LCD.println(tempSlaveId);
  LCD.setCursor(0,1);
  LCD.println("<Back  -  +   OK");
  if(digitalRead(btn1)==1)
  {
    page=0;
    LCD.setCursor(0, 0);
    LCD.println("< PILIH SENSOR >");
  }
  else if(digitalRead(btn3)==1)
  {
    tempSlaveId=tempSlaveId-1;
    Serial.println(tempSlaveId);
  }
  else if(digitalRead(btn4)==1)
  {
    tempSlaveId=tempSlaveId+1;
    Serial.println(tempSlaveId);
  }
  else if(digitalRead(btn5)==1)
  {
    LCD.setCursor(0,0);
    LCD.println("Write ID Success");
    LCD.setCursor(0,1);
    LCD.println("Wait 5 Second...");
    delay(5000);
    page=2;

  }
  if(tempSlaveId<=0)
  {
    tempSlaveId=0;
  }
  else if(tempSlaveId>=9)
  {
    tempSlaveId=9;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  pinMode(btn5, INPUT);

  LCD.init();
  LCD.backlight();
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.println("< PILIH SENSOR >");
  LCD.setCursor(0, 1);
  LCD.println("<Back Next>   OK");


  
}

void loop() {
  if(page==0)
  {
    page_pilihSensor();
  }
  if(page==1)
  {
    page_rwSensorHumidity();
  }
  if(page==2)
  {
    page_rwSensorTemperature();
  }
  if(page==3)
  {
    page_writeSensorHumidity();
  }
  if(page==4)
  {
    page_writeSensorTemperature();
  }

  delay(50);
}
