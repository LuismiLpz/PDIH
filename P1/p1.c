#include <stdio.h>
#include <dos.h>
#define BYTE unsigned char
BYTE MODOTEXTOGRANDE = 1;
BYTE MODOTEXTO =	3;
BYTE MODOGRAFICO = 4;
BYTE colortexto = 0;
BYTE colorfondo = 15;

//coloca el cursor en una posición determinada X,Y
void gotoxy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.dl = x;
	inregs.h.dh = y;
	inregs.h.bh = 0;
	inregs.h.ah = 2;
	int86(0x10, &inregs, &outregs);	
}
void setcursortype(int modo){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(modo){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
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
void textcolor(int ncolor){
	colortexto = ncolor;
}
void textbackground(int ncolor){
	colorfondo = ncolor;
}

void cputchar(unsigned char c){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;
	inregs.h.bl = colorfondo<<4 | colortexto;
	inregs.h.bh = 0;
	inregs.x.cx = 1;
	int86(0x10, &inregs, &outregs);
}
void getche(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
}
void mi_pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}
void pixel(int x, int y, BYTE C){
   union REGS inregs, outregs;
   inregs.x.cx = x;
   inregs.x.dx = y;
   inregs.h.al = C;
   inregs.h.ah = 0x0C;
   int86(0x10, &inregs, &outregs);
}
void clscr(){
	setvideomode(MODOGRAFICO);
	setvideomode(MODOTEXTO);
}
void recuadro(int x1, int y1, int x2,int  y2, int c1, BYTE c2){
	int i;
	int j;
	int k;
	int l;
	textbackground(c1);
	for(i=x1; i<=x2;i++){
		gotoxy(i,y1);
		cputchar(' ');
		gotoxy(i,y2);
		cputchar(' ');
	}
	for(i=y1; i<=y2;i++){
		gotoxy(x1,i);
		cputchar(' ');
		gotoxy(x2,i);
		cputchar(' ');
	}
	textbackground(c2);
	for(k=(x1+1);k<x2;k++){
		for(l=(y1+1);l<y2;l++){
			gotoxy(k,l);
			cputchar(' ');
		}
	}

}
void dibujo(){
	int i;
	int j;
	int k;
	int l;
	setvideomode(MODOGRAFICO);
	//P
	for (i=0;i < 30; i++){
		pixel(10,i+10,1);
	}
	for(j=0;j<15;j++){
		pixel(j+11,10,1);
		pixel(j+11,24,1);
	}
	for(k=0;k<13;k++){
		pixel(26,k+11,1);
	}
	//D
	for (i=0;i < 30; i++){
		pixel(30,i+10,2);
	}
	for(j=0;j<15;j++){
		pixel(j+31,10,2);
		pixel(j+31,39,2);
	}
	pixel(46,11,2);
	pixel(47,12,2);
	pixel(46,38,2);
	pixel(47,37,2);
	for(j=0;j<24;j++){
		pixel(48,j+13,2);
	}
	//I
	for (i=0;i < 30; i++){
		pixel(58,i+10,3);
	}
	for(j=0;j<15;j++){
		pixel(j+51,10,3);
		pixel(j+51,39,3);
	}
	//H
	for (i=0;i < 30; i++){
		pixel(68,i+10,1);
		pixel(83,i+10,1);
	}
	for(j=0;j<14;j++){
		pixel(j+69,25,1);
	}
}
int main(){
	int modo;
	printf("\nVisualizacion del cursor modo grueso:");
	setcursortype(2);
   mi_pausa();
   printf("\nVolviendo a modo cursor normal.");
   setcursortype(1);
   mi_pausa();
   setvideomode(MODOGRAFICO);
   printf("\nModo grafico:");
   mi_pausa();
   setvideomode(MODOTEXTOGRANDE);
   printf("\nModo texto grande:");
   mi_pausa();
   setvideomode(MODOTEXTO);
   printf("\nModo texto normal:"); 
   mi_pausa();
   modo = getvideomode();
   printf("\nModo de video actual: %d",modo);
   mi_pausa();
   printf("\nPrueba de colores:\n");
   textcolor(3);
   textbackground(7);
   cputchar('A');
   mi_pausa();
   printf("\nIntroduce un caracter:\n");
   getche();
  	printf("\nColocando el cursor en la posicion 30,10");
  	gotoxy(30,20);
  	mi_pausa();
  	printf("\nNueva posicion.");
	mi_pausa();
	clscr();
	recuadro(1,1,10,10,2,5);
	mi_pausa();
	dibujo();
	mi_pausa();
	setvideomode(MODOTEXTO);
	return 0;
}