// ESP32-S3 SuperMini — 2x4 Button Matrix
// 2 Rows × 4 Columns = 8 buttons

const int ROWS = 2;
const int COLS = 4;

// Change these to match your PCB wiring
const int rowPins[ROWS] = {
  4, 5
};

const int colPins[COLS] = {
  6, 7, 8, 9
};

// Button state tracking
bool lastState[ROWS][COLS];
bool currentState[ROWS][COLS];

void setup() {
  Serial.begin(115200);

  // Rows are outputs
  for (int r = 0; r < ROWS; r++) {
    pinMode(rowPins[r], OUTPUT);
    digitalWrite(rowPins[r], HIGH);

    for (int c = 0; c < COLS; c++) {
      lastState[r][c] = false;
      currentState[r][c] = false;
    }
  }

  // Columns are inputs with pull-ups
  for (int c = 0; c < COLS; c++) {
    pinMode(colPins[c], INPUT_PULLUP);
  }

  Serial.println("2x4 Matrix Ready");
}

void loop() {

  for (int r = 0; r < ROWS; r++) {

    // Activate current row
    digitalWrite(rowPins[r], LOW);

    delayMicroseconds(5);

    for (int c = 0; c < COLS; c++) {

      // LOW means button is pressed
      bool pressed = digitalRead(colPins[c]) == LOW;

      currentState[r][c] = pressed;

      // Detect button press
      if (pressed && !lastState[r][c]) {
        Serial.print("Pressed: R");
        Serial.print(r);
        Serial.print(" C");
        Serial.println(c);
      }

      // Detect button release
      if (!pressed && lastState[r][c]) {
        Serial.print("Released: R");
        Serial.print(r);
        Serial.print(" C");
        Serial.println(c);
      }

      lastState[r][c] = pressed;
    }

    // Deactivate row
    digitalWrite(rowPins[r], HIGH);
  }

  delay(5);
}