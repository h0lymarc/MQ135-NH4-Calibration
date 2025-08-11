/*  _      ___  _                                
   | |    / _ \| |                               
   | |__ | | | | |_   _ _ __ ___   __ _ _ __ ___ 
   | '_ \| | | | | | | | '_ ` _ \ / _` | '__/ __|
   | | | | |_| | | |_| | | | | | | (_| | | | (__ 
   |_| |_|\___/|_|\__, |_| |_| |_|\__,_|_|  \___|
                   __/ |                         
                  |___/                          
*/

/*Just turn on the sensor 24-48hrs for better accuracy*/

#define MQ_PIN  A0
const float RL = 20.0;   
const float Ro = 3.6;   
const float m = -0.280; 
const float b = 0.425; 

float ppm;

void setup() {
  Serial.begin(115200);
}

void loop() {
  detectNH3();
  delay(1000);
}

void detectNH3() {
  float sensor_volt, RS_gas, RS_ratio;
  float analog_value = analogRead(MQ_PIN);
  Serial.print("Analog value: ");
  Serial.println(analog_value);

 
  sensor_volt = analog_value * (5.0 / 1023.0);

  RS_gas = (RL * (5.0 - sensor_volt) / sensor_volt);
  RS_ratio = RS_gas / Ro;
  ppm = (log10(RS_ratio) - b) / m;


if (ppm < 0) {
    ppm = 0;
  }
  Serial.print("PPM: ");
  Serial.println(ppm);
  Serial.print("ADC: ");
  Serial.println(sensor_volt);
  
  Serial.println();
}
