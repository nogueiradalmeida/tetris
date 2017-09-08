/*************************************************************************** /

	Nome: TETRISJ.C
	Autor: JJunior
	Data: 21/12/1999
	Categoria: Jogo.
	Objetivo: Evitar que as pecas encham o buraco.

/***************************************************************************/

#define CLIP_ON 1
#define CHEAT 20
#define ARQ "fama.bin"
#define JOGADOR 10
#define USUARIO "Cara"
#define COR1 BLUE
#define COR2 LIGHTBLUE

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>
#include <process.h>
#include "jan.h"


int geraPeca (void);
//void printTela(char **tela);
void printTela(char **tela, int opcao,int x1, int y1, int x2, int y2);
void zeraTela (char **tela);
int geraBase (char **tela,int *base);
void fim(void);
void boneco (int x, int y, int tam, int cabeca);
int fama(char *nome, int pontos);
void leArq(char *nome, int pontos);
//void printPeca (int peca);
//void rodad(int peca);
//void peca1(int x, int y);

int pecaN (int x, int y,char **tela, int pos, char bin, int peca);

int peca1(int x, int y,char **tela, char bin);
int peca2(int x, int y,char **tela, int pos,char bin);
int peca3(int x, int y,char **tela, int pos,char bin);
int peca4(int x, int y,char **tela, int pos,char bin);
int peca5(int x, int y,char **tela, int pos,char bin);
int peca6(int x, int y,char **tela, int pos,char bin);
int peca7(int x, int y,char **tela, int pos,char bin);

void quad (int x, int y,int cord, int preench,int corf);


int abertura(void);
int menu (void);
void saindo(void);
int jogo(void);
void ajuda(void);
void creditos(void);
void solidifica(char **tela);

int tx4; //tela por 4 -tamanho do quadrado
int ty;
int contador=-5;


typedef struct famosinho
{
	char nome[JOGADOR];
	int pontos;
} Famoso;

Famoso *famoso;
Famoso lista[10];

int QUAD=20; // Era uma vez uma constante ...
int nivel=1;
int modo=0;

int main()
{
	int i;

	int gdriver=DETECT, gmode;

	//spawnl(P_WAIT,"feit.exe",NULL);

	initgraph (&gdriver, &gmode,"");

	abertura();

	//base=(int *)malloc(tx4/QUAD-2*sizeof(int));

	leArq("",NULL);

	while(1)
	{
		cleardevice();
		menu();
		tx4=getmaxx()/2;
		ty=getmaxy();
		jogo();
	}

	return 0;
}


