#include <NewPing.h>
#include <Servo.h>
#include <LiquidCrystal.h>



Servo servoBarreraEntrada;
Servo servoBarreraSalida;
Servo servoAscensorEntrada;
Servo servoAscensorSalida;
int libreArriba = 6;
int libreAbajo = 6;
const int anguloMaximoServo = 123;
const int TRIGGER_PIN = 2;
const int ECHO_PIN = 3;
const int distanciamax = 20;
const int pinBarreraEntrada = 4;
const int pinBarreraSalida = 13;
const int distanciamin = 10;
const int pinBotonBarreraSalida = 10;
int ascensorEntrada = 0;
int ascensorSalida = 1;
const int pinBotonAscensorEntradaAbajo = 12;
const int pinAscensorEntradaAbajo = A1;
const int pinBotonAscensorSalidaArriba = A2;
const int pinAscensorSalidaArriba = A3;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, distanciamax);




const int rs = 11, en = 9, d4 = 8, d5 = 7, d6 = 6, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  Serial.begin(9600);
  servoBarreraEntrada.attach(pinBarreraEntrada);
  servoBarreraEntrada.write(0);
  servoBarreraSalida.attach(pinBarreraSalida);
  servoBarreraSalida.write(180);
  pinMode(pinBotonAscensorEntradaAbajo, INPUT);
  pinMode(pinBotonBarreraSalida, INPUT);
  pinMode(pinBotonAscensorEntradaAbajo, INPUT);
  pinMode(pinBotonAscensorSalidaArriba, INPUT);
  servoAscensorEntrada.attach(pinAscensorEntradaAbajo);
  servoAscensorEntrada.write(0);
  servoAscensorSalida.attach(pinAscensorSalidaArriba);
  servoAscensorSalida.write(105);
  //LCD
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Plazas arriba: " + String(libreArriba));
  lcd.setCursor(0,1);
  lcd.print("Plazas abajo: " + String(libreAbajo));
}
void actualizarlcd(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Plazas arriba: " + String(libreArriba));
  lcd.setCursor(0,1);
  lcd.print("Plazas abajo: " + String(libreAbajo));
}
void loop() {
  unsigned int distanciaActual = sonar.ping_cm();
  if (distanciaActual < 10 && distanciaActual > 0) {
    Serial.println("Subiendo barrera de entrada");
    Serial.println(distanciaActual);
    servoBarreraEntrada.write(90);
    while (distanciaActual < 10 && distanciaActual > 0){
      delay(100);
      distanciaActual = sonar.ping_cm();
      Serial.println(distanciaActual);
          Serial.println("while");
    }
    Serial.println(distanciaActual);
    delay(1000);
    servoBarreraEntrada.write(0);
    libreAbajo--;
    Serial.println("Restando");
    actualizarlcd();
  }
  if (digitalRead(pinBotonBarreraSalida) == HIGH) {
    while (digitalRead(pinBarreraSalida) == HIGH) {}
    delay(25);
    Serial.println("Subiendo barrera de salida");
    servoBarreraSalida.write(80);
    delay(2000);
    servoBarreraSalida.write(180);
    libreAbajo++;
    actualizarlcd();
  }




  //-------------------------------ASCENSORES------------------------
  if (digitalRead(pinBotonAscensorEntradaAbajo) == HIGH) {
      Serial.println("Botón ascensor entrada accionado");








    if (ascensorEntrada == 0){
      while (digitalRead(pinBotonAscensorEntradaAbajo) == HIGH) {}
      Serial.println("Botón ascensor entrada accionado");
      delay(25);
      for (int i = 0; i < anguloMaximoServo; i++) {
        servoAscensorEntrada.write(i);
        delay(25);
      }
      ascensorEntrada = 1;
      Serial.println("Subiendo ascensor de entrada");
      Serial.println(ascensorEntrada);
      libreAbajo++;
      libreArriba--;
      actualizarlcd();
    } else{
        while (digitalRead(pinBotonAscensorEntradaAbajo) == HIGH) {}
        Serial.println("Botón ascensor entrada accionado");
        delay(25);
        for (int i = anguloMaximoServo; i > 0; i--) {
        servoAscensorEntrada.write(i);
        delay(25);
        }
        ascensorEntrada = 0;
    }
  }
  if (digitalRead(pinBotonAscensorSalidaArriba) == HIGH) {
    if (ascensorSalida == 1){
      while (digitalRead(pinBotonAscensorSalidaArriba) == HIGH) {}
      Serial.println("Boton de ascensor salida activado");
      delay(25);
      for (int i = anguloMaximoServo; i > 0; i--) {
      servoAscensorSalida.write(i);
      delay(25);
      }
      ascensorSalida = 0;
      libreAbajo--;
      libreArriba++;
      actualizarlcd();
    } else{
        while (digitalRead(pinBotonAscensorSalidaArriba) == HIGH) {}
        delay(25);
        for (int i = 0; i < 105; i++) {
        servoAscensorSalida.write(i);
        delay(25);
        }
        ascensorSalida = 1;
      }
  }
}

