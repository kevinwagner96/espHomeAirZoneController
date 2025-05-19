# espHomeAirZoneController

Este proyecto integra un sistema de control de ventilación y sensores de temperatura usando ESPHome y un Arduino Mega, permitiendo la gestión desde Home Assistant.

## Descripción

- **ESPHome**: Controla y monitoriza ventiladores y relés a través de UART, y recibe datos del Arduino Mega.
- **Arduino Mega**: Gestiona servos (ventiladores) y sensores de temperatura DS18B20, recibiendo comandos por UART y enviando lecturas de temperatura.

## Estructura del proyecto
### Arduino
ArduinoMega/ 
    main.ino 

### ESP8266
ESPHome/ 
    main.yaml 
    myCustomSensor.h

## Funcionalidades principales

- Control de hasta 10 ventiladores (servos) individualmente desde Home Assistant.
- Lectura y publicación de temperatura desde sensor DS18B20.
- Comunicación UART entre ESPHome y Arduino Mega.
- Integración sencilla con Home Assistant usando ESPHome API.

## Instalación

### 1. Arduino Mega

1. Carga el archivo [`main.ino`](ArduinoMega/main.ino) en tu Arduino Mega.
2. Conecta los servos a los pines definidos y el sensor DS18B20 al pin 2.

### 2. ESPHome

1. Copia [`main.yaml`](ESPHome/main.yaml) y [`myCustomSensor.h`](ESPHome/myCustomSensor.h) en tu configuración de ESPHome.
2. Ajusta las credenciales WiFi y claves de Home Assistant en `main.yaml`.
3. Flashea tu dispositivo ESP8266/ESP32 con la configuración de ESPHome.

### 3. Conexión UART

- Conecta el TX del ESP al RX3 del Arduino Mega y el RX del ESP al TX3 del Mega (nivel lógico 3.3V ↔ 5V, usa divisor si es necesario).

## Uso

- Controla los ventiladores y relés desde la interfaz de Home Assistant.
- Visualiza la temperatura exterior reportada por el Arduino Mega.

## Créditos

- Autor: Kevin Nelson Wagner
- Licencia: MIT

---