int jogo()
{                              /**** quebraLoop1=0/**/
	int obstaculo=0, quebraLoop1=0,ultimo[2], pula=0, pos=1;
	int linhap, vaiFim=0, cheat;
	int pontos=0;
	int i,j,l,k=0,m=0;
	int peca;
	char op;
	char macete[CHEAT], *mac;
	char jogador[JOGADOR];
	//char sair;

	//char **tela; //tela[coluna][linha]
	//int *base;

	char **tela;



	//Alocando para matriz[tx4][ty]
	tela=(char **)malloc(tx4/QUAD*(sizeof(char *)));
	for(i=0;i<tx4/QUAD;i++)
	{
		tela[i]=(char *)malloc(ty/QUAD*sizeof(char));
	}

	obstaculo=0;
	quebraLoop1=0;
	pula=0;
	pos=1;
	//nivel=1;
	//sair='N';
	vaiFim=0;
	pontos=0;
	k=0,m=0;

	zeraTela(tela);

	getch();

	janela(tx4+50, 102, tx4+250, 262, 7, COR1, 1, "JJUNIOR TETRIS (R) ",15);
	botao(tx4+80, 152, tx4+220, 182, 7, 1, "NIVEL       ",15);
	botao(tx4+80, 202, tx4+220, 232, 7, 1, "PONTOS      ",15);

	gotoxy(64,11);
	printf ("%d",nivel);

	gotoxy(62,14);
	printf ("    ");
	gotoxy(62,14);
	printf ("%d", pontos);

	cheat=0;

	//cleardevice();

	//printTela(tela,1,0,0,0,0);
	//setviewport(QUAD, 1, tx4 - QUAD , ty-QUAD, CLIP_ON);

	/** /
	//BASE
	rectangle(1,ty-2*QUAD+1,tx4+1,ty-QUAD+1);

	///LATERAIS
	rectangle(1,1,QUAD-1,ty-2*QUAD+1);
	rectangle(tx4-QUAD+1,1,tx4+1,ty-2*QUAD+1);
	/**/

	//TAMANHO DA TELA DO JOGO EM SI
	//setviewport(1, 1, tx4 - QUAD + 11, ty-2*QUAD, CLIP_ON);

	//Verifica se o poco nao encheu
	while(!quebraLoop1)
	{
	//Verifica se tem alguma coluna da penultima linha preenchida
		for (i=1;i<tx4/QUAD-2;i++)
			if (tela[i][1]=='1')
				quebraLoop1=1;
		m=0;
		k=tx4/(2*QUAD);

		obstaculo=0;
		pula=0;

		peca=geraPeca();

		switch (peca)
		{
			case 1:
				pos=1;
				break;

			case 2:case 3: case 4:
				pos=rand()%2+1;
				break;

			default:
				pos=rand()%4+1;
				break;
		}

		//printTela(tela,1,0,0,0,0);
		solidifica(tela);

		if (pontos>=100*nivel && nivel<10)
		{
			nivel++;

			zeraTela(tela);

			boneco(tx4/2,getmaxy()/2,20,1);

			gotoxy(64,11);
			printf ("%d",nivel);

			sound(700);
			delay(100);
			nosound();
			sound(700);
			delay(100);
			nosound();
		}

		if (pontos>=1500 || vaiFim==1)
		{
			zeraTela(tela);
			fim();
		}

		//maior=geraBase(tela,base);

		do
		{
			//setbkcolor(WHITE);
			/** /
			gotoxy (70,10); printf ("%d",maior);
			/**DEPURA**/
		  /** /
			setviewport(QUAD+1, 0, tx4-2*QUAD , /** /maior*QUAD-1/** /ty-2*QUAD/** /, CLIP_ON);
			clearviewport();
		  /**/

			op='X';

			while (kbhit() && !pula)
					op=toupper(getch());

			switch (op)
			{
				case 'K': // <-
				/** /
					if (k>0 && tela[k-1][m]!='1') k--;
					break;
				/**/
					if (k>0)
					{
						obstaculo=pecaN (k-1, m,tela, pos, '1', peca);
						if (!obstaculo)
						{
							obstaculo=pecaN (k-1, m,tela, pos, '0', peca);
							k--;
						}
					}
					break;

				case 'M': // ->
					obstaculo=pecaN (k+1, m,tela, pos, '1', peca);
					if (!obstaculo)
					{
						obstaculo=pecaN (k+1, m,tela, pos, '0', peca);
						k++;
					}
					break;

				case 'P': // _
					m++;
					break;

				case 13: // ENTER
					outtext("          Por que parou? ");
					getch();
					break;

				case 32: //ESPACO
					pula=1;
					pontos++;
					break;

				case 'A':
					pos++;
					switch (peca)
					{
						case 1:
							pos=1;
							break;

						case 2:case 3: case 4:
							if (pos>2) pos=1;
							break;

						default:
							if (pos>4) pos=1;
							break;
					}

					obstaculo=pecaN (k, m,tela, pos, '1', peca);

					if (!obstaculo)
					{
						obstaculo=pecaN (k, m,tela, pos, '0', peca);
					}
					else
					{
						pos--;
						switch (peca)
						{
							case 1:
								pos=1;
								break;

							case 2:case 3: case 4:
								if (pos<1) pos=2;
								break;

							default:
								if (pos<1) pos=4;
								break;
						}
					}
					break;

				case 'S':
					pos--;
					switch (peca)
					{
						case 1:
							pos=1;
							break;

						case 2:case 3: case 4:
							if (pos<1) pos=2;
							break;

						default:
							if (pos<1) pos=4;
							break;

					}

					obstaculo=pecaN (k, m,tela, pos, '1', peca);

					if (!obstaculo)
					{
						obstaculo=pecaN (k, m,tela, pos, '0', peca);
					}
					else
					{
						pos++;
						switch (peca)
						{
							case 1:
								pos=1;
								break;

							case 2:case 3: case 4:
								if (pos>2) pos=1;
								break;

							default:
								if (pos>4) pos=1;
								break;
						}

					}
					break;


				case 27: //ESC 27
					setviewport(0, 0, getmaxx() , getmaxy(), CLIP_ON);
						botao(tx4, 302, tx4+300, 332, 7, 1, "Vai desistir " USUARIO "? (S/N)",1);
					op=toupper(getch());
					if (op==13 || op=='S' || op=='Y')
						{
						botao(tx4, 302, tx4+300, 332, 7, 1, "          Po, vacilo ai!         ",1);
						getch();
						//closegraph();
						//exit(1);
						return NULL;
						//saindo();
						/** /
						obstaculo=1;
						pula=1;
						quebraLoop1=1;
						paratudo=1;/**/
					}
					botao(tx4, 302, tx4+300, 332, 0, 1, " ",2);
					setcolor(BLACK);
					rectangle(tx4, 302, tx4+300, 332);
					setviewport(QUAD+1, 0, tx4-2*QUAD , /** /maior*QUAD-1/**/ty-2*QUAD/**/, CLIP_ON);
					break;

				case 59:
					setviewport(0, 0, getmaxx() , getmaxy(), CLIP_ON);
					ajuda();
					getch();
					setviewport(QUAD+1, 0, tx4-2*QUAD , /** /maior*QUAD-1/**/ty-2*QUAD/**/, CLIP_ON);
					break;


				case 'J':
					gotoxy(50,23);
					printf ("COMANDO: (ENTER) ");

					macete[0]=CHEAT-2;
					mac=cgets(macete);
					//puts(mac);

					if (strcmpi(mac,"fim")==0)
					{
						cheat=1;

						setviewport(0, 0, getmaxx() , getmaxy(), CLIP_ON);
						botao(tx4, 302, tx4+300, 332, 7, 1, " Trapaceiro!!! ",1);
						delay(1000);
						botao(tx4, 302, tx4+300, 332, 0, 1, "               ",1);
						setcolor(BLACK);
						rectangle(tx4, 302, tx4+300, 332);
						setviewport(QUAD+1, 0, tx4-2*QUAD , /** / maior*QUAD-1/**/ty-2*QUAD/**/, CLIP_ON);

						vaiFim=1;
						pula=1;

					}

					if (strcmpi(mac,"nivel")==0)
					{
						cheat=1;

						setviewport(0, 0, getmaxx() , getmaxy(), CLIP_ON);
						botao(tx4, 302, tx4+300, 332, 7, 1, " Trapaceiro!!! ",1);
						delay(1000);
						botao(tx4, 302, tx4+300, 332, 0, 1, "               ",1);
						setcolor(BLACK);
						rectangle(tx4, 302, tx4+300, 332);
						setviewport(QUAD+1, 0, tx4-2*QUAD , /** /maior*QUAD-1/**/ty-2*QUAD/**/, CLIP_ON);

						pontos=100*nivel;
						pula=1;
					}

					setcolor(COR1);
					gotoxy(50,23);
					printf ("                  ");
					break;


			}//FIM DO SWITCH(OP)



		obstaculo=pecaN (k, m,tela, pos, '1', peca);

		if (!obstaculo)
		{
			ultimo[0]=k;
			ultimo[1]=m;
		}


		//printTela(tela,2,k ,m ,k+4 ,m+4 );
		printTela(tela,1,0,0,0,0);

		//TEMPO
		if (!pula) delay(600/nivel);



		if (!obstaculo)
		obstaculo=pecaN (k, m,tela, pos, '0', peca);

		m++;

/*** /	fama("ZE",rand()%10000); /**/

		}while(!obstaculo);

		obstaculo=pecaN (k, ultimo[1],tela, pos, '1', peca);

		pontos+=1;

		//printTela(tela,2,k ,m ,k+4 ,m+4 );
		printTela(tela,1,0,0,0,0);

		//PROCURA ALGUMA LINHA PREENCHIDA
		for(j=0;j<ty/QUAD-1;j++) //VARRE LINHAS
		{
			linhap=0;
			for(i=0;i<tx4/QUAD-2;i++) //VARRE COLUNAS
				if (tela[i][j]=='1')
					linhap++;
			if (linhap==i)
			{
				pontos+=10;
				sound(100);
				delay(200);
				nosound();
				/** /
				printf ("Linha %d preenchida",j);
				getch();
				/*DEPURAR*/

				//APAGANDO LINHA 'j' PREENCHIDA
				for(l=j;l>0;l--) //VARRE LINHAS
					for(i=0;i<tx4/QUAD-2;i++) //VARRE COLUNAS
						tela[i][l]=tela[i][l-1];
			}
		}

		gotoxy(62,14);
		printf ("    ");
		gotoxy(62,14);
		printf ("%d", pontos);

	}//QUEBRALOOP1

	for(i=1;i<3;i++)
	{
		sound(i*100);
		delay(100);
		nosound();
	}

	setviewport(0, 0, getmaxx() , getmaxy(), CLIP_ON);

	//outtextxy ("  Po! Ai, vacilo! Cabou!!! ");
	if (pontos<50) botao(tx4, 302, tx4+300, 332, 7, 1, "Se morre, tu eh horrivel!!! ",1);
	else if (pontos<100) botao(tx4, 302, tx4+300, 332, 7, 1, "Voce eh parente da Carla Perez!? ",1);
	else if (pontos<150) botao(tx4, 302, tx4+300, 332, 7, 1, "Tsc Tsc!! Voce eh muito fraquinho!",1);
	else if (pontos<200) botao(tx4, 302, tx4+300, 332, 7, 1, "Ai, treina mais, falou?  ",1);
	else botao(tx4, 302, tx4+300, 332, 7, 1, "Nada mal,"USUARIO"!",1);

	boneco(tx4/2,getmaxy()/2,20,1);

	getch();
	getch();

	if (cheat)
	{
		//setviewport(0, 0, getmaxx() , getmaxy(), CLIP_ON);
		botao(tx4, 302, tx4+300, 332, 7, 1, USUARIO ", tente sem trapaca!! ",1);
		getch();
		saindo();
	}

	//CALCADA DA FAMA !!!
	cleardevice();
	janela(getmaxx()/2-150, 100, getmaxx()/2+150, 210, 7, COR1, 1, "JJUNIOR TETRIS (R) ",15);
	botao(getmaxx()/2-100, 140, getmaxx()/2+100, 190,7, 1, "Qual seu nome, campeao?",1);
	gotoxy(30,15);
	textcolor(WHITE);
	gets(jogador);
	jogador[JOGADOR-1]=NULL;
	fama(jogador,pontos);
	getch();
	getch();




	/** /
	botao(getmaxx()/2-150, 502, getmaxx()/2+150, 532, 7, 1, "Quer jogar de novo, "USUARIO "? (S/N) ",1);
	sair=toupper(getch());
	/**/

	//delay(2000);


}

