#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 3
#define LED_VERDE_PIN 4
#define LED_AMARILLO_PIN 5
#define LED_ROJO_PIN 6

long duracion;
int distancia;

unsigned long previousMillis = 0;  // Para los intervalos del buzzer
unsigned long intervalAmarillo = 45;  // Intervalo para el buzzer cuando el LED es amarillo (45 ms)
unsigned long intervalRojo = 10;     // Intervalo para el buzzer cuando el LED es rojo (10 ms)
bool buzzerState = false;  // Para controlar el estado del buzzer

void setup() {
  // Configuración de pines
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_VERDE_PIN, OUTPUT);
  pinMode(LED_AMARILLO_PIN, OUTPUT);
  pinMode(LED_ROJO_PIN, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // Enviar pulso al sensor ultrasónico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Leer el tiempo de retorno del eco
  duracion = pulseIn(ECHO_PIN, HIGH);
  
  // Calcular la distancia en cm
  distancia = duracion * 0.0344 / 2;

  // Mostrar la distancia en el puerto serie (opcional)
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Obtener el tiempo actual
  unsigned long currentMillis = millis();

  // Control de buzzer y LEDs según la distancia
  if (distancia >= 11) {  // Distancia mayor o igual a 11 cm
    // LED verde sin sonido (buzzer apagado)
    digitalWrite(LED_VERDE_PIN, HIGH);
    digitalWrite(LED_AMARILLO_PIN, LOW);
    digitalWrite(LED_ROJO_PIN, LOW);
    noTone(BUZZER_PIN);  // Apagar buzzer
  } else if (distancia > 5 && distancia <= 10) {  // Distancia entre 6 y 10 cm
    // LED amarillo
    digitalWrite(LED_VERDE_PIN, LOW);
    digitalWrite(LED_AMARILLO_PIN, HIGH);
    digitalWrite(LED_ROJO_PIN, LOW);

    // Controlar el buzzer para que pite cada 45 ms
    if (currentMillis - previousMillis >= intervalAmarillo) {
      previousMillis = currentMillis;  // Actualizar el tiempo
      buzzerState = !buzzerState;  // Cambiar el estado del buzzer
      if (buzzerState) {
        tone(BUZZER_PIN, 1000, 50);  // Emitir un pitido (50 ms)
      }
    }
  } else if (distancia <= 5) {  // Distancia de 5 cm o menos
    // LED rojo
    digitalWrite(LED_VERDE_PIN, LOW);
    digitalWrite(LED_AMARILLO_PIN, LOW);
    digitalWrite(LED_ROJO_PIN, HIGH);

    // Controlar el buzzer para que pite cada 10 ms
    if (currentMillis - previousMillis >= intervalRojo) {
      previousMillis = currentMillis;  // Actualizar el tiempo
      buzzerState = !buzzerState;  // Cambiar el estado del buzzer
      if (buzzerState) {
        tone(BUZZER_PIN, 1000, 50);  // Emitir un pitido (50 ms)
      }
    }
  }

  delay(10);  // Pausa para estabilizar la lectura
}
