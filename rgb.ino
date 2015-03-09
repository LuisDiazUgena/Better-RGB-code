
int redPin = 6, int greenPin = 5, const int bluePin = 3;

int red_old=0,green_old=0,blue_old=0;

void setup() {
  // Iniciar el puerto serie.
  Serial.begin(9600);
  // Marcamos como salidas los pines utilizados.
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  // Si hay informacion disponible en el puerto serie la utilizamos:
  while (Serial.available() > 0) {

    // busca la siguiente cadena de números enteros valida:
    int red = Serial.parseInt();
    // vuelve a buscar.
    int green = Serial.parseInt();
    // vuelve a buscar:
    int blue = Serial.parseInt();

    // busca el caracter de fin de linea. Indica al programa que se ha terminado de introducir datos.
    if (Serial.read() == '\n') {

      // Con constrain nos aseguramos de que el valor esté en el rango del pwm
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      //Para leds de anodo común utiliza, para rojo, por ejemplo: red = 255 - constrain(red, 0, 255);
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255); 

      comparador(red);
      comparador(green);
      comparador(blue_old);

      // fade the red, green, and blue legs of the LED:
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);

      // print the three numbers in one string as hexadecimal:
      Serial.print(red, HEX);
      Serial.print(green, HEX);
      Serial.println(blue, HEX);
    }
  }
  
  //Almacenamos los datos de color anteriores.
  red_old = red;
  green_old = green;
  blue_old = blue;
}

comparador(int akt_value){

  // -- To Do --
}