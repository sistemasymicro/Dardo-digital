//Programa de dardo digital de 5 zonas
const int A = 1;
const int B = 2;
const int C = 3;
const int D = 4;

const int zona1 = 8;
const int zona2 = 9;
const int zona3 = 10;
const int zona4 =11;
const int zona5 = 12;

const  int displayUnidades = 5;
const  int displayDecenas = 6;

int estadoZona1;
int estadoBotonAnteriorZona1;

int estadoZona2;
int estadoBotonAnteriorZona2;

int estadoZona3;
int estadoBotonAnteriorZona3;

int estadoZona4;
int estadoBotonAnteriorZona4;

int estadoZona5;
int estadoBotonAnteriorZona5;

const int tiempo = 6;
const int tiempoAntirebote =10;

int score = 0;
int unidades = 0;
int decenas = 0;

int conta = 0;  // Variable para el contador
boolean estadoAnterior = LOW;    // Estado anterior del botòn
boolean estadoActual = LOW; // Estado actual del botòn

byte inc;

void escribirBcd(byte num){
  digitalWrite(A, (num&1)==1);
  digitalWrite(B, (num&2)==2);
  digitalWrite(C, (num&4)==4);
  digitalWrite(D, (num&8)==8);
}

void setup() {
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(displayUnidades,OUTPUT);
  pinMode(displayDecenas,OUTPUT);
  
  pinMode(zona1,INPUT_PULLUP);
  pinMode(zona2,INPUT_PULLUP);
  pinMode(zona3,INPUT_PULLUP);
  pinMode(zona4,INPUT_PULLUP);
  pinMode(zona5,INPUT_PULLUP);
  
  digitalWrite(displayUnidades,HIGH);
  digitalWrite(displayDecenas,HIGH);

  inc = 0;
  score = 0;
 }
 
 //*******RUTINA ANTIREBOTE *********************************************************
boolean antiRebote  (int pin ) {
  int  contador =0;
  boolean estado;            // guarda el estado del boton 
  boolean estadoAnterior;    // guarda el ultimo estado del boton 

  do {
    estado = digitalRead (pin);
    if (estado != estadoAnterior ){  // comparamos el estado actual 
      contador = 0;
      estadoAnterior = estado;
    }
    else{
      contador = contador + 1;       // aumentamos el contador en 1
    }
    delay (1);
  }
  while (contador < tiempoAntirebote);
  return estado;
}

//************************************************************************

void habilitarUnidades(){
  escribirBcd(unidades);
  digitalWrite(displayUnidades,HIGH);
  digitalWrite(displayDecenas,LOW);
  delay(tiempo);
}  

void habilitarDecenas(){
  escribirBcd(decenas);
  digitalWrite(displayUnidades,LOW);
  digitalWrite(displayDecenas,HIGH);
  delay(tiempo);
}

void loop() {
 
 estadoZona1 = !digitalRead(zona1);
 estadoZona2 = !digitalRead(zona2);
 estadoZona3 = !digitalRead(zona3);
 estadoZona4 = !digitalRead(zona4);
 estadoZona5 = !digitalRead(zona5);

//*******************  ZONA 1 ******************************************************************
  if (estadoZona1  != estadoBotonAnteriorZona1)   {     
    //si hay cambio con respeto al estado 
    if (antiRebote (zona1))    { 
      //checamos  si esta presionado y si lo esta
      score = score + 1;
    }
  }
  
  estadoBotonAnteriorZona1 = estadoZona1;      // guardamos el estado del boton
//*******************************************************************************************

//******************** ZONA 2 ***************************************************************
  if (estadoZona2  != estadoBotonAnteriorZona2)   {     
    //si hay cambio con respeto al estado 
    if (antiRebote (zona2))    { 
      //checamos  si esta presionado y si lo esta
      score = score + 3;
    }
  }
  
  estadoBotonAnteriorZona2 = estadoZona2;      // guardamos el estado del boton
//*******************************************************************************************

//********************** ZONA 3 *************************************************************
  if (estadoZona3  != estadoBotonAnteriorZona3)   {     
    //si hay cambio con respeto al estado 
    if (antiRebote (zona3))    { 
      //checamos  si esta presionado y si lo esta
      score = score + 5;
    }
  }
  
  estadoBotonAnteriorZona3 = estadoZona3;      // guardamos el estado del boton
//*******************************************************************************************

//********************** ZONA4 **************************************************************
  if (estadoZona4  != estadoBotonAnteriorZona4)   {     
    //si hay cambio con respeto al estado 
    if (antiRebote (zona4))    { 
      //checamos  si esta presionado y si lo esta
      score = score + 7;
    }
  }
  
  estadoBotonAnteriorZona4 = estadoZona4;      // guardamos el estado del boton
//*******************************************************************************************

//************************* ZONA 5 **********************************************************
  if (estadoZona5  != estadoBotonAnteriorZona5)   {     
    //si hay cambio con respeto al estado 
    if (antiRebote (zona5))    { 
      //checamos  si esta presionado y si lo esta
      score = score + 10;
    }
  }
  
  estadoBotonAnteriorZona5 = estadoZona5;      // guardamos el estado del boton
//*******************************************************************************************
  
  decenas = score/10;  //Extraigo el dìgito de las unidades
       
  unidades=  score-( decenas*10);  //Extraigo el dìgito de las decenas
        
  
  habilitarUnidades();
  habilitarDecenas();
 
}
