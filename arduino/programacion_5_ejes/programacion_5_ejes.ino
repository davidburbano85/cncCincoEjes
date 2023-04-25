#include <math.h>
#define dirX 3
#define pulArrastre 2
// #define enaX

#define dirY 5
#define pulAlturaY 4
// #define enaY

#define dirZ 6  //intercambiar pines con el eje B
#define pulZ 7
// #define enaZ

#define dirA 8
#define pulA 9
// #define enaA

#define dirB 11 //intercambiar pines con el eje z
#define pulB 10
// #define enaB

//AQUI NOS DETERMINA LA VELOCIDAD DE CADA MOTOR MOTOR
long intervaloDePulsos = 125;

//AQUI SE DETERMINA CUANTOS PASOS SE REQUIEREN PARA DAR UNA VUELTA
int pulsosPorRevolucion = 800;

int estadoDelProceso = 0;
unsigned int repetirProceso = 0;
unsigned long compararProceso = 0;

//MILIMETROS QUE RECORRE POR VUELTA
long milimetrosPorRevolucionArrastre = 87.96;  //este depende del perimetro de la polea que empuja el alambre

//ESTAS SON LAS VUELTAS DESEADAS PARA HACER UN RECORRIDO
unsigned long vueltasDeseadaspulArrastre = 0;
unsigned long vueltasDeseadaspulAlturaY = 0;
unsigned long vueltasDeseadaspulAlturaZ = 0;
unsigned long vueltasDeseadasRotacionA = 0;
unsigned long vueltasDeseadasPulquiebreB = 0;

//ESTAS SON PARA CREAR RESORTES

float vueltasGeneralesDeseadas = 0;
float recibePasoResorte = 0;
float recibeRadioResorte = 0;

//ESTAS SON PARA LA ESTRUCTURA struct Movimientos
long valorFor = 0;
long valorEje = 0;

char claveFor = "";
char claveEje = "";
char dir = "";

//ESTO ES COMO UN DICCIONARIO
struct Movimientos {
  char claveEje = "";
  long valorEje = 0;
  char dir = "";
};

int grados = 0;
int reduccion = 3;
int pasoTornillo = 5;
int radioHerramienta = 4;

int cantidadMovimientos = 2;
//CREAMOS UNA ITERACION
Movimientos* movimientos = new Movimientos[cantidadMovimientos];

void setup() {
  Serial.begin(9600);
  pinMode(dirX, OUTPUT);
  pinMode(pulArrastre, OUTPUT);
  pinMode(pulAlturaY, OUTPUT);
  pinMode(pulZ, OUTPUT);
  pinMode(pulA, OUTPUT);
  pinMode(pulB, OUTPUT);
  pinMode(dirY, OUTPUT);
  pinMode(dirZ, OUTPUT);
  pinMode(dirB, OUTPUT);
}
void loop() {

  switch (estadoDelProceso) {

    case 0:
      iniciar();
      break;

    case 1:
      escogerTipoMaquinado();
      break;
      //      RESORTES
    case 2:
      ingresarDatosDelSerialResortes();
      estadoDelProceso = 3;
      break;

    case 3:
      radioResorte();
      estadoDelProceso = 4;
      break;

    case 4:
      vueltasApriete();
      estadoDelProceso = 5;
      break;

    case 5:
      darAlturaAlResorte();
      estadoDelProceso = 6;
      break;

    case 6:
      figurarResorte();
      estadoDelProceso = 7;
      break;

    case 7:
      regresarAlturaResorte();
      estadoDelProceso = 8;
      break;

    case 8:
      vueltasApriete();
      estadoDelProceso = 9;
      break;

    case 9:
      repetirResorte();
      break;

    case 10:
      ingresarDatosDelSerialPinesZigZag();
      break;



    case 11:
      crearPinesZigZag();
      estadoDelProceso = 13;
      break;

    case 13:
      repetirPines();
      break;


    case 14:
      joystick();
      estadoDelProceso = 15;
      break;

    case 15:
      ejecutarJoystick();
      break;
  }
}
void iniciar() {
  unsigned char recibir;
  Serial.println("o");
  while (!Serial.available()) {}
  recibir = Serial.parseInt();
  estadoDelProceso = recibir == 1 ? 1 : 0;
}
void escogerTipoMaquinado() {
  unsigned recibir = 0;
  Serial.println("a1");
  while (!Serial.available()) {}
  recibir = Serial.parseInt();
  if (recibir == 1) {
    estadoDelProceso = 2;
  } else if (recibir == 2) {
    estadoDelProceso = 10;
  } else if (recibir == 3) {
    estadoDelProceso = 14;
  } else {
    Serial.println("a2");
    estadoDelProceso = 1;
  }
}

