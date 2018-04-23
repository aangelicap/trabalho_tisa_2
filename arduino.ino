int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to voltage
unsigned long fsrResistance;  // The voltage converted to resistance, can be very big so make "long"
unsigned long fsrConductance;
long fsrForce;       // Finally, the resistance converted to force

void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}

void loop(void) {
  fsrReading = analogRead(fsrPin);
  fsrVoltage = fsrReading*(5000/1023);

  if (fsrVoltage == 0) {
    Serial.print("I0");
    Serial.print("\n");
    delay(20);
  } else {
    fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 10000;                // 10K resistor
    fsrResistance /= fsrVoltage;

    fsrConductance = 1000000;           // we measure in micromhos so
    fsrConductance /= fsrResistance;
    
      // Use the two FSR guide graphs to approximate the force
      if (fsrConductance <= 1000) {
        fsrForce = fsrConductance / 80;
        Serial.print("I");
        Serial.print(fsrForce);
        Serial.print("\n");
        delay(20);
       } else {
        fsrForce = fsrConductance - 1000;
        fsrForce /= 30;
        Serial.print("I");
        Serial.print(fsrForce);
        Serial.print("\n");
        delay(20);
      }
  }
  delay(1000);
}