int geraPeca (void)
{
	int r=0;

	srand((unsigned int)time(NULL)); //seed rand, semeia o randomico
	r=rand()%7+1;//1 + (int) (50*rand()/RAND_MAX+1.0);

	return r;

}

void quad (int x, int y,int cord, int preench,int corf)
{
	int poly[8];

	switch (modo)
	{
		case 0:
			//QUADRADO
			poly[0] = x;
			poly[1] = y;
			poly[2] = x+QUAD;
			poly[3] = y;
			poly[4] = x+QUAD;
			poly[5] = y+QUAD;
			poly[6] = x;
			poly[7] = y+QUAD;

			setcolor(corf);
			setfillstyle(preench, cord);
			fillpoly(4, poly); //Poligono com 4 pontos (quadrado)
			break;

		case 1:
			setcolor(corf);
			setfillstyle(preench, cord);
			fillellipse(x+QUAD/2,y+QUAD/2,QUAD/2,QUAD/2);
			break;
	}
}


int peca1(int x, int y,char **tela, char bin) // []
{

	if (tela[x][y]==bin ||	tela[x+1][y]==bin || tela[x][y+1]==bin || tela[x+1][y+1]==bin)
		return 1;
	else
	{
		tela[x][y]=bin;
		tela[x+1][y]=bin;
		tela[x][y+1]=bin;
		tela[x+1][y+1]=bin;
		return 0;
	}

}
/**/
int peca2(int x, int y,char **tela, int pos, char bin) // -|_
{
	switch (pos)
	{
	case 1:  // -|_
		if (tela[x][y]==bin ||	tela[x+1][y]==bin || tela[x+1][y+1]==bin || tela[x+2][y+1]==bin)
			return 1;

		else
		{
			tela[x][y]=bin;
			tela[x+1][y]=bin;
			tela[x+1][y+1]=bin;
			tela[x+2][y+1]=bin;
			return 0;
		}
		//break;


	case 2:  // _|-
		if (tela[x][y+1]==bin ||	tela[x+1][y+1]==bin || tela[x+1][y]==bin || tela[x][y+2]==bin)
			return 1;
		else
		{
			tela[x][y+1]=bin;
			tela[x+1][y+1]=bin;
			tela[x+1][y]=bin;
			tela[x][y+2]=bin;
			return 0;
		}
		//break;
	}

	return NULL;
}

int peca3(int x, int y,char **tela, int pos, char bin) // _|-
{
	switch (pos)
	{
	case 1:
	if (tela[x+2][y]==bin ||	tela[x+1][y]==bin || tela[x+1][y+1]==bin || tela[x][y+1]==bin)
			return 1;
	else
	{
		tela[x+2][y]=bin;
		tela[x+1][y]=bin;
		tela[x+1][y+1]=bin;
		tela[x][y+1]=bin;
		return 0;
	}
	//break;

	case 2:
	if (tela[x][y]==bin ||	tela[x][y+1]==bin || tela[x+1][y+1]==bin || tela[x+1][y+2]==bin)
			return 1;
	else
	{
		tela[x][y]=bin;
		tela[x][y+1]=bin;
		tela[x+1][y+1]=bin;
		tela[x+1][y+2]=bin;
		return 0;
	}
	//break;

	}
	return NULL;

}

