# Un Arduino en mi ascensor
Un edificio antiguo y un garage al nivel del mar es lo que tiene. Que se inunda. 
Llevamos años con el problema de agua en el foso del ascensor. Como es de imaginar, este es un ambiente hostil para la electrónica y la mecánica. Lo que me ha llevado a fracasar con soluciones como la de colocar de mil maneras el nterruptor flotante de una bomba de achique o un microcontrolador con sensores de nivel por resistividad.
La clave es no utilizar un sensor que esté en contacto con un agua salada, con aceites y más de una incívica colilla. 

En 2018 tenemos una tecnología _open hardware_ y unos precios _AliExpress_ que nos permiten montar un detector por ultrasonidos y un controlador de motor por unos 50€.

## Medición por ultrasonidos
La pieza clave de este montaje es el sensor ultrasonidos HC-SR04
Un sensor de ultrasonidos funciona como un sonar de un submarino y consiste en enviar sonidos ultrasónicos, sonidos por encima del espectro autidivo, a través de un emisor que revotan en los objetos y son recibidos por un receptor. Con esto tendríamos a cuánto tiempo esta el objeto, sí, habéis leído bien, estamos calculando el tiempo. Gracias a este tiempo y a la velocidad a la que viaja el sonido, 340 m/s, podemos calcular a que distancia se encuentra el objeto detectado gracias a la fórmula más que conocida por todos nosotros V = S / T. Si despejamos el espacio, S = V x T, es muy sencillo calcular la distancia a la que se encuentra el objeto y, precisamente, el sensor HC-SR04 nos proporciona las herramientas necesarias para hacer estos cálculos.

Este sensor tiene como dos ojos por donde emite y recibe los ultrasonidos, uno es el Trigger (emisor), que se conectará a un pin digital en modo OUTPUT y por donde emitiremos el ultrasonido, y el otro es el Echo (receptor), que se conecta a un pin digital en modo INPUT y se encargará de detectar o recoger la onda ultrasónica.
