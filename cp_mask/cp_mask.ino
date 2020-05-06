/*
 * (c)2020 - V
 * 
 * 2020-05-03
 * 
 *        _____      _                                   _    
 *       / ____|    | |                                 | |   
 *      | |    _   _| |__   ___ _ __ _ __ ___   __ _ ___| | __
 *      | |   | | | | '_ \ / _ \ '__| '_ ` _ \ / _` / __| |/ /
 *      | |___| |_| | |_) |  __/ |  | | | | | | (_| \__ \   < 
 *        \_____\__, |_.__/ \___|_|  |_| |_| |_|\__,_|___/_|\_\
 *               __/ |                                         
 *              |___/                                          
 *              
 *    ╔═══════════════════════════════════════════════════════════════════════════╗        
 *    ║ Coolness: ▲▼▲▼▲ 
 *    ║ Verteidigung: ▲
 *    ║ 2x XP-Rate
 *    ║ 1,5x StreetCred-Rate
 *    ║ "Mit so einer Maske steigerst du deinen StreetCred einfach schneller. Logisch, DU siehst einfach vertrauenswürdiger und cool aus!"
 *    ║ "V hat es gebaut. Es MUSS also gut sein."
 *    ╚═══════════════════════════════════════════════════════════════════════════╝
 *     
 */

#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 14 //Anzahl der insgesamten anzusteuernden LEDs
#define DATA_PIN 4 //Datenleitung RGB-LED-Streifen Pin D4

#define S1 2 // Blinker rechts Pin D2
#define S2 3 // Blinker links Pin D3

float factor = 1.0; //Faktor für Farbberechnung Night Rider beidseitig bunt
volatile unsigned long alteZeit = 0, entprellZeit = 50; //Variablen für Entprellung

//LED-Streifen Deklaration
Adafruit_NeoPixel leds(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

//Prototypen
void IRQ_S1(); //Blinker rechts
void IRQ_S2(); //Blinker links
void nightrider(); //Night Rider Effekt
void nightrider_double(); //Night Rider beidseitig
void nightrider_double_color(); //Night Rider beidseitig in bunt
void nightrider_double_pink_turkis(); //Night Rider beidseitig in pink und türkis
void pink_up(); //pink aufsteigend
void pink_down(); //pink absteigend
void turkis_up(); //türkis aufsteigend
void turkis_down(); //türkis absteigend

void setup() //wird nur einmal nach Start/Reset vom µC aufgerufen
{
  //Serial.begin(115200); //Serielle Konsole mit 115200 Baud auf dem COM-Port vom µC zum Debuggen
  // Blinkerpins als INPUT-Pins definieren, Pullup-R hier extern
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);

  //Interrupts für Taster. Lösen bei fallender Flanke aus, da Pullup-R Input auf HIGH zieht und Taster drücken auf LOW
  attachInterrupt(digitalPinToInterrupt(S1), IRQ_S1, FALLING);
  attachInterrupt(digitalPinToInterrupt(S2), IRQ_S2, FALLING);

  // LED-Streifen Init
  leds.begin();
  leds.show();
  leds.setBrightness(5); // Helligkeit festlegen. Für Dauerbetrieb 60-100 empfohlen. Maxwert: 255
}

void loop() //läuft kontinuierlich durch (intern eine while(1)-Schleife)
{
  for(int i = 0; i < 4; i++)
  {
    nightrider();
  }

  for(int i = 0; i < 5; i++)
  {
    nightrider_double();
  }

  for(int i = 0; i < 3; i++)
  {
    pink_up();
    delay(80);
  }

  for(int i = 0; i < 3; i++)
  {
    turkis_up();
    delay(80);
  }

  for(int i = 0; i < 10; i++)
  {
    nightrider_double_color();
  }
  
  for(int i = 0; i < 3; i++)
  {
    pink_down();
    delay(80);
  }

  for(int i = 0; i <3 ; i++)
  {
    turkis_down();
    delay(80);
  }

  for(int i = 0; i < 7; i++)
  {
    nightrider_double_pink_turkis();
  }
}

void nightrider()
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds.clear(); //alle LEDs ausschalten
    leds.setPixelColor(i, leds.Color(150, 0, 0)); // an Position i LED auf RGB Wert setzen
    leds.show(); //LED leuchten lassen
    delay(50); //Wartezeit, bis weiter im Programm
  }

  for(int i = NUM_LEDS - 1; i > 0; i--)
  {
    leds.clear();
    leds.setPixelColor(i, leds.Color(150, 0, 0));
    leds.show();
    delay(50);
  }
}

