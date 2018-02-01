20171107
========

Para recuperarme de la sequía desarrollativa que me ha atacado casi por sorpresa y me ha dejado prácticamente en blanco todo el mes de Octubre, voy a remozar D'Veel'Ng y posiblemente Bootee.

Lo primero es pasar del código (y compilador) viejo (¡esto es de 2015!) y pasarlo todo a la última versión de MK2, que es la de Yun Wiga (Dark Yun), 0.87.

Pasamos a 0.88 y le damos fran. Lo primero es hacerme el set de gráficos con los sprites modernos y algún que otro retoque y ver si el mapa comprime mejor que packed de alguna forma. Tengo que idear algún tipo de compresión que funcione bien con mapas con pocas tiras horizontales con repetición. Hay mucho patrón de ajedrez en el viejo mapa de Bosque / D'VeelNg.

En una segunda etapa puedo intentar apañarle una segunda fase o Game B o algo así.

El objetivo es liberarlo (con portada y tal) para que lo publique quien quiera a cambio de copias físicas. No sé cómo funcionará esto.

El Mapa
=======

El mapa es de 16 tiles y pico. Los "picos" se repiten poco. Vamos a probar a:

- Packed con decos.
- RLE44 con decos.
- RLE53.

Se me ocurre que el tile 15 es el cerrojo siempre. La información de donde están los cerrojos está en una estructura aparte. Si retiro los cerrojos del mapa en sí y uso $FF como caracter de escape, quizá pueda hacer un híbrido entre RLE53 y packed. Aunque quizá si me lío mucho acabe con una función para pintar la pantalla que ocupe tanto que lo que gane en compresión no compense.

$FE -> Next: cadena packed 0-14
$FF -> Next: cadena packed 16-30
$Fx -> Next: x times next byte.

Es muy complejo.

Voy a ver cuanto ocupa con los compresores que tengo, anda.

```
    Packed con decos.     2400 + 195 = 2595 bytes.
    RLE44 con decos.      2988 bytes.
    RLE53.                2929 bytes.
```

Es duro pero es cierto.

El tema es que esto es así en *este* mapa... Pero si añado otros puede que no tengan tanta mandanga. Aunque si sé que estoy usando packed con decos a lo mejor sí que meto igual de mandanga.

Meh.

~~

Se me ha ido la perola y me he puesto a meter un montón de detalles con los tiles del 16 al 31 XD. En serio, soy hostia.

~~

Voy a inventarme un Dual RLE44 con dos capas a ver qué tal se da :-)

Para cada pantalla, 

- primero se codifica la capa de abajo, la compuesta por los tiles 16-31, usando RLE44 sobre el valor-16 y haciendo que cualquier valor fuera de rango (0-15) se sustituya por el tile anterior, para incrementar la posibilidad de hacer "runs" largos.

- Luego se codifica la capa de arriba, la compuesta por los tiles 0-15, sustituyendo cualquier valor fuera de rango (16-31) por un 0. El renderer debe saltarse los tiles 0.

Probemos, y luego a casa.

~~

```
    Packed con decos.       2400 + 475 = 2875
    RLE44 con decos.        3318 bytes
    RLE53.                  3211 bytes
    DualRLE44.              3743 bytes
```

Vaya fracaso XD

Pero es que 3K por mapa me parece una burrez. ¿Cómo ganar espacio? ¿Y si lo hago CNROM y los guardo en la ROM extra de chr? Puedo meter dos mapas por cada página extra de gráficos. ¿Cuánto se tardaría en leer?

Anda, si neslib tiene VRAM_READ, lo que pasa es que la tengo fumada. Voy a meterla de nuevo :-)

~~

Está claro que puedo leer los tiestos de VRAM. Leer una pantalla cada vez no debe tomar demasiado tiempo, a lo sumo unos cuantos frames. Tengo que leer 96 bytes de datos packed y luego unos cuantos decos. El tema es ver como organizar esto. Quizá necesite los índices en ROM normal y los decos en CHR-ROM.

Los pattern tables (donde meteré esto) estarán en $0000-$1FFFF (8Kb). Puedo probar a meter el mapa ahí a ver si lo puedo hacer. El tema sería:

1. PPU OFF.
2. Paginar CHR-ROM n>0, la que contenga el mapa.
3. Leer 96 bytes desde BASE+n_pant*96
4. Obtener la dirección de los decos y sumarle BASE+MAX_PANTS*96
5. Leer bytes de ahí hasta encontrar un 0

Para codificar todo esto lo suyo es hacer un compresor nuevo adaptando el packmap2 que haga lo siguiente:

1. Sea capaz de procesar una lista de mapas!
2. Genere un binario listo para expandir y cargar como CHR-ROM.
3. Genere un .h con un define del banco de CHR-ROM de cada mapa, más un offset al inicio de cada mapa (en un define, por ejemplo), más un offset al inicio de cada tabla de decos, más un offset para los decos de cada pantalla.

¡Esto suena a mandanga de la buena!

20171108
========

Ayer hice un conversor para mapas en CHR-ROM que por ahora me servirá, aunque lo suyo sería refinarlo para que fuera más flexible. Por ahora guarda los mapas que le digamos en CHR-ROM empezando desde CHR-ROM 1 (eso por ejemplo debería poder parametrizarse) y genera un .h con un índice de decos, info sobre donde está cada menú (ROM y base), y los cerrojos.

Estaría muy interesante hacer esto de forma que pudiese hacer convivir mapas en PRG-ROM y en CHR-ROM, así que tendré eso en cuenta a la hora de escribir el driver que pinte las pantallas.

Voy a convertir el .ene al formato nuevo.

~~

En el .ene original hay un tipo 6 que obviamente es un fanty, pero tengo que ver qué tipo de fanty es. Me pega que sea con colisión.

Sí, son con colisión.

~~

Cosas que implementar: 

- Revisar los disparos y sus prioridades.
- Ver que los tipo 7 con generador siguen funcionando (joder, llevan desactivados desde la primera versión).
- Implementar el item calavera que pone todo rojo y mata a los enemigos.
- Poner a las musas. El sprite para el hotspot tipo objeto puede recibir disparos. No sé si esto sigue en el motor o lo quité.
- En la importación, importar las musas (o hijas de la diosa) para que se pinten 16 pixels más arriba de la cuenta (0 -16).
- ??? debería jugar más y ver las cosas raras.

- El sprite del tipo &H30 implementado debe ser fijo.
- Tengo que normalizar los sprites de los enemigos, que están muy orientados a no poder girarse. Tengo que poner derecha, luego izquierda en el fanty.