int peca6(int x, int y,char **tela, int pos, char bin)     // L
{
	switch (pos)
	{
	case 1: //L
		/**///SE TIVER ALGUM OBSTACULO PRO PROXIMO RETORNE 1
		if (tela[x][y]==bin ||	tela[x][y+1]==bin || tela[x][y+2]==bin || tela[x+1][y+2]==bin)
			return 1;

		else
		{
			tela[x][y]=bin;
			tela[x][y+1]=bin;
			tela[x][y+2]=bin;
			tela[x+1][y+2]=bin;
			return 0;
		}
		//break;

	case 2:   // |-
		if (tela[x][y]==bin ||	tela[x+1][y]==bin || tela[x+2][y]==bin || tela[x][y+1]==bin)
			return 1;
		else
		{
			tela[x][y]=bin;
			tela[x+1][y]=bin;
			tela[x+2][y]=bin;
			tela[x][y+1]=bin;
			return 0;
		}
		//break;

	case 3:   //-|
		if (tela[x][y]==bin ||	tela[x+1][y]==bin || tela[x+1][y+1]==bin || tela[x+1][y+2]==bin)
			return 1;
		else
		{
			tela[x][y]=bin;
			tela[x+1][y]=bin;
			tela[x+1][y+1]=bin;
			tela[x+1][y+2]=bin;
			return 0;
		}
		//break;

	case 4:   //_|
		if (tela[x][y+1]==bin ||	tela[x+1][y+1]==bin || tela[x+2][y+1]==bin || tela[x+2][y]==bin)
			return 1;
		else
		{
			tela[x][y+1]=bin;
			tela[x+1][y+1]=bin;
			tela[x+2][y+1]=bin;
			tela[x+2][y]=bin;
			return 0;
		}
		//break;

	}
	return NULL;
}

int peca5(int x, int y,char **tela, int pos, char bin) // J
{
	switch(pos)
	{
	case 1:                     //J
		if (tela[x+1][y]==bin ||  tela[x+1][y+1]==bin || tela[x+1][y+2]==bin || tela[x][y+2]==bin)
			return 1;
		else
		{
			tela[x+1][y]=bin;
			tela[x+1][y+1]=bin;
			tela[x+1][y+2]=bin;
			tela[x][y+2]=bin;
			return 0;
		}
		//break;

	case 2:	   // |___
		if (tela[x][y]==bin ||  tela[x][y+1]==bin || tela[x+1][y+1]==bin || tela[x+2][y+1]==bin)
			return 1;
		else
		{
			tela[x][y]=bin;
			tela[x][y+1]=bin;
			tela[x+1][y+1]=bin;
			tela[x+2][y+1]=bin;
			return 0;
		}
		//break;

	case 3:                    // |-
		if (tela[x][y]==bin ||  tela[x][y+1]==bin || tela[x][y+2]==bin || tela[x+1][y]==bin)
			return 1;
		else
		{
			tela[x][y]=bin;
			tela[x][y+1]=bin;
			tela[x][y+2]=bin;
			tela[x+1][y]=bin;
			return 0;
		}
		//break;

	case 4:                       // ---|
		if (tela[x][y]==bin ||  tela[x+1][y]==bin || tela[x+2][y]==bin || tela[x+2][y+1]==bin)
			return 1;
		else
		{
			tela[x][y]=bin;
			tela[x+1][y]=bin;
			tela[x+2][y]=bin;
			tela[x+2][y+1]=bin;
			return 0;
		}
		//break;
	}
	return NULL;

}

int peca4(int x, int y,char **tela, int pos, char bin) // |
{
	switch (pos)
	{
		case 1: //|
		if (tela[x][y]==bin ||  tela[x][y+1]==bin || tela[x][y+2]==bin || tela[x][y+3]==bin)
			return 1;
		else
		{
			tela[x][y]=bin;
			tela[x][y+1]=bin;
			tela[x][y+2]=bin;
			tela[x][y+3]=bin;
			return 0;
		}
		//break;

		case 2: // ----
		if (tela[x][y]==bin ||  tela[x+1][y]==bin || tela[x+2][y]==bin || tela[x+3][y]==bin)
			return 1;
		else
		{
			tela[x][y]=bin;
			tela[x+1][y]=bin;
			tela[x+2][y]=bin;
			tela[x+3][y]=bin;
			return 0;
		}
		//break;

	}
	return NULL;

}
int peca7(int x, int y,char **tela, int pos, char bin)//  _|_
{
	switch (pos)
	{
		case 1: //  _|_
		if (tela[x+1][y]==bin ||  tela[x][y+1]==bin || tela[x+1][y+1]==bin || tela[x+2][y+1]==bin)
			return 1;
		else
		{
			tela[x+1][y]=bin;
			tela[x][y+1]=bin;
			tela[x+1][y+1]=bin;
			tela[x+2][y+1]=bin;
			return 0;
		}
		//break;

		case 2: //  |-
		if (tela[x][y]==bin ||  tela[x][y+1]==bin || tela[x][y+2]==bin || tela[x+1][y+1]==bin)
			return 1;
		else
		{
			tela[x][y]=bin;
			tela[x][y+1]=bin;
			tela[x][y+2]=bin;
			tela[x+1][y+1]=bin;
			return 0;
		}
		//break;

		case 3: 	//  ---
		if (tela[x][y]==bin ||  tela[x+1][y]==bin || tela[x+2][y]==bin || tela[x+1][y+1]==bin)
			return 1;
		else
		{
			tela[x][y]=bin;
			tela[x+1][y]=bin;
			tela[x+2][y]=bin;
			tela[x+1][y+1]=bin;
			return 0;
		}
		//break;


		case 4:
		if (tela[x+1][y]==bin ||  tela[x][y+1]==bin || tela[x+1][y+2]==bin || tela[x+1][y+1]==bin)
			return 1;
		else
		{
			tela[x+1][y]=bin;
			tela[x][y+1]=bin;
			tela[x+1][y+2]=bin;
			tela[x+1][y+1]=bin;
			return 0;
		}
		//break;


	}
	return NULL;
}
/***/

