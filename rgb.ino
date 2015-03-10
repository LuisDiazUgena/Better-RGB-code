
int redPin = 6, greenPin = 5, bluePin = 3;
int delayLed = 10; // Tiempo que pasará entre cada cambio de LED (ms)
int red_old = 0, green_old = 0, blue_old = 0;

void setup() {
  // Iniciar el puerto serie.
  Serial.begin(9600);
  // Marcamos como salidas los pines utilizados.
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.println("¡Listo!");
}

void loop() {

  // Si hay informacion disponible en el puerto serie la utilizamos:
  while (Serial.available() > 0) {

    int red = 0, green = 0, blue = 0;

    // busca la siguiente cadena de números enteros valida:
    red = Serial.parseInt();
    // vuelve a buscar.
    green = Serial.parseInt();
    // vuelve a buscar:
    blue = Serial.parseInt();

    // busca el caracter de fin de linea. Indica al programa que se ha terminado de introducir datos.
    // Si no utilizas el IDE de arduino u otro ide que permita incluir el formato
    // de nueva linea al enviar datos por el monitor serie, elimina el comentario
    // de la linea 37 y comenta la linea 36.

    if (Serial.read() == '\n') {
      //if (Serial.read()=='*'){
      // Con constrain nos aseguramos de que el valor esté en el rango del pwm
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      //Para leds de anodo común utiliza, para rojo, por ejemplo: red = 255 - constrain(red, 0, 255);
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);

      // print the three numbers in one string as hexadecimal:
      Serial.print(red, HEX);
      Serial.print(green, HEX);
      Serial.println(blue, HEX);

      //Modificamos el color del led RGB
      fade(redPin, red, red_old);
      fade(greenPin, green, green_old);
      fade(bluePin, blue, blue_old);

      Serial.println("Color conseguido");
      //Almacenamos los datos de color anteriores.
      red_old = red;
      green_old = green;
      blue_old = blue;
    }
  }
}

void fade(int pin, int newValue, int aktValue) {

  //  Esta funcion se encarga de llevar cada color desde su valor actual hasta el siguiente
  //  Distinguimos dos casos:
  //  1 - El nuevo valor es mayor que el valor actual, por lo que hay que aumentarlo
  //  2 - El nuevo valor es menor que el valor actual, por lo que hay que reducirlo

  if (newValue > aktValue) {
    for (int i = aktValue; i < newValue; i++) {
      analogWrite(pin, i);
      delay(delayLed);
    }
  } else if (newValue < aktValue) {
    for (int i = aktValue; i > newValue; i--) {
      analogWrite(pin, i);
      delay(delayLed);
    }
  }
}