void ingresarDatosDelSerialPinesZigZag() {
  Serial.println("e6");  //cuantas pines desea crear
  while (!Serial.available()) {}
  repetirProceso = Serial.parseInt();

  // Serial.println("e5");  //diametro del radio
  // while (!Serial.available()) {}
  // recibeRadioResorte = Serial.parseInt();

  Serial.println("e1");  //cantidad movimientos solo para el zigzag
  while (!Serial.available()) {}
  cantidadMovimientos = Serial.parseInt();


  for (int i = 0; i < cantidadMovimientos; i++) {


    Serial.println("e2");  //escoger eje para mover
    while (!Serial.available()) {}
    claveEje = Serial.read();

    if (claveEje == 'x') {  //'' de esta manera se escoje un caracter para que si lo compare no es con ""
      valorEje = Serial.parseFloat();
      while (!valorEje) {}

      movimientos[i].claveEje = claveEje;
      movimientos[i].valorEje = valorEje;

      Serial.println("e3");
      while (!Serial.available()) {}
      dir = Serial.read();

    } else if (claveEje == 'y') {  //de esta manera se escoje un caracter para que si lo compare no con ""
      valorEje = Serial.parseFloat();
      while (!valorEje) {}

      movimientos[i].claveEje = claveEje;
      movimientos[i].valorEje = valorEje;

      Serial.println("e3");
      while (!Serial.available()) {}
      dir = Serial.read();
      movimientos[i].dir = dir;


    } else if (claveEje == 'a') {  //de esta manera se escoje un caracter para que si lo compare no con ""
      valorEje = Serial.parseFloat();
      while (!valorEje) {}

      movimientos[i].claveEje = claveEje;
      movimientos[i].valorEje = valorEje;

      Serial.println("e3");  // direccion
      while (!Serial.available()) {}
      dir = Serial.read();
      movimientos[i].dir = dir;


    } else if (claveEje == 'b') {  //ESTE ES PARA EL RADIO
      valorEje = Serial.parseFloat();
      while (!valorEje) {}

      movimientos[i].claveEje = claveEje;
      movimientos[i].valorEje = valorEje;

      Serial.println("e3");  // direccion
      while (!Serial.available()) {}
      dir = Serial.read();
      movimientos[i].dir = dir;


    } else {
      Serial.println("f1");
    }
  }
  estadoDelProceso = 11;
}