void nightrider_double()
{
  int j = NUM_LEDS - 1;
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds.clear();
    leds.setPixelColor(i, leds.Color(150, 0, 0));
    leds.setPixelColor(j, leds.Color(150, 0, 0));
    leds.show();
    j--;
    delay(60);
  }
}

void nightrider_double_color()
{
  int j = NUM_LEDS - 1;
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds.clear();
    leds.setPixelColor(i, leds.Color(50*abs(cos(factor)), 100*abs(sin(factor)), 10*abs(tan(factor))));
    leds.setPixelColor(j, leds.Color(50*abs(cos(factor)), 100*abs(sin(factor)), 10*abs(tan(factor))));
    leds.show();
    j--;
    factor += 0.2;
    delay(60);
  }
}

void nightrider_double_pink_turkis()
{
  int j = NUM_LEDS - 1;
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds.clear();
    leds.setPixelColor(i, leds.Color(255, 9, 229));
    leds.setPixelColor(j, leds.Color(9, 217, 255));
    leds.show();
    j--;
    delay(60);
  }
}

void pink_down()
{
  leds.clear();

  int j = 6;
  for(int i = 7; i < NUM_LEDS; i++)
  {
    leds.setPixelColor(i, leds.Color(255, 9, 229));
    leds.setPixelColor(j, leds.Color(255, 9, 229));
    leds.show();
    j--;
    delay(100);
  }
}

void pink_up()
{
  leds.clear();

  int j = NUM_LEDS - 1;
  for(int i = 0; i < 7; i++)
  {
    leds.setPixelColor(i, leds.Color(255, 9, 229));
    leds.setPixelColor(j, leds.Color(255, 9, 229));
    leds.show();
    j--;
    delay(100);
  }
}

void turkis_down()
{
  leds.clear();

  int j = 6;
  for(int i =7 ; i < NUM_LEDS; i++)
  {
    leds.setPixelColor(i, leds.Color(9, 217, 255));
    leds.setPixelColor(j, leds.Color(9, 217, 255));
    leds.show();
    j--;
    delay(100);
  }
}

void turkis_up()
{
  leds.clear();

  int j = NUM_LEDS - 1;
  for(int i = 0; i < 7; i++)
  {
    leds.setPixelColor(i, leds.Color(9, 217, 255));
    leds.setPixelColor(j, leds.Color(9, 217, 255));
    leds.show();
    j--;
    delay(100);
  }
}

void IRQ_S1()
{
  //Blinker rechts
  //Entprellbeispiel ist ausm Netz
  if((millis() - alteZeit) > entprellZeit)
  { 
    detachInterrupt(digitalPinToInterrupt(S1)); //Interrupts unterbrechen, damit die nicht nochmal auslösen können. (Taster prellen wie Sau!)
    detachInterrupt(digitalPinToInterrupt(S2));
    // innerhalb der entprellZeit nichts machen
    //Serial.println("rechts");
    leds.clear();

    for(int j = 0; j < 4; j++)
    {
      for(int i = 6; i >= 0; i--)
      {
        leds.setPixelColor(i, leds.Color(255, 45, 0));
        leds.show();
        delay(120);
      }
      leds.clear();
      delay(80);
    }
    leds.clear();
    alteZeit = millis(); // letzte Schaltzeit merken
    attachInterrupt(digitalPinToInterrupt(S1), IRQ_S1, FALLING); //Interrupts wieder aktivieren
    attachInterrupt(digitalPinToInterrupt(S2), IRQ_S2, FALLING);      
  }
}

void IRQ_S2()
{
  //Blinker links
  //Entprellbeispiel ist ausm Netz
  if((millis() - alteZeit) > entprellZeit)
  { 
    detachInterrupt(digitalPinToInterrupt(S1));
    detachInterrupt(digitalPinToInterrupt(S2));
    // innerhalb der entprellZeit nichts machen
    //Serial.println("links");
    leds.clear();

    for(int j = 0; j < 4; j++)
    {
      for(int i = 7; i < NUM_LEDS; i++)
      {
        leds.setPixelColor(i, leds.Color(255, 45, 0));
        leds.show();
        delay(120);
      }
      leds.clear();
      delay(80);
    }
    leds.clear();
    alteZeit = millis(); // letzte Schaltzeit merken
    attachInterrupt(digitalPinToInterrupt(S1), IRQ_S1, FALLING);
    attachInterrupt(digitalPinToInterrupt(S2), IRQ_S2, FALLING);      
  }
}
