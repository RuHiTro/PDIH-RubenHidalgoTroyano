//Autores:
//RUB…N HIDALGO TROYANO
//MARÕA MEGÕAS MOYANO


#include <stdio.h>
#include <dos.h>
#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;

void mi_pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

int mi_getchar(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}

void mi_putchar(char c){
	 union REGS inregs, outregs;

	 inregs.h.ah = 2;
	 inregs.h.dl = c;
	 int86(0x21, &inregs, &outregs);
}

void setcursortype(int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
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

void mi_modo_video(unsigned char modo){
	union REGS inregs, outregs; 
	inregs.h.ah = 0x00; 
	inregs.h.al = modo; 
	int86(0x10,&inregs,&outregs); 
	return;
}

unsigned char mi_get_modo_video() {
    union REGS inregs, outregs;

    inregs.h.ah = 0x0F;
    int86(0x10, &inregs, &outregs);

    return outregs.h.al;
}

void imprimir_modo_video(unsigned char modo_video) {
    switch (modo_video) {
        case 0x01:
            printf("Modo de video: 40x25\n");
            break;
        case 0x03:
            printf("Modo de video: 80x25\n");
            break;
        case 0x07:
            printf("Modo de video: 80x25 Blanco y Negro\n");
            break;
        case 0x13:
            printf("Modo de video: 320x200 con 256 colores\n");
            break;
        default:
            printf("Modo de video desconocido: %d\n", modo_video);
            break;
    }
}


unsigned char get_text_color() {
    union REGS inregs, outregs;
    inregs.h.ah = 0x08;
    inregs.h.bh = 0x00;
    int86(0x10, &inregs, &outregs);
    return (outregs.h.ah & 0x0F);
}


unsigned char get_text_background_color() {
    union REGS inregs, outregs;
    inregs.h.ah = 0x08; 
    inregs.h.bh = 0x00;
    int86(0x10, &inregs, &outregs);
    return (outregs.h.ah >> 4);
}


void cambiarColorTexto(int color) {
    union REGS inregs, outregs;
    

    inregs.h.ah = 0x09; 
    inregs.h.al = ' '; 
    inregs.h.bh = 0;
    inregs.h.bl = color;

    int86(0x10, &inregs, &outregs);

}

void cambiarColorFondo(int colorFondo) {
    union REGS inregs, outregs;
    
    inregs.h.ah = 0x09; 
    inregs.h.al = ' '; 
    inregs.h.bh = 0;
    inregs.h.bl = (colorFondo << 4);
    int86(0x10, &inregs, &outregs);
}

void cambiarColorTextoYFondo(int colorTexto, int colorFondo) {
    union REGS inregs, outregs;
 
    inregs.h.ah = 0x09; 
    inregs.h.al = ' '; 
    inregs.h.bh = 0;
    inregs.h.bl = (colorFondo << 4) | colorTexto;

    int86(0x10, &inregs, &outregs);
}

void restaurarColores(unsigned char color_texto_original, unsigned char color_fondo_original) {
    cambiarColorTextoYFondo(color_texto_original, color_fondo_original);
    printf("Colores restaurados a los valores originales.\n");
}


void cputchar_color_texto(char c, int colorTexto) {
    union REGS r;
    r.h.ah = 0x09;
    r.h.al = c;
    r.h.bh = 0;
    r.h.bl = colorTexto;
    r.x.cx = 1;
    int86(0x10, &r, &r);
}


void cputchar_fondo(char c, int colorFondo) {
    union REGS r;
    r.h.ah = 0x09;
    r.h.al = c;
    r.h.bh = 0;
    r.h.bl = (colorFondo << 4) | 0x0F;
    r.x.cx = 1;
    int86(0x10, &r, &r);
}


void cputchar_color_fondo(char c, int colorTexto, int colorFondo) {
    union REGS r;
    r.h.ah = 0x09;
    r.h.al = c;
    r.h.bh = 0;
    r.h.bl = (colorFondo << 4) | (colorTexto & 0x0F);
    r.x.cx = 1;
    int86(0x10, &r, &r);
}


void gotoxy(int x, int y) {
    union REGS inregs, outregs;

    if (x < 1) x = 1;
    if (x > 80) x = 80;
    if (y < 1) y = 1;
    if (y > 25) y = 25;

    inregs.h.ah = 0x02; 
    inregs.h.bh = 0x00;
    inregs.h.dh = y - 1;
    inregs.h.dl = x - 1;

    int86(0x10, &inregs, &outregs); 
}


void clrscr() {
    union REGS inregs, outregs;

    inregs.h.ah = 0x06;
    inregs.h.al = 0;
    inregs.h.bh = 0x07;
    inregs.x.cx = 0x0000;
    inregs.x.dx = 0x184F;

    int86(0x10, &inregs, &outregs); 


    printf("Hemos borrado toda la pantalla\n");
}

void clrscr2() {
    int i;
    for (i = 0; i < 25; i++) {
        printf("\n");
    }
    printf("Hemos borrado toda la pantalla\n");
}

void go_to_posicion_correcta() {
	union REGS inregs, outregs;
    
    inregs.h.ah = 0x02;
    inregs.h.bh = 0x00;
    inregs.h.dh = 24;
    inregs.h.dl = 0;

    int86(0x10, &inregs, &outregs);


}

void mostrarColores() {
    printf("Colores disponibles (0-15):\n");
    printf("0 - Negro\n");
    printf("1 - Azul\n");
    printf("2 - Verde\n");
    printf("3 - Aqua\n");
    printf("4 - Rojo\n");
    printf("5 - Magenta\n");
    printf("6 - Amarillo\n");
    printf("7 - Blanco\n");
    printf("8 - Gris\n");
    printf("9 - Azul claro\n");
    printf("10 - Verde claro\n");
    printf("11 - Aqua claro\n");
    printf("12 - Rojo claro\n");
    printf("13 - Magenta claro\n");
    printf("14 - Amarillo claro\n");
    printf("15 - Blanco brillante\n");
}


int pedirColorFondo() {
    int colorFondo;
    printf("Introduce el color del fondo (0-15): ");
    scanf("%d", &colorFondo);

    if (colorFondo < 0) colorFondo = 0;
    if (colorFondo > 15) colorFondo = 15;
    
    return colorFondo;
}


int pedirColorTexto() {
    int colorTexto;
    printf("Introduce el color del texto (0-15): ");
    scanf("%d", &colorTexto);

    if (colorTexto < 0) colorTexto = 0;
    if (colorTexto > 15) colorTexto = 15;
    
    return colorTexto;
}

// establece el modo de v√≠deo: 3-texto, 4-gr√°fico
void modovideo(BYTE modo){
   union REGS inregs, outregs;
   inregs.h.al = modo;
   inregs.h.ah = 0x00;
   int86(0x10, &inregs, &outregs);
}

// pone un pixel en la coordenada X,Y de color C
void pixel(int x, int y, BYTE C){
   union REGS inregs, outregs;
   inregs.x.cx = x;
   inregs.x.dx = y;
   inregs.h.al = C;
   inregs.h.ah = 0x0C;
   int86(0x10, &inregs, &outregs);
}


int getX() {
    union REGS inregs, outregs;

    inregs.h.ah = 0x03;
    inregs.h.bh = 0x00;
    int86(0x10, &inregs, &outregs);

    return outregs.h.dl + 1;
}


int getY() {
    union REGS inregs, outregs;

    inregs.h.ah = 0x03;
    inregs.h.bh = 0x00;
    int86(0x10, &inregs, &outregs);

    return outregs.h.dh + 1;
}


void rectangulo_vacio(int x1, int y1, int x2, int y2, int color1, int color2) {
	int x, y;

    int colorTexto = color1;
    int colorFondo = color2;


    gotoxy(x1, y1);
    cputchar_color_fondo('+',colorTexto, colorFondo);
    for (x = x1 + 1; x < x2; x++) {
        gotoxy(x, y1);
        cputchar_color_fondo('-',colorTexto, colorFondo);
    }
    
    gotoxy(x2, y1);
    cputchar_color_fondo('+',colorTexto, colorFondo);

    for (y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y);
		cputchar_color_fondo('|',colorTexto, colorFondo);
        gotoxy(x2, y);
        cputchar_color_fondo('|',colorTexto, colorFondo);
    }

    gotoxy(x1, y2);
    cputchar_color_fondo('+',colorTexto, colorFondo);
    for (x = x1 + 1; x < x2; x++) {
        gotoxy(x, y2);
        cputchar_color_fondo('-',colorTexto, colorFondo);
    }
    gotoxy(x2, y2);
    cputchar_color_fondo('+',colorTexto, colorFondo);


}

