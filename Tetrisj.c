/*************************************************************************** /

	Nome: TETRISJ.C
	Autor: JJunior
	Data: 21/12/1999
	Objetivo: Evitar que as pecas encham o buraco.

/***************************************************************************/

#define QUAD 20

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <dos.h>

int geraPeca (void);
void printTela(char **tela);
//void printPeca (int peca);
//void rodad(int peca);
void peca1(int x, int y);
void peca2(int x, int y, int pos);
void peca3(int x, int y, int pos);
//void peca4(int x, int y, int pos);
int peca4(int x, int y,char **tela, int pos,char bin);
void peca5(int x, int y, int pos);
void peca6(int x, int y, int pos);
void peca7(int x, int y, int pos);
//void quad(int x,int y); //quadrado
void quad (int x, int y,int cord, int preench,int corf);

int tx4; //tela por 4 -tamanho do quadrado
int ty;

void main()
{
	int obstaculo=0, quebraLoop1=0,quebraLoop2=0;
	int i,j,k=0,m=0;
	int pos=0;
	int peca;
	int gdriver=DETECT, gmode;

	char **tela; //tela[coluna][linha]

	initgraph (&gdriver, &gmode,"");


	tx4=getmaxx()/2;
	ty=getmaxy();

	//Alocando para matriz[tx4][ty]
	tela=(char **)malloc(tx4/QUAD*(sizeof(char *)));
	for(i=0;i<tx4/QUAD;i++)
		tela[i]=(char *)malloc(ty/QUAD*sizeof(char));

	//nao ha nada na tela, zerando a matriz tela
	for(i=0;i<tx4/QUAD;i++)
		for(j=0;j<ty/QUAD;j++)
		{
			tela[i][j]='0';
			quad(i*QUAD,j*QUAD,0,1,15);
			//printf ("%c",tela[i][j]);
		}
	//colocando a ultima linha como 1 - chao
	for(i=0;i<tx4/QUAD;i++)
		tela[i][ty/QUAD-1]='C';

	//Verifica se o poco nao encheu
	while(!quebraLoop1)
	{
	//Verifica se tem alguma coluna da penultima linha preenchida
		for (i=0;i<tx4/QUAD;i++)
			if (tela[i][4]=='1')
				quebraLoop1=1;
	/** /
	while(tela[0][2]!='1')
	{
	/**/
		m=0;
		k=0;

		/**/
		quebraLoop2=0;
		while(!quebraLoop2)
		{

			//Enquanto o elemento nao encontrar o chao ou outro elemento
			for (i=0;i<tx4/QUAD;i++)
				if ( (tela[i][m+2]=='1') || (tela[i][m+3]=='C') || (tela[i][m+4]=='1') && (tela[i][m+3]=='1'))
					quebraLoop2=1;
			/** /
			while (tela[0][m+2]!='C' && tela[0][m+2]!='1') { /**/

			cleardevice();

			//ESCREVE A PECA NA MATRIZ
			//obstaculo=
			peca4(k,m,tela,1,'1');

			printTela(tela);

			/*** /
			gotoxy(1,1);
			for(i=0;i<tx4/QUAD;i++)
				for(j=0;j<ty/QUAD;j++)
				{
					printf ("%c",tela[i][j]);
				}
			/***/

			delay(20);

			/** /Teste para ver se ja chegou no fim vertical da tela
			for (i=0; i<tx4/QUAD;i++)
				if (tela[i][ty/QUAD-1]=='1') //ultima linha possui algum 1 ?
					k=tx4/QUAD+1;//break     //se possuir, pare
			/***/

			//mudara=peca4(k,m+2,tela,1,'0'); //Testa se havera rotacao pro proximo
			//peca4(k,m,tela,1,'1'); //Conserta matriz alterada

			//APAGA A PECA NA MATRIZ
			/** /
			for (i=0;i<tx4/QUAD;i++)
				if ( tela[k][m+3]=='1' || tela[k][m+3]=='C')
				{
					i=tx4/QUAD; //break for
				}
				else peca4(k+3,m,tela,1,'0');
				/**/


			/** /
			if (tela[k][m+3]!='C' && tela[k][m+3]!='1' ) peca4(k,m,tela,1,'0');/**/
			if (/** /!obstaculo && /**/!quebraLoop2)
				peca4(k,m,tela,1,'0');

			m++;
			if(k<tx4/QUAD-2) k++;

		}

	}

	getch();

	peca=geraPeca();
	/**** /
	while(!kbhit() && y<480)
		{
		//printPeca(peca);
		pos++;
		if (pos<1) pos=4;
		if (pos>4) pos=1;
		peca4(x,y,pos);
		delay(1000);
		cleardevice();
		y+=QUAD;
		}
	/*** /
	while(!kbhit() && y<480)
		{
		//printPeca(peca);
		peca5(x,y,1);
		delay(1000);
		cleardevice();
		peca5(x,y,2	);
		delay(1000);
		cleardevice();
		peca5(x,y,3	);
		delay(1000);
		cleardevice();
		peca5(x,y,4	);
		delay(1000);
		cleardevice();
		y+=QUAD;
		}
	/***/

}

int geraPeca (void)
{
	int r=0;

	srand((unsigned int)time(NULL)); //seed rand, semeia o randomico
	r=rand()%7+1;//1 + (int) (50*rand()/RAND_MAX+1.0);

	return r;

}
/*
void quad(int x,int y) //desenha uma quadrado
{
	rectangle(x,y,x+QUAD,y+QUAD);
}
*/

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

