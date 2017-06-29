enum ButtonState {
  Normal,
  Pushed
};

struct Button {
  int pin;
  bool state;
  unsigned long pressedStart;
};

Button btn0 = { 2, false, 0 };
Button btn1 = { 3, false, 0 };
Button btn2 = { 4, false, 0 };
Button btn3 = { 5, false, 0 };

void setup() {
  pinMode(btn0.pin, INPUT_PULLUP);  // sets this pin as an input and activates the internal pullup so you don't need a resistor
  pinMode(btn1.pin, INPUT_PULLUP);
  pinMode(btn2.pin, INPUT_PULLUP);
  pinMode(btn3.pin, INPUT_PULLUP);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
}

void queryHardwareForButtonState(struct Button *btn) {
    int currentState = digitalRead(btn->pin);
    //btn->state = digitalRead(btn->pin);

    if(currentState == LOW) {
        btn->state = true;
        //btn.pressedStart = millis();
 
    } else if(currentState == HIGH){
        btn->state = false;
        //digitalWrite(LED_BUILTIN, LOW);
    }
  
}

void addButtonToJSON(Button btn) {
  Serial.print(" { ");
  Serial.print("\"id\": ");
  Serial.print(btn.pin);
  Serial.print(", ");
  Serial.print("\"state\": ");
  
  if( btn.state == false ) {
    Serial.print("false");
    
  } else {
    Serial.print("true");
  }

  Serial.print(" }");
}

void sendAllButtonStates() {
    Serial.print("{ \"buttons\": [");
    addButtonToJSON(btn0);
    Serial.print(",");
    addButtonToJSON(btn1);
    Serial.print(",");
    addButtonToJSON(btn2);
    Serial.print(",");
    addButtonToJSON(btn3);

    Serial.print(" ] }\n");
  
}

void loop() {
    queryHardwareForButtonState(&btn0);
    queryHardwareForButtonState(&btn1);
    queryHardwareForButtonState(&btn2);
    queryHardwareForButtonState(&btn3);
    sendAllButtonStates();
    //delay(250);
}

