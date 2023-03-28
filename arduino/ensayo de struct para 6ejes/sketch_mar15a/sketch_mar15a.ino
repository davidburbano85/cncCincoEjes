float ejeX = 0;
float ejeY = 0;
float ejeZ = 0;
float ejeA = 0;
float ejeB = 0;
char ejeAMover = "";
float valorEje = 0;
int numMovimientos=3;
float movimientos[3] = {};


void setup() {
  Serial.begin(9600);
}
void loop() {

  for (int i = 0; i < 3; i++) {
    

    if (!Serial.available()) {
      Serial.println("ingresela el eje que desea mover X, Y, Z, , B : ");
    }
    while (!Serial.available()) {}
    ejeAMover = Serial.read();
    Serial.println(ejeAMover);

    if (ejeAMover == 'x') {  //de esta manera se escoje un caracter para que si lo compare no con ""
      Serial.println("escogio el ejeX");
      Serial.println("por favor escriba la distancia de el eje" + String(ejeAMover));
      while (!Serial.available()) {}
      valorEje = Serial.parseFloat();
      //Serial.println("escogio: " + float(valorEje) + "mm en el ejeX");
      movimientos[i] = valorEje;
      Serial.print("este es el movimiento numero: ");
      int n=i;
      Serial.println(n+1);
      Serial.print("con una distacia de:");
      Serial.println(movimientos[i]);

    } else if (ejeAMover == 'y') {  //de esta manera se escoje un caracter para que si lo compare no con ""
      Serial.println("escogio el ejeY");
      Serial.println("por favor escriba la distancia de el eje" + String(ejeAMover));
      while (!Serial.available()) {}
      valorEje = Serial.parseFloat();
      //Serial.println("escogio: " + float(valorEje) + "mm en el ejeX");
      movimientos[i] = valorEje;
      Serial.print("este es el movimiento numero: ");
      int n=i;
      Serial.println(n+1);
      Serial.print("con una distacia de:");
      Serial.println(movimientos[i]);

    } else if (ejeAMover == 'z') {  //de esta manera se escoje un caracter para que si lo compare no con ""
      Serial.println("escogio el ejeZ");
      Serial.println("por favor escriba la distancia de el eje" + String(ejeAMover));
      while (!Serial.available()) {}
      valorEje = Serial.parseFloat();
      //Serial.println("escogio: " + float(valorEje) + "mm en el ejeX");
      movimientos[i] = valorEje;
      Serial.print("este es el movimiento numero: ");
      int n=i;
      Serial.println(n+1);
      Serial.print("con una distacia de:");
      Serial.println(movimientos[i]);
      
    } 
    
    
    
    
    else {
      Serial.println("ese eje no existe");
    }
  }
  Serial.println("se acabo ciclo for");




  // movimiento[0] = valorEje;
  // movimiento[1] = valorEje;
  // movimiento[2] = valorEje;
  // movimiento[3] = valorEje;
  // movimiento[4] = valorEje;
}