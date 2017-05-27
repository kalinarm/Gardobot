


SimpleDHT11 dht11;

class Temperature
{
public :
  void getValue() {
    // read with raw sample data.
    byte temperature = 0;
    byte humidity = 0;
    byte data[40] = {
      0    };
    if (dht11.read(pinTemperature, &temperature, &humidity, data)) {
      Serial.print("Read DHT11 failed");
      return;
    }

    //Serial.print("Sample RAW Bits: ");
    for (int i = 0; i < 40; i++) {
      //Serial.print((int)data[i]);
      if (i > 0 && ((i + 1) % 4) == 0) {
        //Serial.print(' ');
      }
    }
    //Serial.println("");

    /*Serial.print("Sensor Temp/humidity: ");
    Serial.print((int)temperature); 
    Serial.print(" *C, ");
    Serial.print((int)humidity); 
    Serial.println(" %");*/
  }
};