void printTela(char **tela, int opcao,int x1, int y1, int x2, int y2)
{
	int i,j;

	switch (opcao)
	{
	case 1: //TELA TODA
		//Varre a matriz e imprime os quadrados selecionados
		for(i=0;i<tx4/QUAD;i++) //COLUNAS
			for(j=0;j<ty/QUAD-1;j++) //LINHAS
			{
				if (tela[i][j]=='1')
				{
					quad(i*QUAD,j*QUAD,nivel%15,nivel,15);
				}
				//else quad(i*QUAD,j*QUAD,0,1,0);
			 }
		/** /
		for(i=0;i<tx4/QUAD;i++) //BASE
			if (tela[i][ty/QUAD-1]=='1')
				{
					quad(i*QUAD,ty-2*QUAD,COR1,4,COR1);
				}
		for(i=0;i<ty/QUAD-1;i++) //COLUNAS VERTICAIS
		{
			if (tela[0][i]=='1')
				{
					quad(0,i*QUAD,COR1,4,COR1);
				}
			if  (tela[tx4/QUAD-1][i]=='1')
				{
					quad(tx4-2*QUAD+1,i*QUAD,COR1,4,COR1);
				}
		}
		/**/

		break;

	case 2:
		/**/
		//IMPRIME DE X1(x1,y1) a X2(x2,y2)
		for (i=x1;i<x2;i++)
			for (j=y1;j<y2;j++)
			{
				if (tela[i][j]=='1')
				{
					quad(i*QUAD,j*QUAD,nivel%15,3,15);
				}
			} /**/

		break;
	}

}

int pecaN (int x, int y,char **tela, int pos, char bin, int peca)
{
	int obstaculo=0;


	switch (peca)

	{

	case 1:
	obstaculo=peca1(x,y,tela,bin);
	return obstaculo;
	//break;

	case 2:
	obstaculo=peca2(x,y,tela,pos,bin);
	return obstaculo;
	//break;

	case 3:
	obstaculo=peca3(x,y,tela,pos,bin);
	return obstaculo;
	//break;

	case 4:
	obstaculo=peca4(x,y,tela,pos,bin);
	return obstaculo;
	//break;

	case 5:
	obstaculo=peca5(x,y,tela,pos,bin);
	return obstaculo;
	//break;

	case 6:
	obstaculo=peca6(x,y,tela,pos,bin);
	return obstaculo;
	//break;

	case 7:
	obstaculo=peca7(x,y,tela,pos,bin);
	return obstaculo;
	//break;

	}

	return NULL;
}

void zeraTela (char **tela)
{
	int i,j;

	//nao ha nada na tela, zerando a matriz tela
	for(i=0;i<tx4/QUAD;i++)
		for(j=0;j<ty/QUAD;j++)
		{
			tela[i][j]='0';
			quad(i*QUAD,j*QUAD,COR1,1,15);
			//printf ("%c",tela[i][j]);
		}
	//colocando a ultima linha como 1 - chao
	for(i=0;i<tx4/QUAD;i++)
		tela[i][ty/QUAD-1]='1';
	//colocando as paredes

	for(i=0;i<ty/QUAD;i++)
	{
		//tela[0][i]='1';
		tela[tx4/QUAD-2][i]='1';
	}
}

int geraBase (char **tela,int *base)
{
	int i,j;
	int maior=0;

	for(i=0;i<tx4/QUAD-2;i++) //COLUNAS
		for(j=0;j<ty/QUAD;j++) //LINHAS
			if (tela[i][j]=='1')
			{
				base[i]=j;
				j=ty/QUAD-1;
			}

	for (i=0;i<tx4/QUAD-2;i++)
	{   /** /
		gotoxy(70,i+1);
		printf ("COL %d = %d",i+1,base[i]);
		/**/
		if (base[i]>maior)
			maior=base[i];
	}
	/** /
	gotoxy(70,20);
	printf ("%d",maior);
	/**/
	return maior;

}


void fim(void)
{
	int i;

	for (i=100;i<1100;i=i+100)
	{
		sound(i);
		delay(100);
		nosound();
	}
	for (i=1100;i>100;i=i-100)
	{
		sound(i);
		delay(100);
		nosound();
	}

	setviewport(0, 0, getmaxx(), getmaxy(), CLIP_ON);

	botao(tx4+100, 302, tx4+200, 332, 7, 1, "Parabens "USUARIO"!",1);
	boneco(getmaxx()/2,getmaxy()/2,20,0);


	getch();
	getch();

	closegraph();

	saindo();
}

