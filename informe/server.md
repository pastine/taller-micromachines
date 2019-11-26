# Micromachines

##Server

### Servidor
El servidor cuenta con un Acceptor de clientes, en el handshake les informa las partidas existentes o si desea crear una nueva, si es así, debe indicar cuantos jugadores serán.

### Carreras
La carrera cuenta con la clase Environment y un vector de Players. En el ambiente están encapsuladas las clases: Limit, Track y la clase propia de Box2D b2World, encargada de simular la física. Cada carrera corre en un hilo diferente y a su vez todos los jugadores participantes de la misma corren en hilos diferentes.

### Entidades
La clase Entity es la clase madre de todos los elementos que componen la carrera, la pista, el borde, los autos y elementos dinámicos. Eston son simulados por el motor físico.

### Autos
Esta clase se encarga de modificar la física del auto y efectuar los contactos con los demás elementos. Para manejar el auto existe la clase CarHandler.

### Elementos extra

Los elementos extras son: 

* Boost
* Health
* Boulder
* Oil
* Mud

Los primeros dos pertenecen a un subgrupo que hereda de Consumable, que a su vez hereda de Entity. Ambos son elementos consumibles que cuando entran en contacto con un auto desaparecen y reaparecen en otro lugar de la pista.
 
### Handler de colisiones

El motor físico brinda una forma para escuchar colisiones entre elementos. Utiliza funciones de callback implementadas por todos los elementos físico, cada uno cuenta con un identificador del tipo `int` con el Listener de Colisiones filtra que hacer con cada uno. Por ejemplo, cuando dos autos chocan llaman a start_contact de cada uno y se efectuan los cambios correspondientes.

### Mensajes
El template de StateHandler se utiliza para enviar y recibir mensajes, en el caso del jugador recibe un movimiento para indicarle al auto y envia un JSON con el update de las posición del auto y otra clase de flags. Cada jugador cuenta con un receiver y un updater, ambas corren en hilos diferentes. El template StateHandler cuenta con una cola bloqueante donde se encolan los mensajes a enviar/recibir. Ambos tienen una referencia a el ClientProxy, ya que no se puede copiar porque contiene un Socket para la comunicación.