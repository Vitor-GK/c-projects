
#include <stdio.h>

int main()
{
    int X, Y, resultado;
    char a;

    printf("Escolha uma operação:\n");
    printf("a: Somar dois números\n");
    printf("b: Subtrair dois números\n");
    printf("c: Multiplicar dois números\n");
    printf("d: Dividir dois números\n");
    printf("Digite a opção desejada: \n");
    scanf(" %c", &a);
    
    if(a != 'a' && a != 'b' && a != 'c' && a != 'd') {
        printf("ERRO: Opção inválida. Reinício da calculadora\n");
        return 0;
        }
    switch(a) {
        
        case 'a':
        printf("digite os dois números\n");
        scanf("%d %d", &X, &Y);
        resultado = X + Y;
        printf("%d\n", resultado);
        break;
        
        case 'b':
        printf("digite os dois números\n");
        scanf("%d %d", &X, &Y);
        resultado = X - Y;
        printf("%d\n", resultado);
        break;
        
        case 'c':
        printf("digite os dois números\n");
        scanf("%d %d", &X, &Y);
        resultado = X * Y;
        printf("%d\n", resultado);
        break;
        
        case 'd':
        printf("digite os dois números\n");
        scanf("%d %d", &X, &Y);
        if(Y == 0) {
        printf("ERRO: Divisão por 0 não é permitida\n");
        return 0;
        } else {
        resultado = X / Y;
        printf("%d\n", resultado);
        break;
        }
        }

    return 0;
}
