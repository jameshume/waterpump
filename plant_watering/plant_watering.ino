// Tested just one iHaospace Capacitive Soil Moisture Sensor 
//    In tap water totally submerged, analog pin reads 290 ish
//    When dry analog pin reads 500 ish
//
// Using an Elegoo relay switch to turn on/off VicTsing Submersible Water Pump (400Gph 1500L/H Ultra-Quiet)
//
// TODO add Innovateking-EU HC-SR04 Ultrasonic Module Distance Sensor Kit to detect how full the water
// tank is.

static const int moisture_sensor_pin = A0;
static const int relay_pin = 3;
static const int poll_interval_ms = 1000; //1800000; // 30 minutes
static const int moisture_val_pump_start = 500;
static const int moisture_val_pump_stop = 350;

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 57600 );
}

void loop() {
  static int loop_counter = 0;

  // Monitor the moisture aproximately every half hour second - `see poll_interval_ms`
  const int moisture_val = analogRead(moisture_sensor_pin);
  Serial.println(String("Moisture = ") + moisture_val);
  
  if (moisture_val >= moisture_val_pump_start)
  {
    // Just determined this value experimentally
    Serial.println("Starting pump");
    digitalWrite(relay_pin, HIGH);
    while(analogRead(moisture_sensor_pin) > moisture_val_pump_stop)
    {
      delay(1);
    }
    Serial.println("Stopping pump");
    digitalWrite(relay_pin, LOW);
  }
  
  delay(poll_interval_ms);
}
