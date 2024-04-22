// 바뀐 코드 : 정상 동작
#include <Wire.h>
#include <DHT11.h>

#define SLAVE_ADDRESS   0x04

// GPIO PIN
#define ULTRA_SOCNIC_ECHO 8     // 초음파 센서
#define ULTRA_SOVIC_TRIG 9      // 초음파 센서
#define TEMPER_IN 3             // 내부 온도 센서
#define TEMPER_OUT 4            // 외부 온도 센서
#define LIGHT_IN A0             // 내부 조도 센서
#define LIGHT_OUT A1            // 외부 조도 센서
#define DUST_IN A2              // 내부 미세먼지 센서
#define DUST_OUT A3             // 외부 미세먼지 센서
#define WATER 2                 // 빗물 센서

// sensor variables
int ultra_sonic = 9999;
int temper_in = 9999;
int temper_out = 9999;
int light_in = 9999;
int light_out = 9999;
int dust_in = 9999;
int dust_out = 9999;
int water = 9999;

DHT11 dht_in(TEMPER_IN);
DHT11 dht_out(TEMPER_OUT);

// protocol
int High_Data = 0;
int Low_Data = 0;
int Header = 0;
int Tail = 0;

// send variables
int receive_num = 0;
int send_cnt = 0;

void setup()
{
 Serial.begin(9600);

  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  // pin mode setting
  pinMode(ULTRA_SOCNIC_ECHO, INPUT);
  pinMode(ULTRA_SOVIC_TRIG, OUTPUT);
  pinMode(LIGHT_IN, INPUT);
  pinMode(LIGHT_OUT, INPUT);
  pinMode(DUST_IN, INPUT);
  pinMode(DUST_OUT, INPUT);
  pinMode(WATER, INPUT);

//  Serial.println("Ready");
}

void loop()
{
  ultra_sonic = ultra_sonic_signal();
  // temper_in = temper_signal('I');
  // temper_out = temper_signal('O');
  light_in = light_signal('I');
  light_out = light_signal('O');
  dust_in = dust_signal('I');
  dust_out = dust_signal('O');
  water = water_signal();

  Serial.println("<초음파>");
  Serial.println(ultra_sonic);
  
  Serial.println("<온도>");
  Serial.print("in : ");
  Serial.print(temper_in);
  Serial.print(" / out : ");
  Serial.println(temper_out);

  Serial.println("<밝기>");
  Serial.print("in : ");
  Serial.print(light_in);
  Serial.print(" / out : ");
  Serial.println(light_out);

  Serial.println("<미세먼지>");
  Serial.print("in : ");
  Serial.print(dust_in);
  Serial.print(" / out : ");
  Serial.println(dust_out);
  
  Serial.println("<수분량>");
  Serial.println(water);

  Serial.println();
}

int ultra_sonic_signal()
{
  long dur, dis;

  digitalWrite(ULTRA_SOVIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_SOVIC_TRIG, HIGH);
  delayMicroseconds(10);

  dur = pulseIn(ULTRA_SOCNIC_ECHO, HIGH);
  dis = dur * 17 / 1000;

  return dis;
}

float temper_signal(char c)
{
  float temp, humid; // non use value

  if (c == 'I') {
    temp = dht_in.readTemperature();
    return temp;
  } 
  else {
    temp = dht_out.readTemperature();
    return temp;
  }
}

int light_signal(char c)
{
  if (c == 'I') {
    return analogRead(LIGHT_IN);
  }
  else {
    return analogRead(LIGHT_OUT);
  }
}

int dust_signal(char c)
{
  if (c == 'I') {
    return analogRead(DUST_IN);
  }
  else {
    return analogRead(DUST_OUT);
  }
}

int water_signal()
{
  return digitalRead(WATER);
}

void receiveData(int byteCount) 
{  
  while (Wire.available()) {  
    receive_num = Wire.read(); 
    // Serial.println(receive_num);
  }  
}

void sendData() 
{  
  if (receive_num == 110) { // send water data
    if (send_cnt % 4 == 0) Wire.write(110);
    else if (send_cnt % 4 == 1) Wire.write(water / 100);
    else if (send_cnt % 4 == 2) Wire.write(water % 100);
    else if (send_cnt % 4 == 3) Wire.write(water / 100 + water % 100);
  }
  else if (receive_num == 120) { // send inside temperature data
    if (send_cnt % 4 == 0) Wire.write(120);
    else if (send_cnt % 4 == 1) Wire.write(temper_in / 100);
    else if (send_cnt % 4 == 2) Wire.write(temper_in % 100);
    else if (send_cnt % 4 == 3) Wire.write(temper_in / 100 + temper_in % 100);
  }
  else if (receive_num == 130) { // send inside dust data
    if (send_cnt % 4 == 0) Wire.write(130);
    else if (send_cnt % 4 == 1) Wire.write(dust_in / 100);
    else if (send_cnt % 4 == 2) Wire.write(dust_in % 100);
    else if (send_cnt % 4 == 3) Wire.write(dust_in / 100 + dust_in % 100);
  }
  else if (receive_num == 140) { // send inside light data
    if (send_cnt % 4 == 0) Wire.write(140);
    else if (send_cnt % 4 == 1) Wire.write(light_in / 100);
    else if (send_cnt % 4 == 2) Wire.write(light_in % 100);
    else if (send_cnt % 4 == 3) Wire.write(light_in / 100 + light_in % 100);
  }
  else if (receive_num == 210) { // send ultra sonic data
    if (send_cnt % 4 == 0) Wire.write(210);
    else if (send_cnt % 4 == 1) Wire.write(ultra_sonic / 100);
    else if (send_cnt % 4 == 2) Wire.write(ultra_sonic % 100);
    else if (send_cnt % 4 == 3) Wire.write(ultra_sonic / 100 + ultra_sonic % 100);
  }
  else if (receive_num == 220) { // send outside temperature data
    if (send_cnt % 4 == 0) Wire.write(220);
    else if (send_cnt % 4 == 1) Wire.write(temper_out / 100);
    else if (send_cnt % 4 == 2) Wire.write(temper_out % 100);
    else if (send_cnt % 4 == 3) Wire.write(temper_out / 100 + temper_out % 100);
  }
  else if (receive_num == 230) { // send outside dust data
    if (send_cnt % 4 == 0) Wire.write(230);
    else if (send_cnt % 4 == 1) Wire.write(dust_out / 100);
    else if (send_cnt % 4 == 2) Wire.write(dust_out % 100);
    else if (send_cnt % 4 == 3) Wire.write(dust_out / 100 + dust_out % 100);
  }
  else if (receive_num == 240) { // send outside light data
    if (send_cnt % 4 == 0) Wire.write(240);
    else if (send_cnt % 4 == 1) Wire.write(light_out / 100);
    else if (send_cnt % 4 == 2) Wire.write(light_out % 100);
    else if (send_cnt % 4 == 3) Wire.write(light_out / 100 + light_out % 100);
  }
  send_cnt = send_cnt%4;
}

