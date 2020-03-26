# ProgettoPao

Questo software ha il semplice compito di fornire un interfaccia user friendly per la creazione di preventivi.
Sfrutta dei semplici file xml per la serializzazione i cataloghi di oggetti che riguardano il mondo delle stampanti (normali,
multifunzione, cartucce, ecc..)
Il software permette di caricare e visualizzare un catalogo specifico, selezionare gli oggetti che si vogliono 
acquistare/noleggiare e di indicarne la quantità.
Sia il totale acquistato che quello noleggiato, tenendo conto di prezzi e tempistiche, è possibile stamparlo informato PDF
nel quale è possibile inserire anche i dati del cliente in modo che sia esso che il fornitore possano averne una copia.

## Specifiche

Il software è stato fatto tenendo in considerazione le direttive del progetto che ci erano state assegnate ovvero:
- Creazione di un container templatizzato a nostra scelta (il più consono per questo progetto era la lista)
- Creazione di uno smart Pointer che si occupasse di fare operazioni profonde ma senza creare copie dello stesso oggetto
in caso di creazione di nuovi puntatori
- Creazione di una gerarchia leggermente profonda con almeno 2 o più classi astratte
- Utilizzo dei pattern MV o MVC (in questo caso MVC)
- Interfaccia grafica creata da zero senza i tool forniti dall'IDE utilizzato (in questo caso QT Creator)
