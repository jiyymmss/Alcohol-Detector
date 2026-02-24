const int mq3Pin = A0; // Analog input pin A0
const int buzzerPin = 7; // Buzzer connected to digital pin 7

void setup() {
  Serial.begin(115200); // Initialize serial communication
  pinMode(mq3Pin, INPUT); // Set the analog pin as input
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
}

void loop() {
  int sensorValue = analogRead(mq3Pin); // Read analog value from the sensor
  float voltage = sensorValue * (5.0 / 1023.0); // Convert sensor value to voltage (assuming 5V Arduino)
  
  float sensorCurve = 0.21; // Sensitivity characteristic curve
  float sensorOffset = 0.22; // Sensor offset value
  float alcoholConcentration = sensorCurve * voltage - sensorOffset; // Calculate estimated alcohol concentration
  
  if (alcoholConcentration < 0.00) {
    alcoholConcentration = 0.00; // Avoid negative values
  }
  
  int alcoholConcentrationInt = static_cast<int>(alcoholConcentration * 1000); // Convert to integer milligrams per liter

  if(alcoholConcentrationInt > 100){
    digitalWrite(buzzerPin, HIGH);  
  }else{
    digitalWrite(buzzerPin, LOW);  
  }

if (alcoholConcentrationInt == 0){
  Serial.print("");
}else if(alcoholConcentrationInt == 0 && alcoholConcentrationInt < 40){
  Serial.println(alcoholConcentrationInt);
}else{
  Serial.println(alcoholConcentrationInt);
}

  // Serial.println(alcoholConcentrationInt); // Send alcohol concentration data to ESP8266
  delay(1000); // Delay before sending the next reading
}
