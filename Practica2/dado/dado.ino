
// Declaración de LEDs
int led1 = 1;
int led3 = 3;
int led4 = 4;
int led5 = 5;
int led6 = 6;
int led7 = 7;
int led8 = 8;

int num;

/* Declaración de los pines y la interrupción correspondiente al pin número 2.
Inicialización de la semilla para números aleatorios.*/

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led3, OUTPUT);
  attachInterrupt(0,probarDado,FALLING);
  randomSeed(analogRead(0));
  
}

/* Función "loop" vacía, pues no se precisa de ningún ciclo en este software. Toda la funcionalidad del programa se lleva a cabo mediante interrupciones. */
void loop() {}


/*Función que genera 200 tiradas aleatorias y guarda en un contador la frecuencia con la que ha salido cada número.
A continuación saca todo por el puerto serie.*/

void probarDado(){
  int i, uno=0, dos=0, tres=0, cuatro=0, cinco=0, seis=0;
  for(i = 0;i<200;i++){
    num = random(1,7); 
    //delay(10000);
    switch(num){
      case 1: uno++; break;
      case 2: dos++; break;
      case 3: tres++; break;
      case 4: cuatro++; break;
      case 5: cinco++; break;
      case 6: seis++; break;     
    }
  }
    Serial.begin(9600);
    Serial.println(uno);
    Serial.println(dos);
    Serial.println(tres);
    Serial.println(cuatro);
    Serial.println(cinco);
    Serial.println(seis);
    Serial.end();
  
  
}

/* Función para realizar una tirada y muestra el valor de la operación por el puerto serie. */

void lanzarDado(){
  int i;
  for(i = 0;i<20;i++){
    num = random(1,7); 
    mostrarNumero(num);
    delay(10000);
  }
  Serial.begin(9600);
  Serial.println(num);
  Serial.end();
}


/* Función que muestra un número "n" pasado por parámetro encendiendo los leds correspondientes. */

void mostrarNumero(int n){
    digitalWrite(led1,LOW); 
    digitalWrite(led8,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);
    digitalWrite(led6,LOW);
    digitalWrite(led7,LOW);
  switch(n){
    case 1: digitalWrite(led8,HIGH);break;
    case 2: digitalWrite(led4,HIGH);digitalWrite(led5,HIGH);break;
    case 3: digitalWrite(led4,HIGH);digitalWrite(led5,HIGH);digitalWrite(led8,HIGH);break;
    case 4: digitalWrite(led4,HIGH);digitalWrite(led5,HIGH);digitalWrite(led7,HIGH);digitalWrite(led1,HIGH);break;
    case 5: digitalWrite(led4,HIGH);digitalWrite(led5,HIGH);digitalWrite(led7,HIGH);digitalWrite(led1,HIGH);digitalWrite(led8,HIGH);break;
    case 6:digitalWrite(led1,HIGH);digitalWrite(led3,HIGH);digitalWrite(led4,HIGH);digitalWrite(led5,HIGH);digitalWrite(led6,HIGH);digitalWrite(led7,HIGH);break;
  }
}

/*Función para generar un número determinado de tiradas de dado. */

void lanzar(int veces){
  int i;  
    for(i = 0;i<veces;i++) 
      lanzarDado(); 
}
