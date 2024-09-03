// Learn about the ESP32 WiFi simulation in
// https://docs.wokwi.com/guides/esp32-wifi

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// #include <DHT.h>
// #include <dht.h>
#include <DHTesp.h>

DHTesp dhtSensor;
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

#define btn1 16
#define btn2 17
#define btn3 18
#define btn4 2
#define btn5 4
#define relay 19

const int DHT_PIN = 15;

int page           = 0;
int pilihanSensor  = 0;
int tempSlaveId    = 0;
int humidSlaveId   = 0;

void page_pilihSensor() {
  LCD.setCursor(0, 1);
  LCD.println("<Back Next>   OK");
  if(pilihanSensor == 1) 
  {
    LCD.setCursor(0, 0);
    LCD.println("<  temperature >");
    Serial.println(pilihanSensor);
  }
  else if(pilihanSensor == 2) 
  {
    LCD.setCursor(0, 0);
    LCD.println("<   humidity   >");
    Serial.println(pilihanSensor);
  }

  if(digitalRead(btn1)==1)
  {
    pilihanSensor = pilihanSensor+1;
    Serial.println(pilihanSensor);
  }
  else if(digitalRead(btn2)==1)
  {
    pilihanSensor = pilihanSensor+1;
    Serial.println(pilihanSensor);
  }
  else if(digitalRead(btn5)==1)
  {
    Serial.println("OK");
    Serial.println(pilihanSensor);
    if(pilihanSensor == 1)
    {
      page=2;
    }
    else if(pilihanSensor == 2)
    {
      page=1;
    }
  }
  if(pilihanSensor == 3)
  {
    pilihanSensor = 1;
  }
  Serial.println(page);
}


void page_rwSensorHumidity() {
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  LCD.setCursor(0,0);
  LCD.println("HUMID :" + String(data.humidity, 1) + "%");
  LCD.setCursor(0,1);
  LCD.println("<Back Write>    ");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
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
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  LCD.setCursor(0,0);
  LCD.println("TEMP :" + String(data.temperature, 2) + "C");
  LCD.setCursor(0,1);
  LCD.println("<Back Write>    ");
  Serial.println("Temperature: " + String(data.temperature, 2) + "°C");
  if(digitalRead(btn1)==1)
  {
    page=0;
    pilihanSensor = 1;
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
    pilihanSensor = 2;
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
    page=5;
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
    page=6;
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

void page_vadidateWriteHumidity() {
  LCD.setCursor(0,0);
  LCD.println(" WRITE PROCCESS ");
  LCD.setCursor(0,1);
  LCD.println("WAIT FOR 10 SEC ");
  //VALIDATING 
  LCD.setCursor(0,0);
  LCD.println("RESTARTING .....");
  LCD.setCursor(0,1);
  LCD.println("PLEASE WAIT ....");
  delay(5000);
  digitalWrite(relay, HIGH);
  Serial.println("relay nyala");
  delay(5000);
  Serial.println("relay mati");
  digitalWrite(relay, LOW);
  LCD.setCursor(0,0);
  LCD.println("SUCCESS RESTART ");
  LCD.setCursor(0,1);
  LCD.println("WAIT FOR 5 SEC  ");
  delay(3000);
  LCD.clear();
  page=1;
}

void page_vadidateWriteTemperature() {
  LCD.setCursor(0,0);
  LCD.println(" WRITE PROCCESS ");
  LCD.setCursor(0,1);
  LCD.println("WAIT FOR 10 SEC ");
  //VALIDATING 
  LCD.setCursor(0,0);
  LCD.println("RESTARTING .....");
  LCD.setCursor(0,1);
  LCD.println("PLEASE WAIT ....");
  delay(5000);
  digitalWrite(relay, HIGH);
  delay(5000);
  digitalWrite(relay, LOW);
  LCD.setCursor(0,0);
  LCD.println("SUCCESS RESTART ");
  LCD.setCursor(0,1);
  LCD.println("WAIT FOR 5 SEC  ");
  delay(3000);
  LCD.clear();
  page=2;
}


void setup() {
  Serial.begin(115200);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  pinMode(btn5, INPUT);
  pinMode(relay, OUTPUT);
  // pinMode(sensor, INPUT);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

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
  if(page==5)
  {
    page_vadidateWriteHumidity();
  }
  if(page==6)
  {
    page_vadidateWriteTemperature();
  }

  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  delay(50);
}