void crearPinesZigZag() {

  for (int i = 0; i < cantidadMovimientos; i++) {

    claveFor = movimientos[i].claveEje;

    if (claveFor == 'x') {
      valorFor = movimientos[i].valorEje;
      dir = movimientos[i].dir;

      int finCiclo = valorFor + 1;
      long pulsos = pulsosPorRevolucion * valorFor;
      vueltasDeseadaspulArrastre = (pulsos / milimetrosPorRevolucionArrastre);

      unsigned long tiempoInicioX = micros();
      unsigned long vueltasDadasX = 0;
      while (vueltasDadasX < vueltasDeseadaspulArrastre) {
        unsigned long tiempoActualX = micros();
        if (tiempoActualX - tiempoInicioX >= intervaloDePulsos && vueltasDadasX < vueltasDeseadaspulArrastre) {
          tiempoInicioX += intervaloDePulsos;
          digitalWrite(pulArrastre, !digitalRead(pulArrastre));
          if (digitalRead(pulArrastre)) vueltasDadasX++;
        }

        digitalWrite(dirX, HIGH);
      }
      digitalWrite(pulArrastre, LOW);
    }
    if (claveFor == 'y') {
      valorFor = movimientos[i].valorEje;
      dir = movimientos[i].dir;
      int finCiclo = valorFor + 1;

      if (dir == 'D') {

        digitalWrite(dirY, HIGH);
      } else if (dir == 'I') {
        digitalWrite(dirY, LOW);

      } else {
        Serial.println("f1");
      }
      digitalWrite(dirZ, HIGH);

      vueltasDeseadaspulAlturaZ = pulsosPorRevolucion * 2;
      unsigned long tiempoInicioZ = micros();
      unsigned long vueltasDadasZ = 0;
      while (vueltasDadasZ < vueltasDeseadaspulAlturaZ) {
        unsigned long tiempoActualZ = micros();
        if (tiempoActualZ - tiempoInicioZ >= intervaloDePulsos && vueltasDadasZ < vueltasDeseadaspulAlturaZ) {
          tiempoInicioZ += intervaloDePulsos;
          digitalWrite(pulZ, !digitalRead(pulZ));
          if (digitalRead(pulZ)) vueltasDadasZ++;
        }
      }
      digitalWrite(pulZ, LOW);



      int pulsosConReduccion = pulsosPorRevolucion * reduccion;
      vueltasDeseadaspulAlturaY = (pulsosConReduccion * valorFor / 360);
      unsigned long tiempoInicioY = micros();
      unsigned long vueltasDadasY = 0;
      while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
        unsigned long tiempoActualY = micros();
        if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
          tiempoInicioY += intervaloDePulsos;
          digitalWrite(pulAlturaY, !digitalRead(pulAlturaY));
          if (digitalRead(pulAlturaY)) vueltasDadasY++;
        }
      }
      digitalWrite(dirZ, LOW);


      vueltasDeseadaspulAlturaZ = pulsosPorRevolucion * 2;
      tiempoInicioZ = micros();
      vueltasDadasZ = 0;
      while (vueltasDadasZ < vueltasDeseadaspulAlturaZ) {
        unsigned long tiempoActualZ = micros();
        if (tiempoActualZ - tiempoInicioZ >= intervaloDePulsos && vueltasDadasZ < vueltasDeseadaspulAlturaZ) {
          tiempoInicioZ += intervaloDePulsos;
          digitalWrite(pulZ, !digitalRead(pulZ));
          if (digitalRead(pulZ)) vueltasDadasZ++;
        }
      }
      digitalWrite(pulZ, LOW);

      vueltasDeseadaspulAlturaY = (32);

      tiempoInicioY = micros();
      vueltasDadasY = 0;
      while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
        unsigned long tiempoActualY = micros();
        if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
          tiempoInicioY += intervaloDePulsos;
          digitalWrite(pulAlturaY, !digitalRead(pulAlturaY));
          if (digitalRead(pulAlturaY)) vueltasDadasY++;
        }
      }
    }

    if (claveFor == 'a') {
      valorFor = movimientos[i].valorEje;
      dir = movimientos[i].dir;

      int finCiclo = valorFor + 1;

      if (dir == 'D') {
        digitalWrite(dirA, HIGH);
      } else if (dir == 'I') {
        digitalWrite(dirA, LOW);

      } else {
        Serial.println("f1");
      }
      int pulsosConReduccion = pulsosPorRevolucion * reduccion;
      vueltasDeseadasRotacionA = (pulsosConReduccion * valorFor / 360);

      unsigned long tiempoInicioA = micros();
      unsigned long vueltasDadasA = 0;
      while (vueltasDadasA < vueltasDeseadasRotacionA) {
        unsigned long tiempoActualA = micros();
        if (tiempoActualA - tiempoInicioA >= intervaloDePulsos && vueltasDadasA < vueltasDeseadasRotacionA) {
          tiempoInicioA += intervaloDePulsos;
          digitalWrite(pulA, !digitalRead(pulA));
          if (digitalRead(pulA)) vueltasDadasA++;
        }
      }
      digitalWrite(pulA, LOW);
      digitalWrite(dirA, LOW);
    }
    if (claveFor == 'b') {

      recibeRadioResorte = movimientos[i].valorEje;
      dir = movimientos[i].dir;

      int finCiclo = recibeRadioResorte + 1;

      if (dir == 'D') {
        digitalWrite(dirB, HIGH);
      } else if (dir == 'I') {
        digitalWrite(dirB, LOW);

      } else {
        Serial.println("f1");
      }

      double valorM = 0;  //recordar esto solo para radios entre 15 y 40
      double valorB = 0;  //recordar esto solo para radios entre 15 y 40
      double pasoPorRevolucion = 5;
      //TENER EN CUENTA QUE AUNQEU DICE MOTOR Y EN SI EL QUE DEBE MOVERSE ES EL MOTOR B

      if (recibeRadioResorte > 4 && recibeRadioResorte < 15) {
        valorM = 0.57;  //recordar esto solo para radios entre 15 y 40
        valorB = 136.53;
        double distanciaCentroEjeDesdeCeroPieza = (valorM * recibeRadioResorte + valorB) - 130.8;  //recordar esto solo para radios entre 15 y 40
        double totalRevoluciones = distanciaCentroEjeDesdeCeroPieza / pasoPorRevolucion;
        double pulsosTotales = pulsosPorRevolucion * totalRevoluciones;

        int vueltasDeseadaspulAltura = pulsosTotales;

        unsigned long tiempoInicio = micros();
        unsigned long vueltasDadas = 0;
        while (vueltasDadas < vueltasDeseadaspulAltura) {
          unsigned long tiempoActual = micros();
          if (tiempoActual - tiempoInicio >= intervaloDePulsos && vueltasDadas < vueltasDeseadaspulAltura) {
            tiempoInicio += intervaloDePulsos;
            digitalWrite(pulB, !digitalRead(pulB));
            if (digitalRead(pulB)) vueltasDadas++;
          }
          digitalWrite(dirB, LOW);
        }
        digitalWrite(pulB, LOW);
      }

      if (recibeRadioResorte > 13 && recibeRadioResorte < 41) {
        valorM = 0.35;  //recordar esto solo para radios entre 15 y 40
        valorB = 139.67;
        double distanciaCentroEjeDesdeCeroPieza = (valorM * recibeRadioResorte + valorB) - 130.8;  //recordar esto solo para radios entre 15 y 40
        double totalRevoluciones = distanciaCentroEjeDesdeCeroPieza / pasoPorRevolucion;
        double pulsosTotales = pulsosPorRevolucion * totalRevoluciones;

        vueltasDeseadaspulAlturaY = pulsosTotales;

        unsigned long tiempoInicioY = micros();
        unsigned long vueltasDadasY = 0;
        while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
          unsigned long tiempoActualY = micros();
          if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
            tiempoInicioY += intervaloDePulsos;
            digitalWrite(pulB, !digitalRead(pulB));
            if (digitalRead(pulB)) vueltasDadasY++;
          }
          digitalWrite(dirB, LOW);
        }
        digitalWrite(pulB, LOW);
      }

      if (recibeRadioResorte > 39 && recibeRadioResorte < 81) {
        valorM = 0.24;  //recordar esto solo para radios entre 15 y 40
        valorB = 144.01;
        double distanciaCentroEjeDesdeCeroPieza = (valorM * recibeRadioResorte + valorB) - 130.8;  //recordar esto solo para radios entre 15 y 40
        double totalRevoluciones = distanciaCentroEjeDesdeCeroPieza / pasoPorRevolucion;
        double pulsosTotales = pulsosPorRevolucion * totalRevoluciones;

        vueltasDeseadaspulAlturaY = pulsosTotales;

        unsigned long tiempoInicioY = micros();
        unsigned long vueltasDadasY = 0;
        while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
          unsigned long tiempoActualY = micros();
          if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
            tiempoInicioY += intervaloDePulsos;
            digitalWrite(pulB, !digitalRead(pulB));
            if (digitalRead(pulB)) vueltasDadasY++;
          }
          digitalWrite(dirB, LOW);
        }
        digitalWrite(pulB, LOW);
      }

      if (recibeRadioResorte > 79 && recibeRadioResorte < 149) {
        valorM = 0.18;  //recordar esto solo para radios entre 15 y 40
        valorB = 149;
        double distanciaCentroEjeDesdeCeroPieza = (valorM * recibeRadioResorte + valorB) - 130.8;  //recordar esto solo para radios entre 15 y 40
        double totalRevoluciones = distanciaCentroEjeDesdeCeroPieza / pasoPorRevolucion;
        double pulsosTotales = pulsosPorRevolucion * totalRevoluciones;

        vueltasDeseadaspulAlturaY = pulsosTotales;

        unsigned long tiempoInicioY = micros();
        unsigned long vueltasDadasY = 0;
        while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
          unsigned long tiempoActualY = micros();
          if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
            tiempoInicioY += intervaloDePulsos;
            digitalWrite(pulB, !digitalRead(pulB));
            if (digitalRead(pulB)) vueltasDadasY++;
          }
          digitalWrite(dirB, LOW);
        }
        digitalWrite(pulB, LOW);
      }

      unsigned long tiempoInicioX = micros();
      unsigned long vueltasDadasX = 0;
      double perimetro = recibeRadioResorte * 2 * 3.15;

      vueltasDeseadaspulArrastre = (pulsosPorRevolucion * recibeRadioResorte / milimetrosPorRevolucionArrastre);

      while (vueltasDadasX < vueltasDeseadaspulArrastre) {
        unsigned long tiempoActualXx = micros();
        if (tiempoActualXx - tiempoInicioX >= intervaloDePulsos && vueltasDadasX < vueltasDeseadaspulArrastre) {
          tiempoInicioX += intervaloDePulsos;
          digitalWrite(pulArrastre, !digitalRead(pulArrastre));
          if (digitalRead(pulArrastre)) vueltasDadasX++;
        }
        digitalWrite(dirX, HIGH);
      }
      digitalWrite(pulArrastre, LOW);



      unsigned long tiempoInicioY = micros();
      unsigned long vueltasDadasY = 0;
      vueltasDeseadaspulAlturaY = 115;

      while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
        unsigned long tiempoActualY = micros();
        if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
          tiempoInicioY += intervaloDePulsos;
          digitalWrite(pulAlturaY, !digitalRead(pulAlturaY));
          if (digitalRead(pulAlturaY)) vueltasDadasY++;
        }
      }
      digitalWrite(pulAlturaY, LOW);

      tiempoInicioX = micros();
      vueltasDadasX = 0;

      vueltasDeseadaspulArrastre = (pulsosPorRevolucion * 2 * perimetro / milimetrosPorRevolucionArrastre);

      while (vueltasDadasX < vueltasDeseadaspulArrastre) {
        unsigned long tiempoActualXx = micros();
        if (tiempoActualXx - tiempoInicioX >= intervaloDePulsos && vueltasDadasX < vueltasDeseadaspulArrastre) {
          tiempoInicioX += intervaloDePulsos;
          digitalWrite(pulArrastre, !digitalRead(pulArrastre));
          if (digitalRead(pulArrastre)) vueltasDadasX++;
        }
      }
      digitalWrite(pulArrastre, LOW);
    }
  }
}

