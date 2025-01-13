#include <Arduino.h>

// Pines táctiles
const int touchPins[6] = {T0, T6, T7, T8, T9, T4}; // Pines personalizados
const int noteFrequencies[6] = {262, 294, 330, 349, 392, 440}; // Notas: DO, RE, MI, FA, SOL, LA

// Pin del parlante
const int speakerPin = 26;

// Sensibilidad táctil (ajústala según sea necesario)
const int touchThreshold = 30;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 6; i++) {
    touchAttachInterrupt(touchPins[i], nullptr, touchThreshold);
  }
  pinMode(speakerPin, OUTPUT);
  Serial.println("Teclado táctil listo");
}

void loop() {
  for (int i = 0; i < 6; i++) {
    int touchValue = touchRead(touchPins[i]);
    if (touchValue < touchThreshold) {
      playNote(noteFrequencies[i]);
      delay(300); // Evitar múltiples activaciones
    }
  }
}

// Reproduce una nota en el parlante
void playNote(int frequency) {
  tone(speakerPin, frequency, 200); // Reproduce la nota durante 200 ms
  delay(200);
  noTone(speakerPin); // Detiene el tono
}
