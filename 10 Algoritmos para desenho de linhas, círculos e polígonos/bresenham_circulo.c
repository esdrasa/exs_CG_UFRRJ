#include <stdio.h>


void desenhaPixel(int x, int y){
    printf("(%d),(%d)\n", x, y);
}


int main (void){

    int r, x1, y1;
    float p = 0.0;

    printf("Informe o raio: ");
    scanf("%d", &r);

    x1 = 0, y1 = r;
    p = (5.0 / 4) - r;

    desenhaPixel(x1,y1);

    while (x1 < y1) {
        if(p<0){
            x1 = x1 + 1;
            p = p + 2*x1 + 1;
        }
        else{
            x1 = x1 + 1;
            y1 = y1 - 1;
            p = p + 2*x1 + 1 - 2*y1;
        }
        desenhaPixel(x1,y1);
    }
    return 0;
}
