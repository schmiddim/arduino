 /*
 HC 06
 Wiring
 //https://www.psi-online.de/BluetoothModem_1966.html?print=1


App
//  https://play.google.com/store/apps/details?id=mobi.dzs.android.BluetoothSPP

Ebay
// http://www.ebay.de/itm/231258586592?ssPageName=STRK:MEWNX:IT&_trksid=p3984.m1439.l2649


This works not on digital Pins
HC06
*/
char val; // variable to receive data from the serial port
int ledpin = 13; // LED connected to pin 48 (on-board LED)

void setup() {

  pinMode(ledpin, OUTPUT);  // pin 48 (on-board LED) as OUTPUT
  Serial.begin(9600);       // start serial communication at 9600bps
  digitalWrite(ledpin, HIGH);
}

void loop() {
  
  if( Serial.available() )       // if data is available to read
  {
    val = Serial.read();         // read it and store it in 'val'
  }
  if( val == 'H' )               // if 'H' was received
  {
    digitalWrite(ledpin, HIGH);  // turn ON the LED
    delay(100);n
    Serial.write("HIGH");
  } else { 
    digitalWrite(ledpin, LOW);   // otherwise turn it OFF
  }
  delay(100);                    // wait 100ms for next reading
} 
