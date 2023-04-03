#define dirX 3
#define pulArrastre 2
// #define enaX

#define dirY 4
#define pulAlturaY 5
// #define enaY

#define dirZ 6
#define pulZ 13
// #define enaZ

#define dirA 8
#define pulA 9
// #define enaA

#define dirB 10
#define pulB 11
// #define enaB

//AQUI NOS DETERMINA LA VELOCIDAD DE CADA MOTOR MOTOR
long intervaloDePulsos = 125;

//AQUI SE DETERMINA CUANTOS PASOS SE REQUIEREN PARA DAR UNA VUELTA
int pasosPorRevolucion = 800;

int estadoDelProceso = 0;
int tipoMaquinado = 0;

//MILIMETROS QUE RECORRE POR VUELTA
long milimetrosPorRevolucionArrastre = 87.96;  //este depende del perimetro de la polea que empuja el alambre
float milimetrosPorRevolucionAlturaY = 0;
float alambreTotalRequeridoPorResorte = 0;

//ESTAS SON LAS VUELTAS DESEADAS PARA HACER UN RECORRIDO
unsigned long vueltasDeseadaspulArrastre = 0;
unsigned long vueltasDeseadaspulAlturaY = 0;
unsigned long vueltasDeseadasDiametroZ = 0;
unsigned long vueltasDeseadasRotacionA = 0;
unsigned long vueltasDeseadasPulquiebreB = 0;

//ESTAS SON PARA CREAR RESORTES
float mValor = 0;
float xValor = 0;
float bValor = 0;
unsigned long recibePasoResorte = 0;
unsigned long recibeRadioResorte = 0;

float factorPaso = 0;
float proporcionAlPaso = 0;
float proporcionAlPerimetro = 0;

long distanciaCerodePiezaAEjeDoblador = 0;
float vueltasGeneralesDeseadas = 0;
long totalVueltasMotor = 0;

//ESTAS SON PARA LA ESTRUCTURA struct Movimientos
int valorFor = 0;
int valorEje = 0;

char claveFor = "";
char claveEje = "";
char dir = "";

