#include <JC_Button.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <EEPROM.h>

Servo myservo;

#define ENTER_BUTTON_PIN 11
#define UP_BUTTON_PIN 10
#define DOWN_BUTTON_PIN 9
#define BACK_BUTTON_PIN 8
#define MANUAL_BUTTON_PIN A1
#define HALL_LED_PIN 7
#define SERVO_PIN 6
#define POWER_LED_PIN 5
#define HALL_PIN 2  

Button enterBtn(ENTER_BUTTON_PIN);
Button upBtn(UP_BUTTON_PIN);
Button downBtn(DOWN_BUTTON_PIN);
Button backBtn(BACK_BUTTON_PIN);
Button manualFeedBtn(MANUAL_BUTTON_PIN);

LiquidCrystal_I2C lcd(0x20, 16, 2);

// Змінні для RTC DS1307
int clockData[7];  // [секунди, хвилини, години, день тижня, день, місяць, рік]

// Змінні
unsigned long hallSensorTime;
unsigned long rotationTime = 2000;
boolean manualFeed = false;
boolean hall_sensor_fail = false;

unsigned long blink_previousMillis = 0;
boolean blink_state = false;
unsigned long blink_interval = 500;


int count;
boolean feeding1_complete = false;
boolean feeding2_complete = false;
boolean feeding1_trigger = false;
boolean feeding2_trigger = false;
boolean servoOn = true;

// Датчик Холла
volatile boolean hallSensorActivated = false;
volatile int isr_count = 1;

void hallActiveISR() {
  hallSensorActivated = true;
  digitalWrite(HALL_LED_PIN, HIGH);
  isr_count++;
}

void startFeeding(int feedNumber = 1);

// Стани
enum {
  btnENTER,
  btnUP,
  btnDOWN,
  btnBACK,
};

enum STATES {
  MAIN,
  MENU_EDIT_FEED1,
  MENU_EDIT_FEED2,
  MENU_EDIT_TIME,
  MENU_EDIT_PORTION,
  EDIT_FEED1_HOUR,
  EDIT_FEED1_MIN,
  EDIT_FEED2_HOUR,
  EDIT_FEED2_MIN,
  EDIT_HOUR,
  EDIT_MIN,
  EDIT_PORTION
};

STATES state = MAIN;

// Час та порції
int Hour = 12;
int Minute = 0;
int portion = 5;

int feed_time1_hour = 8;
int feed_time1_min = 0;
int feed_time2_hour = 18;
int feed_time2_min = 0;

int userInput;

byte check_Char[8] = {
  B00000,
  B00000,
  B00001,
  B00011,
  B10110,
  B11100,
  B11000,
  B00000
};

// Функції для роботи з DS1307
void DS1307_get(int *timeArray) {
  Wire.beginTransmission(0x68);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(0x68, 7);
  for (int i = 0; i < 7; i++) {
    timeArray[i] = bcdToDec(Wire.read());
  }
}

void DS1307_set() {
  Wire.beginTransmission(0x68);
  Wire.write(0x00);
  Wire.write(decToBcd(0));  // Секунди
  Wire.write(decToBcd(Minute));  // Хвилини
  Wire.write(decToBcd(Hour));    // Години
  Wire.write(decToBcd(1));       // День тижня (1 = понеділок)
  Wire.write(decToBcd(1));       // День місяця
  Wire.write(decToBcd(1));       // Місяць
  Wire.write(decToBcd(24));      // Рік (2024)
  Wire.endTransmission();
}

byte decToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}

byte bcdToDec(byte val) {
  return ((val / 16 * 10) + (val % 16));
}

// Оновлення часу з RTC
void updateTimeFromRTC() {
  DS1307_get(clockData);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Setup starting...");
 
  // Ініціалізація I2C для RTC
  Wire.begin();
 
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, check_Char);

  // Ініціалізація кнопок
  enterBtn.begin();
  upBtn.begin();
  downBtn.begin();
  backBtn.begin();
  manualFeedBtn.begin();

  // Налаштування пінів
  pinMode(POWER_LED_PIN, OUTPUT);
  pinMode(HALL_LED_PIN, OUTPUT);
  pinMode(HALL_PIN, INPUT_PULLUP);

  // Переривання
  attachInterrupt(digitalPinToInterrupt(HALL_PIN), hallActiveISR, FALLING);
 
  digitalWrite(POWER_LED_PIN, HIGH);
  digitalWrite(HALL_LED_PIN, LOW);

  // Завантаження з EEPROM
  get_feed_time1();
  get_feed_time2();
  get_completed_feedings();
  get_portion();
 
  myservo.attach(SERVO_PIN); // Приєднуємо серво тут один раз
  myservo.write(94);
  Serial.println("Setup successful!");
}

