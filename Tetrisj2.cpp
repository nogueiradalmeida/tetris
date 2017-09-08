/*************************************************************************** /

	Nome: TETRISJ.C
	Autor: JJunior
	Data: 21/12/1999
	Categoria: Jogo.
	Objetivo: Evitar que as pecas encham o buraco.

/***************************************************************************/

#define QUAD 20
#define CLIP_ON 1

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>

int geraPeca (void);
void printTela(char **tela);
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

void main()
{
	int obstaculo=0, quebraLoop1=0,ultimo[2], pula=0, pos=1, linhap;
	int i,j,k=0,m=0;
	int peca;
	int gdriver=DETECT, gmode;
	char op;

	char **tela; //tela[coluna][linha]

	initgraph (&gdriver, &gmode,"");

	tx4=getmaxx()/2;
	ty=getmaxy();

	//Alocando para matriz[tx4][ty]
	tela=(char **)malloc(tx4/QUAD*(sizeof(char *)));
	for(i=0;i<tx4/QUAD;i++)
	{
		tela[i]=(char *)malloc(ty/QUAD*sizeof(char));
	}

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
		tela[i][ty/QUAD-1]='1';
	//colocando as paredes
	for(i=0;i<ty/QUAD;i++)
	{
		tela[0][i]='1';
		tela[tx4/QUAD-1][i]='1';
	}

	getch();
	cleardevice();

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
		for (i=1;i<tx4/QUAD-1;i++)
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




		do
		{
			//setbkcolor(BLACK);
			clearviewport();

			op='X';

			while (kbhit() && !pula)
				op=toupper(getch());

			switch (op)
			{
				case 'K': // <-
					if (k>0 && tela[k-1][m]!='1') k--;
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
					pula=1;
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
				closegraph();
				exit(1);
				break;



		}

		obstaculo=pecaN (k, m,tela, pos, '1', peca);

		if (!obstaculo)
		{
			ultimo[0]=k;
			ultimo[1]=m;
		}

		printTela(tela);



		//TEMPO
		if (!pula) delay(100);



		if (!obstaculo)
		obstaculo=pecaN (k, m,tela, pos, '0', peca);

		m++;


		}while(!obstaculo);

		obstaculo=pecaN (k, ultimo[1],tela, pos, '1', peca);

		printTela(tela);

		//PROCURA ALGUMA LINHA PREENCHIDA
		for(j=0;j<ty/QUAD-1;j++) //VARRE LINHAS
		{
			linhap=0;
			for(i=1;i<tx4/QUAD-1;i++) //VARRE COLUNAS
				if (tela[i][j]=='1')
					linhap++;
			if (linhap==tx4/QUAD-2)
			{
				/** /
				printf ("Linha %d preenchida",j);
				getch();
				/*DEPURAR*/

				//APAGANDO LINHA 'j' PREENCHIDA
				for(j;j>1;j--) //VARRE LINHAS
					for(i=1;i<tx4/QUAD-1;i++) //VARRE COLUNAS
						tela[i][j]=tela[i][j-1];
			}
		}


	}
	for(i=1;i<3;i++)
	{
		sound(i*100);
		delay(100);
		nosound();
	}

	outtext ("Obrigado por jogar JJunior Tetris! ");
	getch();

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

void printTela(char **tela)
{
	int i,j;
	//Varre a matriz e imprime os quadrados selecionados
	for(i=0;i<tx4/QUAD;i++) //COLUNAS
		for(j=0;j<ty/QUAD;j++) //LINHAS
		{
			if (tela[i][j]=='1')
			{
				quad(i*QUAD,j*QUAD,RED,1,15);
			}
			//else quad(i*QUAD,j*QUAD,0,1,0);
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