void boneco (int x, int y, int tam, int cabeca)
{
	tam=tam/10;

	if (!cabeca)
	{
		//TORAX
		setcolor(LIGHTGRAY);
		setfillstyle(5,RED);
		fillellipse(x,y,x/6*tam,y/3*tam);


		/** /
		//BRACO DIREITO
		setcolor(LIGHTGRAY);
		setfillstyle(1,BROWN);
		fillellipse(x+100,y-40,x/5*tam,y/20*tam);
		//BRACO ESQUERDO
		fillellipse(x-100,y-40,x/5*tam,y/20*tam);
		/**/

		//PERNA DIREITA
		setcolor(DARKGRAY);
		setfillstyle(9,COR1);
		fillellipse(x+40,y+140,x/20*tam,y/3*tam);
		//PERNA ESQUERDA
		fillellipse(x-40,y+140,x/20*tam,y/3*tam);

		setfillstyle(9,DARKGRAY);
		fillellipse(x-40,y+320,x/20*tam,y/4*tam);
		fillellipse(x+40,y+320,x/20*tam,y/4*tam);
	}

	//CABECA
	setcolor(LIGHTGRAY);
	setfillstyle(1,BROWN);
	fillellipse(x,y/2+20,x/8*tam,y/6*tam);
	setcolor(BLACK);
	setfillstyle(1,WHITE);
	fillellipse(x-20,y/2+10,10*tam,10*tam);
	fillellipse(x+20,y/2+10,10*tam,10*tam);
	putpixel(x-20,y/2+10,BLACK);
	putpixel(x+20,y/2+10,BLACK);
	arc(x,y-70,180,360,30);

	while(!kbhit() && !cabeca)
	{
		setcolor(BLACK);
		setfillstyle(1,WHITE);
		fillellipse(x-20,y/2+10,10*tam,10*tam);
		fillellipse(x+20,y/2+10,10*tam,10*tam);
		putpixel(x-20,y/2+10,BLACK);
		putpixel(x+20,y/2+10,BLACK);
		delay(rand()%7000);
		setfillstyle(1,BROWN);
		fillellipse(x-20,y/2+10,10*tam,10*tam);
		fillellipse(x+20,y/2+10,10*tam,10*tam);
		delay(rand()%200);
	}

}
/*
int fama(char *nome, int pontos)
{
	/*
	char nomeTemp[JOGADOR];
	int pontosTemp;
	*//*
	int i,j;
	int a,b;
	int max=10000;
	int menorPontuacao=10000;
	int trocou,fim;

	Famoso famTemp;

	for (i=0;i<3500;i++)
			putpixel(rand()%getmaxx(),rand()%getmaxy(), BLACK);


	cleardevice();
	for (i=0;i<500;i++)
		{
			a=rand()%getmaxx();
			b=rand()%getmaxy();
			putpixel(a,b, WHITE + BLINK);
			a=rand()%getmaxx();
			b=rand()%getmaxy();
			putpixel(a,b, LIGHTGRAY + BLINK);
			a=rand()%getmaxx();
			b=rand()%getmaxy();
			putpixel(a,b, DARKGRAY + BLINK);
		}
	settextstyle(0, HORIZ_DIR,3);
	setcolor(BROWN);
	outtextxy (getmaxx()/2-178,22,"CALCADA DA FAMA");
	setcolor(YELLOW);
	outtextxy (getmaxx()/2-180,20,"CALCADA DA FAMA");
	setcolor(WHITE);
	settextstyle(0, HORIZ_DIR,1);
	outtextxy (getmaxx()/2-120,50,"Onde as Estrelas Brilham mais!");


	//INSERINDO NOVO FAMOSO NA MEMORIA
	if (contador==9 && pontos>menorPontuacao && pontos!=NULL)
	{
		//contador-=1;
		strcpy(famoso[contador].nome, nome);
		famoso[contador].pontos = pontos;

	}
	else if (contador<9 && pontos!=NULL)
	{
		contador++;
		strcpy(famoso[contador].nome, nome);
		famoso[contador].pontos = pontos;
	}
	//else /* //se nao gravar nada e o contador==10/** /	contador-=1;

	//ORDENA (BUBBLE SORT)
	/*
	fim=contador+1;
	do
	{
		trocou=0;
		for(i=0;i<fim-1;i++)
		{
			if (famoso[i].pontos<famoso[i+1].pontos)
			{
				famTemp=famoso[i];
				famoso[i]=famoso[i+1];
				famoso[i+1]=famTemp;
				trocou=1;
			}
		}
		fim--;
	}while(trocou);
	/**/

	//INSERINDO NOVO FAMOSO
	/** /
	if (contador>=10 && pontos>menorPontuacao)
	{
		//PERCORRE ATE O NONO
		for(i=0;i<9;i++)
			fread (&famTemp, sizeof(struct Famoso), 1, pa);

		//ESCREVE NO DECIMO
		fwrite (nome,   JOGADOR*sizeof(char), 1, pa);
		fwrite (&pontos,   sizeof(int), 1, pa);
		contador++;
	}
	else if (contador<10)
	{
		fwrite (nome,   JOGADOR*sizeof(char), 1, pa);
		fwrite (&pontos,   sizeof(int), 1, pa);
		contador++;
	}
	/** /

	//IMPRIMINDO
	j=0;
	for (i=0;i<=contador;i++)
	{
		gotoxy(22,7+i+j);
		printf ("%s",famoso[i].nome);
		gotoxy(52,7+i+j);
		printf ("%d",famoso[i].pontos);
		j++;
	}
	/** /
	gotoxy(60,2);
	printf ("NOVO: %s - %d",nome,pontos);
	////**/
	/**TELEVISAO** /
	while(!kbhit())
		for (i=0;i<500;i++)
		{
			putpixel(rand()%getmaxx(),rand()%getmaxy(), WHITE + BLINK);
			putpixel(rand()%getmaxx(),rand()%getmaxy(), BLACK);
		}
	/**/

	//getch();

	/** /
	exit(1);
	/**DEPURA** /
	return NULL;
}
*/

int fama(char *nome, int pontos)
{
	Famoso famTemp;
	int max=10000;
	int menorPontuacao=10000, piorJogador=10;
	int i,j;
	int a,b;
	int trocou,fim;
	/*
	char nomeTemp[JOGADOR];
	int pontosTemp;
	*//*


	**/
	for (i=0;i<3500;i++)
			putpixel(rand()%getmaxx(),rand()%getmaxy(), BLACK);


	cleardevice();
	for (i=0;i<500;i++)
		{
			a=rand()%getmaxx();
			b=rand()%getmaxy();
			putpixel(a,b, WHITE + BLINK);
			a=rand()%getmaxx();
			b=rand()%getmaxy();
			putpixel(a,b, LIGHTGRAY + BLINK);
			a=rand()%getmaxx();
			b=rand()%getmaxy();
			putpixel(a,b, DARKGRAY + BLINK);
		}
	settextstyle(0, HORIZ_DIR,3);
	setcolor(BROWN);
	outtextxy (getmaxx()/2-178,22,"CALCADA DA FAMA");
	setcolor(YELLOW);
	outtextxy (getmaxx()/2-180,20,"CALCADA DA FAMA");
	setcolor(WHITE);
	settextstyle(0, HORIZ_DIR,1);
	outtextxy (getmaxx()/2-120,50,"Onde as Estrelas Brilham mais!");

	for (i=0;i<contador;i++)
		if (lista[i].pontos<=menorPontuacao)
		{
			 menorPontuacao=lista[i].pontos;
			 piorJogador=i;
		}

	//INSERINDO NOVO FAMOSO NA MEMORIA
	if (contador>8 && pontos>menorPontuacao && pontos!=NULL)
	{
		//contador-=1;
		strcpy(lista[piorJogador].nome, nome);
		lista[piorJogador].pontos = pontos;

	}
	else if (contador<9 && pontos!=NULL)
	{
		contador++;
		strcpy(lista[contador].nome, nome);
		lista[contador].pontos = pontos;
	}
	//else /* //se nao gravar nada e o contador==10/**/	contador-=1;

	//ORDENA (BUBBLE SORT)
	fim=contador+1;
	do
	{
		trocou=0;
		for(i=0;i<fim-1;i++)
		{
			if (lista[i].pontos<lista[i+1].pontos)
			{
				famTemp=lista[i];
				lista[i]=lista[i+1];
				lista[i+1]=famTemp;
				trocou=1;
			}
		}
		fim--;
	}while(trocou);
	/**/

	//INSERINDO NOVO FAMOSO
	/** /
	if (contador>=10 && pontos>menorPontuacao)
	{
		//PERCORRE ATE O NONO
		for(i=0;i<9;i++)
			fread (&famTemp, sizeof(struct Famoso), 1, pa);

		//ESCREVE NO DECIMO
		fwrite (nome,   JOGADOR*sizeof(char), 1, pa);
		fwrite (&pontos,   sizeof(int), 1, pa);
		contador++;
	}
	else if (contador<10)
	{
		fwrite (nome,   JOGADOR*sizeof(char), 1, pa);
		fwrite (&pontos,   sizeof(int), 1, pa);
		contador++;
	}
	/**/

	//IMPRIMINDO
	j=0;
	for (i=0;i<=contador;i++)
	{
		if (lista[i].pontos!=NULL)
		{
			gotoxy(22,7+i+j);
			printf ("%s",lista[i].nome);
			gotoxy(52,7+i+j);
			printf ("%d",lista[i].pontos);
			j++;
		}
	}
	/** /
	gotoxy(60,2);
	printf ("NOVO: %s - %d",nome,pontos);
	////**/
	/**TELEVISAO** /
	while(!kbhit())
		for (i=0;i<500;i++)
		{
			putpixel(rand()%getmaxx(),rand()%getmaxy(), WHITE + BLINK);
			putpixel(rand()%getmaxx(),rand()%getmaxy(), BLACK);
		}
	/**/

	//getch();

	/** /
	exit(1);
	/**DEPURA**/
	return NULL;
}


