#include <stdio.h>
#include <time.h>

#define N 100000000

#define fim_string -1
#define AP -2 //Abre Parenteses
#define FP -3 //Fecha Parenteses
#define I -4
#define F -5
#define K -6
#define D -7
#define B -8
#define S -9
#define C -10
#define E -11
#define Y -12

#define sum -13
#define sub -14
#define mul -15
#define lt -16

#define True -17
#define False -18


/*
 i
 f
 k
 d
 b
 s
 c
 e
 y
 */

/*
 * Entrada
 */
static int entrada[N] = {S, AP, K, AP, S, I, I, FP, FP, AP, S, AP, S, AP, K, S, FP, K, FP, AP, K, AP, S, I, I, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 2, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, lt, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, 1, FP, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, K, K, FP, I, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 1, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, sub, FP, FP, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, mul, FP, FP, FP, FP, 5, fim_string};

static int saida[N];

void printar_array(unsigned int *array1) {
   int i;
   unsigned int fimString = -1;
   for(i = 0;array1[i] != fimString;i++){
       switch (array1[i]){
            case AP:
               printf("(");
               break;
            case I:
                printf("I");
                break;
            case F:
                printf("F");
                break;
            case K:
                printf("K");
                break;
            case D:
                printf("D");
                break;
            case B:
                printf("B");
                break;
            case S:
                printf("S");
                break;
            case C:
                printf("C");
                break;
            case E:
                printf("E");
                break;
            case Y:
                printf("Y");
                break;
            case sum:
                printf("+");
                break;
            case sub:
                printf("-");
                break;
            case mul:
                printf("*");
                break;
            case lt:
                printf("<");
                break;
            case True:
                printf("True");
                break;
            case False:
                printf("False");
                break;
            case FP:
               printf(")");
               break;
            case fim_string:
                break;
            default:
               printf("%u ", array1[i]);
       }
   }
   printf("\n");
}

/*
 * Remove o parenteses da posição 0 e seu oposto
 */

void remove_parenteses(int *array1){
    int p = 0;
    int paren = 1;
    while (paren) {
        array1[p] = array1[p+1];
        p++;
        if(array1[p] == AP){
            paren++;
        }else if(array1[p] == FP){
            paren--;
        }
    }
    p--;
    while(array1[p+1] != fim_string && array1[p+2] != fim_string){
        array1[p] = array1[p+2];
        p++;
    }
    array1[p] = fim_string;
}

/*
 * Procura o fim do conjunto de inteiros
 */
void casa_parenteses(int* array1, int* p) {
    int paren = 1;
    int a = *p;
    while (paren) {
        unsigned int c  = array1[a];
        if(c == AP){
            paren++;
        }else if(c == FP){
            paren--;
        }
        a++;
    }
    *p = a;
}

/*
 * Verifica se a posicao do array é um inteiro ou um conjunto de inteiros
 */
void acha_argumento(int *array1, int *p){
    int c = (*p)++;
    if (array1[c] == AP) {
        casa_parenteses(array1,p);
    }
}

/*
 * Kab = a
 */