void rectangulo_lleno(int x1, int y1, int x2, int y2, int color1, int color2) {
    int x, y;

    int colorTexto = color1;
    int colorFondo = color2;

    
    gotoxy(x1, y1);
    cputchar_color_fondo('+', colorTexto, colorFondo); 
    for (x = x1 + 1; x < x2; x++) {
        gotoxy(x, y1);
        cputchar_color_fondo('-', colorTexto, colorFondo);
    }
    gotoxy(x2, y1);
    cputchar_color_fondo('+', colorTexto, colorFondo);


    for (y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y);
        cputchar_color_fondo('|', colorTexto, colorFondo);
        for (x = x1 + 1; x < x2; x++) {
            gotoxy(x, y);
            cputchar_color_fondo(' ', colorTexto, colorFondo);
        }
        gotoxy(x2, y);
        cputchar_color_fondo('|', colorTexto, colorFondo);
    }


    gotoxy(x1, y2);
    cputchar_color_fondo('+', colorTexto, colorFondo); 
    for (x = x1 + 1; x < x2; x++) {
        gotoxy(x, y2);
        cputchar_color_fondo('-', colorTexto, colorFondo);
    }
    gotoxy(x2, y2);
    cputchar_color_fondo('+', colorTexto, colorFondo);
}


void dibujar_conejo(int base_x, int base_y) {
    gotoxy(base_x, base_y);
    printf(" (\\/) ");
    gotoxy(base_x, base_y + 1);
    printf(" (..) ");
    gotoxy(base_x, base_y + 2);
    printf("c(  ) ");
    gotoxy(base_x, base_y + 3);
    printf("  oo  ");
}