~~

Hotspots son: 

```
    1. Objeto
    2. Llave
    3. Vida
    4. Calavera
```

~~

Voy a escribir el driver. Al final tendré drivers para todos los formatos de mapa en CHR-ROM, pero como yo soy de los de haz-haz, pues por ahora sólo soporto PACKED en CHR-ROM y ya ampliaré. 

La idea es copiar en buffer de pantalla los 96 bytes desde VRAM y luego expandir desde ahí. He hecho simulaciones y si copio los 96 bytes en la segunda mitad del buffer de 192, no se me "pisa" nunca. Si no te lo crees, mira:

```
    ·· ·· ·· ·· ·· ·· <- Buffer de 6 espacios

    ·· ·· ·· 12 34 56 <- Copio el packed a partir de la mitad.
    ^^       --       <- Empiezo aquí.

    01 02 ·· 12 34 56 <- Expando 
          ^^    --    <- y muevo el cursor

    01 02 03 04 45 56 <- Expando
                ^^ -- <- y muevo el cursor

    01 02 03 04 05 06 <- Expando.
```

Por cierto, importante:

**cur_bank debe contener el banco de CHR-ROM activo, ya que será necesario para "volver a él" tras copiar los tiestos para la pantalla actual**


~~

Bueno, el driver está completo. Es el momento de juntar todas las pichas y hacer una primera compilación básica. Lo primero es apañar compile.bat, luego ya el definitions.h

20171109
========

Tengo que revisar el tema de los enemigos que se mueren. Los normales lo hacen, pero los tipo 7 y sus generadores no. Tiempo de recordar!

~~

Empezamos desde el principio: En la colisión bala->enemigo.

Para un enemigo normal se hace:

```
    enems_drain ();
    bullets_destroy ();
```

Para un tipo 7 (colisionando con `(en_x, en_y)`, que son las coordenadas del minion) se hace justo eso, pero solo si `_en_state` (o sea, si el minion está activo; si no se podría colisionar con "la nada").

Además, hay otra comprobación aparte con `(en_x1, en_y1)`, las coordenadas del generador, que hace sus propias cosas: quita la bala y resta `en_gen_life`.  Pero creo que aquí está la confusión: si la vida llega a cero también llama a `enems_drain`. Tengo que revisar eso.

Veamos `enems_drain`.

Esta función simplemente decrementa la vida, y si esta llega a 0 se llama a `enems_kill`.

`enems_kill` es la que pone `en_t` a 0, hace la muerte persistente (si aplica), anota un muerto más en una flag (si aplica), incrementa `pbodycount` (que en este juego no usamos), y cosas así.

Creo que lo mejor que puedo hacer es:

- En `enems_drain`, si `rdt == 0x70`, poner `_en_state` a 0 en vez de llamar a `enems_kill`.
- En la colisión con el generador, llamar a `enems_kill` directamente, y no a `enems_drain`.

¡Probemos!

~~

Solucionado. 

Ahora hay un bug: Si empuja hacia abajo o hacia la derecha (incremento), también dispara. Hacia arriba o hacia la izquierda (decremento), lo hace correctamente (no dispara si empuja). Lo mirow.

Urm, es raruo. A veces pasa, a veces no :-/ Lo raruo es que siempre se comprueba antes el empujón, y se deja bloqueado el disparo. Voy a reforzar eso un poco...

~~

Creo que tengo que hacer esto de otra forma, y centralizar todo el pulsado del botón.

~~ 

Voy a separar llaves de push boxes. Voy a hacer que las push boxes solo se puedan empujar pulsando disparo. Voy a reorganizarlo todo!

~~

Uf, reorganizado. Creo que todo es mucho mejor, más interesante y me permite tener más bloques que actuen como push box (como cerrojo aún no, pero eso me da igual). Lo de los bloques que actuen como push box tiene que ver con la idea que he tenido:

Combinar D'Veel'Ng con Cadaverion, ¡sin scripting!

La idea es tener un push box específico que si se mueve a un tile específico (todo definible), haga subir un contador y fije el push box (le bajo los bits 0 y 1, o bien lo cambie por otro tile, como en el Cadaverion original). Cuando el contador llegue a un numero específico, se abre el cerrojo de esa pantalla. Ese número específico puede calcularse al pintar la pantalla contando los tiles específicos "touchplate".

Pero antes tengo que apañar las hostages o musas o lo que coño sean.

20171110
========

Ayer, como siempre, me puse a hacer cosas y a hacer cosas y arreglar y pulir y modificar ... y no apunté nada. Pero esto ha avanzado mucho. De todos modos, tengo que apuntar cosas importantes:

Para pulir:

[ ] Los minions del tipo 7 no acaban en explosión. No queda del todo mal, porque la explosión del último impacto "da el pego", pero...
[ ] Cuando se coge la calavera, hay "extraños". Tengo que revisar eso. Al coger la calavera deberían morir los enemigos normales y los minions de los TYPE_7, todos con explosión. Es probable que tenga que cambiar cosas porque creo que al matar a los minions ya se reposicionan (x,y) en el generador, y entonces la explosión iría donde no debe.

Para modificar:

[ ] La calavera también debería restarte vida. Rollo, sacrificas un punto de vida por acabar con todos los enemigos.
[ ] Bajar el número de vidas. Es demasiado alto.
[ ] Los minions se mueren al segundo golpe ¿Qué pasa con su vitalidad? No recuerdo si se definía a golpe de #define. Si no, hacerlo así (como con los fantys: Si no existe directiva propia, pillar la general).

Cosas:

Sobre la implementación de los touchplates para Cadaverion. Necesito varias cosas:

1. Poder definir varios tiles cerrojo. Esto es para poder tener los que se abren con llave y los que se abren con touchplates. El (los!) conversor(es!) de mapas deberían poder recibir listas de cerrojos. El # de tile que abren las llaves se #define. 

2. Hay que hacer que las cajas sean floaty como en el MK3 de los Ordenadores de Mierda. Debe poder moverse por el escenario sin destruir el fondo.

3. Al activar los touchplates, tenemos que añadir una tabla análoga a behs. Son pocos bytes desperdiciados que permiten tener un código más simple.

a) Para cada tile, si es un push-box, define qué número de tile representa el touchplate que activa.
b) Para cada tile, si es un touchplate, define qué cerrojo abre.

4. Hay que definir un "número de touchplates por cerrojo". Al entrar en la pantalla, si un cerrojo está cerrado, se contará el número de touchplates que lo abre que hay en pantalla.

Todo eso de arriba va a dar mucho juego.

~~

