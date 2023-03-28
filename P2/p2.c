#include <ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#define DELAY 50000
bool parada(int xb, int yb, int xp, int yp);
int main(){
	int rows, cols;
	bool seguir = true;
	int x = 40, y = 12;
 	int max_y = 25, max_x = 80;
 	int next_x = 0;
 	int directionx = 1;
 	int next_y = 0;
 	int directiony = 1;
 	int prev_y= 10;
 	int prev_yd= 10;
 	int gol_p1 =0, gol_p2 = 0;
 	int xc = 0, yc = 10;
 	int xcd =80 , ycd = 10;
	int ch = 0;
	char golchar[20],golchar2[20];

	initscr();
 	noecho();
 	do{
 		ch = ' ';
 		gol_p1 = 0;
 		gol_p2 = 0;
        sprintf(golchar,"%d",gol_p1);
        sprintf(golchar2,"%d",gol_p2);
 		seguir = true;
 	if (has_colors() == FALSE) {
    	endwin();
    	printf("Your terminal does not support color\n");
    	exit(1);
	}

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3,COLOR_WHITE,COLOR_BLUE);
    clear();

    refresh();
    getmaxyx(stdscr, rows, cols); 

    WINDOW *window = newwin(rows,cols,0,0);
    wbkgd(window, COLOR_PAIR(2));
    box(window, '|', '-'); 

    mvwprintw(window, 1, 1, "Juego realizado por Luis Miguel López López");
    mvwprintw(window, 2, 1, "github: @LuismiLpz");
    mvwprintw(window, 3, 1, "Controles pala izquierda: w para subir,s para bajar");
    mvwprintw(window, 4, 1, "Controles pala derecha: UPARROW para subir,DOWNARROW para bajar");
    mvwprintw(window, 10, 30, "El primero en llegar a 9 gana.");
    mvwprintw(window, 11, 11, "Pulse cualquier tecla para iniciar y q para salir del juego.");
    wrefresh(window);

    ch = getch(); 
    if (ch == 'q')
    {
        seguir = false;
    }
 //Juego	
 	cbreak();
 	keypad(stdscr, TRUE);
 	curs_set(FALSE);
 	nodelay(stdscr, TRUE);

 	while(seguir){
 		clear();
 		//pelota
 		mvprintw(y, x, "o");
 		//pala izquierda
 		mvprintw(yc, xc, "|");
 		mvprintw(yc-1, xc, "|");
 		mvprintw(yc-2, xc, "|");
 		mvprintw(yc+1, xc, "|");
 		mvprintw(yc+2, xc, "|");
 		//pala derecha
 		mvprintw(ycd, xcd, "|");
 		mvprintw(ycd-1, xcd, "|");
 		mvprintw(ycd-2, xcd, "|");
 		mvprintw(ycd+1, xcd, "|");
 		mvprintw(ycd+2, xcd, "|");
 		//Marcador
 		sprintf(golchar,"%d",gol_p1);
 		mvprintw(0,35,golchar);
 		sprintf(golchar2,"%d",gol_p2);
 		mvprintw(0,45,golchar2);
 		for(int i = 0; i<max_y;i++)
 			mvprintw(i, 40, "|");
 		refresh();
 		ch = getch();
 		switch(ch){
 			case 'w':
          		yc -= 1;
          		break;
          	case 's':
          		yc += 1;
          		break;
          	case KEY_UP:
          		ycd -= 1;
          		break;
 			case KEY_DOWN:
 				ycd += 1;
 				break;
 			case 'q':
 				seguir = false;
 				break;
		}
 		usleep(DELAY);

 		next_x = x + directionx;
 		next_y = y + directiony;

 		if(parada(xcd,ycd,next_x,next_y)) {
 			directionx*=-1;
 			x+= directionx;
 		} else if (next_x >= max_x) {
 			gol_p1+= 1;
 			x = 40;
 			y = 12;
 			directionx *= -1;
 		} else if(parada(xc,yc,next_x,next_y)){
 			directionx*=-1;
 			x+= directionx;
 		} else if(next_x < 0){
 			gol_p2 += 1;
 			x = 40;
 			y= 12;
 			directionx *= -1;
 		} else
 			x+= directionx;

 		if (next_y >= max_y || next_y < 0) {
 			directiony*= -1;
 		} else {
 			y+= directiony;
 		}
 		if(yc > max_y-3 || yc < 2)
 			yc = prev_y;
 		else
 			prev_y = yc;
 		if(ycd > max_y-3 || ycd < 2)
 			ycd = prev_yd;
 		else
 			prev_yd = ycd;
 		if(gol_p1 > 9 || gol_p2 > 9)
 			seguir = false;
 	}
 	//Fin del juego
 	nodelay(stdscr, FALSE);
 	WINDOW *window2 = newwin(rows,cols,0,0);
 	wbkgd(window2, COLOR_PAIR(2));
    box(window2, '|', '-'); 

    mvwprintw(window2, 1, 10, "Resultado Jugador 1:	");
    mvwprintw(window2, 1, 31, golchar);
    mvwprintw(window2, 5, 10, "Resultado Jugador 2:	");
    mvwprintw(window2, 5, 31, golchar2);
    if(gol_p1>gol_p2){
    	mvwprintw(window2, 10, 10, "Ha ganado el jugador 1. ¡Felicidades!");
    }else if(gol_p2 > gol_p1){
    	mvwprintw(window2, 10, 10, "Ha ganado el jugador 2. ¡Felicidades!");
    }else{
    	mvwprintw(window2, 10, 10, "La partida ha terminado en empate.");
    }
    mvwprintw(window2, 20, 10, "Fin del Juego. Pulse q para salir u otra tecla para volver a empezar.");
    wrefresh(window2);
    ch = getch();
    }while(ch!='q');
    

    getch(); 

    getch(); 
	endwin();
	return 0;
}
//Devuelve si las coordenadas de la pelota coinciden con las de algun segmento de la barra o no.
bool parada(int xb, int yb, int xp, int yp){

	return(
		((yb == yp)||
		((yb+1) == yp)||
		((yb+2) == yp)|| 
		((yb-1) == yp)||
		((yb-2) == yp))&&(xb==xp));
}