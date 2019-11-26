# Server

## Inicialización

Para inicializar el server:

```
$ ./server servicio archivo_config.txt
```

El archivo de configuración deberá contener un JSON con la disposición de la pista. La pista está compuesta por tiles cuadradas y triángulos isósceles. Las claves del JSON son "curved", "straight" y "curved_center".

EJ:

```JSON
{
  "curved": [
    {
      "x0": <float>,
      "x1": <float>,
      "x2": <float>,
      "y0": <float>,
      "y1": <float>,
      "y2": <float>
    } ,...
  ],
  "straight": [
    {
      "angle": <float>,
      "x": <float>,
      "y": <float>
    } ,...
  ],
  "curved_center": [
    {
      "angle": <float>,
      "x": <float>,
      "y": <float>
    } ,...
  ]
}
```

En cada clave:

* "straight": En esta clave se encuentran los centros geométricos de las partes rectas de la pista.
* "curved": Siendo las curvas triángulos, los 3 vértices del triángulo en `{"x0": n, "x1": n,"x2": n, "y0": n, "y1": n,"y2": n}`.
* "curved_center": Centros geométricos de las partes curvas de la pista.

## Armado del archivo de configuración 

Para el armado de la pista utilizamos la interfaz gráfica que proporciona Box2D, denominada "Testbed". Y tiene la siguiente forma:

![Pista](Track_croquis.png)

Para reproducir el armado de la pista remitirse a [este repositorio](https://github.com/milenamarchese/Box2D) donde se explica como inicializar la Testbed y como agregar una prueba nueva. El archivo de la prueba a agregar es "FooTest.h".

## MODS



## Como cerrar 

Para terminar con todas las partidas existentes y cerrar el servidor, escribir en la termina el caracter 'q' y se despedirá.

```
q
Goodbye!
```




 