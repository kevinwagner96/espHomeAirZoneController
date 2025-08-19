#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define NUM_SERVOS 10
const int servoPins[NUM_SERVOS] = {34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
Servo servos[NUM_SERVOS];


// Sensor DS18B20
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
unsigned long lastTempRead = 0;
const unsigned long tempInterval = 30000;

// Comando de servo
struct ServoCommand {
  int index;
  int angle;
};

// Cola de comandos
const int QUEUE_SIZE = 20;
ServoCommand commandQueue[QUEUE_SIZE];
int queueStart = 0;
int queueEnd = 0;
int servoRunning = 0;
bool commandInProgress = false;
unsigned long lastCommandTime = 0;
const unsigned long commandDelay = 1000;  // tiempo entre comandos
int currentAngle[NUM_SERVOS] = {0};

String inputString = "";
bool receiving = false;

void enqueueCommand(int index, int angle) {
  int nextEnd = (queueEnd + 1) % QUEUE_SIZE;
  if (nextEnd != queueStart) {  // No llena
    commandQueue[queueEnd].index = index;
    commandQueue[queueEnd].angle = angle;
    queueEnd = nextEnd;
  } else {
    Serial.println("Cola llena, comando descartado");
  }
}

bool dequeueCommand(ServoCommand &cmd) {
  if (queueStart == queueEnd) return false;  // Vacía
  cmd = commandQueue[queueStart];
  queueStart = (queueStart + 1) % QUEUE_SIZE;
  return true;
}

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);

  // Inicializar servos
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0);
    delay(500);
    servos[i].detach();
  }

  // Inicializar sensor de temperatura
  sensors.begin();
}

void loop() {
  // Procesar comandos entrantes
  while (Serial3.available()) {
    char inChar = (char)Serial3.read();
    if (inChar == '[') {
      receiving = true;
      inputString = "";
    } else if (inChar == ']') {
      receiving = false;
      processCommand(inputString);
    } else if (receiving) {
      inputString += inChar;
    }
  }

  // Ejecutar comando de servo si no hay uno en progreso
  if (!commandInProgress) {
    ServoCommand cmd;
    if (dequeueCommand(cmd)) {
      commandInProgress = true;
      servoRunning = cmd.index;
      lastCommandTime = millis();

      // Ejecutar comando
      moveServoSlow(cmd.index, cmd.angle, 1, 10);
      Serial.print("Servo: ");
      Serial.print(cmd.index);
      Serial.println(" ejecutado");      
    }
  } else {
    if (millis() - lastCommandTime >= commandDelay) {
      servos[servoRunning].detach();
      commandInProgress = false;      
    }
  }

  // Leer temperatura periódicamente
  if (millis() - lastTempRead >= tempInterval) {
    lastTempRead = millis();
    sensors.requestTemperatures();
    delay(750);  // espera típica de conversión

    float tempC = sensors.getTempCByIndex(0);
    if (tempC != DEVICE_DISCONNECTED_C) {
      Serial.print("Temperatura: ");
      Serial.print(tempC);
      Serial.println(" °C");
      Serial3.print("{\"sensores\":[{\"sensor\":\"Temperatura\",\"name\":\"Exterior\",\"value\":");
      Serial3.print(tempC);
      Serial3.println("}]}");
    } else {
      Serial.println("Error: Sensor no conectado");
    }
  }
}

void processCommand(const String& command) {
  // Espera formato F:idx:angle
  if (command.startsWith("F:")) {
    int firstColon = command.indexOf(':');
    int secondColon = command.indexOf(':', firstColon + 1);

    if (firstColon != -1 && secondColon != -1) {
      int index = command.substring(firstColon + 1, secondColon).toInt();
      int angle = command.substring(secondColon + 1).toInt();

      if (index >= 0 && index < NUM_SERVOS && angle >= 0 && angle <= 180) {
        enqueueCommand(index, angle);
      }
    }
  }
}

void moveServoSlow(int index, int target, int step, int delayMs) {
  // Obtener ángulo actual
  int current = currentAngle[index];

  // Adjuntar servo (en caso de que no esté activo)
  servos[index].attach(servoPins[index]);

  // Mover de forma gradual
  if (current < target) {
    for (int pos = current; pos <= target; pos += step) {
      servos[index].write(pos);
      currentAngle[index] = pos; // guardar último ángulo
      delay(delayMs);
    }
  } else {
    for (int pos = current; pos >= target; pos -= step) {
      servos[index].write(pos);
      currentAngle[index] = pos;
      delay(delayMs);
    }
  }

  // Detener señal para liberar el servo
  servos[index].detach();
}