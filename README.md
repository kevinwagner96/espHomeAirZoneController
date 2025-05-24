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

## Diagrama

<img width="572" alt="Image" src="https://private-user-images.githubusercontent.com/23692189/447264373-29025eaa-cb48-4408-acc2-f489d6c3702f.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDgwOTczMDYsIm5iZiI6MTc0ODA5NzAwNiwicGF0aCI6Ii8yMzY5MjE4OS80NDcyNjQzNzMtMjkwMjVlYWEtY2I0OC00NDA4LWFjYzItZjQ4OWQ2YzM3MDJmLnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNTA1MjQlMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjUwNTI0VDE0MzAwNlomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPWU2OWI0MmYwNTk1Nzc2OTZiNjg4MDg4OGFmOGY5YjA1YWU1NGZmMTNlYzZhZTRhYTNiOTAwNWRmNzE2ZWU5MjgmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0In0.iXesPPFsOB7C3l9SmDBk-JK1rhEyZrXOEmG1kofDM70" style="max-width: 100%;">

## Créditos

- Autor: Kevin Nelson Wagner
- Licencia: MIT

---