void loop() {
  updateTimeFromRTC();  // Оновлюємо час з DS1307
  changing_states();
  check_buttons();
  check_feedtime();
  manual_feed_check();
  check_hall_sensor();
}

void check_buttons() {
  enterBtn.read();
  upBtn.read();
  downBtn.read();
  backBtn.read();
  manualFeedBtn.read();

  if (enterBtn.wasPressed()) {
    Serial.println("Enter pressed");
    userInput = btnENTER;
    menu_transitions(userInput);

    enterBtn.read();
    delay(50);
    enterBtn.read();
  }
  if (upBtn.wasPressed()) {
    Serial.println("Up pressed");
    userInput = btnUP;
    menu_transitions(userInput);
  }
  if (downBtn.wasPressed()) {
    Serial.println("Down pressed");
    userInput = btnDOWN;
    menu_transitions(userInput);
  }
  if (backBtn.wasPressed()) {
    Serial.println("Back pressed");
    userInput = btnBACK;
    menu_transitions(userInput);
  }
  if (manualFeedBtn.wasPressed()) {
    Serial.println("Manual feed pressed");
    manualFeed = true;
  }
}

void changing_states() {
  switch (state) {
    case MAIN:
      display_current_time();
      display_feeding_times();
      display_portion();
      break;
    case MENU_EDIT_FEED1:
      display_set_feed_time1_menu();
      break;
    case MENU_EDIT_FEED2:
      display_set_feed_time2_menu();
      break;
    case MENU_EDIT_TIME:
      display_set_time_menu();
      break;
    case MENU_EDIT_PORTION:
      display_set_portion_menu();
      break;
    case EDIT_FEED1_HOUR:
      set_feed_time1();
      break;
    case EDIT_FEED1_MIN:
      set_feed_time1();
      break;
    case EDIT_FEED2_HOUR:
      set_feed_time2();
      break;
    case EDIT_FEED2_MIN:
      set_feed_time2();
      break;
    case EDIT_HOUR:
      set_the_time();
      break;
    case EDIT_MIN:
      set_the_time();
      break;
    case EDIT_PORTION:
      set_the_portion();
      break;
  }
}

