
//---------------------------------------------------//
//                                                   //
//             Arduino Photoresistor reader          //
//             Deigned for ROSpiBot project          //
//                                                   //
//  Sketch by Andrea Fioroni (andrifiore@gmail.com)  //
//                                                   //
//                  GitHub repo:                     //
// https://github.com/isarlab-department-engineering //
//                                                   //
//---------------------------------------------------//

// This sketch reads the analogic value from a photoresistor
// and communicates it to a Raspberry through the serial port

#define photoPin A0   // photoresistor pin
#define LEDPin 9      // LED pin
#define spinDelay 200 // complessive loop delay
#define ledDelay 50   // LED blink delay
#define redPin  11     // red semaphore pin
#define greenPin  12   // green semaphore pin

int photoSensor = 0;
int semaphoreState = 0;
int semaphoreCount = 0;

void setup() {
  Serial.begin(9600); // initialise serial port (9600 baud)
  pinMode(photoPin, INPUT); // setupt photoresistor as input
  pinMode(LEDPin, OUTPUT);  // setupt LED pin as output
  pinMode(redPin, OUTPUT);  // setupt red semaphore pin as output
  pinMode(greenPin, OUTPUT);  // setupt green semaphore pin as output
  analogWrite(LEDPin, 0);   // shutdown LED
  digitalWrite(redPin, HIGH); // start with red semaphore
  semaphoreCount = 35;                                                                                                                                                                  
}

void loop() {
  photoSensor = analogRead(photoPin); // read photoresistor
  Serial.println(photoSensor);  // write photoresistor value on the serial port

  semaphoreCount = semaphoreCount+1;
  if(semaphoreCount == 60) { // 12*5 = 60 (every loop is 200 ms, so they will swap every 12 secs
    swapSemaphore();
  }

  analogWrite(LEDPin, map(photoSensor,0,300,0,255));
  //blinkLED();
  
  delay(spinDelay - ledDelay);
}

void blinkLED() {
  analogWrite(LEDPin, 20);  // LED on
  delay(ledDelay);
  analogWrite(LEDPin, 0);   // LED off
}

void swapSemaphore() {
  if(semaphoreState == 1) { // green
    semaphoreState = 0;
    semaphoreCount = 35;
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  } else { // red
    semaphoreState = 1;
    semaphoreCount = 0;
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
}

