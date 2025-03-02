// C++ code
//
#include <LiquidCrystal.h>

//temperature sensor variables
float temp_vout;   
float temp; 
float voltage;

//gas sensor variables
int gas_sensor_port = A1;
int gas_sensor_value = 0;

// Wind speed measurement variables
float V_wind = 0;
float Windspeedfloat;
int Windspeedint;

// Rainfall measurement variables
float rain;
const int triggerPin = 10;
const int echoPin = 9;
long duration;
LiquidCrystal lcd(8, 2, 6, 5, 4, 3); // LCD setup

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(A0, INPUT);  //temperature sensor analog input
  pinMode(A1, INPUT);     //gas sensor analog input 
  pinMode(A2, INPUT); // Set pin A2 as input for wind speed measurement
  pinMode(7, OUTPUT);     //gas sensor digital output
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2); // Initialize LCD
  Serial.println("Setup done"); // Debugging statement
}

void loop() {
  temp_vout = analogRead(A0);
  voltage = temp_vout * 0.0048828125; //convert analog value between 0 to 1023 with 5000mV/5V ADC 
  temp = (voltage - 0.5) * 100.0;
  Serial.print("Current temperature: ");
  Serial.println(temp); // Print temperature value
  delay(1000); // Delay for 1 second
  Serial.println("Looping..."); // Debugging statement
  
  // Read wind speed
  float V_wind = analogRead(A2) * (5.0 / 1023.0);
  
  // Convert voltage to MPH
  Windspeedint = (V_wind - 0.4) * 10 * 2.025 * 2.237;
  Windspeedfloat = (V_wind - 0.4) * 10 * 2.025 * 2.237;
  
  // Output wind speed to serial monitor
  Serial.print("Wind Speed: ");
  if (Windspeedfloat <= 0)
  {
    Serial.print("0.0");
  } 
  else 
  {
    Serial.print(Windspeedfloat);
  }
  Serial.println(" MPH");
  
  // Output anemometer voltage to serial monitor
  Serial.print("Anemometer Voltage: ");
  if (V_wind > 2) 
  {
    Serial.println("Out of range!");
  }
  else if (V_wind < 0.4)
  {
    Serial.println("Out of range!");
  } 
  else
  {
    Serial.print(V_wind);
    Serial.println(" V");
  }
  
  delay(1000); // Delay for 1 second before the next reading
  
  //for gas sensor 
  
  gas_sensor_value = analogRead(gas_sensor_port);
  Serial.println("Gas sensor value: " + String(gas_sensor_value));
  if (gas_sensor_value > 200)
  {
    tone(7,523,1000);
  }
  // For rainfall measurement
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  rain = 0.01723 * duration;

  // Display rainfall on LCD
  lcd.setCursor(0, 0);
  lcd.print("Rainfall: ");
  lcd.print(rain);
  lcd.print(" mm");

  // Print rainfall to serial monitor
  Serial.print("Rainfall: ");
  Serial.print(rain);
  Serial.println(" mm");

  delay(1000); // Delay for stability
  //wind speed LCD output
  lcd.setCursor(0,1);        // adjust cursor
  lcd.print("Wind speed");
  lcd.print(" ");
  if (V_wind < 0.4)
  {         
    lcd.print("0");
  }     	 
  else 
  {				      
    lcd.print(Windspeedint);
  }
  lcd.print("MPH");
  //wind speed serial monitor output
  Serial.print("Wind Speed: ");       
  if (Windspeedfloat <= 0)
  {            
    Serial.print("0.0");}				
  else{									 
    Serial.print(Windspeedfloat);}	// Output Wind speed value
  Serial.println(" MPH");				
  delay(100);
}