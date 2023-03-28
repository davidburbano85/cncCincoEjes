//EJE DE ROTACION
#define dirRot 3
#define pulRot 2

//EJE DE ARRASTE DE ALAMBRE
#define pulAv 5
#define dirAv 6



//EJE DIAMETRAL
#define dirDia 4
#define pulDia 7


//EJE ARTICULACION BRAZO
#define dirBra 8
#define pulBra 9

//EJE DE PASO DE RESORTE
#define dirPas 10
#define pulPas 11

// INTERVALO DE TIEMPO
long intervalPulRot = 800;  // en microsegundos
long intervaloPulAv = 800;  // En microsegunndos
long intervalPulDia = 800;  // en microsegundos
long intervaloPulBra = 800;  // En microsegunndos
long intervalPulPas = 800;  // en microsegundos



//PASO POR REVOLUCION DE CADA MOTOR
int pasosPorRevPulRot = 800;
int pasosPorRevPulAv = 800;
int pasosPorRevPulDia = 800;
int pasosPorRevPulBra= 800;
int pasosPorRevPulPas= 800;

int estadoDelProceso = 0;
int repetir = 0;

//--------DATOS USUARIO---------
unsigned long nvR = 0;
unsigned long nvAv = 0;
unsigned long nvDia = 0;
unsigned long nvBra = 0;
unsigned long nvPas= 0;

//-------------LAS VUELTAS DESEADAS DE CADA MOTOR------------------

unsigned long vueltasDeseadasPulRot = 0;  // pasosPorRevPulRot * nvR;
unsigned long vueltasDeseadasPulAv = 0;   // pasosPorRevPulAv * nvAv;
unsigned long vueltasDeseadasPulDia = 0;   // pasosPorRevPulAv * nvAv;
unsigned long vueltasDeseadasPulBra = 0;   // pasosPorRevPulAv * nvAv;
unsigned long vueltasDeseadasPulpas = 0;   // pasosPorRevPulAv * nvAv;


//----------------PREGUNTAS AL USUARIO----------------------------
String msg1 =" ";
String msg2 ="";
String msg3 ="";
String msg6 = "";
String msg7 = "";
String msg8 = "";
String msg9 = "";
String msg10 = "";
String msg11 = "";
String msg12 = "";
String msg13 = "";
String msg14 = "";
String msg15 = "";

String msg5 = "si desea otro resorte marque 1 de lo contrario marque 0";


String msg4 = "cuantos resortes desea repetir?";
String msg5 = "si desea otro resorte marque 1 de lo contrario marque 0";





String reset = "";
String dir = "";

void setup() {
  Serial.begin(9600);

  pinMode(pulRot, OUTPUT);
  pinMode(dirRot, OUTPUT);


  pinMode(pulAv, OUTPUT);
  pinMode(dirAv, OUTPUT);
}

void loop() {

  switch (estadoDelProceso) {
    case 0:
      iniciar();
      break;

    case 1:
      cargarDatosDesdeSerial();
      estadoDelProceso = nvAv > 0 && nvR > 0 && dir != "" ? 2 : 1;
      //validar datos o si no mandar respuesta
      //Serial.print(String(estadoDelProceso) + " esto es el 1");
      break;

    case 2:
      realizarCalculos();
      estadoDelProceso = 3;

    case 3:
      String datos = "Los datos cargados son: paso del resorte: " + String(nvAv) + " numero de vueltas " + String(nvR);
      String datos2 = "direccion del resorte " + String(dir) + " la cantidad de resortes: "
                      + String(repetir) + "  y el estado es: " + String(estadoDelProceso);

      Serial.println(datos);
      Serial.println(datos2);
      calculosVueltasInicioFin();
      estadoDelProceso = 4;

    case 4:
      encenderMotores();
      estadoDelProceso = 5;

    case 5:
      calculosVueltasInicioFin();
      estadoDelProceso = 6;

    case 6:
      desajusteResorte();
      estadoDelProceso = 7;

    case 7:
      regresoAvance();
      estadoDelProceso = 8;

    case 8:
      repiteResorte();
      estadoDelProceso = 9;

    case 9:
      volverACero();
  }
}

void iniciar() {
  unsigned char recibir;

  Serial.println("conectando... presione 1 para continuar");
  while (Serial.available() <= 0) {}

  estadoDelProceso = Serial.available() == 1 ? 1 : 0;
  recibir = Serial.read();
  //Serial.println("El estado del proceso es :  " + String(estadoDelProceso) + " lo que recibio de pytohn es: " + char(recibir));
}

void cargarDatosDesdeSerial() {
  // ********DATOS PARA MOTOR DE ROTACION************ //
  Serial.println(msg1);
  while (Serial.available() <= 0) {}
  nvR = Serial.parseFloat();

  Serial.println(msg2);
  while (Serial.available() <= 0) {}
  dir = Serial.readString();


  // ********DATOS PARA MOTOR DE AVANCE***********//

  Serial.println(msg3);
  while (Serial.available() <= 0) {}
  nvAv = Serial.parseFloat();

  // ************DATOS PARA REPETIR RESORTES******//
  Serial.println(msg4);
  while (Serial.available() <= 0) {}
  repetir = Serial.parseInt();
}