Tal y como están las cosas, si en el conversor de mapas sólamente "identifico" los locks y se guardan como siempre, para saber el tipo de lock tengo que hacer una lectura a scr_buff. Tampoco es mucha coña, y me ahorra espacio.

~~

Voy a modificar los conversores para permitir una lista de cerrojos. O no sé, quizá sólo modifique el conversor que estoy usando y ya vaya modificando los demás cuando lo vaya usando, que es mi modus operandi XD

~~

Ya he cambiado packmamchrrom.exe, rle44map.exe y rle53map.exe, que son los que más uso (y pronto habrá rle44mapchrrom y rle54mapchrrom, pero no en este proyecto).

Ahora lo suyo es convertir los push-boxes en floating boxes. Pero jiuston, tenemos un problema. Con un solo tipo de push box, bastaba con pintar y poner el beh en `scr_attr`, pero un 0 en `scr_buff`. Ma como. Si ahora tengo varios tipos de push boxes, ¿cómo sé cuál estoy moviendo?. Mal.

Necesitaría otro buffer de pantalla para los push boxes, Y 192 bytes más de RAM como que no.

Ahora mismo tengo `scr_attr` y `scr_buff` separados por velocidad. `scr_attr [n]` equivale a `behs [scr_buff [n]]`, una indirección más. ¿Me joderá mucho la marrana? ¡Porque estoy leyendo behs continuamente! Voy a hacer un find in files para asustarme (o no).

Fuck.

Se usa para meter los contadores en los tiles "breakable". Hm. No me lo puedo fumar aunque quiera.

Pensemos más.

Si forzamos que todos los tiles empujables estén entre los 16 primeros, nos valen 4 bits para almacenarlos. Entonces puedo codificar esto, creo, en los atributos.

Un empujable es 00001011. En los 4 bits más significativo podría meter el índice del empujable en cuestión sin problema, pero esos bits ya tienen otros significados. Revisemos:

- Slippery Bit suelo ponerlo en el bit 4. ¡En vista lateral, un push box floaty de # de tile impar siempre sería resbaloso!
- Conveyor Bit suelo ponerlo en el bit 5. ¡En vista lateral, un push box floaty de # 2, 3, 6, 7, 10, 11, 14 o 15 arrastrará a izquierda (par) o derecha (impar)!.

Obviamente los push box 'floaty' no serán compatibles con estas cosas.  Tampoco me importa, si necesito algo parecido a push boxes en vista lateral en el futuro los puedo implementar de otra forma.

~~

Voy a hacer esta implementación de los bloques floaty conservando la implementación normal.

~~

Qué hacer:

1. Al pintar la pantalla, detectar un tile con beh `PUSH_BOX`, sustituir por 0 en `scr_buff`, codificar su número de tile shl 4 en `scr_attr`.
2. Al detectar push box, "borrar" con el contenido de `scr_buff`, y obtener el # del tile que hay que pintar de `scr_attr` (voy a sacarlo a una variable porque será necesario en el futuro próximo).

¡Con eso y un bizcocho debería funcionar!

~~

Sí, hecho y funcionando.

~~

Con esta infraestructura, puedo comenzar a hacer el tema de los touchplates... Pero ya tu sabeh que soy un hombre de acción y sin un nivel en el que ir probándolo no me gusta programar. Lo malo es que estó se está poniendo chungo para hacer cosas en el curro por cejas levantadas y gente al liquindoi, por eso... Mal.

Yo sé de qué hablo. 

~~

Cuando haga los touchplates debo activar automáticamente un `#define SPECIAL_BOLTS` para que al abrir un bolt con llave, para encontrarlo, compruebe que realmente es el tile bolt definido.

20171111
========

Veamos, algoritmia.

Dijimos que los touchpads llevan asociados qué tipo de cerrojo abren. Vamos a establecer que ese cerrojo aparece UNA vez en la pantalla. Obviamente no comprobamos nada en el engine, es tontería... Pero pueden aparecer varios tipos de cerrojos.

Además, un valor de 0xff en el comportamiento asociado del pushbox significa que activará cualquier touchplate.

Tenemos pues un array de 32 posiciones con la "vida" de cada cerrojo. Al entrar en la pantalla se inicializa a cero.

- Para cada tile que se dibuja, si su beh es "0" (transpasable), se mira en el array de comportamientos si tiene algún cerrojo asociado (!= 0).
- Para esa posición del array de "vida", se incrementa en 1 el del cerrojo asociado.

A la hora de mover un pushbox, en la casilla destino, si es un touchplate (tiene un cerrojo asociado != 0), se decrementa en 1 la "vida" de dicho cerrojo.

Cuando la vida vale 0, se busca la posición de dicho cerrojo en pantalla (entre los cerrojos con n_pant actual, se mira la posición en `scr_buff`), se borra el tile, y se marca el cerrojo como "abierto".

Creo que puede funcionar, pero ahora no tengo mucha energía para programarlo...

Aunque lo puedo empezar.

~~

Al final lo he implementado todo, pero no lo puedo probar aún. Necesito datos. Mapa ya tengo, pero hay que colocar enemigos y tal.

Mañana. Aunque creo que lo he hecho bien :)

~~

Mierda, al final lo he dejado funcionando. Tenía un par de problemas, pero era porque no había tenido en cuenta que cada mapa pudiese tener un set de cerrojos diferente. Modificado el conversor y apañado un mini desliz en el código, y ¡funciona!

Joder, lo mola todo!

20171112
========

Hoy he hecho 8 pantallas más en el mapa 1 (disjuntas), para un segundo nivel, pero por alguna razón que se me escapa no funcionan los touchplates. Como es tarde y tengo una pila de platos infinita, creo que pasaré y lo repararé en otro momento.

20171113
========

Hace días que me ronda la idea (intentaba resistirme), pero creo que el juego necesita más "cosas" para ir variando y alternando, y al final lo haré: que se pueda saltar.

Obviously no voy a meter una tercera dimensión real. El salto sólo valdrá para esquivar enemigos y agujeros en el suelo. Los pinchos no pincharán si estás saltando y tu altura es superior a cierto umbral.

Lo hará of course precalculando los incrementos (o mejor, directamente precalculando el desplazamiento vertical, en forma de restar un número en cada frame del salto), pero quiero mirar cómo lo hice en key to time.

Una vez hecho, esto afectará a:

