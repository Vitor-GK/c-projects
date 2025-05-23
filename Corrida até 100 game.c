#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//variáveis multiplayers
int j = 0;
int i = 0;
int jogadores[1000];
int pontos[1000];
int fim = 0;
int b = 0;
// variáveis comportamentais da máquina:
float pressa = 0.1; //pressa para ganhar; 0.1 - 0.3
float sequencia = 0; //sequência de acertos; 0.0 - 0.2
float diferenca = 0.1; //diferença de pontos; 0.0 - 0.3
float receio = 0.05; // receio de perder; 0.05-  0.2
float comportamento;

int rodada = 0; //qual o rodada o jogo está
int pontosrodada = 0; //pontos acumulados na rodada
int pj = 0; //pontos jogador
int pm = 0; //pontos máquina
int resultado = 0; //resultado sorteio
int sequenciaj = 0;
int decisao; //jogar o dado ou não

void comportamentais() {
    //valor da variável diferenca
    if(pm - pj >= 24)
    diferenca = 0.0;
    if(pm - pj == 0)
    diferenca = 0.1;
    if(pm - pj < 0 && pm - pj >= -15)
    diferenca = 0.2;
    if(pm - pj < -15)
    diferenca = 0.3;
    
    //valor da variável pressa
    if(100 - pm > 36)
    pressa = 0.1;
    if(100 - pm <= 36)
    pressa = 0.2;
    if(100 - pm <= 18)
    pressa = 0.3;
    
    //valor da variável sequência
    if(sequenciaj == 1)
    sequencia = 0.1;
    if(sequenciaj == 2)
    sequencia = 0.15;
    if(sequenciaj >= 3)
    sequencia = 0.2;
    
    //valor da variável receio
    if(2 <= rodada && rodada < 5)
    receio = 0.1;
    if(5 <= rodada && rodada < 7)
    receio = 0.15;
    if(7 <= rodada)
    receio = 0.2;
    
    comportamento = pressa + sequencia + diferenca + receio;
}
    
void aberturajogador() {
    
    printf("Você começa!\n");
    
    printf("você tem %d pontos\n", pj);
    
    printf("Para jogar os dados digite 1: \n");
    }

void aberturamaquina() {
    printf("A máquina começa!\n");
    
    printf("A Máquina tem %d pontos\n", pm);
    
}

void sorteioj() {
    
    resultado = 1 + rand() % 6;
    if(resultado == 1) { 
    pontosrodada = 0;
    decisao = 10;
    sequenciaj = 0;
    }
    if(resultado != 1) {
    pontosrodada = pontosrodada + resultado;
    sequenciaj++;
    }
    
    
    
}
void sorteiom() {
    resultado = 1 + rand() % 6;
    if(resultado == 1) { 
    pontosrodada = 0;
    decisao = 10;
    return;
    }
    if(resultado != 1) 
    pontosrodada += resultado;
}
void explicacaoj() {
    if(resultado == 1) {
    printf("Você tirou 1 e os seus pontos dessa rodada zeraram, é a vez da máquina!\n");
    printf("Você tem %d pontos\n\n", pj);
    sleep(4);
    } else {
        printf("Você tirou %d\n", resultado);
        printf("Os seus pontos nessa rodada são: %d\n", pontosrodada);
        printf("Se quiser continuar envie '1', se não quiser envie '0' e seus pontos nessa rodada serão somados ao seu total!\n");
        do {
        scanf("%d", &decisao);
        } while (decisao != 0 && decisao != 1);
    }
    
}
void explicacaojm(int i) {
    if(resultado == 1) {
    printf("Você tirou 1 e os seus pontos dessa rodada zeraram!\n");
    printf("Você tem %d pontos acumulados\n\n", pontos[i]);
    sleep(4);
    } else {
        printf("Você, jogador %d, tirou %d\n", jogadores[i], resultado);
        printf("Os seus pontos nessa rodada são: %d\n", pontosrodada);
        printf("Se quiser continuar envie '1', se não quiser envie '0' e seus pontos nessa rodada serão somados ao seu total!");
        printf("//////////////////////////////////////");
        do {
        scanf("\n%d", &decisao);
        } while (decisao != 0 && decisao != 1);
    }
    
}
void turnojogadorm() {
    for(i = 0; i < j; i++) {
        
        if (b == 1) {
            printf("Jogador %d, envie '1' para jogar\n", jogadores[i]);
            scanf("%d", &decisao);
            b = 0;
        } else if (b == 2) {
            printf("Próximo jogador, envie '1' para jogar\n");
            scanf("%d", &decisao);
            b = 0;
        }   
        pontosrodada = 0;
        sorteioj();
        explicacaojm(i);
        if(resultado == 1) {
        b = 2;
        continue;
        }
        
        if(decisao == 1) {
            while (decisao == 1){
                sorteioj();
                explicacaojm(i);
                if(resultado == 1)
                continue;
            }
        } 
        if(decisao == 0) {
            pontos[i] += pontosrodada;
            decisao = 10;
            pontosrodada = 0;
            printf("Jogador %d, agora você tem %d pontos acumulados\n\n", jogadores[i], pontos[i]);
            b = 2;
            if(resultado == 1)
            b = 2;
        }
        if(pontos[i] >= 100) {
            fim = 1;
            return;
        }
        
    }
    printf("Agora é a vez da máquina\n\n");
} 