void leArq(char *nome, int pontos)
{
	Famoso famTemp;
	FILE *pa;
	int max=10000;
	//int menorPontuacao=10000;
	int i;

	if (  ( (pa=fopen(ARQ,"r+b")) == NULL ) ) //Se nao Existe arquivo
	{
		if ( (pa=fopen(ARQ,"w+b"))==NULL) //Crie
		{
			gotoxy(45,20);
			printf("ERRO com o arquivo %s! \n", ARQ);
			saindo();
		}
/** /	else
		{
			fwrite ("JJunior",   JOGADOR*sizeof(char), 1, pa);
			fwrite (&max,   sizeof(int), 1, pa);
		}
		/**/
	}

	rewind(pa);

	//CONTANDO OS FAMOSOS CADASTRADOS
	contador=0;
	while(!feof(pa))
	{
		fread (famTemp.nome, JOGADOR*sizeof(char), 1, pa);
		fread (&famTemp.pontos, sizeof(int), 1, pa);
		contador++;
		//if (famTemp.pontos<=menorPontuacao) menorPontuacao=famTemp.pontos;
	}

	free(famoso);

	famoso=(Famoso *)malloc((contador+1)*sizeof(Famoso));

	rewind(pa);


	//LENDO ARQUIVO->MEMORIA
	strcpy(lista[0].nome,"JJunior");
	lista[0].pontos=max;


	for(i=1;i<10;i++)
	{
		strcpy(lista[i].nome,NULL);
		lista[i].pontos=NULL;
	}
	for (i=0;i<contador-1;i++)
	{
		fread (lista[i].nome,   JOGADOR*sizeof(char), 1, pa);
		fread (&lista[i].pontos, sizeof(int)         , 1, pa);
	}



	rewind(pa);

	fclose(pa);

}

int abertura(void)
{
	int i, modo;

	settextstyle(0, HORIZ_DIR,2);

	/**/

	//TV
	while(!kbhit())
	{
		for (i=0;i<500;i++)
		{
			putpixel(rand()%getmaxx(),rand()%getmaxy(), WHITE + BLINK);
			putpixel(rand()%getmaxx(),rand()%getmaxy(), BLACK);
		}
	botao(30,100,600,120,0,1,"",CYAN);
	rectangle(30,100,600,120);
	outtextxy (40,102,"NAO USE TELEVISAO,"           " PRATIQUE TETRIS!");
	}

	botao(30,100,600,120,0,1,"",BLACK);
	rectangle(30,100,600,120);

	for (i=0;i<800;i++)
	{
		putpixel(30+rand()%570,100+rand()%20, WHITE + BLINK);
		putpixel(30+rand()%570,100+rand()%20, BLACK);
	}

	boneco(getmaxx()/2,getmaxy()/2,20,0);

	settextstyle(0, HORIZ_DIR,5);
	setcolor(COR1);
	outtextxy (40,202,"JJUNIOR TETRIS");
	setcolor(COR2);
	outtextxy (42,200,"JJUNIOR TETRIS");
	settextstyle(0, HORIZ_DIR,1);

	getch();getch();getch();

	//FOCO PRETO
	for (i=1;i<600;i+=5)
		{
		setcolor(BLACK);
		setfillstyle(1, BLACK);
		fillellipse(getmaxx()/2,getmaxy()/2,i,i);
		}
	/**/

	
}