void dibujar_gato(int x, int y) {
    gotoxy(x, y);
    printf(" /\\_/\\ ");
    gotoxy(x, y + 1);
    printf("( o.o )");
    gotoxy(x, y + 2);
    printf(" > ^ < ");
}


void dibujar_pollo(int x, int y) {
    gotoxy(x, y);
    printf("  __");
    gotoxy(x, y + 1);
    printf("<(o )___");
    gotoxy(x, y + 2);
    printf(" (___/  ");
    gotoxy(x, y + 3);
    printf(" ^^     ");
}


void dibujar_bob_esponja(int x, int y) {
    gotoxy(x, y);
    printf(" +-----+ ");
    gotoxy(x, y + 1);
    printf(" | O O | ");
    gotoxy(x, y + 2);
    printf(" |  o  | ");
    gotoxy(x, y + 3);
    printf(" | '-' | ");
    gotoxy(x, y + 4);
    printf(" +-----+ ");
}

void dibujar_pez(int x, int y) {
    gotoxy(x, y);
    printf("><(((∫>");
}

void dibujar_cuadrado(int base_x, int base_y, int tamano) {
    int i, j;

    for (i = base_x; i < base_x + tamano; i++) {
        for (j = base_y; j < base_y + tamano; j++) {
            pixel(i, j, 2);
        }
    }
}

void dibujar_rombo(int cx, int cy, int tamano) {
    int i, j;
    for (i = -tamano; i <= tamano; i++) {
        for (j = -tamano; j <= tamano; j++) {
            if (abs(i) + abs(j) <= tamano) { 
                pixel(cx + i, cy + j, 1);
            }
        }
    }
}