void turnomaquina() {
    if(pj >= 100 || pm >= 100) {
    fim = 1;
    return;
    }
    printf("A máquina está pensando\n\n");
    printf("(///------)\n");
    sleep(1);
    printf("(//////---)\n");
    sleep(1);
    printf("(/////////)\n\n");
    sleep(1);
    
    pj = pontos[0];
    pontosrodada = 0;
    comportamentais();
    
    if(comportamento >= 0.8) {
        for(int i = 1; i <=3; i++) {
            sorteiom();
            printf("A máquina tirou %d\n", resultado);
            if(resultado == 1) {
                printf("Portanto, a máquina perdeu os pontos dessa rodada\n");
                printf("A máquina tem %d pontos acumulados\n\n", pm);
                pontosrodada = 0;
                return;
            } else {
                printf("A máquina somou %d pontos nessa rodada\n", pontosrodada);
            }
            printf("A máquina tem %d pontos acumulados\n\n", pm);
        }
        pm = pm + pontosrodada;    
        printf("Agora a máquina tem %d pontos acumulados\n\n", pm);
        pontosrodada = 0;
    } 
    if(0.6 <= comportamento && comportamento < 0.8) {
        for(int i = 1; i <=2; i++) {
            sorteiom();
            printf("A máquina tirou %d\n", resultado);
            if(resultado == 1) {
                printf("Portanto, a máquina perdeu os pontos dessa rodada\n");
                printf("A máquina tem %d pontos acumulados\n\n", pm);
                pontosrodada = 0;
                return;
            } else {
                printf("A máquina somou %d pontos nessa rodada\n", pontosrodada);
            }
            printf("A máquina tem %d pontos acumulados\n\n", pm);
        }
        pm = pm + pontosrodada;    
        printf("Agora a máquina tem %d pontos acumulados\n\n", pm);
        pontosrodada = 0;
    } 
    if(0.25 <= comportamento && comportamento < 0.6) {
            sorteiom();
            printf("A máquina tirou %d\n", resultado);
            if(resultado == 1) {
                printf("Portanto, a máquina perdeu os pontos dessa rodada\n");
                printf("A máquina tem %d pontos acumulados\n\n", pm);
                pontosrodada = 0;
                return;
            } else {
                printf("A máquina somou %d pontos nessa rodada\n", pontosrodada);
            }
        pm = pm + pontosrodada;    
        printf("Agora máquina tem %d pontos acumulados\n\n", pm);
        pontosrodada = 0;
    } 
    if(comportamento < 0.25) {
        printf("A máquina passou a vez\n");
        printf("A máquina tem %d pontos acumulados\n\n", pm);
        return;
    }
    pontosrodada = 0;
    sleep(4);
    b = 1;
    if(pm >= 100)
    fim = 1;
}
void turnojogador() {
    if(pj >= 100 || pm >= 100)
    return;
    
    pontosrodada = 0;
    sorteioj();
    explicacaoj();
    
    if(decisao == 1) {
        while (decisao == 1){
            sorteioj();
        explicacaoj();
        }
    } 
    if(decisao == 0) {
        pj = pj + pontosrodada;
        decisao = 10;
        pontosrodada = 0;
        printf("Você tem %d pontos acumulados\n", pj);
        printf("Agora é a vez da máquina\n\n");
        sleep(4);
    }
} 

int main() {
srand(time(NULL));
    
printf("Este é o jogo Corrida até 100!\n");
sleep(2);

printf("Quantas pessoas irão Jogar(1-1000)?\n");
scanf("%d", &j);
jogadores[j];
pontos[j];

for(i = 0; i < j; i++) {
pontos[i] = 0;
jogadores[i] = i + 1;
}

sleep(2);

if(j == 1) {

printf("Primeiramente, iremos decidir quem começará jogando os dados, você ou a máquina:\n\n");
sleep(2);
printf("Mas antes, duas observação: a sua primeira jogada, após o turno da máquina, é automática para maior fluidez do jogo. Também, espere o tempo da máquina pensar \ne enviar os textos antes de mandar sua decisão no chat. Bom jogo!!!\n\n");
    sleep(6);
if(rand() % 2 == 0) {
    aberturajogador();

scanf("%d", &decisao);
while(decisao != 1) {
    printf("Digite '1' para jogar\n");
    scanf("%d", &decisao);
}
while(pj < 100 && pm < 100) {
    rodada++;
    turnojogador();
    turnomaquina();
    sequenciaj = 0;
    }
} else {
    aberturamaquina();
    while(pj < 100 && pm < 100) {
    rodada++;
    turnomaquina();
    sequenciaj = 0;
    turnojogador();
    }
}
if(pj >= 100)
printf("Parabéns, você venceu!!!\n");
else
printf("A máquina vence!!!\n");

//código para o multiplayer    
} else {
    printf("Ok, %d pessoas irão jogar.\n", j);
    printf("A ordem das jogadas é do jogador 1 ao %d, vocês escolhem quais jogadores querem ser e, após todos jogadores jogarem, é a vez da máquina.\n", j);
    printf("Jogador 1, digite '1' para lançar os dados!\n");

    scanf("%d", &decisao);
    while(decisao != 1) {
    printf("Digite '1' para jogar\n");
    scanf("%d", &decisao);
}
b = 0;
if(decisao == 1) {
    while(1 != 2) {
        rodada++;
        turnojogadorm();
        if(fim)
        break; 
        
        turnomaquina();
        sequenciaj = 0;
        if(fim)
        break;
    }
  }
  for(int k = 0; k <= j; k++) {
      if(pontos[k] >= 100)
      printf("Parabéns jogador %d, você venceu!!!", jogadores[k]);
  }
  if(pm >= 100)
  printf("A máquina vence!");
}
    return 0;
}