void ingresarDatosDelSerialResortes() {
  Serial.println("b1");  //Por favor ingresa el radio del resorte
  while (!Serial.available()) {}
  recibeRadioResorte = Serial.parseFloat();

  Serial.println("b2");  //Por favor ingresa el paso del resorte
  while (!Serial.available()) {}
  recibePasoResorte = Serial.parseFloat();  //este es en milimetros

  Serial.println("b3");  //Por favor ingresa la cantidad de revoluciones del resorte
  while (!Serial.available()) {}
  vueltasGeneralesDeseadas = Serial.parseFloat();

  Serial.println("b4");  //Por favor ingresa la direccion "D" gira a la derecha y "I" gira a la izquierda
  while (!Serial.available()) {}
  dir = Serial.read();

  Serial.println("b5");  //cuantas veces desea repetir el resorte
  while (!Serial.available()) {}
  repetirProceso = Serial.parseInt();
}
void radioResorte() {
  double valorM = 0;  //recordar esto solo para radios entre 15 y 40
  double valorB = 0;  //recordar esto solo para radios entre 15 y 40
  double pasoPorRevolucion = 5;
  //TENER EN CUENTA QUE AUNQEU DICE MOTOR Y EN SI EL QUE DEBE MOVERSE ES EL MOTOR B

  if (recibeRadioResorte > 4 && recibeRadioResorte < 15) {
    valorM = 0.57;  //recordar esto solo para radios entre 15 y 40
    valorB = 136.53;
    double distanciaCentroEjeDesdeCeroPieza = (valorM * recibeRadioResorte + valorB) - 130.8;  //recordar esto solo para radios entre 15 y 40
    double totalRevoluciones = distanciaCentroEjeDesdeCeroPieza / pasoPorRevolucion;
    double pulsosTotales = pulsosPorRevolucion * totalRevoluciones;

    vueltasDeseadaspulAlturaY = pulsosTotales;

    unsigned long tiempoInicioY = micros();
    unsigned long vueltasDadasY = 0;
    while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
      unsigned long tiempoActualY = micros();
      if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
        tiempoInicioY += intervaloDePulsos;
        digitalWrite(pulB, !digitalRead(pulB));
        if (digitalRead(pulB)) vueltasDadasY++;
      }
      digitalWrite(dirB, LOW);
    }
    digitalWrite(pulB, LOW);
  }

  if (recibeRadioResorte > 13 && recibeRadioResorte < 41) {
    valorM = 0.35;  //recordar esto solo para radios entre 15 y 40
    valorB = 139.67;
    double distanciaCentroEjeDesdeCeroPieza = (valorM * recibeRadioResorte + valorB) - 130.8;  //recordar esto solo para radios entre 15 y 40
    double totalRevoluciones = distanciaCentroEjeDesdeCeroPieza / pasoPorRevolucion;
    double pulsosTotales = pulsosPorRevolucion * totalRevoluciones;

    vueltasDeseadaspulAlturaY = pulsosTotales;

    unsigned long tiempoInicioY = micros();
    unsigned long vueltasDadasY = 0;
    while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
      unsigned long tiempoActualY = micros();
      if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
        tiempoInicioY += intervaloDePulsos;
        digitalWrite(pulB, !digitalRead(pulB));
        if (digitalRead(pulB)) vueltasDadasY++;
      }
      digitalWrite(dirB, LOW);
    }
    digitalWrite(pulB, LOW);
  }

  if (recibeRadioResorte > 39 && recibeRadioResorte < 81) {
    valorM = 0.24;  //recordar esto solo para radios entre 15 y 40
    valorB = 144.01;
    double distanciaCentroEjeDesdeCeroPieza = (valorM * recibeRadioResorte + valorB) - 130.8;  //recordar esto solo para radios entre 15 y 40
    double totalRevoluciones = distanciaCentroEjeDesdeCeroPieza / pasoPorRevolucion;
    double pulsosTotales = pulsosPorRevolucion * totalRevoluciones;

    vueltasDeseadaspulAlturaY = pulsosTotales;

    unsigned long tiempoInicioY = micros();
    unsigned long vueltasDadasY = 0;
    while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
      unsigned long tiempoActualY = micros();
      if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
        tiempoInicioY += intervaloDePulsos;
        digitalWrite(pulB, !digitalRead(pulB));
        if (digitalRead(pulB)) vueltasDadasY++;
      }
      digitalWrite(dirB, LOW);
    }
    digitalWrite(pulB, LOW);
  }

  if (recibeRadioResorte > 79 && recibeRadioResorte < 149) {
    valorM = 0.18;  //recordar esto solo para radios entre 15 y 40
    valorB = 149;
    double distanciaCentroEjeDesdeCeroPieza = (valorM * recibeRadioResorte + valorB) - 130.8;  //recordar esto solo para radios entre 15 y 40
    double totalRevoluciones = distanciaCentroEjeDesdeCeroPieza / pasoPorRevolucion;
    double pulsosTotales = pulsosPorRevolucion * totalRevoluciones;

    vueltasDeseadaspulAlturaY = pulsosTotales;

    unsigned long tiempoInicioY = micros();
    unsigned long vueltasDadasY = 0;
    while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
      unsigned long tiempoActualY = micros();
      if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
        tiempoInicioY += intervaloDePulsos;
        digitalWrite(pulB, !digitalRead(pulB));
        if (digitalRead(pulB)) vueltasDadasY++;
      }
      digitalWrite(dirB, LOW);
    }
    digitalWrite(pulB, LOW);
  }
}


