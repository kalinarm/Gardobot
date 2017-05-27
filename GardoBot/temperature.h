


SimpleDHT11 dht11;

class Temperature
{
public :
float temperature;
float humidity;
  void getValue() {
    // read with raw sample data.
    byte _temperature = 0;
    byte _humidity = 0;
    byte data[40] = {
      0    };
    if (dht11.read(pinTemperature, &_temperature, &_humidity, data)) {
      Serial.print("Read DHT11 failed");
      return;
    }
    temperature = _temperature;
    humidity =_humidity;
    //Serial.print("Sample RAW Bits: ");
    /*for (int i = 0; i < 40; i++) {
      //Serial.print((int)data[i]);
      if (i > 0 && ((i + 1) % 4) == 0) {
        //Serial.print(' ');
      }
    }*/
    //Serial.println("");

   // Serial.print("Sensor Temp/humidity: ");
    //Serial.print((int)temperature); 
    //Serial.print(";");
    //Serial.println((int)humidity); 
   // Serial.println(" %");
  }
};

