#include<stdio.h>
#include<dos.h>

int getcha(){
	union REGS inregs, outregs;
	int caracter;
	inregs.h.ah = 1;
	int86(0x21,&inregs,&outregs);
	caracter = outregs.h.al;
	return caracter;
}
void putcha(int caracter){
	union REGS inregs, outregs;
	inregs.h.ah=0x09;
	inregs.h.al=caracter;
	int86(0x10,&inregs,&outregs);
}
void mi_pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}
void setvideomode(int modo){
	union REGS inregs,outregs;
	inregs.h.al = modo;
	inregs.h.ah = 0;
	int86(0x10, &inregs, &outregs);
}
int getvideomode(){
	union REGS inregs, outregs;
	int modo;
	inregs.h.ah= 15;
	int86(0x10,&inregs,&outregs);
	modo = outregs.h.al;
	return modo;
}
int main(){
	int modo;
	int tmp;
	modo = getvideomode();
   	printf("\nModo de video actual: %d",modo);
   	mi_pausa();
   	setvideomode(4);
   	modo = getvideomode();
   	printf("\nModo de video actual: %d",modo);
   	mi_pausa();
   	setvideomode(3);
	printf("\nPulsa una tecla: ");
	tmp = getcha();
	printf("\nTecla pulsada: ");
	putchar(tmp);
	mi_pausa();
	return 0;
}