//ESTO ES COMO UN DICCIONARIO
struct Movimientos {
  char claveEje = "";
  int valorEje = 0;
  char dir = "";
};

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
}
void loop() {

  switch (estadoDelProceso) {

    case 0:
      iniciar();
      break;
    case 1:
      escogerTipoMaquinado();
      break;

    case 2:
      ingresarDatosDelSerialResortes();
      estadoDelProceso = 3;
      break;

    case 3:
      darAlturaAlResorte();
      estadoDelProceso = 4;
      break;

    case 4:
      figurarResorte();
      estadoDelProceso = 1;
      break;
    case 5:
      ingresarDatosDelSerialPines();
      estadoDelProceso = 6;

      break;
    case 6:
      crearPines();
      break;

    case 7:
      joystick();
      estadoDelProceso = 8;
      break;
    case 8:
      ejecutarJoystick();
  }
}
void iniciar() {
  unsigned char recibir;
  Serial.println("concectando... presione 1 para continuar");
  while (!Serial.available()) {}
  recibir = Serial.parseInt();
  estadoDelProceso = recibir == 1 ? 1 : 0;



  // Serial.println("El estado del proceso es :  " + String(estadoDelProceso) + " lo que recibio de pytohn es: " + int(recibir));
}
void escogerTipoMaquinado() {

  Serial.println("el sistema a iniciado correctamente por favor seleccione una de las siguientes opciones: ");
  Serial.println("1 para crear resortes,  2 para crear pines,  3 modo joystick");
  while (!Serial.available()) {}
  unsigned char recibir = Serial.parseInt();
  if (recibir == 1) {
    estadoDelProceso = 2;
  } else if (recibir == 2) {
    estadoDelProceso = 5;
  } else if (recibir == 3) {
    estadoDelProceso = 7;
  } else {
    Serial.println("su peticion es incorrecta vuelva a intentar");
    estadoDelProceso = 1;
  }
}
void ingresarDatosDelSerialPines() {
  Serial.println("ingrese la cantidad de movimientos que realizara");
  while (!Serial.available()) {}
  cantidadMovimientos = Serial.parseInt();
  Serial.print("cantidad movimientos solicitados: ");
  Serial.println(cantidadMovimientos);

  for (int i = 0; i < cantidadMovimientos; i++) {


    Serial.println("ingrese el eje que desea mover y la distancia:  X, Y, Z, A, B : ");
    while (!Serial.available()) {}
    claveEje = Serial.read();

    if (claveEje == 'x') {  //'' de esta manera se escoje un caracter para que si lo compare no es con ""
      valorEje = Serial.parseFloat();
      while (!valorEje) {}

      movimientos[i].claveEje = claveEje;
      movimientos[i].valorEje = valorEje;

    } else if (claveEje == 'y') {  //de esta manera se escoje un caracter para que si lo compare no con ""
      valorEje = Serial.parseFloat();
      while (!valorEje) {}

      movimientos[i].claveEje = claveEje;
      movimientos[i].valorEje = valorEje;

      Serial.println("por favor escriba la direccion de el eje Der:'D', Izq: 'I' ");
      while (!Serial.available()) {}
      dir = Serial.read();
      movimientos[i].dir = dir;
      Serial.println(movimientos[i].dir);


    } else if (claveEje == 'z') {  //de esta manera se escoje un caracter para que si lo compare no con ""
      valorEje = Serial.parseFloat();
      while (!valorEje) {}

      movimientos[i].claveEje = claveEje;
      movimientos[i].valorEje = valorEje;

      Serial.println("por favor escriba la direccion de el eje Der:'D', Izq: 'I' ");
      while (!Serial.available()) {}
      dir = Serial.read();
      movimientos[i].dir = dir;
      Serial.println(movimientos[i].dir);


    } else if (claveEje == 'a') {  //de esta manera se escoje un caracter para que si lo compare no con ""
      valorEje = Serial.parseFloat();
      while (!valorEje) {}

      movimientos[i].claveEje = claveEje;
      movimientos[i].valorEje = valorEje;

      Serial.println("por favor escriba la direccion de el eje Der:'D', Izq: 'I' ");
      while (!Serial.available()) {}
      dir = Serial.read();
      movimientos[i].dir = dir;
      Serial.println(movimientos[i].dir);


    } else if (claveEje == 'b') {  //de esta manera se escoje un caracter para que si lo compare no con ""
      valorEje = Serial.parseFloat();
      while (!valorEje) {}

      movimientos[i].claveEje = claveEje;
      movimientos[i].valorEje = valorEje;

      Serial.println("por favor escriba la direccion de el eje Der:'D', Izq: 'I' ");
      while (!Serial.available()) {}
      dir = Serial.read();
      movimientos[i].dir = dir;
      Serial.println(movimientos[i].dir);


    } else if (claveEje == 'm') {
      Serial.println("escogiste mover ejes en conjunto el eje de empuje");
      Serial.println("y el eje de altura, se moveran con el mismo radio");

      Serial.println("por favor escriba la distancia de el eje" + String(claveEje));
      while (!Serial.available()) {}
      valorEje = Serial.parseFloat();
      movimientos[i].claveEje = claveEje;
      movimientos[i].valorEje = valorEje;
    } else {
      Serial.println("ese eje no existe por favor elija entre: x, y, z, a, b");
    }

    // Serial.println(n + 1);
    // Serial.print("con el eje:");
    // Serial.println(movimientos[i].claveEje);
    // Serial.print("con una distancia de:");
    // Serial.println(movimientos[i].valorEje);
  }
  for (int j = 0; j < cantidadMovimientos; j++) {
    //int J = j;

    Serial.print("esta es la clave: ");
    Serial.println(movimientos[j].claveEje);

    Serial.print("este es el valor: ");
    Serial.println(movimientos[j].valorEje);
  }
}
void crearPines() {

  for (int i = 0; i < cantidadMovimientos; i++) {

    claveFor = movimientos[i].claveEje;

    if (claveFor == 'x') {
      valorFor = movimientos[i].valorEje;
      dir = movimientos[i].dir;
      int finCiclo = valorFor + 1;

      vueltasDeseadaspulArrastre = (pasosPorRevolucion * valorFor);
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
    if (claveFor == 'y') {
      valorFor = movimientos[i].valorEje;
      dir = movimientos[i].dir;
      int finCiclo = valorFor + 1;

      if (dir == 'D') {
        Serial.println("se tomo la direccion derecha en eje Y");
        digitalWrite(dirY, HIGH);
      } else if (dir == 'I') {
        Serial.println("se tomo la direccion izquierda en eje Y");
        digitalWrite(dirY, LOW);

      } else {
        Serial.println("esa direccion no es valida");
      }

      vueltasDeseadaspulAlturaY = (pasosPorRevolucion * valorFor);
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
      digitalWrite(dirY, LOW);
    }
    if (claveFor == 'z') {
      valorFor = movimientos[i].valorEje;
      dir = movimientos[i].dir;

      int finCiclo = valorFor + 1;

      if (dir == 'D') {
        Serial.println("se tomo la direccion derecha en eje Z");
        digitalWrite(dirZ, HIGH);
      } else if (dir == 'I') {
        Serial.println("se tomo la direccion izquierda en eje Z");
        digitalWrite(dirZ, LOW);

      } else {
        Serial.println("esa direccion no es valida");
      }


      vueltasDeseadasDiametroZ = (pasosPorRevolucion * valorFor);
      unsigned long tiempoInicioZ = micros();
      unsigned long vueltasDadasZ = 0;
      while (vueltasDadasZ < vueltasDeseadasDiametroZ) {
        unsigned long tiempoActualZ = micros();
        if (tiempoActualZ - tiempoInicioZ >= intervaloDePulsos && vueltasDadasZ < vueltasDeseadasDiametroZ) {
          tiempoInicioZ += intervaloDePulsos;
          digitalWrite(pulZ, !digitalRead(pulZ));
          if (digitalRead(pulZ)) vueltasDadasZ++;
        }
      }
      digitalWrite(pulZ, LOW);
      digitalWrite(dirZ, LOW);
    }
    if (claveFor == 'a') {
      valorFor = movimientos[i].valorEje;
      dir = movimientos[i].dir;

      int finCiclo = valorFor + 1;

      if (dir == 'D') {
        Serial.println("se tomo la direccion derecha en eje A");
        digitalWrite(dirA, HIGH);
      } else if (dir == 'I') {
        Serial.println("se tomo la direccion izquierda en eje A");
        digitalWrite(dirA, LOW);

      } else {
        Serial.println("esa direccion no es valida");
      }

      vueltasDeseadasRotacionA = (pasosPorRevolucion * valorFor);
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
      valorFor = movimientos[i].valorEje;
      dir = movimientos[i].dir;

      int finCiclo = valorFor + 1;

      if (dir == 'D') {
        Serial.println("se tomo la direccion derecha en eje B");
        digitalWrite(dirB, HIGH);
      } else if (dir == 'I') {
        Serial.println("se tomo la direccion izquierda en eje B");
        digitalWrite(dirB, LOW);

      } else {
        Serial.println("esa direccion no es valida");
      }

      vueltasDeseadasPulquiebreB = (pasosPorRevolucion * valorFor);
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
      digitalWrite(dirB, LOW);
    }


    if (claveFor == 'm') {
      Serial.print("seleccionaste ab esto es desde la funcion crear pines");
    }
  }


  estadoDelProceso = 1;
}
void ingresarDatosDelSerialResortes() {
  Serial.println("ingrese el radio del Resorte");
  while (!Serial.available()) {}
  recibeRadioResorte = Serial.parseFloat();

  Serial.println("ingrese el paso del Resorte");
  while (!Serial.available()) {}
  recibePasoResorte = Serial.parseFloat();  //este es en milimetros

  Serial.println("ingrese la cantidad de vueltas del resorte");
  while (!Serial.available()) {}
  vueltasGeneralesDeseadas = Serial.parseFloat();

  Serial.println("Ingrese la direccion del resorte, derecha'D', izquierda 'I' ");
  while (!Serial.available()) {}
  dir = Serial.read();
}
void darAlturaAlResorte() {

  unsigned long tiempoInicioX = micros();
  unsigned long vueltasDadasX = 0;
  unsigned long tiempoInicioY = micros();
  unsigned long vueltasDadasY = 0;
  if (recibeRadioResorte > 14 && recibeRadioResorte < 41) {
    xValor = recibeRadioResorte;
    mValor = 0.35064;
    bValor = 139.669;
    distanciaCerodePiezaAEjeDoblador = (mValor * xValor + bValor) - 130.8;  // distancia desdeel eje del motor al eje doblador
    unsigned long perimetro = 2 * xValor * 3.1416;
    Serial.println("perimetro: " + String(perimetro) + "mm.  y este es el radio: " + String(xValor));
    factorPaso = perimetro / recibePasoResorte;  //esta es la proporcion que hay entre una vuelta del resorte y el paso
    alambreTotalRequeridoPorResorte = perimetro * vueltasGeneralesDeseadas;
    totalVueltasMotor = alambreTotalRequeridoPorResorte / milimetrosPorRevolucionArrastre;

    for (int i = 0; i < recibePasoResorte; i++) {
      int paso = 0;
      if (paso <= i) {
        int I = i + 1;

        proporcionAlPerimetro = factorPaso * I;  //esto es una vuelta
        proporcionAlPaso = I;
        paso++;

        vueltasDeseadaspulArrastre = (pasosPorRevolucion * proporcionAlPerimetro);
        vueltasDeseadaspulAlturaY = (pasosPorRevolucion * proporcionAlPaso);

        // EN TEORIA ESTO SOLO ES PARA LA PRIMER VUELTA
        while (vueltasDadasX < vueltasDeseadaspulArrastre || vueltasDadasY < vueltasDeseadaspulAlturaY) {
          unsigned long tiempoActualX = micros();
          if (tiempoActualX - tiempoInicioX >= intervaloDePulsos && vueltasDadasX < vueltasDeseadaspulArrastre) {
            tiempoInicioX += intervaloDePulsos;
            digitalWrite(pulArrastre, !digitalRead(pulArrastre));
            if (digitalRead(pulArrastre)) vueltasDadasX++;
          }
          unsigned long tiempoActualY = micros();
          if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
            tiempoInicioY += intervaloDePulsos;
            digitalWrite(pulAlturaY, !digitalRead(pulAlturaY));
            if (digitalRead(pulAlturaY)) vueltasDadasY++;
          }
        }
        digitalWrite(dirY, HIGH);
        if (dir == 'D') {
          digitalWrite(dirX, HIGH);
        } else if (dir == 'I') {
          digitalWrite(dirX, LOW);
        } else {
          Serial.println("direccion incorrecta");
        }
      }
      if(dir=='D'){
        Serial.println("girara a la derecha.");
      }else if(dir=='I'){
        Serial.println("girara a la izquierda.");
      }
    }
    digitalWrite(dirX, LOW);
    digitalWrite(dirY, LOW);
    digitalWrite(pulAlturaY, LOW);
    digitalWrite(pulArrastre, LOW);

  } else if (recibeRadioResorte > 39 && recibeRadioResorte < 81) {
    xValor = recibeRadioResorte;
    mValor = 0.35064;
    bValor = 139.669;
    //revisar si el long es viable o toca float
    distanciaCerodePiezaAEjeDoblador = (mValor * xValor + bValor) - 130.8;  // distancia desdeel eje del motor al eje doblador
    unsigned long perimetro = 2 * xValor * 3.1416;
    factorPaso = perimetro / recibePasoResorte;  //esta es la proporcion que hay entre una vuelta del resorte y el paso
    alambreTotalRequeridoPorResorte = perimetro * vueltasGeneralesDeseadas;
    totalVueltasMotor = alambreTotalRequeridoPorResorte / milimetrosPorRevolucionArrastre;


    for (int i = 0; i < recibePasoResorte; i++) {
      int paso = 0;
      if (paso <= i) {
        int I = i + 1;

        proporcionAlPerimetro = factorPaso * I;  //esto es una vuelta
        proporcionAlPaso = I;
        paso++;

        vueltasDeseadaspulArrastre = (pasosPorRevolucion * proporcionAlPerimetro);
        vueltasDeseadaspulAlturaY = (pasosPorRevolucion * proporcionAlPaso);

        // EN TEORIA ESTO SOLO ES PARA LA PRIMER VUELTA
        while (vueltasDadasX < vueltasDeseadaspulArrastre || vueltasDadasY < vueltasDeseadaspulAlturaY) {
          unsigned long tiempoActualX = micros();
          if (tiempoActualX - tiempoInicioX >= intervaloDePulsos && vueltasDadasX < vueltasDeseadaspulArrastre) {
            tiempoInicioX += intervaloDePulsos;
            digitalWrite(pulArrastre, !digitalRead(pulArrastre));
            if (digitalRead(pulArrastre)) vueltasDadasX++;
          }
          unsigned long tiempoActualY = micros();
          if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
            tiempoInicioY += intervaloDePulsos;
            digitalWrite(pulAlturaY, !digitalRead(pulAlturaY));
            if (digitalRead(pulAlturaY)) vueltasDadasY++;
          }
        }
        digitalWrite(dirY, HIGH);
        if (dir == 'D') {
          Serial.println("girara a la derecha");
          digitalWrite(dirX, HIGH);
        } else if (dir == 'I') {
          Serial.println("girara a la izquierda");
          digitalWrite(dirX, LOW);
        } else {
          Serial.println("direccion incorrecta");
        }
      }
    }
    digitalWrite(dirX, LOW);
    digitalWrite(dirY, LOW);
    digitalWrite(pulAlturaY, LOW);
    digitalWrite(pulArrastre, LOW);

  } else if (recibeRadioResorte > 79 && recibeRadioResorte < 151) {
    xValor = recibeRadioResorte;
    mValor = 0.35064;
    bValor = 139.669;
    //revisar si el long es viable o toca float
    distanciaCerodePiezaAEjeDoblador = (mValor * xValor + bValor) - 130.8;  // distancia desdeel eje del motor al eje doblador
    unsigned long perimetro = 2 * xValor * 3.1416;
    factorPaso = perimetro / recibePasoResorte;  //esta es la proporcion que hay entre una vuelta del resorte y el paso
    alambreTotalRequeridoPorResorte = perimetro * vueltasGeneralesDeseadas;
    totalVueltasMotor = alambreTotalRequeridoPorResorte / milimetrosPorRevolucionArrastre;


    for (int i = 0; i < recibePasoResorte; i++) {
      int paso = 0;
      if (paso <= i) {
        int I = i + 1;

        proporcionAlPerimetro = factorPaso * I;  //esto es una vuelta
        proporcionAlPaso = I;
        paso++;

        vueltasDeseadaspulArrastre = (pasosPorRevolucion * proporcionAlPerimetro);
        vueltasDeseadaspulAlturaY = (pasosPorRevolucion * proporcionAlPaso);

        // EN TEORIA ESTO SOLO ES PARA LA PRIMER VUELTA
        while (vueltasDadasX < vueltasDeseadaspulArrastre || vueltasDadasY < vueltasDeseadaspulAlturaY) {
          unsigned long tiempoActualX = micros();
          if (tiempoActualX - tiempoInicioX >= intervaloDePulsos && vueltasDadasX < vueltasDeseadaspulArrastre) {
            tiempoInicioX += intervaloDePulsos;
            digitalWrite(pulArrastre, !digitalRead(pulArrastre));
            if (digitalRead(pulArrastre)) vueltasDadasX++;
          }
          unsigned long tiempoActualY = micros();
          if (tiempoActualY - tiempoInicioY >= intervaloDePulsos && vueltasDadasY < vueltasDeseadaspulAlturaY) {
            tiempoInicioY += intervaloDePulsos;
            digitalWrite(pulAlturaY, !digitalRead(pulAlturaY));
            if (digitalRead(pulAlturaY)) vueltasDadasY++;
          }
        }
        digitalWrite(dirY, HIGH);
        if (dir == 'D') {
          Serial.println("girara a la derecha");
          digitalWrite(dirX, HIGH);
        } else if (dir == 'I') {
          Serial.println("girara a la izquierda");
          digitalWrite(dirX, LOW);
        } else {
          Serial.println("direccion incorrecta");
        }
      }
    }

    digitalWrite(dirX, LOW);
    digitalWrite(dirY, LOW);
    digitalWrite(pulAlturaY, LOW);
    digitalWrite(pulArrastre, LOW);
  }
}
void figurarResorte() {
  unsigned long tiempoInicioX = micros();
  unsigned long vueltasDadasX = 0;

  //ESTO YA ESTA LISTO!!!!!!!!!!!!!!!!!!!1
  vueltasDeseadaspulArrastre = (pasosPorRevolucion * totalVueltasMotor);

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
void joystick() {

  Serial.println("multiplica la velocidad: x1, x10, x100, x1000 ");
  while (!Serial.available()) {}
  valorEje = Serial.parseInt();
}
void ejecutarJoystick() {
  bool direccion = false;

  int ejeX = 1;
  int ejeY = 1;
  int ejeZ = 1;
  int ejeA = 1;
  int ejeB = 1;

  Serial.println("Presione el boton del  eje que desea mover X, Y, Z, A, B ó R para resetear la velocidad");
  while (!Serial.available()) {}
  claveEje = Serial.read();

  if (claveEje == 'x') {

    if (direccion == true) {
      digitalWrite(dirX, HIGH);
    } else if (direccion == false) {
      digitalWrite(dirX, LOW);
    }
    vueltasDeseadaspulArrastre = pasosPorRevolucion * ejeX * valorEje;
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

    if (direccion == true) {
      digitalWrite(dirY, HIGH);
    } else if (direccion == false) {
      digitalWrite(dirY, LOW);
    }

    vueltasDeseadaspulAlturaY = pasosPorRevolucion * ejeY * valorEje;

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

    if (direccion == true) {
      digitalWrite(dirZ, HIGH);
    } else if (direccion == false) {
      digitalWrite(dirZ, LOW);
    }

    vueltasDeseadasDiametroZ = pasosPorRevolucion * ejeZ * valorEje;

    unsigned long tiempoInicioZ = micros();
    unsigned long vueltasDadasZ = 0;
    while (vueltasDadasZ < vueltasDeseadasDiametroZ) {
      unsigned long tiempoActualZ = micros();
      if (tiempoActualZ - tiempoInicioZ >= intervaloDePulsos && vueltasDadasZ < vueltasDeseadasDiametroZ) {
        tiempoInicioZ += intervaloDePulsos;
        digitalWrite(pulZ, !digitalRead(pulZ));
        if (digitalRead(pulZ)) vueltasDadasZ++;
      }
    }
    digitalWrite(pulZ, LOW);
  }
  if (claveEje == 'a') {

    if (direccion == true) {
      digitalWrite(dirA, HIGH);
    } else if (direccion == false) {
      digitalWrite(dirA, LOW);
    }

    vueltasDeseadasRotacionA = pasosPorRevolucion * ejeA * valorEje;

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

    if (direccion == true) {
      digitalWrite(dirB, HIGH);
    } else if (direccion == false) {
      digitalWrite(dirB, LOW);
    }

    vueltasDeseadasPulquiebreB = pasosPorRevolucion * ejeB * valorEje;

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
  if (claveEje == 'r') {
    joystick();
  }
}