- Animación y render: Hay que poner el frame de sartar (que tengo que añadir al spriteset) y subir el sprite en el eje Y.
- Colisión con los huecos (holes) del suelo (que tendré que activar en el motor). Si estás saltando, no caes. O mejor expresado: sólo caes si no estás saltando.
- Colisión con los `EVIL_TILES`: sólo se registra si estamos saltando y estamos fuera del intervalo "seguro" del salto. Este intervalo lo sabré en cuanto precalcule los offsets.
- ¿Lo mismo para la colisión con los enemigos?

Igualmente tendré que añadir tiles que resbalan. Lo chungo va a ser combinar esto con los empujables, porque me quedo sin bits. Pero algo se me ocurrirá...

Porque tengo evil, hole, semiobstacle, obstacle en los 4 bits que tengo utilizables. Los otros 4 bits suelen codificar un número de tile empujable si los 4 bits principales valen 0xB (o sea, 1011). Por ahora los empujables que uso tienen índices altos, >7...

Voy a pensar, si uso el bit 4 (& 0x10), los tiles resbalosos serían 0x10. Creo que como el uso de los bits superiores para codificar el número de tile empujable solo pasa para tiles obstáculo, puedo reusarlos para cosas que pasen para tiles traspasables.

Qué lío ¿no? No. 

Creo que no hay problema en modificar AX y RX con el bit 4 levantado.

Pero antes de esto quizá estaría bien mover el punto donde hay colisión central. Ahora mismo es (x+8,y+8), lo que sitúa el punto en el centro horizontal del sprite, y a 8 pixels de sus pies. Quizá tendría que bajarlo a (x+8, y+12) para que estas cosas tuviesen más sentido, o incluso a (x+8, y+14). O quizá detectar dos puntos, (x+8,y+12) y (x+8,y+15). Total, esa detección la tengo de gratis prácticamente.

Ahora mismo tenemos el `PLAYER_ENABLE_CENTER_DETECTIONS`, que se usa en la vista lateral para detectar cosas en este centro (x+8,y+8) del jugador. A saber, se detecta:

- Evil tile hit para el modo `EVIL_TILE_CENTER`.
- Que estamos en el agua.
- Tile Get.

Um, esto puede ser un pequeño pifostio. Vamos a seguir divagando que se me aclararán las ideas.

Veamos, el tema que te quema es detectar agujeros, tiles que matan y suelo resbaloso de forma más o menos coherente. Como estamos en lo que queremos que sea una suerte de perspectiva diédrica (los tiles se ven desde arriba y desde el frente a la vez: es lo que se sugiere al mirar las estatuas o el sprite de Cheril, por ejemplo), lo suyo sería hacer las detecciones sobre el suelo que pisa Cheril.


- Ahora mismo Cheril colisiona con un cuadrado de 8 pixels de lado situado en la parte inferior de su sprite. Sin embargo...
- ¡La detección de holes está en un rectángulo mucho más pequeño, de 2 pixels de alto, desde y+4 a y+15!
- La colisión con tile que te mata se deteca en el punto (y+8,x+8).

¿Será el momento de partir la baraja y crearme un player_move "limpio" para juegos genitales, como hice en MK2 en tiempos (y abandoné)?

~~

Tengo estas cosas en player_move

```
    - Tiestos iniciales.
    - Vertical
        - Gravedad (si aplica)
        - Poll pad
        - Move (con control de no salirse)
        - Colisión
        - Floor detections (vista lateral)
            - ppossee
            - conveyors
            - propellers
            - `EVIL_TILE_ON_FLOOR`
            - slippery
        - Saltos
    - Horizontal
        - Poll pad
        - Move (con control de no salirse)
        - Colisión
        - Solve facing (GENITAL)
    - Center point detections
    - Evil tile hit (para center y multi)
    - Hidden
    - Spinning
    - Float
    - Pad A/B stuff (fire).
    - Butt
    - Render.
```

El problema de separar en un nuevo `player_move` es que puede que llegue el momento en el que tenga que mantener dos códigos, así que voy a romper la función en varias partes que pueda intercambiar separadamente:

- Tiestos iniciales
- Vertical
- Horizontal
- Center point detection
- Evil tile hit
- Extra stuff
- Render

Lo separo por ahora en `#include`s y vemos qué tal se va dando.

~~

Ya he hecho la separación, pero antes de seguir debería repasar bien todo el comportamiento de los tipo 7 para:

1. Poder configurar el número de hits que se llevan los minions y el número de hits que se llevan los generadores para desaparecer.
2. Que al matar a un minion aparezca la explosión.

Hecho esto, la idea es fortalecer los tipo 7 (aumentar la cadencia de apareción, disminuir los tiempos de congelación) y hacer las muertes persistentes.

No sé si activar el persistent deaths me joderá el mapa de memoria, voy a ver antes que nada. . . Sí, sigue compilando y parece que va bien.

En otro orden de cosas, no me fijé demasiado al ordenar los tiles en el mapa 1 y creo que eso hace que estén ocupando un huevo de patow. Básicamente hay demasiados tiles considerados decoraciones y el tamaño se ha disparado del copón. Lo suyo es que cada mapa ocupase por debajo de los 2700 bytes con 25 pantallas, todo incluido, para poder meter 3 por cada página de CHR-ROM.

2700 con 25 pantallas da 108 bytes, lo que resulta ser un margen bastante pequeño para decoraciones, teniendo en cuenta que 96 de esos bytes serán el mapa packed. 14 bytes de decoraciones no es realista . . .

El tema de las pantallas es peliagudo. De todos modos voy a examinar el tileset y a ver qué fallo hay.

Usando RLE53 me ahorraría las decoraciones y haría que el render de pantalla fuese más rápido. El índice de las decos me lo fumo, y lo sustituyo por un índice de pantallas. Lo malo es que estos mapas comprimen muy mal en RLE.

¡Pero es pasta gorda, joder, ahora mismo el mapa 1, que está a falta de 11 pantallas, tiene 1166 bytes de decoraciones!

O sea, ahora mismo ya ocupa 2400 + 1166 bytes = 3566. Para ser justos, ocupa 14 * 96 + 1166 = 1344 + 1166 = 2510 bytes.

En RLE53 ocuparía 1895. Eso ya está mejor por goleada.

"Cuando pueda" debería probar a modificar un poco el mapa 0 (para arreglarlo, que está feo por muchos sitios) y pensar un poco en compresión para meterlo en RLE53.

Creo que me paso a RLE53. Voy a ir haciendo un rle53mapchrrom.bas XD

~~

Vamos a mirar el tema de los tipo 7.

Necesito que revienten un poco al morirse, pero claro, se están reposicionando. Voy a ver si puedo dejarlo tal y como está pero haciendo el reposicionado en el momento de crearlos o algo.

