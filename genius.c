//PROTOTI

int Leds[3] = {8, 9, 10};; // FAZENDO UM VETOR PARA DECLARAR OS LEDS

int Botoes[3] ={ 2, 3, 4}; // FAZENDO UM VETOR PARA DECLARAR OS BOTOES

int sequencia[100]= {}; //SEQUENCIA DE JOGDAS
int rodadaatual=0; //VERIFICA QUAL JOGADA O JOGO ESTA, A CADA RODADA QUE PASSA O JOGO AUMENTA UMA DIFICULDADE

int game_over= false; //VARIAVEL PARA VERIFICAR SE O JOGO TERMINOU 
int passo_sequencia=0; //ESSA VARIAVEL É UMA AUXILIAR PARA QUAL PASSO O JOGADOR ESTSA

int botao_pressionado = 0; //VERIFICA SE O BOTAO FOI PRESSIONADO 

void setup()  
{  
  for (int i = 0; i <= 2; i++) {
    pinMode(Leds[i], OUTPUT);
  } //DECLARANDO OS LEDS
  for (int i = 0; i <= 2; i++) {
    pinMode(Botoes[i], INPUT);
  } //DECLARANDO BOTAO 
  pinMode(5,OUTPUT);
  Serial.begin(9600); //INICIALIZANDO A SERIAL PARA COMUNICAÇÃO COM O USUARIO DO JOGO, PLANO É MOSTRAR NO DISPLAY
}  

void proximaRodada() {

  int numero_sorteado = random(0, 3); //SORTEANDO UM NUMERO ALEATORII 

  sequencia[rodadaatual++] = numero_sorteado;

}
void reproduzirSequencia() {
  for (int i = 0; i < rodadaatual; i++) {
    digitalWrite(Leds[sequencia[i]], HIGH);
    delay(500);
    digitalWrite(Leds[sequencia[i]], LOW);
    delay(100);
  }
}
void aguardarjogada() {
  boolean jogada_feita= false;
  while (!jogada_feita) { //ENQUANTO A JOGADA NAO FOR FEITA, OU SEJA O BOTAO NÃO FOR PRESSIONADO A JOGADA NAO FOI FEITA 
    for (int i = 0; i <= 3; i++) {
      if (digitalRead(Botoes[i]) == HIGH) {
        botao_pressionado = i;      //O BOTAO É PRECIOSNADO
        digitalWrite(Leds[i], HIGH);
        delay(300); //ASCENDO O LED QUE O BTAO FOI PRESSIONADO
        digitalWrite(5, HIGH);
        delay(200);
        digitalWrite(5, LOW);
        
        digitalWrite(Leds[i], LOW);
        jogada_feita = true; //APAGA O LED E TROCA A VARIAVEL PARA VERDADEIRA, IDENTIFICADO QUE O BOTAO FOI PRESSIONADO
      }
    }
    delay(10);
  }
}

void verificarjogada() {
  if (sequencia[passo_sequencia] != botao_pressionado) {
    for (int i = 0; i <= 3; i++) {
      digitalWrite(Leds[i], HIGH);
      delay(200);
      digitalWrite(Leds[i], LOW);
      Serial.println("GAME OVER");
    }

    game_over = true;

  }

}

void aguardajogador() {//aguarda o jogador enquanto ele nao faz 
  for (int i = 0; i < rodadaatual; i++) {
    aguardarjogada();
    verificarjogada();
    if (game_over) {
      break;
    }
    passo_sequencia++;
  }
    passo_sequencia= 0;
}

void loop()  
{  
 if (game_over) {
  int frequencia;
  float seno;
   for(int x=0;x<180;x++){
   //converte graus para radiando e depois obtém o valor do seno
   seno=(sin(x*3.1416/180));
   //gera uma frequência a partir do valor do seno
   frequencia = 2000+(int(seno*1000));
   tone(5, frequencia);
   delay(3);
   }
     noTone(5);
    int sequencia[100] = {};
    rodadaatual = 0;
    passo_sequencia = 0;
    game_over = false;
      delay(1000);

  }
  int aux;
  if (rodadaatual == 0){
  for (aux = 0;aux<3;aux++){
    digitalWrite(Leds[0], HIGH);
     digitalWrite(Leds[1], HIGH);
     digitalWrite(Leds[2], HIGH);
     delay(300);
     digitalWrite(Leds[0], LOW);
     digitalWrite(Leds[1], LOW);
     digitalWrite(Leds[2], LOW);
     delay(300);    
    }
    delay(2000);
  }
    
   proximaRodada(); //chama a proxima rodada
   reproduzirSequencia(); // reproduz a sequencia para decorar 
   aguardajogador(); //aguarda jogador apertar os botões corretors 
   delay(2000);
   
 
    
  }    