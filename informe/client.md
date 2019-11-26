# Cliente

## Comunicación cliente - servidor

### Protocolo

Lo primero que decidimos fué que utilizaríamos un protocolo de texto, ya que nos iba a facilitar a la hora de depurar el juego poder revisar qué fué lo que se estuvo mandando.

Optamos por utilizar el formato JSON para representar el _estado_ del juego. Es decir, el servidor le mandaría al cliente una string representando el estado actual del juego en formato JSON, para que este pueda mostrarlo en pantalla.

Para esto investigamos bibliotecas externas que implementen parseo de JSON. Nos encontramos con esta:

> https://github.com/nlohmann/json

Luego de leer la sección de _"design goals"_ de esta biblioteca, decidimos utilizarla por la simplicidad que ofrecía.

Por otro lado, también existía la opción de serializar un JSON a binario si es que estabamos teniendo problemas de performance.

El formato del estado se vería de esta manera:

```JSON
{
  "cars": [
    {
      "angle": <float>,
      "id": <float>,
      "speed": <float>,
      "x": <float>,
      "y": <float>
    }
  ],
  "center": {
    "x": <float>,
    "y": <float>
  },
  "elements": {
    "boost": [
        {"x": <float>, "y": <float>}
    ],
    "health": [
        {"x": <float>, "y": <float>}
    ],
  },
  "user": {
    "crash": <bool>,
    "end": <bool>,
    "lap": <int>,
    "lives": <int>,
    "mud": <bool>,
    "name": <string>,
    "total_laps": <int>
  }
}
```

De esta manera podemos identificar en qué lugar se encuentra cada elemento del lado del servidor y algunos flags que nos resultarían importantes.

Nótese que no hay ningún tipo de información sobre la pista o mapa. Esto es porque, ya que era algo que no va a cambiar durante el juego, decidimos mandarlo al inicio de la partida, junto a otra información sobre el jugador que se está conectando.

Para lograr este primer intercambio de información, decidimos implementar un _"handshake"_ entre el cliente y el servidor.

### Handshake

Como mencionamos previamente, entre el cliente y el servidor hay un primer intercambio de información que permitirá obtener la información necesaria para comenzar la partida.

Cómo funciona este intercambio de información:

```
1. servidor le envía a cliente las partidas disponibles
2. cliente le envía al servidor la partida seleccionada
3. servidor le envía al cliente la información del mapa para esa partida
```

Información de servidor al cliente sobre la partida que eligió tendrá este formato:

```JSON
{
  "curved": [
    {
      "angle": <float>,
      "x": <float>,
      "y": <float>
    }
  ],
  "elements": {
    "boulders": [
      {
        "x": <float>,
        "y": <float>
      }
    ],
    "muds": [
      {
        "x": <float>,
        "y": <float>
      }
    ],
    "oils": [
      {
        "x": <float>,
        "y": <float>
      }
    ]
  },
  "tracks": [
    {
      "angle": <float>,
      "x": <float>,
      "y": <float>
    }
  ]
}
```

### Implementación

Para lograr una implementación desacoplada de las decisiones de diseño definimos ciertas entidades.

__Socket__

Es la clase que implementa el envío de bytes sobre un socket.

__Communication__

Es la entidad que se ocupa de mandar y recibir texto por un el socket.

El socket solo entiende de mandar y recibir bytes. La responsabilidad de esta clase es transformar estos bytes a cadenas de c++.

__Serializers__

Estas son entidades de un nivel superior a _Communication_, ya que son las que se ocupan de transformar cierto tipo de información a cadenas. Para luego poder envíarlas por _Communication_.

Definimos estos serializers:

+ MoveSerializer
+ RacesSerializer
+ StateSerializer
+ TrackSerializer

Cada uno de estos sabe como transformar la información que se le manda a una cadena, y también desde la cadena que representa la información a los datos que se van a poder usar.

__Proxies__

Por último, la capa que corre arriba de todo esto, es la de los proxies.

Estos saben como recopilar la información y a que serializadores llamar, y también como entender la información que los serializadores les proveen.

Tenemos el proxy que va a usar el cliente: __ServerProxy__

Al cual se le va a poder pedir el estado actual del juego, para luego poder renderizarlo. Además, se le va a envíar el tipo de movimiento que el jugador realizó.

Por otro lado, tenemos el __ClientProxy__. Este va a ser usado por el servidor para mandarle el estado del juego y recibir los movimientos de los jugadores.