Hum, a ver, `_en_x = _en_x1; _en_y = _en_y1;` está al crear el minion. ¿qué ocurre?

Igualmente, cuando muere un minion lo único que se hace es poner `_en_state = 0` y reiniciar el contador de idle.

Veo que la vida del minion es en_life. ¿Dónde se inicializa? -> al crear el minion. OK, esto lo tengo controlado: es la constante `TYPE7_MINION_LIFE`. Está a 1, la subo a 3.

~~

He hecho que `_en_washit` se active en el último disparo también, pero hay un reposicionamiento. Creo que sé por qué es. El reposicionamiento se hace antes incluso de empezar a aparecer. Voy a ver si puedo cambiar este comportamiento.

~~

Creo que he solucionado eso también.

~~

Acabo de programar los axis horizontal y vertical (menos el salto, claro), y voy a ver si funciona del tirón. Debe ir como antes, pero con el bounding box más mejor. 

Por ahora no puedo probar el slippery ni los holes, pero puedo ver si colisiona bien con el escenario y si se comporta guay con los evil tiles.

~~

¡¡Funcionando todo!!
Fin por hoy :-)

20171114
========

Me he calculado los saltos para que cubran 32 pixels en linea recta a máxima velocidad... Pero como la velocidad máxima es 2 pixels por frame, el salto se resuelve en 16 frames. Me parece poco. He hecho las ecuaciones y calculado los offsets para mover al sprite. Si veo que es muy corto lo recalculo, y ya veré de limitar la velocidad a un valor menor durante el salto o algo parecido.

Tengo que reutilizar variables que no se usan en modo genital para el salto. Necesito contar los frames, poco más. Puedo usar pj como flag y pctj para contar los frames.

~~

Funciona perfe (tengo que modificar ahora las colisiones `pholed` y meter una sombra), pero creo que 16 es demasiado corto. Voy a probar con 24.

~~

Hoy en "cosas que debería documentar y nunca hice"...

Holes
=====

Son tiles traspasables (normalmente beh & 2) en los que el jugador cae. Cuando el jugador pisa uno de estos agujeros, se pone a cierto el flag `pholed`.

Lo que pasa a continuación te sorprenderá.

Tienes que manejar la animación de caerse y el decremento de `pholed` de forma automática. Tal y como está, son tocar, `pholed` se pone a 48 cuando pisas el agujero. Tú eres quien tiene que decrementarlo y cambiar el frame.

Todo esto se hace en `player_mods/cell_selection.h`.

Pero ahora estoy siendo más ordenado y moviendo el decremento al sitio de las cosas estas.

~~

No he contado con que este juego no tiene respawn... ¿Qué pasa cuando me caigo con el agujero? ¿Dónde reaparece? Prefiero verlo XD Luego ya pondré que aparezca por donde entró en la pantalla.

~~

Hay muchas cosas que no están finas. Las colisiones de las bolas hacen extraños. Y a veces el caer por los precipicios queda raro porque desaparece sobre el borde. Puedo parchear para darle más jarapa si pvy es >0 , o simplemente poner las velocidades al máximo.

Voy a mirar lo de los disparos y a probar lo otro antes de dejarlo por hoy.

20171120
========

Los disparos siguen haciendo raros. Voy a revisarlos todos de pe a pa. 

Empezamos desde el principio: El usuario pulsa el botón de disparo: una simple llamada a `bullets_fire ()`.

`bullets_fire` busca un slot, y al obtenerlo crea la bala `(b_x, b_y)` en `prx + boffsx [rdb]` y `pry + boffsy [rdb]`.

Las balas se pintan en `(b_x, b_y)`, y la colisión con el escenario está en su "centro" `(b_x + 4, b_y + 4)`. Esto está bien.

Teniendo esto en cuenta, lo primero que hago es corregir los offsets en `precalcs.h`, que están obviamente mal. Done.

Para colisionar con el hotspot tipo 1, se usa la función collide, llamando con `collide (b_x [bi], b_y [bi], hrx, hry)`. En esta llamada, `(b_x, b_y)` son las coordenadas de la esquina superior izquierda de un cuadrado de 8x8 (la bala) y `(hrx, hry)` las de la esquina superior izquierda de un cuadrado de 16x16 (el hotspot, en este caso la parte inferior del sprite).

La función collide colisiona algo con algo desde -7 hasta +15 del segundo algo, lo que está bien en este caso (cuadrado de 8 con cuadrado de 16):

```
    x-7    x            x+15
    |      ||              ||       |
    \-------/              \--------/
        8  \---------------/    8
                   16
```

Verticalmente hace exactamente igual, con lo que esta colisión parece correcta.

La otra colisión es con los enemigos. En este caso también se utiliza collide entre `(b_x, b_y)` y `(_en_x, _en_y)`, lo que parece correcto.

Hum. El otro día me pareció que hacía extraños pero todo parece que va bien. Es raro.

Lo que sí voy a hacer es que los parpadeantes paren las balas aunque no reciban daño.

Marco esto como hecho y sigo con lo siguiente...

~~ 

Que no se rebote cuando se está parpadeando en `evil_tile_hit`. Estaba seguro de haber resuelto esto pero o lo he sobrescrito, o lo hice en el classic y no está en new_genital. Voy a verlo.

Se ha quedao mejor.

20171220
========

Esto se me ha estancado un poco. Por alguna razón recuerdo que había complatado todo el mapa "1" (el de los puzzles) con pantallas, pero en git me faltan todavía cinco o seis. Tengo que buscar en los ordenadores donde suelo desarrollar a ver si se trata de un commit no hecho o que tengo que dejar la droga.

Además he estado desganado y más interesado en otras cosas. Llevo todo Diciembre sin hacer prácticamente nada.

Hoy tampoco podré tirarle, pero llevo tiempo rumiando una adición que quiero dejar bien documentada porque si no se irá al carajo.

~~

El tema va de tiles "apagados" que se "encienden" disparándoles de 1 a N bolas. Funcionan en realidad como los touchplates (creo que se podría compartir parte de las infraestructuras) y abren puertas. 

El juego está en que hay tiles obstáculos que dejan pasar las bolas y tiles que no, además de que los empujables las detienen. 

Con esto se pueden crear nuevos puzzles guays, o al menos situaciones con bichos pesados acosándonos mientras encendemos todas las luces.

~~

La fase con esto debería abrir la segunda CHR-ROM de mapas. Tengo que mirar a ver si hay suficientes patrones libres en CHR0 para meter los tiles que faltan (necesito 8 patrones). También he pensado que estaría medio que cierta animación en los tiles que se abren, que el que desaparezcan simplemente es un poco spectrum. Eso implica meter una entidad que actualizar más, pero hay sitio - la lluvia que metí pilla tiempo de frame pero creo que nos lo podemos permitir.