int main(){
	unsigned char modo_video;
	unsigned char color_texto_original, color_fondo_original;
	int color_fondo, color_texto;
	int tmp;
	int x, y;
	int xx, yy;
	int i;
	int x1, y1, x2, y2, auxiliar;

	printf("\nPulsa una tecla...  ");
	tmp = mi_getchar();

	printf("\nHas pulsado: ");
    mi_putchar( (char)tmp );

	printf("\nCursor invisible: ");
   	setcursortype(0);
   	mi_pausa();
   	printf("\nCursor grueso: ");
   	setcursortype(2);
   	mi_pausa();
   	printf("\nCursor normal: ");
   	setcursortype(1);
   	mi_pausa();
   	
   	
   	mi_modo_video(1);  
    printf("\nEn C. Pulsa una tecla...  ");

    modo_video = mi_get_modo_video();

    imprimir_modo_video(modo_video);

    mi_pausa();

    mi_modo_video(3);

    imprimir_modo_video(mi_get_modo_video());
    
    printf("\nEn C. Pulsa una tecla...\n");

    mi_pausa();

    color_texto_original = get_text_color();
    color_fondo_original = get_text_background_color();

 
    printf("Color de TEXTO actual: %d\n", color_texto_original);
    printf("Color de FONDO actual: %d\n", color_fondo_original);
    mi_pausa();
	


    cambiarColorTexto(4);
    printf("Texto en color rojo\n");
    mi_pausa();
    color_texto = get_text_color();
    color_fondo = get_text_background_color();
    printf("Color de TEXTO actual: %d\n", color_texto);
    printf("Color de FONDO actual: %d\n", color_fondo);
    mi_pausa();
    
    cambiarColorFondo(5);
    printf("Fondo en color magenta\n");
    mi_pausa();
    color_texto = get_text_color();
    color_fondo = get_text_background_color();
    printf("Color de TEXTO actual: %d\n", color_texto);
    printf("Color de FONDO actual: %d\n", color_fondo);
    mi_pausa();
    
    cambiarColorTextoYFondo(9, 7);
    printf("Texto en color azul claro con fondo blanco\n");
    mi_pausa();
    color_texto = get_text_color();
    color_fondo = get_text_background_color();
    printf("Color de TEXTO actual: %d\n", color_texto);
    printf("Color de FONDO actual: %d\n", color_fondo);
    mi_pausa();
    
    restaurarColores(color_texto_original, color_fondo_original);
    mi_pausa();
    
    mostrarColores();
    color_texto = pedirColorTexto();
    mostrarColores();
    color_fondo = pedirColorFondo();
    
    cambiarColorTextoYFondo(color_texto, color_fondo);
    printf("Color y fondo seleccionados\n");
    mi_pausa();
    

    restaurarColores(color_texto_original, color_fondo_original);
    mi_pausa();
    
    
    printf("Caracter en rojo: ");
    cputchar_color_texto('R', 4);
    printf("\n");

    printf("Caracter con fondo azul: ");
    cputchar_fondo('F', 1);
    printf("\n");

    printf("Caracter amarillo sobre fondo magenta: ");
    cputchar_color_fondo('Z', 14, 5);
    printf("\n");
    mi_pausa();
    
    printf("\nPulsa una tecla...  ");
	tmp = mi_getchar();
	printf("\n");
    mostrarColores();
    color_texto = pedirColorTexto();
    mostrarColores();
    color_fondo = pedirColorFondo();
    cputchar_color_fondo(tmp, color_texto, color_fondo);
    printf("\n");
    mi_pausa();

    printf("Texto antes de borrar la pantalla...\n");
    mi_pausa();

    clrscr();

    mi_pausa();
    

    printf("Introduce la columna (1-80): ");
    scanf("%d", &x);
    printf("Introduce la fila (1-25): ");
    scanf("%d", &y);

    gotoxy(x, y);
    xx = getX();
    yy = getY();
    mi_pausa();
    printf("El cursor esta en la posicion X: %d, Y: %d.", x, y);
    mi_pausa();
    
	
	go_to_posicion_correcta();
	mi_pausa();
	printf("Regresamos a la posicion inferior izquierda\n");
	mi_pausa();
	
    
    modovideo(MODOGRAFICO);

    pixel(10,40,0);
    pixel(10,50,1);
    pixel(15,60,2);
    pixel(20,70,3);

    for(i=0; i<100; i++){
      pixel(i,i, i%4 );
    }

    mi_pausa();
    
    modovideo(MODOTEXTO);
    
    

    
    printf("Introduce las coordenadas de la esquina superior izquierda (x1, y1): ");
    scanf("%d %d", &x1, &y1);

    printf("Introduce las coordenadas de la esquina inferior derecha (x2, y2): ");
    scanf("%d %d", &x2, &y2);
    
    if(x1>x2){
    	auxiliar=x1;
    	x1=x2;
    	x2=auxiliar;
	}
	
	if(y1>y2){
    	auxiliar=y1;
    	y1=y2;
    	y2=auxiliar;
	}
	
	
	mostrarColores();
    color_texto = pedirColorTexto();
    mostrarColores();
    color_fondo = pedirColorFondo();
    
  
    rectangulo_vacio(x1, y1, x2, y2, color_texto, color_fondo);

    mi_pausa();

    go_to_posicion_correcta();
    
    clrscr2();
    
    printf("Introduce las coordenadas de la esquina superior izquierda (x1, y1): ");
    scanf("%d %d", &x1, &y1);

    printf("Introduce las coordenadas de la esquina inferior derecha (x2, y2): ");
    scanf("%d %d", &x2, &y2);
    
    if(x1>x2){
    	auxiliar=x1;
    	x1=x2;
    	x2=auxiliar;
	}
	
	if(y1>y2){
    	auxiliar=y1;
    	y1=y2;
    	y2=auxiliar;
	}
	
	mostrarColores();
    color_texto = pedirColorTexto();
    mostrarColores();
    color_fondo = pedirColorFondo();
    
    rectangulo_lleno(x1, y1, x2, y2, color_texto, color_fondo);

    mi_pausa();
    
    go_to_posicion_correcta();
    mi_pausa();
    
    clrscr2();
    
    dibujar_conejo(5, 5);
	
	go_to_posicion_correcta();
	mi_pausa();
	
	clrscr2();
	
	
	dibujar_gato(30, 2);
    dibujar_pollo(10, 10);
    dibujar_bob_esponja(40, 12);
    dibujar_pez(5, 3);
    
    go_to_posicion_correcta();
	mi_pausa();
    

	modovideo(MODOGRAFICO);

    dibujar_rombo(100, 60, 50); 
    mi_pausa();

    modovideo(MODOTEXTO);
    
    modovideo(MODOGRAFICO);

    dibujar_cuadrado(100, 50,100);
    mi_pausa();

    modovideo(MODOTEXTO);

   

    
	
	
    
	return 0;
}
