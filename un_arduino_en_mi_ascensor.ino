// Configuramos los pines del sensor Trigger y Echo
const int PinTrig = 7;
const int PinEcho = 6;

// Configuramos el pin del rele
const int PinRele = 9;

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
  
  // Comparamos la medida con las distancias de referencia y activamos o apagamos el rele
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
