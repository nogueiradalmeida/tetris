/*************************************************************************** /

	Nome: TETRISJ.C
	Autor: JJunior
	Data: 21/12/1999
	Categoria: Jogo.
	Objetivo: Evitar que as pecas encham o buraco.

/***************************************************************************/

#define QUAD 20
#define CLIP_ON 1
#define CHEAT 20
#define ARQ fama.txt

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>
#include "jan.h"

int geraPeca (void);
//void printTela(char **tela);
void printTela(char **tela, int opcao,int x1, int y1, int x2, int y2);
void zeraTela (char **tela);
int geraBase (char **tela,int *base);
void fim(void);
void boneco (int x, int y, int tam, int cabeca);
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

int tx4; //tela por 4 -tamanho do quadrado
int ty;

int nivel=1;

void main()
{
	int obstaculo=0, quebraLoop1=0,ultimo[2], pula=0, pos=1;
	int linhap, maior, vaiFim=0, cheat=0;
	int pontos=0;
	int i,j,l,k=0,m=0;
	int peca;
	int gdriver=DETECT, gmode;
	char op;
	char macete[CHEAT], *mac;

	char **tela; //tela[coluna][linha]
	int *base;

	initgraph (&gdriver, &gmode,"");

	tx4=getmaxx()/2;
	ty=getmaxy();

	//Alocando para matriz[tx4][ty]
	tela=(char **)malloc(tx4/QUAD*(sizeof(char *)));
	for(i=0;i<tx4/QUAD;i++)
	{
		tela[i]=(char *)malloc(ty/QUAD*sizeof(char));
	}

	base=(int *)malloc(tx4/QUAD-2*sizeof(int));

	zeraTela(tela);

	getch();

	janela(tx4+50, 102, tx4+250, 262, 7, 9, 1, "JJUNIOR TETRIS (R) ",15);
	botao(tx4+80, 152, tx4+220, 182, 7, 1, "NIVEL       ",15);
	botao(tx4+80, 202, tx4+220, 232, 7, 1, "PONTOS      ",15);

	gotoxy(64,11);
	printf ("%d",nivel);

	gotoxy(62,14);
	printf ("    ");
	gotoxy(62,14);
	printf ("%d", pontos);



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

		printTela(tela,1,0,0,0,0);

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

		maior=geraBase(tela,base);

		do
		{
			//setbkcolor(WHITE);
			/** /
			gotoxy (70,10); printf ("%d",maior);
			/**DEPURA**/

			setviewport(QUAD+1, 0, tx4-2*QUAD , maior*QUAD-1/** /ty-2*QUAD/**/, CLIP_ON);
			clearviewport();

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
						botao(tx4, 302, tx4+300, 332, 7, 1, "Vai sair do jogo pela-saco? (S/N)",1);
					op=toupper(getch());
					if(op==13 || op=='S' || op=='Y')
						{
						botao(tx4, 302, tx4+300, 332, 7, 1, "          Po, vacilo ai!         ",1);
						getch();
						//closegraph();
						exit(1);
						}
					botao(tx4, 302, tx4+300, 332, 0, 1, " ",2);
					setcolor(BLACK);
					rectangle(tx4, 302, tx4+300, 332);
					setviewport(QUAD+1, 0, tx4-2*QUAD , maior*QUAD-1/** /ty-2*QUAD/**/, CLIP_ON);
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
						vaiFim=1;
						pula=1;

					}

					if (strcmpi(mac,"nivel")==0)
					{
						cheat=1;
						pontos=100*nivel;
						pula=1;
					}

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


	}
	for(i=1;i<3;i++)
	{
		sound(i*100);
		delay(100);
		nosound();
	}

	setviewport(0, 0, getmaxx() , getmaxy(), CLIP_ON);

	//outtextxy ("  Po! Ai, vacilo! Cabou!!! ");
	if (pontos<50) botao(tx4, 302, tx4+300, 332, 7, 1, "Se morre cara, tu eh horrivel!!! ",1);
	else if (pontos<100) botao(tx4, 302, tx4+300, 332, 7, 1, "Voce eh parente da Carla Perez!? ",1);
	else if (pontos<150) botao(tx4, 302, tx4+300, 332, 7, 1, "Tsc Tsc Tsc!! Voce eh muito fraquinho!",1);
	else if (pontos<200) botao(tx4, 302, tx4+300, 332, 7, 1, "Ai, treina mais, falou?  ",1);
	else botao(tx4, 302, tx4+300, 332, 7, 1, "Nada mal!",1);

	boneco(tx4/2,getmaxy()/2,20,1);

	getch();
	getch();
	getch();
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
		break;


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
		break;
	}
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
	break;

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
	break;

	}

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
		break;

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
		break;

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
		break;

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
		break;

	}
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
		break;

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
		break;

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
		break;

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
		break;
	}

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
		break;

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
		break;

	}

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
		break;

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
		break;

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
		break;


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
		break;


	}
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
					quad(i*QUAD,ty-2*QUAD,BLUE,4,LIGHTBLUE);
				}
		for(i=0;i<ty/QUAD-1;i++) //COLUNAS VERTICAIS
		{
			if (tela[0][i]=='1')
				{
					quad(0,i*QUAD,BLUE,4,LIGHTBLUE);
				}
			if  (tela[tx4/QUAD-1][i]=='1')
				{
					quad(tx4-2*QUAD+1,i*QUAD,BLUE,4,LIGHTBLUE);
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
	break;

	case 2:
	obstaculo=peca2(x,y,tela,pos,bin);
	return obstaculo;
	break;

	case 3:
	obstaculo=peca3(x,y,tela,pos,bin);
	return obstaculo;
	break;

	case 4:
	obstaculo=peca4(x,y,tela,pos,bin);
	return obstaculo;
	break;

	case 5:
	obstaculo=peca5(x,y,tela,pos,bin);
	return obstaculo;
	break;

	case 6:
	obstaculo=peca6(x,y,tela,pos,bin);
	return obstaculo;
	break;

	case 7:
	obstaculo=peca7(x,y,tela,pos,bin);
	return obstaculo;
	break;

	}

}

void zeraTela (char **tela)
{
	int i,j;

	//nao ha nada na tela, zerando a matriz tela
	for(i=0;i<tx4/QUAD;i++)
		for(j=0;j<ty/QUAD;j++)
		{
			tela[i][j]='0';
			quad(i*QUAD,j*QUAD,9,1,15);
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

	botao(tx4+100, 302, tx4+200, 332, 7, 1, "Parabens!",1);
	boneco(getmaxx()/2,getmaxy()/2,20,0);


	getch();

	closegraph();

	exit(1);
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
		setfillstyle(9,LIGHTBLUE);
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