void menu_transitions(int input) {
  switch (state) {
    case MAIN:
      if (input == btnENTER) {
        lcd.clear();
        state = MENU_EDIT_FEED1;
      }
      if (input == btnBACK) {
        hall_sensor_fail = false;
      }
      break;
    case MENU_EDIT_FEED1:
      if (input == btnBACK) {
        lcd.clear();
        state = MAIN;
      } else if (input == btnENTER) {
        lcd.clear();
        state = EDIT_FEED1_HOUR;
      } else if (input == btnDOWN) {
        lcd.clear();
        state = MENU_EDIT_FEED2;
      }
      break;
    case EDIT_FEED1_HOUR:
      servoOn = false;
      if (input == btnUP) {
        feed_time1_hour++;
        if (feed_time1_hour > 23) feed_time1_hour = 0;
      } else if (input == btnDOWN) {
        feed_time1_hour--;
        if (feed_time1_hour < 0) feed_time1_hour = 23;
      } else if (input == btnBACK) {
        lcd.clear();
        servoOn = true;
        state = MENU_EDIT_FEED1;
      } else if (input == btnENTER) {
        state = EDIT_FEED1_MIN;
      }
      break;
    case EDIT_FEED1_MIN:
      if (input == btnUP) {
        feed_time1_min++;
        if (feed_time1_min > 59) feed_time1_min = 0;
      } else if (input == btnDOWN) {
        feed_time1_min--;
        if (feed_time1_min < 0) feed_time1_min = 59;
      } else if (input == btnBACK) {
        state = EDIT_FEED1_HOUR;
      } else if (input == btnENTER) {
        lcd.clear();
        lcd.print("*Settings Saved*");
        delay(1000);
        lcd.clear();
        servoOn = true;
        write_feeding_time1();

        feeding1_complete = false; 
        EEPROM.write(4, feeding1_complete); 

        state = MAIN;
      }
      break;
    case MENU_EDIT_FEED2:
      if (input == btnUP) {
        lcd.clear();
        state = MENU_EDIT_FEED1;
      } else if (input == btnENTER) {
        lcd.clear();
        state = EDIT_FEED2_HOUR;
      } else if (input == btnDOWN) {
        lcd.clear();
        state = MENU_EDIT_TIME;
      }
      break;
    case EDIT_FEED2_HOUR:
      servoOn = false;
      if (input == btnUP) {
        feed_time2_hour++;
        if (feed_time2_hour > 23) feed_time2_hour = 0;
      } else if (input == btnDOWN) {
        feed_time2_hour--;
        if (feed_time2_hour < 0) feed_time2_hour = 23;
      } else if (input == btnBACK) {
        lcd.clear();
        servoOn = true;
        state = MENU_EDIT_FEED2;
      } else if (input == btnENTER) {
        state = EDIT_FEED2_MIN;
      }
      break;
    case EDIT_FEED2_MIN:
      if (input == btnUP) {
        feed_time2_min++;
        if (feed_time2_min > 59) feed_time2_min = 0;
      } else if (input == btnDOWN) {
        feed_time2_min--;
        if (feed_time2_min < 0) feed_time2_min = 59;
      } else if (input == btnBACK) {
        state = EDIT_FEED2_HOUR;
      } else if (input == btnENTER) {
        lcd.clear();
        lcd.print("*Settings Saved*");
        delay(1000);
        lcd.clear();
        servoOn = true;
        write_feeding_time2();

        feeding2_complete = false;
        EEPROM.write(5, feeding2_complete);

        state = MAIN;
      }
      break;
    case MENU_EDIT_TIME:
      if (input == btnUP) {
        lcd.clear();
        state = MENU_EDIT_FEED2;
      } else if (input == btnENTER) {
        lcd.clear();
        state = EDIT_HOUR;
      } else if (input == btnDOWN) {
        lcd.clear();
        state = MENU_EDIT_PORTION;
      }
      break;
    case EDIT_HOUR:
      if (input == btnUP) {
        Hour++;
        if (Hour > 23) Hour = 0;
      } else if (input == btnDOWN) {
        Hour--;
        if (Hour < 0) Hour = 23;
      } else if (input == btnBACK) {
        lcd.clear();
        state = MENU_EDIT_TIME;
      } else if (input == btnENTER) {
        state = EDIT_MIN;
      }
      break;
    case EDIT_MIN:
      if (input == btnUP) {
        Minute++;
        if (Minute > 59) Minute = 0;
      } else if (input == btnDOWN) {
        Minute--;
        if (Minute < 0) Minute = 59;
      } else if (input == btnBACK) {
        state = EDIT_HOUR;
      } else if (input == btnENTER) {
        lcd.clear();
        lcd.print("*Settings Saved*");
        delay(1000);
        lcd.clear();
        // Встановлюємо час на DS1307
        DS1307_set();
        state = MAIN;
      }
      break;
    case MENU_EDIT_PORTION:
      if (input == btnUP) {
        lcd.clear();
        state = MENU_EDIT_TIME;
      } else if (input == btnENTER) {
        lcd.clear();
        state = EDIT_PORTION;
      }
      break;
    case EDIT_PORTION:
      if (input == btnUP) {
        portion++;
        if (portion > 20) portion = 1;
      } else if (input == btnDOWN) {
        portion--;
        if (portion < 1) portion = 20;
      } else if (input == btnBACK) {
        lcd.clear();
        state = MENU_EDIT_PORTION;
      } else if (input == btnENTER) {
        lcd.clear();
        lcd.print("*Settings Saved*");
        delay(1000);
        lcd.clear();
        write_portion();
        state = MAIN;
      }
      break;
  }
}

