#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int buzzer = 13;
bool loaded = true;
bool canStartLoop = false;

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 8, 7, 6, 5 };
uint8_t rowPins[ROWS] = { 12, 11, 10, 9 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  initialize();
  load(800);
}

bool selected = false;

void loop() {
  if(canStartLoop=true){
    char key = keypad.getKey();
    if(!selected){
      lcd.print("> .");delay(100);lcd.clear();
      lcd.print("> ..");delay(100);lcd.clear();
      lcd.print("> ...");delay(100);lcd.clear();
    }
    
    switch(key){

      case '1': 
      selected = true;
      dobuzz(3);
      lcd.clear();
      lcd.print("Selected 1"); 
      break;

      case '2': 
      selected = true;
      dobuzz(3);
      lcd.clear();
      lcd.print("Selected 2"); 
      break;

      case '3': 
      selected = true;
      dobuzz(3);
      lcd.clear();
      lcd.print("Selected 3"); 
      break;


    }
  }
}

void initialize(){
  lcd.init();
  lcd.noBacklight();
  lcd.print("  Initialized");
  dobuzz(0);
  delay(500);
  lcd.backlight();
  dobuzz(0);
  delay(500);
}
void load(int loadTime){
  //for effect
  loaded = false;
  int timer = 150;
  lcd.clear();
  lcd.print("    Loading");
  delay(loadTime);
  while(!loaded){
  lcd.println(".....");
  if(timer >= 0){timer--;} else {loaded=true;}
  }
  lcd.clear();
  lcd.println("     Loaded");
  dobuzz(0);
  delay(loadTime);
  lcd.clear();
  delay(loadTime/2);
  lcd.print("Select action");
  dobuzz(1);
  delay(1000);
  lcd.clear();
  lcd.print("Press & hold");
  dobuzz(1);
  delay(1000);
  lcd.clear();
  canStartLoop = true;
}

void dobuzz(int whatbuzz){
  switch(whatbuzz){
    case 0:
    tone(buzzer,50);
    delay(50);
    noTone(buzzer);
    break;

    case 1:
    tone(buzzer,100);
    delay(50);
    noTone(buzzer);
    break;

    case 3:
    tone(buzzer,150);
    delay(25);
    noTone(buzzer);
  }
}