void vueltasApriete() {
  unsigned long tiempoInicioX = micros();
  unsigned long vueltasDadasX = 0;
  double perimetro = recibeRadioResorte * 2 * 3.15;

  vueltasDeseadaspulArrastre = (pulsosPorRevolucion * recibeRadioResorte / milimetrosPorRevolucionArrastre);
  digitalWrite(dirX, HIGH);

  while (vueltasDadasX < vueltasDeseadaspulArrastre) {
    unsigned long tiempoActualXx = micros();
    if (tiempoActualXx - tiempoInicioX >= intervaloDePulsos && vueltasDadasX < vueltasDeseadaspulArrastre) {
      tiempoInicioX += intervaloDePulsos;
      digitalWrite(pulArrastre, !digitalRead(pulArrastre));
      if (digitalRead(pulArrastre)) vueltasDadasX++;
    }
  }

  vueltasDeseadaspulAlturaY = 115;

  unsigned long tiempoInicioY = micros();
  unsigned long vueltasDadasY = 0;
  while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
    unsigned long tiempoActualY = micros();
    if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
      tiempoInicioY += intervaloDePulsos;
      digitalWrite(pulAlturaY, !digitalRead(pulAlturaY));
      if (digitalRead(pulAlturaY)) vueltasDadasY++;
    }
  }
  digitalWrite(pulAlturaY, LOW);

  tiempoInicioX = micros();
  vueltasDadasX = 0;

  vueltasDeseadaspulArrastre = (pulsosPorRevolucion * 2 * perimetro / milimetrosPorRevolucionArrastre);
  digitalWrite(dirX, HIGH);
  while (vueltasDadasX < vueltasDeseadaspulArrastre) {
    unsigned long tiempoActualXx = micros();
    if (tiempoActualXx - tiempoInicioX >= intervaloDePulsos && vueltasDadasX < vueltasDeseadaspulArrastre) {
      tiempoInicioX += intervaloDePulsos;
      digitalWrite(pulArrastre, !digitalRead(pulArrastre));
      if (digitalRead(pulArrastre)) vueltasDadasX++;
    }
  }
}