void check_feedtime() {
  // Використовуємо реальний час з DS1307
  if (clockData[0] == 0) {  // Секунди == 0
    if ((clockData[2] == feed_time1_hour) && (clockData[1] == feed_time1_min)) {
      feeding1_trigger = true;
      if (servoOn && !feeding1_complete) {
        lcd.clear();
        lcd.print("First Feeding");
        startFeeding(1);
      }
    } else if ((clockData[2] == feed_time2_hour) && (clockData[1] == feed_time2_min)) {
      feeding2_trigger = true;
      if (servoOn && !feeding2_complete) {
        lcd.clear();
        lcd.print("Second Feeding");
        startFeeding(2);
      }
    }
  }
 
  // Скидання опівночі
  if (clockData[2] == 0 && clockData[1] == 0) {
    feeding1_complete = false;
    feeding2_complete = false;
    EEPROM.write(4, feeding1_complete);
    EEPROM.write(5, feeding2_complete);
  }
}

void display_current_time() {
  lcd.setCursor(11, 0);
  add_leading_zero(clockData[2]);  // Години
  lcd.print(":");
  add_leading_zero(clockData[1]);  // Хвилини
}

void add_leading_zero(int num) {
  if (num < 10) lcd.print("0");
  lcd.print(num);
}

void display_feeding_times() {
  lcd.setCursor(0, 0);
  lcd.print("F1:");
  add_leading_zero(feed_time1_hour);
  lcd.print(":");
  add_leading_zero(feed_time1_min);
  lcd.print(" ");
  if (feeding1_complete) lcd.write(0);
  else lcd.print(" ");
 
  lcd.setCursor(0, 1);
  lcd.print("F2:");
  add_leading_zero(feed_time2_hour);
  lcd.print(":");
  add_leading_zero(feed_time2_min);
  lcd.print(" ");
  if (feeding2_complete) lcd.write(0);
  else lcd.print(" ");
}

void display_portion() {
  lcd.setCursor(12, 1);
  lcd.print("P:");
  add_leading_zero(portion);
}

void startFeeding(int feedNumber = 1) {
  myservo.attach(SERVO_PIN);
  count = 0;
  hallSensorTime = millis();

  hall_sensor_fail = false;
 
  while (count < portion) {
    servoStart();
   
    if (hallSensorActivated) {
      count++;
      Serial.print("Feeding#"+ String(feedNumber) +" scored: count = ");
      Serial.println(count);
      hallSensorTime = millis();
      hallSensorActivated = false;
      digitalWrite(HALL_LED_PIN, LOW);
      continue;
    }
   
    if (millis() - hallSensorTime > rotationTime) {
      Serial.print("Protection 'jiggle': ");
      Serial.print(millis() - hallSensorTime);
      Serial.print(" > ");
      Serial.println(rotationTime);
      hall_sensor_fail = true;
      digitalWrite(HALL_LED_PIN, HIGH);
      hallSensorTime = millis();
      jiggle();
    }
  }

  if (feedNumber == 1) {
    Serial.println("Feeding #1 is completed");
    feeding1_complete = true;
    EEPROM.write(4, feeding1_complete);
  } else if (feedNumber == 2) {
    Serial.println("Feeding #2 is completed");
    feeding2_complete = true;
    EEPROM.write(5, feeding2_complete);
  } else if (feedNumber == 99) {
    Serial.println("Manual feeding is completed");
  }

  hallSensorActivated = false;
 
  servoStop();
  digitalWrite(HALL_LED_PIN, LOW);
  myservo.detach();
 
  lcd.clear();
  delay(2000);
  lcd.clear();
}

void servoStart() {
  myservo.write(180);
}

void servoStop() {
  myservo.write(94);
}

void jiggle() {
  myservo.write(80);
  delay(30);
  myservo.write(93);
  delay(30);
  myservo.write(180);
}

void write_feeding_time1() {
  EEPROM.write(0, feed_time1_hour);
  EEPROM.write(1, feed_time1_min);
}

void write_feeding_time2() {
  EEPROM.write(2, feed_time2_hour);
  EEPROM.write(3, feed_time2_min);
}

void write_portion() {
  EEPROM.write(6, portion);
}

void get_feed_time1() {
  feed_time1_hour = EEPROM.read(0);
  if (feed_time1_hour > 23) feed_time1_hour = 8;
  feed_time1_min = EEPROM.read(1);
  if (feed_time1_min > 59) feed_time1_min = 0;
}