void reduz_K(int* array1, int* array2) {
    int a, nA;
    int n = 1;

    a = n;
    acha_argumento(array1,&n);

    nA = n-1;
    acha_argumento(array1,&n);

    int k = 0;
    int i;

    for (i = a; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * Sabc = ac(bc)
 */
void reduz_S(int *array1, int *array2) {
    int a, nA;
    int b, nB;
    int c, nC;
    int n = 1;
    a = n;
    acha_argumento(array1,&n);
    nA = n-1;
    b = n;
    acha_argumento(array1,&n);
    nB = n-1;
    c = n;
    acha_argumento(array1,&n);
    nC = n-1;

    int k = 0;
    int i;

    for (i = a; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = c; i <= nC; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = b; i <= nB; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = c; i <= nC; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = FP;
    k++;
    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

void reduz_I(int* array1, int* array2) {
    int a, nA;
    int n = 1;

    a = n;
    acha_argumento(array1,&n);
    nA = n-1;

    //I a => a
    int k = 0;
    int i;
    for (i = a; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}
/*
 * B f g x => f (g x)
 */
void reduz_B(int* array1, int* array2) {
    int f, nF;
    int g, nG;
    int x, nX;
    int n = 1;
    f = n;
    acha_argumento(array1,&n);
    nF = n-1;
    g = n;
    acha_argumento(array1,&n);
    nG = n-1;
    x = n;
    acha_argumento(array1,&n);
    nX = n-1;
    int k = 0;
    int i;
    for (i = f; i <= nF; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = AP;
    k++;
    for (i = g; i <= nG; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = x; i <= nX; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = FP;
    k++;
    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * C: C f g x => f x g
 */
void reduz_C(int* array1, int* array2) {
    int f, nF;
    int g, nG;
    int x, nX;
    int n = 1;
    f = n;
    acha_argumento(array1,&n);
    nF = n-1;
    g = n;
    acha_argumento(array1,&n);
    nG = n-1;
    x = n;
    acha_argumento(array1,&n);
    nX = n-1;
    int k = 0;
    int i;
    for (i = f; i <= nF; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = x; i <= nX; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = g; i <= nG; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}


/*
 * S1: S1 c f g x => c (f x) (g x)
 */

void reduz_S1(int* array1, int* array2) {
    int c, nC;
    int f, nF;
    int g, nG;
    int x, nX;
    int n = 1;
    c = n;
    acha_argumento(array1,&n);
    nC = n-1;
    f = n;
    acha_argumento(array1,&n);
    nF = n-1;
    g = n;
    acha_argumento(array1,&n);
    nG = n-1;
    x = n;
    acha_argumento(array1,&n);
    nX = n-1;
    int k = 0;
    int i;
    for (i = c; i <= nC; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = AP;
    k++;
    for (i = f; i <= nF; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = x; i <= nX; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = FP;
    k++;
    array2[k] = AP;
    k++;
    for (i = g; i <= nG; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = x; i <= nX; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = FP;
    k++;
    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * B1: B1 c f g x => c f (g x)
 */

void reduz_B1(int* array1, int* array2) {
    int c, nC;
    int f, nF;
    int g, nG;
    int x, nX;
    int n = 1;
    c = n;
    acha_argumento(array1,&n);
    nC = n-1;
    f = n;
    acha_argumento(array1,&n);
    nF = n-1;
    g = n;
    acha_argumento(array1,&n);
    nG = n-1;
    x = n;
    acha_argumento(array1,&n);
    nX = n-1;
    int k = 0;
    int i;
    for (i = c; i <= nC; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = f; i <= nF; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = AP;
    k++;
    for (i = g; i <= nG; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = x; i <= nX; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = FP;
    k++;
    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * C1: C1 c f g x => c (f x) g
 */

void reduz_C1(int* array1, int* array2) {
    int c, nC;
    int f, nF;
    int g, nG;
    int x, nX;
    int n = 1;
    c = n;
    acha_argumento(array1,&n);
    nC = n-1;
    f = n;
    acha_argumento(array1,&n);
    nF = n-1;
    g = n;
    acha_argumento(array1,&n);
    nG = n-1;
    x = n;
    acha_argumento(array1,&n);
    nX = n-1;
    int k = 0;
    int i;
    for (i = c; i <= nC; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = AP;
    k++;
    for (i = f; i <= nF; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = x; i <= nX; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = FP;
    k++;
    for (i = g; i <= nG; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * Y: Y x => x (Y x)
 */

void reduzY(int* array1, int* array2) {
    int x, nX;
    int n = 1;
    x = n;
    acha_argumento(array1,&n);
    nX = n-1;
    int k = 0;
    int i;
    for (i = x; i <= nX; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = AP;
    k++;
    for (i = x; i <= nX; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = FP;
    k++;
    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}


/*
 * + a b => a + b
 */
void reduzSum(int* array1, int* array2) {
    array2[0] = array1[1] + array1[2];
    int i = 3, k = 1;
    for (; array1[i] != fim_string; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * - a b => a - b
 */
void reduzSub(int* array1, int* array2){
    array2[0] = array1[1] - array1[2];
    int i = 3, k = 1;
    for (; array1[i] != fim_string; i++){
        array2[k] = array1[i];
        k++;
    }
    array2[k] = fim_string;
}
/*
 * * a b => a * b
 */
void reduzMul(int* array1, int* array2) {
    array2[0] = array1[1] * array1[2];
    int i = 3, k = 1;
    for (; array1[i] != fim_string; i++){
        array2[k] = array1[i];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * < a b => T
 */
void reduzlt(int *array1, int *array2) {
    array2[0] = array1[1] < array1[2] ? True : False;
    int i = 3, k = 1;
    for (; array1[i] != fim_string; i++){
        array2[k] = array1[i];
        k++;
    }
    array2[k] = fim_string;
}

/*
 * T a b => a
 */
void reduzT(int* array1, int* array2) {
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1,&n);

    nA = n-1;
    acha_argumento(array1,&n);

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * F a b => b
 */
void reduzF(int* array1, int* array2) {
    int A, nA;
    int BB, nBB;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    BB = n;
    acha_argumento(array1,&n);
    nBB = n-1;

    int k = 0;
    int i;

    for (i = BB; i <= nBB; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

int main(){
    int *array1, *array2, *array3;
    array1 = entrada;
    array2 = saida;
    while(array1[1] != fim_string){
        switch (array1[0]){
            case AP:
                remove_parenteses(array1);
                array2[0] = fim_string;
                break;
            case I:
                reduz_I(array1,array2);
                break;
            case F:
                reduz_C1(array1,array2);
                break;
            case K:
                reduz_K(array1,array2);
                break;
            case D:
                reduz_S1(array1,array2);
                break;
            case B:
                reduz_B(array1,array2);
                break;
            case S:
                reduz_S(array1,array2);
                break;
            case C:
                reduz_C(array1,array2);
                break;
            case E:
                reduz_B1(array1,array2);
                break;
            case Y:
                reduzY(array1,array2);
                break;
            case sum:
                reduzSum(array1,array2);
                break;
            case sub:
                reduzSub(array1,array2);
                break;
            case mul:
                reduzMul(array1,array2);
                break;
            case lt:
                reduzlt(array1,array2);
                break;
            case True:
                reduzT(array1,array2);
                break;
            case False:
                reduzF(array1,array2);
                break;
            default:
                break;
        }
        array3 = array1;
        array1 = array2;
        array2 = array3;
    }
    printar_array(array1);
    float clks = CLOCKS_PER_SEC;
    printf("\nTempo = %f", (clock()/clks));
    return 0;
}