void realizarCalculos() {
  vueltasDeseadasPulRot = pasosPorRevPulRot * (nvR - 4);
  vueltasDeseadasPulAv = pasosPorRevPulAv * (nvAv - 4);
}
void regresoAvance() {
  vueltasDeseadasPulAv = pasosPorRevPulAv * (nvAv - 4);
  unsigned long tiempoInicio2 = micros();
  unsigned long vueltasDadasAvance = 0;


  while (vueltasDadasAvance < vueltasDeseadasPulAv) {
    unsigned long tiempoActual = micros();

    if (tiempoActual - tiempoInicio2 >= intervaloPulAv && vueltasDadasAvance < vueltasDeseadasPulAv) {
      tiempoInicio2 += intervaloPulAv;
      digitalWrite(pulAv, !digitalRead(pulAv));
      if (digitalRead(pulAv)) vueltasDadasAvance++;
      digitalWrite(dirAv, HIGH);
    }
  }
  digitalWrite(pulAv, LOW);
}

void encenderMotores() {
  unsigned long tiempoInicio1 = micros();
  unsigned long tiempoInicio2 = micros();
  unsigned long vueltasDadasRotor = 0;
  unsigned long vueltasDadasAvance = 0;

  while (vueltasDadasRotor < vueltasDeseadasPulRot || vueltasDadasAvance < vueltasDeseadasPulAv) {
    unsigned long tiempoActual = micros();
    if (tiempoActual - tiempoInicio1 >= intervalPulRot && vueltasDadasRotor < vueltasDeseadasPulRot) {
      tiempoInicio1 += intervalPulRot;
      digitalWrite(pulRot, !digitalRead(pulRot));
      if (digitalRead(pulRot)) vueltasDadasRotor++;
    }
    if (tiempoActual - tiempoInicio2 >= intervaloPulAv && vueltasDadasAvance < vueltasDeseadasPulAv) {
      tiempoInicio2 += intervaloPulAv;
      digitalWrite(pulAv, !digitalRead(pulAv));
      digitalWrite(dirAv, LOW);
      if (digitalRead(pulAv)) vueltasDadasAvance++;



      if (dir == "D") {
        digitalWrite(dirRot, HIGH);
      }
      if (dir == "I") {
        digitalWrite(dirRot, LOW);
      }
    }
  }

  digitalWrite(pulRot, LOW);
  digitalWrite(pulAv, LOW);
}

void repiteResorte() {
  while (true) {
    while (repetir >= 1) {
      Serial.println("presione 1 para continuar con las repeticiones");
      while (Serial.available() == 0) {};
      int recibe = Serial.parseInt();
      if (recibe == 1) {
        calculosVueltasInicioFin();
        encenderMotores();
        calculosVueltasInicioFin();
        desajusteResorte();
        regresoAvance();
        repetir--;
      };
    }
    break;
  }
}

void volverACero() {
  Serial.println(msg5);
  while (Serial.available() == 0) {};
  int reciben = Serial.parseInt();
  if (reciben == 1) {
    estadoDelProceso = 1;
  } else if (reciben == 0) {
    Serial.println("fin del proceso. Fue un gusto trabajar contigo ");
    Serial.println(" ");
  }
}

void calculosVueltasInicioFin() {

  unsigned long vueltasDeseadasPulRot1 = pasosPorRevPulRot * 2;
  unsigned long tiempoInicio3 = micros();
  unsigned long vueltasDadasRotor = 0;

  while (vueltasDadasRotor < vueltasDeseadasPulRot1) {
    unsigned long tiempoActual1 = micros();
    if (tiempoActual1 - tiempoInicio3 >= intervalPulRot && vueltasDadasRotor < vueltasDeseadasPulRot1) {
      tiempoInicio3 += intervalPulRot;
      digitalWrite(pulRot, !digitalRead(pulRot));
      if (digitalRead(pulRot)) vueltasDadasRotor++;
    }

    if (dir == "D") {
      digitalWrite(dirRot, HIGH);
    }
    if (dir == "I") {
      digitalWrite(dirRot, LOW);
    }
  }
}

void desajusteResorte() {

  unsigned long vueltasDeseadasPulRot1 = pasosPorRevPulRot * 2;
  unsigned long tiempoInicio3 = micros();
  unsigned long vueltasDadasRotor = 0;


  while (vueltasDadasRotor < vueltasDeseadasPulRot1) {
    unsigned long tiempoActual1 = micros();
    if (tiempoActual1 - tiempoInicio3 >= intervalPulRot && vueltasDadasRotor < vueltasDeseadasPulRot1) {
      tiempoInicio3 += intervalPulRot;
      digitalWrite(pulRot, !digitalRead(pulRot));
      if (digitalRead(pulRot)) vueltasDadasRotor++;
    }

    if (dir == "D") {
      digitalWrite(dirRot, LOW);
    }
    if (dir == "I") {
      digitalWrite(dirRot, HIGH);
    }
  }
}
