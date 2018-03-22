# Un Arduino en mi ascensor
Vivo en un edificio antiguo con un garage al nivel del mar. ¿Y que es lo que pasa? Típico. Se nos inunda el foso del ascensor. 
Llevamos años aplicando diferentes soluciones. Pero el ambiente de humedad, grasa y salitre las deja fuera de juego en pocas semanas. He fracasado con soluciones de un interruptor-boya flotante para bomba de achique o un microcontrolador con sensores de nivel por resistividad.
Ahora creo que la clave está en probar con sensores que no estén en contacto con un agua salada, aceitosa y con más de una incívica colilla blotando. 

En 2018 tenemos una tecnología _open hardware_ y unos precios _AliExpress_ que nos permiten montar un detector por ultrasonidos y un controlador de motor por menos de 50€. 

## Medición por ultrasonidos
La pieza clave de este montaje es el sensor ultrasonidos HC-SR04:

![un_arduino_en_mi_ascensor](https://github.com/McOrts/un_arduino_en_mi_ascensor/blob/master/HC-SR04.jpg?raw=true)

Este sensor de ultrasonidos tiene el mismo principio de funcionamiento que el sonar de un submarino y consiste en enviar ultrasónicos. Que son sonidos por encima del rango autidivo. Estas ondas enviadas por un emisor revotan en los objetos y son recibidos por un receptor. Con esto tendríamos a cuánto tiempo esta el objeto, sí, habéis leído bien, estamos calculando el tiempo. Gracias a este tiempo y a la velocidad a la que viaja el sonido, 340 m/s, podemos calcular a que distancia se encuentra el objeto detectado gracias a la fórmula más que conocida por todos nosotros V = S / T. Si despejamos el espacio, S = V x T, es muy sencillo calcular la distancia a la que se encuentra el objeto y, precisamente, el sensor HC-SR04 nos proporciona las herramientas necesarias para hacer estos cálculos.

Este sensor tiene como dos ojos por donde emite y recibe los ultrasonidos, uno es el Trigger (emisor), que se conectará a un pin digital en modo OUTPUT y por donde emitiremos el ultrasonido, y el otro es el Echo (receptor), que se conecta a un pin digital en modo INPUT y se encargará de detectar o recoger la onda ultrasónica.

## Microcontrolador Arduino Uno
Elegí esta placa porque es un estándar en el mundo Maker y hay infinidad de informarción y recursos para utilizarla. Además se entiende muy bien con mi MacBook.

![un_arduino_en_mi_ascensor](https://github.com/McOrts/un_arduino_en_mi_ascensor/blob/master/ArduinoUno-callouts1.jpeg?raw=true)

## Montaje

La lista completa de materiales que he utilizado:
* [HC-SR04](http://tienda.bricogeek.com/sensores-distancia/741-sensor-de-distancia-por-ultrasonidos-hc-sr04.html?gclid=Cj0KCQjwqM3VBRCwARIsAKcekb3qY7cWrXjUY-CE1J8Xp8oWFxz3HD6KZ_uWyTUAF_bsOsXkzUNLFgcaAgegEALw_wcB) Sensor de ultrasonidos
* [Arduino Uno](http://tienda.bricogeek.com/arduino/305-arduino-uno-0805833349009.html) Microcontrolador
* [rele](https://www.amazon.es/dp/B01H2D2RI0/ref=cm_sw_r_em_api_c_294SAbK736BR8) Módulo de relé de 2 canales con 5V
* [Dupont wires](https://www.amazon.es/dp/B00QV7O052/ref=cm_sw_r_em_api_c_m94SAbDEAVKVB) Cables Dupont
* [Carcasa](https://www.amazon.es/dp/B06XCFGP9N/ref=cm_sw_r_em_api_c_N74SAbJ0VTKXJ) Carcasa fluorescente para Arduino Uno

El código

```
// Configuramos los pines del sensor Trigger y Echo
const int PinTrig = 7;
const int PinEcho = 6;

// Configuramos el pin del rele
const int PinRele = 8;

// Constante velocidad sonido en cm/s
const float VelSon = 34000.0;

// Constantes de operacion
const int NivelMax = 40;
const int NivelMin = 60;
const int TiempoArranque = 6000;

float distancia;

void setup()
{
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
  // Ponemos el pin Trig en modo salida
  pinMode(PinTrig, OUTPUT);
  // Ponemos el pin Echo en modo entrada
  pinMode(PinEcho, INPUT);
  // Ponemos el pin Rele en modo salida y iniciado
  pinMode(PinRele, OUTPUT);
  digitalWrite(PinRele, LOW);
}

void loop()
{
  iniciarTrigger();
  
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(PinEcho, HIGH);
  
  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  distancia = tiempo * 0.000001 * VelSon / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  if (distancia < NivelMax)
  {
    digitalWrite(PinRele, HIGH);
    Serial.println("on");
  }
  if (distancia > NivelMin)
  {
    digitalWrite(PinRele, LOW);
    Serial.println("off");
  }
  delay(500);
}
 
// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
  // Ponemos el Triger en estado bajo y esperamos 2 ms
  digitalWrite(PinTrig, LOW);
  delayMicroseconds(2);
  
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(PinTrig, HIGH);
  delayMicroseconds(10);
  
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(PinTrig, LOW);
}
```