~~

Voy a estudiar el código tal y como está a ver cómo los podría implementar.

Detección
---------

Ahora mismo, mientras se dibuja la pantalla, si nos encontramos un touchplate se incrementa en 1 la "vida" del tile cerrojo relacionado. Análogamente podría hacerse con los encendibles. Para touchplates:

```c
#ifdef ENABLE_TOUCHPLATES
    if (c_tp_defs) {
        if (rda == 0 && (rdb = c_tp_defs [rdt])) {
            bolt_lives [rdb] ++;
        }
    }
#endif
```

Sería añadir en ese bloque (dentro de `if (c_tp_defs)`) un caso rollo `else if ((rda & LIGHTABLE_BITS) == LIGHTABLE_BITS)`  o algo por el estilo, o incluso con un OR porque a fin de cuentas es lo mismo, esto es:

```c
#ifdef ENABLE_TOUCHPLATES
    if (c_tp_defs) {
        if ((rda == 0 || (rda & LIGHTABLE_BITS) == LIGHTABLE_BITS) && (rdb = c_tp_defs [rdt])) {
            bolt_lives [rdb] ++;
        }
    }
#endif
```

Acción
------

En el caso de los touchplates, la acción se realiza cuando se detecta que hemos movido el push box correcto encima. En ese caso se hace un 

```c
    bolt_lives [rdb] --;
    [...]

    if (bolt_lives [rdb] == 0) {
        // Clear this bolt
        bolts_clear_bolt_from_touchplate ();
        // rdc contains the cleared bolt YX
        set_map_tile (rdc & 0xf, rdc >> 4, 0);
        sfx_play (SFX_CHOF, SC_LEVEL);
    }
```

En este nuevo caso habría que detectarlo en las colisiones de los disparos con el escenario. Antes que nada, necesito que cada tile encendible tenga una vida (luego resuelvo esto). Al detectar colisión con encendible, se decrementa esa vida. Cuando esa vida es cero, el tile se cambia por encendido y se hace lo del trozo de arriba, que tendré que encapsular para reaprovecharlo.

Codificar la vida de los tiles
------------------------------

Esto es parecido a lo que hice hace poco en otro juego que no recuerdo ahora (vaya hombre). Es usar BITs del beh para codificar esto.

Voy a hacer un poco de memoria XD.

Coño, es en este juego. Los uso para los empujables floaty, para almacenar el # de tile que los representa. Pues igual: en los tiles encendibles, tendré que almacenar ahí la vida. Son 4 bits, puedo usar incluso 3, porque 8 ya me parece un buen número. De hecho, esto me permitiría incluso definri la vida inicial en el puto beh y ahorrar más código!

JOJO, GENIUS!

So, remember
------------

Para los tiles encendibles, la vida irá almacenada en 3 bits. LIGHTABLE_BIT valdrá 128, y la vida será `((beh & 0x70) >> 4)`

~~

Con todo esto los tengo funcionando en un plis con 0.2 de código :-)

Para simplificar, además, si N es apagado, N+1 es encendido.

Cuando encuentre un rato para dibujar veo esto. Necesito gráficos y un nuevo tileset antes que nada. 

Otra cosa que debería dejar listo son los cutscenes o intros de las fases en las que Cheril se levanta de la cama y avanzas un par de pantallas de la cripta hasta llegar a la puerta de entrada de la fase que sea.

20171224
========

Para gestionar pequeñas animaciones maptileras, voy a crear un módulo general que lleve para adelante N animaciones.

- Un slot de animación estará activo si contiene un puntero a una animación (o sea, si no es 0).
- Se define un XY para la animación, en otro array (mismo índice).
- El puntero a la animación contiene secuencias de 2 bytes: #frames, #tile.

El cambio consistiría en cambiar el setteo del cerrojo a 0 por una animación que termine en tile 0.

~~

Después de programarlo, he pensado que no es la mejor solución (pero lo dejo ahí, porque podrá valer para otra cosa aunque sea en otro juego), ya que necesita tener un tile más mínimo para hacer la animación. Creo que valdrá con poner una explosión.

Esto me lleva a pensar que el tema de las explosiones en los enemigos es bastante apañada pero quizá no es óptima. Podría crear un módulo que gestionase explosiones que pudiese crear donde quisiera definiéndoles una duración o incuso una animación mejor. A la hora de golpear o eliminar enemigos sólo tendría que "crear" explisiones en los sitios indicados sin tener que liarla tanto con los estados como ahora. Quizá sería mejor solución ya que no uso demasiados sprites (bueno, con la lluvia sí, pero meh).

Sería un módulo nuevo que gestionase "N" explosiones. Tú las lanzas en x,y y él se encarga de hacerlas animar un rato (el que le digas) y matarlas.

Necesito una explosión mejor. Por lo menos con algunos frames, que lo que hay ahora es cutre cutre. Tengo que pensar en qué puede funcionar mejor.

~~

Estoy super cansado, pero bueno.

20171226
========

Vamos a intentar terminar lo de las explosiones y me voy a la siguiente cosa, que llevo años enganchado y dando vueltas (aunque he mejorado bastantes detallitos).

Ahora mismo está programado pero lo hice cansado y sin echar cuenta, por lo que es posible que funcione como el puto culou.

~~

Pues no estaba mal. He estado más tiempo de la cuenta integrándolo (y creo que lo he dejado guay), eso sí.

Debería ir pensando en modificar los sprites y las cosas para la versión compo. ¡Ya es hora de que enseñe algo! Tengo que crear la infraestructura para generar la versión mojonia o la versión compo fácilmente desde compile.bat.

~~

He hecho el set para USA... eh... para la compo y he creado la infraestructura para poder generar la ROM de la compo fácilmente (con sus historias).

Iba a ponerme a hacer un set nuevo para las fases con tiles que se encienden y tal, pero antes quiero montar la minifase intro que saldrá antes de cada fase normal.

~~

Bueno, la secuencia de Cheril en la cámara inicial antes de cada nivel está hecha, a falta de ponerla acostada hasta que se pulse una tecla. Voy a ver si puedo hacer eso sin liarla parder.

20171229
========

Voy a implementar los tiles que se encienden y a hacer una fase que parta en tres trozos para intercalar entre las otras. El encendido podría hacerlo (fácil) con una sustitución de tiles, aunque no sé por qué se me antoja hacerlo animado con sprites. Voy por esa vía.