void get_feed_time2() {
  feed_time2_hour = EEPROM.read(2);
  if (feed_time2_hour > 23) feed_time2_hour = 18;
  feed_time2_min = EEPROM.read(3);
  if (feed_time2_min > 59) feed_time2_min = 0;
}

void get_portion() {
  portion = EEPROM.read(6);
  if (portion > 20 || portion < 1) portion = 5;
}

void get_completed_feedings() {
  feeding1_complete = EEPROM.read(4);
  feeding2_complete = EEPROM.read(5);
}

void check_hall_sensor() {
  if (hall_sensor_fail) {
    blinkFunction();
    digitalWrite(HALL_LED_PIN, blink_state ? HIGH : LOW);
  } else {
    digitalWrite(HALL_LED_PIN, LOW);
  }
}

void manual_feed_check() {
  if (manualFeed) {
    manualFeed = false;
    lcd.clear();
    lcd.print("Manual Feeding");
    startFeeding(99);
    manualFeedBtn.read();
    delay(50); 
    manualFeedBtn.read();
  }
}

void blinkFunction() {
  unsigned long currentMillis = millis();
  if (currentMillis - blink_previousMillis > blink_interval) {
    blink_previousMillis = currentMillis;
    blink_state = !blink_state;
  }
}

// Інші функції відображення меню
void display_set_feed_time1_menu() {
  lcd.setCursor(2, 0);
  lcd.print("Menu Options");
  lcd.setCursor(0, 1);
  lcd.print("Set Feed Time 1");
}

void display_set_feed_time2_menu() {
  lcd.setCursor(2, 0);
  lcd.print("Menu Options");
  lcd.setCursor(0, 1);
  lcd.print("Set Feed Time 2");
}

void display_set_time_menu() {
  lcd.setCursor(2, 0);
  lcd.print("Menu Options");
  lcd.setCursor(2, 1);
  lcd.print("Set the Time");
}

void display_set_portion_menu() {
  lcd.setCursor(2, 0);
  lcd.print("Menu Options");
  lcd.setCursor(0, 1);
  lcd.print("Set the Portion");
}

void set_feed_time1() {
  lcd.setCursor(0, 0);
  lcd.print("Set Feed Time 1");
  lcd.setCursor(5, 1);
 
  if (state == EDIT_FEED1_HOUR) {
    if (!blink_state) add_leading_zero(feed_time1_hour);
    else lcd.print("  ");
  } else {
    add_leading_zero(feed_time1_hour);
  }
 
  lcd.print(":");
 
  if (state == EDIT_FEED1_MIN) {
    if (!blink_state) add_leading_zero(feed_time1_min);
    else lcd.print("  ");
  } else {
    add_leading_zero(feed_time1_min);
  }
 
  blinkFunction();
}

void set_feed_time2() {
  lcd.setCursor(0, 0);
  lcd.print("Set Feed Time 2");
  lcd.setCursor(5, 1);
 
  if (state == EDIT_FEED2_HOUR) {
    if (!blink_state) add_leading_zero(feed_time2_hour);
    else lcd.print("  ");
  } else {
    add_leading_zero(feed_time2_hour);
  }
 
  lcd.print(":");
 
  if (state == EDIT_FEED2_MIN) {
    if (!blink_state) add_leading_zero(feed_time2_min);
    else lcd.print("  ");
  } else {
    add_leading_zero(feed_time2_min);
  }
 
  blinkFunction();
}

void set_the_time() {
  lcd.setCursor(2, 0);
  lcd.print("Set the Time");
  lcd.setCursor(5, 1);
 
  if (state == EDIT_HOUR) {
    if (!blink_state) add_leading_zero(Hour);
    else lcd.print("  ");
  } else {
    add_leading_zero(Hour);
  }
 
  lcd.print(":");
 
  if (state == EDIT_MIN) {
    if (!blink_state) add_leading_zero(Minute);
    else lcd.print("  ");
  } else {
    add_leading_zero(Minute);
  }
 
  blinkFunction();
}

void set_the_portion() {
  lcd.setCursor(0, 0);
  lcd.print("Set the Portion");
  lcd.setCursor(7, 1);
 
  if (!blink_state) add_leading_zero(portion);
  else lcd.print("  ");
 
  blinkFunction();
}