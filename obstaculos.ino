#define SENSOR_PIN 34  // Pin conectado a la salida del sensor de obstáculos (HW-201)
#define BUZZER_PIN 25  // Pin conectado al buzzer activo

void setup() {
  pinMode(SENSOR_PIN, INPUT); // Usar PULLDOWN si hay ruido
  pinMode(BUZZER_PIN, OUTPUT);    // Configurar el pin del buzzer como salida
  digitalWrite(BUZZER_PIN, LOW);  // Asegurarse de que el buzzer esté apagado al iniciar
  Serial.begin(115200);           // Inicializar la comunicación serial para depuración
}

void loop() {
  int sensorValue = digitalRead(SENSOR_PIN);  // Leer el estado del sensor de obstáculos

  if (sensorValue == LOW) {
    // El sensor detecta un obstáculo (normalmente LOW cuando detecta)
    sirenSound();
    Serial.println("Obstáculo detectado.");
  } else {
    // No se detecta obstáculo
    digitalWrite(BUZZER_PIN, LOW);  // Apagar el buzzer
    Serial.println("No hay obstáculo.");
  }

  delay(100);  // Pequeño retraso para evitar lecturas erráticas
}

void sirenSound() {
  // Emitir un sonido de sirena alternando frecuencias
  for (int i = 0; i < 2; i++) {
    tone(BUZZER_PIN, 1000);  // Emitir un tono de 1000 Hz
    delay(200);              // Mantener el tono durante 200 ms
    tone(BUZZER_PIN, 1500);  // Emitir un tono de 1500 Hz
    delay(200);              // Mantener el tono durante 200 ms
  }
  noTone(BUZZER_PIN);  // Detener el tono al terminar
}