~~

Los reflejos son más sencillos porque solo pueden aparecer y solo necesitan almacenar x e y. La animación ya me la apañaré para que salga automáticamente sin tener que usar contadores aparte. Voy a crear algo de infraestructura, aunque hasta que no tenga nivel y otras cosas no podré probar un carajo de patho.

~~

Vale, esto está funcionando. Voy a jugar a una fase normal para comprobar que no he roto nada.

~~

Pues algo está roto, y mucho. Hay corrupción de diferentes formas y colores dependiendo de como mueva las cosas en RAM...

Voy a ir comentando cosas a ver cuando empieza a joderse.

En fin, gajes del oficio.

~~

En teoría, si comento `ENABLE_LIGHTABLES` y `ENABLE_SHINES` debería ir. Of course, es diferente de ayer, porque he cambiado cosas de sitio para aprovechar mejor todo, así que empezaré a fullear desde ese punto.

Así ya casca. Tras hacer un puzzle, al cambiar de pantalla hay corrupción. Voy a mirar el cacho que he movido para restar vida de los cerrojos, quizá esté ahí el problemo.

~~

Mover: no se jode.
Mover mucho: no se jode.
Colocar: no se jode.
Abrir cerrojo colocando: se jode.

Bueno, al menos lo tengo acorralao XD

~~

En la función, se espera que rdb sea el número del cerrojo que tenemos que atacar, y rdf la posición donde está el cerrojo. Pero esto sólo tras ejecutar `bolts_clear_bolt_from_touchplate`.

`bolts_clear_bolt_from_touchplate` busca en `scr_buff` el tile rdb (el cerrojo), y cuando lo encuentra, devuelve su posición en rdf.

`bolt_lives [rdb]` debe ser correcto (paso de mirar), porque el conteo de "vidas" es correcto y cuando llega a 0 se borra el macanaqui y se muestra la explosión.

Esto es lo que me raya: todo funciona guay hasta que cambiamos de pantalla y entonces se jode the marrane.

Vamos, la paleta se va a tomar por culo.

Si la paleta se corrompe ¿es posible que neslib esté haciendo fullerías? ¿Puede ser posible que esté mandando cosas a la PPU fuera de vblank, por alguna misteriosa razón?

~~

Digo, hay un PAL_BUF, justo después de TEMP, en ZP.

Si hay corrupción, es que hay un buffer overflow. Algo implicado en los manejes estos. Pero ¿qué?... 

Quizá ha estado ahí siempre, pero ahora esté dando la cara por el tema de que la RAM está más apretá.

~~