void darAlturaAlResorte() {
  //MOVIMIENTO DE MOTORES
  unsigned long tiempoInicioX = micros();
  unsigned long vueltasDadasX = 0;
  unsigned long tiempoInicioZ = micros();
  unsigned long vueltasDadasZ = 0;
  //  PERIMETRO
  double perimetro = recibeRadioResorte * 2 * 3.15;
  double totalAlambre = perimetro;
  double vueltasMotorPorPerimetro = totalAlambre / milimetrosPorRevolucionArrastre;
  double pulsoPerimetro = pulsosPorRevolucion * vueltasMotorPorPerimetro;
  double tiempoPerimetro = pulsoPerimetro * (4 * intervaloDePulsos) / 1000000;
  //ALTURA
  double avancePorRevolucion = 5;
  double totalVueltasAltura = recibePasoResorte / avancePorRevolucion;
  double pulsosAltura = pulsosPorRevolucion * totalVueltasAltura;
  double tiempoAltura = pulsosAltura * (4 * intervaloDePulsos) / 1000000;
  //PROMEDIANDO
  double promedioPulAltPer = (pulsoPerimetro + pulsosAltura) / 2;
  double promedioTiempo = (tiempoPerimetro + tiempoAltura) / 2;
  //INTERVALOS DE TIEMPO A USAR
  double intervaloPerimetro = ((promedioTiempo * 1000000) / pulsoPerimetro) / 2;
  double intervaloAltura = ((promedioTiempo * 1000000) / pulsosAltura) / 2;

  double x = (vueltasMotorPorPerimetro * pulsosPorRevolucion);
  double a = (totalVueltasAltura * pulsosPorRevolucion);

  tiempoInicioX = micros();
  vueltasDadasX = 0;
  digitalWrite(dirZ, HIGH);
  digitalWrite(dirX, HIGH);
  while (vueltasDadasX < x || vueltasDadasZ < a) {
    unsigned long tiempoActualX = micros();
    if (tiempoActualX - tiempoInicioX >= intervaloPerimetro && vueltasDadasX < x) {
      tiempoInicioX += intervaloPerimetro;
      digitalWrite(pulArrastre, !digitalRead(pulArrastre));
      if (digitalRead(pulArrastre)) vueltasDadasX++;
    }
    unsigned long tiempoActualZ = micros();
    if (tiempoActualZ - tiempoInicioZ >= intervaloAltura && vueltasDadasZ < a) {
      tiempoInicioZ += intervaloAltura;
      digitalWrite(pulZ, !digitalRead(pulZ));
      if (digitalRead(pulZ)) vueltasDadasZ++;
    }
  }
}
void figurarResorte() {
  unsigned long tiempoInicioX = micros();
  unsigned long vueltasDadasX = 0;
  double perimetro = 2 * recibeRadioResorte * 3.15;

  if (vueltasGeneralesDeseadas > 6) {


    vueltasDeseadaspulArrastre = ((pulsosPorRevolucion * perimetro * (vueltasGeneralesDeseadas - 6)) / milimetrosPorRevolucionArrastre);
    digitalWrite(dirX, HIGH);

    while (vueltasDadasX < vueltasDeseadaspulArrastre) {
      unsigned long tiempoActualXx = micros();
      if (tiempoActualXx - tiempoInicioX >= intervaloDePulsos && vueltasDadasX < vueltasDeseadaspulArrastre) {
        tiempoInicioX += intervaloDePulsos;
        digitalWrite(pulArrastre, !digitalRead(pulArrastre));
        if (digitalRead(pulArrastre)) vueltasDadasX++;
      }
    }

    digitalWrite(pulArrastre, LOW);
  }
}
void regresarAlturaResorte() {
  //MOVIMIENTO DE MOTORES
  unsigned long tiempoInicioX = micros();
  unsigned long vueltasDadasX = 0;
  unsigned long tiempoInicioZ = micros();
  unsigned long vueltasDadasZ = 0;
  //  PERIMETRO
  double perimetro = recibeRadioResorte * 2 * 3.15;
  double totalAlambre = perimetro;
  double vueltasMotorPorPerimetro = totalAlambre / milimetrosPorRevolucionArrastre;
  double pulsoPerimetro = pulsosPorRevolucion * vueltasMotorPorPerimetro;
  double tiempoPerimetro = pulsoPerimetro * (4 * intervaloDePulsos) / 1000000;
  //ALTURA
  double avancePorRevolucion = 5;
  double totalVueltasAltura = recibePasoResorte / avancePorRevolucion;
  double pulsosAltura = pulsosPorRevolucion * totalVueltasAltura;
  double tiempoAltura = pulsosAltura * (4 * intervaloDePulsos) / 1000000;
  //PROMEDIANDO
  double promedioPulAltPer = (pulsoPerimetro + pulsosAltura) / 2;
  double promedioTiempo = (tiempoPerimetro + tiempoAltura) / 2;
  //INTERVALOS DE TIEMPO A USAR
  double intervaloPerimetro = ((promedioTiempo * 1000000) / pulsoPerimetro) / 2;
  double intervaloAltura = ((promedioTiempo * 1000000) / pulsosAltura) / 2;

  double x = (vueltasMotorPorPerimetro * pulsosPorRevolucion);
  double a = (totalVueltasAltura * pulsosPorRevolucion);
  digitalWrite(dirZ, LOW);
  digitalWrite(dirX, HIGH);
  while (vueltasDadasX < x || vueltasDadasZ < a) {
    unsigned long tiempoActualX = micros();
    if (tiempoActualX - tiempoInicioX >= intervaloPerimetro && vueltasDadasX < x) {
      tiempoInicioX += intervaloPerimetro;
      digitalWrite(pulArrastre, !digitalRead(pulArrastre));
      if (digitalRead(pulArrastre)) vueltasDadasX++;
    }
    unsigned long tiempoActualZ = micros();
    if (tiempoActualZ - tiempoInicioZ >= intervaloAltura && vueltasDadasZ < a) {
      tiempoInicioZ += intervaloAltura;
      digitalWrite(pulZ, !digitalRead(pulZ));
      if (digitalRead(pulZ)) vueltasDadasZ++;
    }
  }
}