/*
void peca1(int x, int y) // []
{
	quad(x,y);
	quad(x+QUAD,y);
	quad(x,y+QUAD);
	quad(x+QUAD,y+QUAD);
}

void peca2(int x, int y, int pos)      // -|_
{
	switch (pos)
	{
	case 1:  // -|_
		quad(x,y);
		quad(x+QUAD,y);
		quad(x+QUAD,y+QUAD);
		quad(x+2*QUAD,y+QUAD);
		break;

	case 2:  // _|-
		quad(x,y+QUAD);
		quad(x+QUAD,y+QUAD);
		quad(x+QUAD,y);
		quad(x,y+2*QUAD);
		break;
	}
}

void peca3(int x, int y, int pos)      // _|-
{
	switch (pos)
	{
	case 1:
		quad(x+2*QUAD,y);
		quad(x+QUAD,y);
		quad(x+QUAD,y+QUAD);
		quad(x,y+QUAD);
		break;
	case 2:
		quad(x,y);
		quad(x,y+QUAD);
		quad(x+QUAD,y+QUAD);
		quad(x+QUAD,y+2*QUAD);
		break;
	}
}
/***/
int peca4(int x, int y,char **tela, int pos, char bin)     // L
{
	switch (pos)
	{
	case 1: //L
		/** ///SE TIVER ALGUM OBSTACULO RETORNE 1
		if (tela[x][y]==bin &&	tela[x][y+1]==bin && tela[x][y+2]==bin && tela[x+1][y+2]==bin)
			return 1;
		//if(y+2<ty/QUAD)

		else		/**/
		{
			tela[x][y]=bin;
			tela[x][y+1]=bin;
			tela[x][y+2]=bin;
			tela[x+1][y+2]=bin;
			return 0;
		}
		//else return 0;
		break;

	case 2:   // |-
		if(y+1<ty/QUAD)
		{
			tela[x][y]=bin;
			tela[x+1][y]=bin;
			tela[x+2][y]=bin;
			tela[x][y+1]=bin;
			return 1;
		}
		else return 0;
		break;

	case 3:   //-|
		if(y+2<ty/QUAD)
		{
			tela[x][y]=bin;
			tela[x+1][y]=bin;
			tela[x+1][y+1]=bin;
			tela[x+1][y+2]=bin;
			return 1;
		}
		else return 0;
		break;

	case 4:   //_|
		if(y+1<ty/QUAD)
		{
			tela[x][y+1]=bin;
			tela[x+1][y+1]=bin;
			tela[x+2][y+1]=bin;
			tela[x+2][y]=bin;
			return 1;
		}
		else return 0;
		break;
	/*
	case 1: //L
		quad(x,y);
		quad(x,y+QUAD);
		quad(x,y+2*QUAD);
		quad(x+QUAD,y+2*QUAD);
		break;

	case 2:   // |-
		quad(x,y);
		quad(x+QUAD,y);
		quad(x+2*QUAD,y);
		quad(x,y+QUAD);
		break;

	case 3:   //-|
		quad(x,y);
		quad(x+QUAD,y);
		quad(x+QUAD,y+QUAD);
		quad(x+QUAD,y+2*QUAD);
		break;

	case 4:   //_|
		quad(x,y+QUAD);
		quad(x+QUAD,y+QUAD);
		quad(x+2*QUAD,y+QUAD);
		quad(x+2*QUAD,y);
		break;
	*/
	}
}
/*** /
void peca5(int x, int y, int pos)     // J
{
	switch(pos)
	{
	case 1:                     //J
		quad(x+QUAD,y);
		quad(x+QUAD,y+QUAD);
		quad(x+QUAD,y+2*QUAD);
		quad(x,y+2*QUAD);
		break;

	case 2:                      // |___
		quad(x,y);
		quad(x,y+QUAD);
		quad(x+QUAD,y+QUAD);
		quad(x+2*QUAD,y+QUAD);
		break;

	case 3:                    // |-
		quad(x,y);
		quad(x,y+QUAD);
		quad(x,y+2*QUAD);
		quad(x+QUAD,y);
		break;

	case 4:                       // ---|
		quad(x,y);
		quad(x+QUAD,y);
		quad(x+2*QUAD,y);
		quad(x+2*QUAD,y+QUAD);
		break;
	}

}

void peca6(int x, int y, int pos) // |
{
	switch (pos)
	{
		case 1: //|
		quad(x,y);
		quad(x,y+QUAD);
		quad(x,y+2*QUAD);
		quad(x,y+3*QUAD);
		break;

		case 2: // ----
		quad(x,y);
		quad(x+QUAD,y);
		quad(x+2*QUAD,y);
		quad(x+3*QUAD,y);
		break;

	}

}

void peca7(int x, int y, int pos) //  _|_
{
	switch (pos)
	{
		case 1: //  _|_
		quad(x+QUAD,y);
		quad(x,y+QUAD);
		quad(x+QUAD,y+QUAD);
		quad(x+2*QUAD,y+QUAD);
		break;

		case 2: //  |-
		quad(x,y);
		quad(x,y+QUAD);
		quad(x,y+2*QUAD);
		quad(x+QUAD,y+QUAD);
		break;

		case 3: 	//  ---
		quad(x,y);  //   |
		quad(x+QUAD,y);
		quad(x+2*QUAD,y);
		quad(x+QUAD,y+QUAD);
		break;

		case 4:              //  _|
		quad(x+QUAD,y);      //   |
		quad(x,y+QUAD);
		quad(x+QUAD,y+QUAD);
		quad(x+QUAD,y+2*QUAD);
		break;

	}
}
/***/

void printTela(char **tela)
{
	int i,j;
	//Varre a matriz e imprime os quadrados selecionados
	for(i=0;i<tx4/QUAD;i++)
		for(j=0;j<ty/QUAD;j++)
		{
			if (tela[i][j]=='1')
			{
				quad(i*QUAD,j*QUAD,1,1,15);
			}
			//else quad(i*QUAD,j*QUAD,0,1,0);
		}
}
