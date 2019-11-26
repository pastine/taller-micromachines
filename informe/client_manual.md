## Iniciar la aplicación

Luego de haber corrido las dependencias y compilado los archivos necesarios, se va a poder inciar la aplicación del cliente de esta manera:

```bash
./client <host> <puerto>
```

Luego de haber puesto el input correcto (y que el servidor este corriendo en el host y puerto especificados) se levantará la sigueinte ventana:

![](pantalla_1_cliente.png)

Aquí vamos a poder especificar el nombre que queremos usar y si quisieramos usar un bot, podríamos elegir el tipo de bot.

Luego de esto, vamos a crear la partida para comenzar una nueva partida.

El número default de jugadores es 4, pero puede ser cambiado. La partida no va a empezar hasta que esten conectados todos los jugadores.

Por otro lado, si quisieramos unirnos a una partida, nos van a aparecer las partidas disponibles para unirnos:

![](pantalla_2_cliente.png)

---

## Instrucciones de Juego

### Movimientos

Una vez dentro del juego, vamos a poder comenzar a mover el auto. Hay tres formas diferentes de lograr moverlo.

1. Avanzar

    Para lograr avanzar vamos a poder tocar la tecla W o bién la flecha "arriba".

2. Doblar

    Para doblar vamos a usar A (izquierda) o D (derecha), o bién las flechas de la izquierda o derecha. 

3. Frenar y Reversa

    Utilizando la tecla S vamos a poder frenar el auto, pero si se mantiene suficiente tiempo apretada va a comenzar a ir en reversa. Otra tecla posible será la flecha de abajo.


El jugador va a comenzar con tres vidas totales que se irán reduciendo en el evento de que el auto choque contra otro auto, los límites de la pista o las piedras.

### Obstáculos

Durante la carrera, el jugador va a encontrarse con ciertos obstáculos en la pista, estos van a afectar de maneras distintas al jugador.

#### Piedras

Al chocar con una piedra, el jugador va a perder una vida y ocurrirá una explosión.

Además, la piedra es un objeto sólido, por lo tanto el jugador no va a poder atravesarla y deberá maniobrar alrededor de la misma

#### Barro

Cuándo el jugador pase por encima del barro, se le va a reducir la visibilidad por un tiempo.

#### Aceite

Cuándo el jugador pase por encima del aceite, se le va a reducir el agarre al auto, por lo que le va a dificultar doblar.

### Consumibles

Durante la carrera, el jugador va a poder agarrar consumibles que tendrán distintos efectos.


#### Boost

Luego de agarrar un boost, se le va a dar un golpe de aceleración al auto del jugador, lo que lo llevará a ir más rápido por un tiempo.

#### Vida

Luego de pasar por una vida, se va a consumir. Si el jugador no tenía su vida al máximo, esta se le repondrá por una unidad.

### Vueltas

Para terminar la carrera el jugador va a tener que cumplir con el número de vueltas especificado en la pantalla.

Para completar una vuelta, el jugador va a tener que pasar por todas las curvas de la pista. Si se pierde una curva, no se le contará la vuelta como tal.

Luego de terminar las vueltas, se le va a indicar al jugador en que posición quedó.

### Sonidos

Por default los sonidos del juego van a escucharse, pero si se quiere puede presionar la tecla `m` para apagarlos.