Todo el choco de las explosiones está relativamente alto en RAM (en concreto, expl_yd está en 07BB. ¿Me estaré colando? VOy a quitar la explosión a ver qué pasa.

~~

Nope. Sin explosión se sigue jodiendo igualmente. Ar.

Voy a empezar a comentar cosas de una en una sin ton ni son a ver.

- Comento todo el bloque: funciona.
- Descomento la llamada a `bolts_clear_bolt_from_touchplate ()`

~~

Hostia, cuelgue random al poner la estatua en su sitio :-/ Random digo porque joder, no había pasado antes, ¡estaba mirando otra cosa!

~~

Creo que voy a volver al estado de ayer y a poner todo de nuevo poco a poco a ver. Esto es un poco raro todo ya. Hago un zip con la mierda cambiada y voy rehaciendo poco a poco.

~~

Mecano en mi vida. El cuelgue ya estaba en la versión del día 26. Tendré que volver más atrás incluso.

Joder en dios.

~~

He hecho pruebas. Definitivamente el problema está en el módulo de las explosiones. Si comento el cuerpo de todas las funciones se va el cuelgue. Pensé que lo había arreglado con un cambio pero veo que no. Seguro que me estoy follando bien los arrays de slots y hostias. Al menos lo tengo cogío por el cojón.

Pero ahora lo tengo que dejar.

20180102
========

Acabo de detectar un problema. Si codifico un empujable en los behs para poder moverlo por ahí, eso puede coincidir con el bit 128 que es el que detecta al los lightables. Yupi yai yei.

Me quedo sin bits y sin ideas, ¿what do? ¿Una combinación? El empujable es "E", que tiene el bit 7 a 1. No puedo usar otro bit, la leche, ya no me quedan.

```
    1. mata
    2. hole
    4. obstáculo debil
    8. obstáculo fuerte
    16. resbala.
```

Me puedo permitir resbala porque si en alguna combinación se levanta 16 no va a resbalar un obstáculo. 

El problema es aquí, que tiles empujables > 7 levantan el bit 7. Los empujables son 11 (8+2+1) o 13 (8+4+1).

Los lightables podrían ser, por ejempo, 12 (8+4), pero tendría que hacer detección exclusiva de la parte baja. 

Esto cada vez está más guarreras. Pero al menos 12 me da el estado obstáculo que necesito. Debería transformar en 8 al convertir.

¿Y si uso 15? Todos los bits a 1, es la última que me queda. 

Vamos a ver.

Lo he modificado pero creo que lo he vuelto a romper XD Ofú, qué harto me tiene esto.

Otro poltersgeist con dolor de cabeza. En buena hora se me ocurrió esto.

20180103
========

El problema tiene que ver con los bits de los behaviours que se están pisando, como siempre. Se me hacen cortos los bytes. Necesito rediseñar esto, al menos para el modo New Genital.

Pensando, todos los estados con "contador" en el MSB son estados relacionados a los tiles sólidos: los tiles destructibles, los tiles cerrojo y los tiles encendibles. Por tanto, de entrada, si sólido, el MSB es un contador. 

```
    CCCC 1xxx 
```

Si el bit 3 es 0, entonces los MSB podría utilizarlos para estados relacionados con los tiles traspasables. Ojal, que por primera vez en casi 8 años voy a cambiar esto:

```
   xSHK 0xxx
```

Con S = slippery, H = hole y K = killing. 

De esta manera tengo aún un bit libre para algo más que quiera meter. Los estados que me faltan están relacionados con representar estas cosas:

- El tile es encendible.
- El tile es empujable.
- El tile es traspasable por proyectiles.
- El tile es un cerrojo.

De este modo, si el bit 3 es 1, podríamos tener:

```
    - Transpasable por proyectiles: 11xx    [0xC]
    - Empujable: 1x1x                       [0xA]
    - Encendible: 1xx1                      [0x9]
    - Cerrojo: 1111                         [0xF]
```

El problema es que tengo más estados que bits. He tenido a bien que los cerrojos sean la excepción por ahora. Si necesito más cosas, tendré que revisar esto. 

Ahora mismo esto me permitiría combinar cosas como empujable y encendible.

Creo que mejor que definir bits en el #define, lo suyo es definir la operación de comparación completa, para poder tener más flexibilidad en el futuro o con otro tipo de motor.

Este cambio es heavy. A ver qué tal.

~~

Ok, cambiado. Ahora a recoger los pedazos:

Problema 1
----------

Cuando abres cerrojo con lightables, se modifica "otro" tile. ¿La detección del cerrojo está mal?

Veo que `bolt_lives [0] = 1`, cuando sólo debería `bolt_lives [31] = 1`. Why.

Sin embargo, se decrementa correctamente `bolt_lives [31]`. Pero luego la explosión y la modificación del escenario ocurren en otro sitio. Mirar esto again, a ver.

`rde` vale 0x37 cuando debería valer 0xb8. La explosión y modificación son en 0x37. 

De dónde carajo saldrá este 0x37...

En el buffer, el cerrojo sale como tile 0x1a cuando debería ser el 0x1f. Cuando se llama a `bolts_decrease_life`, rdb, que contiene el número de tile del cerrojo, vale 0x1a.

¿Por qué vale 0x1a?

rdb es `c_tp_defs [scr_buff [rdf]]`, y rdf sale de la posición de contacto de la bala. O sea, scr_buff [rdf] debería valer el valor del tile lightable, que es ...

shee, que esto es lo de ayer, no sigas mirando; recuerda mejor. 0x1a es 26, que es el tile por el que se sustituye un empujable.

Esto significa que el tile en el buffer ha sido sustituido, y eso es porque el tile lightable ha sido detectado como empujable.

Que era lo que yo vine a corregir haciendo toooodo este cambio, wtf!

Revisemos `^_^u`

Tengo:

```c
#define IS_PUSH_BOX(a)              (((a)!=0xff&&((a)&0x0a)==0x0a))
#define IS_LIGHTABLE(a)             ((a)!=0xff&&(((a)&0x09)==0x09))
```

Eu, ahí hay algo raro. Revisa, macanaqui.

Los dejo así:

```c
#define IS_PUSH_BOX(a)              ((!IS_BOLT(a))&&(((a)&0x0a)==0x0a))
#define IS_LIGHTABLE(a)             ((!IS_BOLT(a))&&(((a)&0x09)==0x09))
```

Los behs implicados son: 9 para el lightable (bien) y 10 para el push box. (9 & 10) = 8, no cumpliría la condición.

Probemos...

OK, funcionando.

Ahora voy a seguir jugando, a ver si veo otros problemas.

~~

Problema 2
----------

Murciélagos generados no traspasan el escenario. Examinar los type_7.

~~

Todo el resto parece ir bien, pero no me quedo tranquilo hasta que rejuegue las fases viejas.

20180106
========

Puse una demo en nesdev y me han apuntado lo que yo ya pensaba arreglar de todas formas: el modo "torreta", en el que el disparo te "bloquea". Tengo que hacerlo de una forma diferente, como se hace en Sgt. Helmet's Commando, de forma que se te permite girar mientras estás bloqueado disparando. Como no recuerdo como lo hice, lo primero será estudiar y recordar cómo está implementado.

~~

Ahora mismo, al disparar, se asigna `pfixct = TURRET_FRAMES`. Si `pfixct`, entonces se decrementa y se pone `pad = 0` bloqueando los controles.

Es `pfixct` el que pone el frame de la mano extendida, pro lo que habrá que tener algo parecido.

De hecho, `pfixct` se activa al empujar una push box también, y esto sí que es necesario.

O sea, tengo que mantener `pfixct`, pero además introducir *aparte* la lógica del disparo de Sgt. Helmet's Commando, la cual estudiaré en brever, que Windows se quiere actualizar.

~~

El método en Helmet implica también un pfixct. Quizá tenga que renombrar la pfixct existente, porque no quiero que convivan.

En Helmet:

- Si `pfixct`, se decrementa.
- Si se cambia la dirección de pad0, `pfixct = 0`. Detectar si se cambia la dirección del pad es:

```c
	if ((pad0 & 0xf0) != (prevpad)) pfixct = 0;
	prevpad = (pad0 & 0xf0);
```

- Cuando disparas, `pfixct = TURRET_FRAMES`.
- Si `pfixct`, lo que se hace es `invalidar la aceleración de las direcciones del pad`, pero sólo eso. El `pfacing` sigue cambiándose.

Si incorporo esto a este motor el gameplay mejorará bastante. Pero antes necesito distinguir `pfixct` y dividirlo en `pfixct_fire` y `pfixct_push`.

Cambiar `TURRET_FRAMES` por `PUSHING_FRAMES` y `FIRING_FRAMES`.

~~ 

Done!

20180112
========

Sigo dispersísimo y, por tanto, avanzando de forma muy lenta. Queda realmente poco, pero igualmente quedan apenas 19 días y aún no tengo ni música.

Quiero revisar una vez más el tema de la física en estado pholed. Por lo pronto, he introducido que en modo pholed, la colisión sea contra tiles que no sean agujeros, por lo que lo suyo sería no frenar tan drásticamente la aceleración.

Para salvar la perspectiva, cuando la dirección es vertical positiva, debería haber un boost. El que hay es perfecto.

El resto de las direcciones las voy a revisar justo ahora a ver qué hacen.

Vaya, lo que se hace es cambiar pvx y pvy por el valor de las constantes `PLAYER_V_INERTIA_X` y `PLAYER_V_INERTIA_Y` con el signo correcto.

```c
    #define PLAYER_V_INERTIA_X              4
    #define PLAYER_V_INERTIA_Y              32
```

Esto lo puse para que el jugador no se saliese de pozos pequeños horizontalmente.

Ahora que los bordes del pozo deberían pararte, creo que no tiene sentido que X sea tan pequeño.

Probemos.

Meh, queda lo suficientemente bien.

~~

20180130
========

RECTA FINALW.

Todo:

[ ] Ingame 4, seguramente pillada de la nieve de Jill.
[X] Dibujo para el final.
[X] Montar title, intro, final.
[X] Implementar el tipo SKULL de los hotspots, que lo había pillado mal: Revive TODOS los enemigos.

20180131
========

To test:
[ ] Final de la fase final (tocar a Cheril).
[ ] Principio a fin (aunque sea fumándome los niveles).
[ ] Los SKULL funcionan.

To do:
[ ] Pasar Jill nieve -> Ingame 4.
[ ] Pasar música murcia -> Title.
