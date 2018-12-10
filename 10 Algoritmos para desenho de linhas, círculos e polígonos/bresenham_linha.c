#include <stdio.h>

void desenhaPixel(int x, int y){
    printf("(%d),(%d)\n", x, y);
}

int main (void){

    int x1, x2, y1, y2, p, dx, dy, incrementoX, incrementoY;

    printf("Informe o x1 e y1: ");
    scanf("%d %d", &x1, &y1);
    printf("Informe o x2 e y2: ");
    scanf("%d %d", &x2, &y2);

    dx = x2-x1;
    dy = y2-y1;

    incrementoY = 2*dy;
    incrementoX = 2*dx;

    desenhaPixel(x1,y1);

    p = (incrementoY)-dx;

    while(x1<x2){
        if(p<0){
            p = p + incrementoY;
            x1 = x1 + 1;
        }
        else{
            p = p + incrementoY - incrementoX;
            x1 = x1 + 1;
            y1 = y1 + 1;
        }
        desenhaPixel(x1,y1);
    }
    return 0;
}