int menu (void)
{

	int op=0;

	settextstyle(0, HORIZ_DIR,1);

	while (op!=1)
	{
		janela(getmaxx()/2-100,  2, getmaxx()/2+100, 412, 7, COR1, 1, "MENU",15);
		botao(getmaxx()/2-50,  52, getmaxx()/2+50,  82, 7, 1, "1. INICIAR",15);
		botao(getmaxx()/2-50, 102, getmaxx()/2+50, 132, 7, 1, "2. MODO   ",15);
		botao(getmaxx()/2-50, 152, getmaxx()/2+50, 182, 7, 1, "3. NIVEL  ",15);
		botao(getmaxx()/2-50, 202, getmaxx()/2+50, 232, 7, 1, "4. TAMANHO",15);
		botao(getmaxx()/2-50, 252, getmaxx()/2+50, 282, 7, 1, "5. AJUDA  ",15);
		botao(getmaxx()/2-50, 302, getmaxx()/2+50, 332, 7, 1, "6. FAMOSOS",15);
		botao(getmaxx()/2-50, 352, getmaxx()/2+50, 382, 7, 1, "7. SAIR   ",15);

		botao(getmaxx()/2-250, 422, getmaxx()/2+250, 452, 7, 1, "Escolha o numero correspondente a opcao, "USUARIO".",COR1);

		op=getch();
		op=atoi(&op);

		switch (op)
		{
			case 1:
				break;

			case 2:
				janela(getmaxx()/2+120, 102, getmaxx()/2+320, 262, 7, COR1, 1, "MODELO DAS PECA",15);
				botao(getmaxx()/2+150, 152, getmaxx()/2+290, 182, 7, 1, "1. CLASSICO     ",15);
				botao(getmaxx()/2+150, 202, getmaxx()/2+290, 232, 7, 1, "2. DESCE REDONDO",15);
				op=getch();
				op=atoi(&op);
				switch(op)
				{
					case 1:case 2:
					modo=op-1;
					break;
				 /** /
					default:
					modo=0;
					break; /**/
				}
				op=0;
				break;

			case 3:
				janela(getmaxx()/2+120, 102, getmaxx()/2+320, 262, 7, COR1, 1, "NIVEL DE DIFICULDADE",15);
				botao(getmaxx()/2+150, 152, getmaxx()/2+290, 182, 7, 1, "1. DIMINUI",15);
				botao(getmaxx()/2+150, 202, getmaxx()/2+290, 232, 7, 1, "2. AUMENTA",15);
				botao(getmaxx()/2+150, 280, getmaxx()/2+290, 310, 7, 1, "NIVEL ATUAL    ",15);
				gotoxy(74,19);
				printf ("%d",nivel);
				op=getch();
				op=atoi(&op);
				switch(op)
				{
					case 1:
					if (nivel>1) nivel--;
					break;

					case 2:
					if (nivel<10) nivel++;
					break;

				 /** /
					default:
					modo=0;
					break; /**/
				}
				op=0;
				break;

			case 4:
				janela(getmaxx()/2+120, 102, getmaxx()/2+320, 262, 7, COR1, 1, "TAMANHO DAS PECAS",15);
				botao(getmaxx()/2+150, 152, getmaxx()/2+290, 182, 7, 1, "1. NORMAL",15);
				botao(getmaxx()/2+150, 202, getmaxx()/2+290, 232, 7, 1, "2. PEQUENO",15);
				op=getch();
				op=atoi(&op);
				switch(op)
				{
					case 1:
					QUAD=20;
					break;

					case 2:
					QUAD=10;
					break;

				 /** /
					default:
					modo=0;
					break; /**/
				}
				op=0;
				break;

			case 5:
				botao(getmaxx()/2-250, 422, getmaxx()/2+250, 452, 7, 1, "Instrucoes de Jogo",COR1);
				ajuda();
				getch();
				break;

			case 6:
				fama("",NULL);
				getch();
				break;


			case 7:
				botao(getmaxx()/2-250, 422, getmaxx()/2+250, 452, 7, 1, "Vai sair do jogo "USUARIO "? (S/N)",COR1);
				op=toupper(getch());
				if(op==13 || op=='S' || op=='Y')
					{
					botao(getmaxx()/2-250, 422, getmaxx()/2+250, 452, 7, 1, "Maior mancada ai!!",COR1);
					getch();
					//closegraph();
					saindo();
					}
				botao(getmaxx()/2-250, 422, getmaxx()/2+250, 452, 7, 1, "",COR1);
				setcolor(BLACK);
				rectangle(tx4, 302, tx4+300, 332);
				break;

			default:
				botao(getmaxx()/2-250, 422, getmaxx()/2+250, 452, 7, 1, "ESCOLHA UM NUMERO ACIMA !!!!!!!",RED);
				sound(200);
				delay(100);
				nosound();
				delay(300);
				break;
		}

		cleardevice();
	}

	if (modo!=0 && modo!=1) modo=0;

	/***** DEPURA  * /
	exit(1);      /**/


}

void saindo(void)
{
	int i;
	FILE *pa;

	if (  ( (pa=fopen(ARQ,"r+b")) == NULL ) ) //Se nao Existe arquivo
		if ( (pa=fopen(ARQ,"w+b"))==NULL) //Crie
		{
			gotoxy(45,20);
			printf("ERRO com o arquivo %s! \n", ARQ);
			saindo();
		}

	rewind(pa);


	//GRAVANDO NO ARQUIVO
	for(i=0;i<contador-1;i++)
	{
		fwrite (&lista[i],   sizeof(Famoso), 1, pa);
	}

	fclose(pa);

	closegraph();

	creditos();

	exit(1);
}


void ajuda(void)
{

	janela(QUAD+1, 0, getmaxx()/2-2*QUAD, getmaxy()-2*QUAD, 7, COR1, 1, "AJUDA",15);
	settextstyle(0, HORIZ_DIR,1);
	setcolor(WHITE);

	outtextxy(QUAD+5, 60, "OBJETIVO DO JOGO: ");
	outtextxy(QUAD+5, 80, "Evitar encher o buraco        ");

	outtextxy(QUAD+5,150, "COMANDOS BASICOS:             ");
	outtextxy(QUAD+5,170, "<A> Gira no sentido horario   ");
	outtextxy(QUAD+5,190, "<S> Gira trigonometricamente  ");
	outtextxy(QUAD+5,210, "<SETAS> Comandam a peca       ");
	outtextxy(QUAD+5,230, "<BARRA DE ESPACO> Cai rapido  ");
	outtextxy(QUAD+5,300, "<ENTER> Paralisa o jogo       ");
	outtextxy(QUAD+5,320, "<ESC> Sai do jogo             ");
	outtextxy(QUAD+5,340, "<J> Comando extra             ");
	outtextxy(QUAD+5,360, "<F1> Ajuda (esta janela)      ");

}

void creditos(void)
{
	puts("QUEM FEZ TUDO FOI EU");
}

void solidifica(char **tela)
{
	int i,j;

	//Varre a matriz e imprime os quadrados selecionados
	for(i=0;i<tx4/QUAD;i++) //COLUNAS
		for(j=0;j<ty/QUAD-1;j++) //LINHAS
		{
			if (tela[i][j]=='1')
			{
				tela[i][j]=='S';
			}
		}
}