void joystick() {

  Serial.println("g1");
  while (!Serial.available()) {}
  valorEje = Serial.parseInt();
  Serial.println("h1");
  while (!Serial.available()) {}
}
void ejecutarJoystick() {

  int ejeX = 1;
  int ejeY = 1;
  int ejeZ = 1;
  int ejeA = 1;
  int ejeB = 1;



  claveEje = Serial.read();
  if (claveEje == 'r') {
    joystick();
  }

  if (claveEje == 'd') {
    digitalWrite(dirX, !digitalRead(dirX));
    digitalWrite(dirA, !digitalRead(dirA));
    digitalWrite(dirB, !digitalRead(dirB));
    digitalWrite(dirY, !digitalRead(dirY));
    digitalWrite(dirZ, !digitalRead(dirZ));
  }

  if (claveEje == 'x') {

    vueltasDeseadaspulArrastre = ejeX * valorEje;
    unsigned long tiempoInicioX = micros();
    unsigned long vueltasDadasX = 0;
    while (vueltasDadasX < vueltasDeseadaspulArrastre) {
      unsigned long tiempoActualX = micros();
      if (tiempoActualX - tiempoInicioX >= intervaloDePulsos && vueltasDadasX < vueltasDeseadaspulArrastre) {
        tiempoInicioX += intervaloDePulsos;
        digitalWrite(pulArrastre, !digitalRead(pulArrastre));
        if (digitalRead(pulArrastre)) vueltasDadasX++;
      }
    }
    digitalWrite(pulArrastre, LOW);
  }
  if (claveEje == 'y') {

    vueltasDeseadaspulAlturaY = ejeY * valorEje;
    unsigned long tiempoInicioY = micros();
    unsigned long vueltasDadasY = 0;
    while (vueltasDadasY < vueltasDeseadaspulAlturaY) {
      unsigned long tiempoActualY = micros();
      if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
        tiempoInicioY += intervaloDePulsos;
        digitalWrite(pulAlturaY, !digitalRead(pulAlturaY));
        if (digitalRead(pulAlturaY)) vueltasDadasY++;
      }
    }
    digitalWrite(pulAlturaY, LOW);
  }
  if (claveEje == 'z') {

    vueltasDeseadaspulAlturaZ = ejeZ * valorEje;
    unsigned long tiempoInicioZ = micros();
    unsigned long vueltasDadasZ = 0;
    while (vueltasDadasZ < vueltasDeseadaspulAlturaZ) {
      unsigned long tiempoActualZ = micros();
      if (tiempoActualZ - tiempoInicioZ >= intervaloDePulsos && vueltasDadasZ < vueltasDeseadaspulAlturaZ) {
        tiempoInicioZ += intervaloDePulsos;
        digitalWrite(pulZ, !digitalRead(pulZ));
        if (digitalRead(pulZ)) vueltasDadasZ++;
      }
    }
    digitalWrite(pulZ, LOW);
  }
  if (claveEje == 'a') {

    vueltasDeseadasRotacionA = ejeA * valorEje;
    unsigned long tiempoInicioA = micros();
    unsigned long vueltasDadasA = 0;
    while (vueltasDadasA < vueltasDeseadasRotacionA) {
      unsigned long tiempoActualA = micros();
      if (tiempoActualA - tiempoInicioA >= intervaloDePulsos && vueltasDadasA < vueltasDeseadasRotacionA) {
        tiempoInicioA += intervaloDePulsos;
        digitalWrite(pulA, !digitalRead(pulA));
        if (digitalRead(pulA)) vueltasDadasA++;
      }
    }
    digitalWrite(pulA, LOW);
  }
  if (claveEje == 'b') {

    vueltasDeseadasPulquiebreB = ejeB * valorEje;
    unsigned long tiempoInicioB = micros();
    unsigned long vueltasDadasB = 0;
    while (vueltasDadasB < vueltasDeseadasPulquiebreB) {
      unsigned long tiempoActualB = micros();
      if (tiempoActualB - tiempoInicioB >= intervaloDePulsos && vueltasDadasB < vueltasDeseadasPulquiebreB) {
        tiempoInicioB += intervaloDePulsos;
        digitalWrite(pulB, !digitalRead(pulB));
        if (digitalRead(pulB)) vueltasDadasB++;
      }
    }
    digitalWrite(pulB, LOW);
  }
}

void repetirResorte() {
  int repetirP = repetirProceso - 1;
  if (repetirP >= compararProceso) {
    estadoDelProceso = 3;
  }
  repetirProceso--;
  if (repetirProceso == 0) {
    estadoDelProceso = 1;
  }
}
void repetirPines() {
  if (repetirProceso > 0) {
    int repetirP = repetirProceso - 1;

    if (repetirP >= compararProceso) {
      estadoDelProceso = 12;
    }
    repetirProceso--;
    if (repetirProceso == 0) {
      estadoDelProceso = 1;
    }
  }
}
