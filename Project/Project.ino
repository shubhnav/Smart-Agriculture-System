#include <SoftwareSerial.h>

SoftwareSerial ports(2,3);//rx,tx

int temperature(){
  float temp=0;
  temp=analogRead(A0);
  temp=temp*0.48828125;
  //Serial.print("Temparature   ");
  //Serial.print(temp);
  //Serial.print("*C");
  //Serial.println();
  delay(1000);
  
  return (int)temp;
  }
int soilsensor(){
  int soil= analogRead(A4);
  //Serial.print("Moisture  ");
  //Serial.print(soil);
  //Serial.println();
  delay(1000);
  return soil;
  }
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    ports.begin(9600);
    delay(50);

    ports.println("AT+CGMI;\r\n");// network
    delay(1000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());
    
    ports.println("AT+CSQ;\r\n");// network strength
    delay(1000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());

    ports.println("AT+CREG?;\r\n");// registered sim card
    delay(1000);
    while (ports.available())  //forward data  to monitor
    Serial.write(ports.read());

    ports.println("AT+CGATT=1;\r\n");// attach to gprs
    delay(5000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());


    ports.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\";\r\n");// open gprs context
    delay(5000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());

    ports.println("AT+SAPBR=3,1,\"APN\",\"internet\";\r\n");// apn of internet provider
    delay(5000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());
    
    ports.println("AT+SAPBR=1,1;\r\n");// permissions to read 
    delay(5000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());
    
    ports.println("AT+SAPBR=2,1;\r\n");// permission to write
    delay(5000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());

}

void loop() {
  // put your main code here, to run repeatedly:
  
  
    
    int t=temperature();
    delay(50);
    int humi=soilsensor();
    delay(50);
    ports.println("AT+HTTPINIT;\r\n");// http service request
    delay(20000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());

    ports.println("AT+HTTPPARA=\"CID\",1;\r\n");// argument to write in server
    delay(10000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());
   
    
    ports.print("AT+HTTPPARA=\"URL\",\"http://agriculture19.000webhostapp.com/index.php?t=");// server address
    ports.print(t);
    ports.print("&h=");
    ports.print(humi);
    ports.print("\"\r\n"); 
    delay(10000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());

  
    ports.println("AT+HTTPACTION=0;\r\n");// http post action
    delay(10000);
    while (ports.available())  //forward data  to monitor
    Serial.write(ports.read());

    ports.println("AT+HTTPREAD;\r\n");// read 
    delay(20000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());
    
    ports.println("AT+HTTPTERM;\r\n");// http session termination
    delay(5000);
    while (ports.available())  // forward data  to monitor
    Serial.write(ports.read());
    
    if(t>50 || humi>800)
       ports.println("ATD+917024942***;\r\n");
     delay(10000);
}
