/*

	JJunior - 	www.jjuniorz.cjb.net
				jjuniorz@bol.com.br
				jjunior@dcc.ufrj.br


*/

/** /
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
//#include "\meusdo~1\c\mouse\mouse.c"
/**/

void janela(int x1, int y1, int x2, int y2, int cor1, int cor2, int preench, char *titulo, int cor3);
void botao(int x1, int y1, int x2, int y2, int cor1, int preench, char *titulo, int cor2);
void fundo (int cor, int preench);
/** /
void main(void)
{
   /* request auto detection * /
   int gdriver = DETECT, gmode /*,errorcode*/;

   //int cor,preench;
   //char op='X', temp[20];


   /* initialize graphics and local variables * /
   initgraph(&gdriver, &gmode, "");

   //FUNDO PADRAO
   //fundo (int cor, int preench)
   fundo(0,1);


/***** /
	while (op!='S')
	{
/***** /
		//Usuario fornece a cor e o preenchimento
		gotoxy(1,1);
		printf ("Forneca a cor (0 a 15): ");
		gets(temp);
		cor= atoi(temp) %16 ;
		gotoxy(1,2);
		printf ("Forneca o tipo de preenchimento (0 a 10): ");
		gets(temp);
		preench= atoi(temp) %12 + 1;

		//Se preench for 0 limpe a tela
		if (!preench) fundo(0,1);

		fundo (cor,preench);
/***** /
		op=toupper(getch());
	}
/***** /



   //640x480

   //janela(x1, y1, x2, y2, cor1 interna, cor2 da barra de titulo, preench, char *titulo, cor3 do titulo);
   janela(220, 100, 420, 400, 7, 9, 1, "JJOP",15);

   //botao(int x1, int y1, int x2, int y2, int cor1, int preench, char *titulo, int cor2);
   botao(260, 350, 380, 380, 7, 1, "OK",15);

   setcolor(0);
   outtextxy(225,250,"JJunior Operation System");
   outtextxy(225,260,"pelo 0800-171171! Ligue!");


   getch();
   //closegraph();
}
/**/

void fundo (int cor, int preench)
{
	int poly[8];

	//Fundo da tela 640x480
	poly[0] = 0;
	poly[1] = 0;
	poly[2] = 638;
	poly[3] = 0;
	poly[4] = 638;
	poly[5] = 478;
	poly[6] = 0;
	poly[7] = 478;

	setcolor(BLACK);
	setfillstyle(preench, cor);
	fillpoly(4, poly); //Poligono com 4 pontos (quadrado)
}


void janela(int x1, int y1, int x2, int y2, int cor1, int cor2, int preench, char *titulo, int cor3)
{
			//pontos 1 e 2, cor da janela e o tipo de preenchimento

	int poly1[8],poly2[8];

	setfillstyle(preench,cor1);

	poly1[0] = x1;
	poly1[1] = y1;

	poly1[2] = x2;
	poly1[3] = y1;

	poly1[4] = x2;
	poly1[5] = y2;

	poly1[6] = x1;
	poly1[7] = y2;

	//Poligono com contorno branco
	setcolor(WHITE);
	fillpoly(4, poly1);

	//Sombreado cinza_escuro
	setcolor(DARKGRAY);
	line(x1,y2,x2,y2);
	line(x2,y2,x2,y1);

	//Barra de cima
	setfillstyle(preench,cor2);
	x1=x1+1;
	y1=y1+1;
	x2=x2-1;
	y2=y1+20;
	poly2[0] = x1;
	poly2[1] = y1;
	poly2[2] = x2;
	poly2[3] = y1;
	poly2[4] = x2;
	poly2[5] = y2;
	poly2[6] = x1;
	poly2[7] = y2;
	setcolor(BLACK); //cor do contorno do poligono
	fillpoly(4, poly2);


	setcolor(cor3); //cor da fonte
	//Verifica se o titulo eh maior do q o espaco disponivel na janela
	if ( (strlen(titulo)*8.5) >(x2-x1) ) titulo=NULL;
	else outtextxy ((x2+x1)/2-strlen(titulo)*4,y1+6,titulo);




}

void botao(int x1, int y1, int x2, int y2, int cor1, int preench, char *titulo, int cor2)
{
			//pontos 1 e 2, cor da botao e o tipo de preenchimento

	int poly[8];

	setfillstyle(preench,cor1);

	poly[0] = x1;
	poly[1] = y1;

	poly[2] = x2;
	poly[3] = y1;

	poly[4] = x2;
	poly[5] = y2;

	poly[6] = x1;
	poly[7] = y2;

	//Poligono com contorno branco
	setcolor(WHITE);
	fillpoly(4, poly);

	//Sombreado cinza_escuro
	setcolor(DARKGRAY);
	line(x1,y2,x2,y2);
	line(x2,y2,x2,y1);

	setcolor(cor2); //cor da fonte
	//Verifica se o titulo eh maior do q o espaco disponivel na janela
	if ( (strlen(titulo)*8.5) >(x2-x1) ) titulo=NULL;
	else outtextxy ((x2+x1)/2-strlen(titulo)*4,(y2+y1)/2-3,titulo);

	/***** /
	getch();getch();

	//APERTOU O BOTAO
	//BRANCO
	setcolor(WHITE);
	line(x1,y2,x2,y2);
	line(x2,y2,x2,y1);
	//Sombreado cinza_escuro
	setcolor(DARKGRAY);
	line(x1,y2,x1,y1);
	line(x1,y1,x2,y1);

	/*****/

}