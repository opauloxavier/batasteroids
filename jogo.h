#define LARGURA 600
#define ALTURA 800
#define NOME "Batman: The Bat Revenge"
#define N_VIDA 3

typedef int bool;
#define true 1
#define false 0

typedef struct{
	
	int tipo;
	SDL_Rect quadAsteroid;
	int destruido;
	int anguloAsteroid;
}ASTEROID;

typedef struct{
	SDL_Rect quadTiro;
	int angulo_tiro;
	bool exists;
}TIRO;

typedef struct{
	SDL_Rect vida;
}VIDA;


SDL_Surface *home,*nave,*janela,*espaco,*temp,*angulonave,*texto,*tiro_nave,*tiro_rotated,*asteroide,*vida_img,*morcego,*morcego_medio,*explosao,*nuvens,*img_escudo,*tiro_animado,*gameover_screen,*barra_pontuacao,*rect_multiplicador;
SDL_Surface *multi_1x,*multi_2x,*multi_4x,*multi_8x,*pause_screen,*transparencia,*mute_img,*mute_on_txt,*mute_off_txt,*nome_ttf,*creditos_img;
SDL_Surface *nave1,*nave2,*nave3,*nave4,*nave5,*nave6,*angulonave1,*angulonave2,*angulonave3,*angulonave4,*angulonave5,*trocadenome_img;

SDL_Event event;
SDL_Rect espacot,navet,asteroide_img,part_asteroid,vida_posicao[3],rect_morcego[16],rect_morcego2[16],rect_morcego3[16],rect_explosao[16],rect_tiro[8],quadExplode;
SDL_Rect movimento_explosao,rect_nuvens[200],quadEscudo,rect_pontuacao,quadDeath,rect_naveanimada[6];
TTF_Font *fonte,*fonte2;
SDL_Color white={255,255,255};
SDL_Color gray={127,127,127};
SDL_Color transparente={255,255,255,50};
SDL_Rect rect_teste={400,400,100,100};
SDL_Rect rect_trocanome={290,268,100,100};
SDL_Rect notificacao={400,70,58,11};

//FILES
FILE *fo,*ranking;
char *jogador_txt="data/jogador.txt";
char *recorde_txt="data/records.txt";
char nome_jogador[10];
char nome_jogador_reserva[10];
int posicao_nome = 0;

bool move[4]={0,0,0,0};
const int FPS=30;
int teste=0;
bool aberto=true;
int angulo=0;
int atirar=0;
float vel_tiro=20;
int centro_nave_x, centro_nave_y,i;
float angulo_tiro;
float angulo_nave;
float x=200,y=200;
float x_inicio=200,y_inicio=200;
float velocidade=0;
char pontuacao_txt[80],vida_txt[20],nome_txt[50],recarga_txt[20],abatido_txt[20],multiplicador_txt[5],bemvindo_txt[25];
int pontuacao=0;
int highscores=0;
int finalizou=0;
int vida=3;
int asteroide_destruiu=0;
int som_notificacao=0;
int mute=0;

int escudo=0;
int dead=0;

int mousex;
int mousey;

bool dinamico=true;


float d_x,d_y;
float desloca_x(float,float);
float desloca_y(float,float);
void escreverTexto(int,int,char*,int,int,int,int);
void config();

//Variaveis Tiro
TIRO tiro[5];
int numero_tiros=5;
int recarga=100;

//Variaveis Vida
VIDA total_vidas[3];

//Variáveis asteroides
int contador=0;
int soma = 0;
ASTEROID asteroides[24];
int geraAsteroidInicial(ASTEROID asteroides[]);
int destroiAsteroid(ASTEROID asteroides[], int soma, int contador);
int achar_vazio(ASTEROID asteroides[]);
float asteroide_x,asteroide_y;

//Variavies animaçoes
void setanimation(SDL_Rect* );
void setexplosion(SDL_Rect* );
//frames
int frame_morcego=0;
int frame_morcego1=1;
int frame_morcego2=2;
int frame_explosao=10;
int frame_nuvens=1;
int frame_tiro=0;
int frame_notificacao=0;

int tipo_notificacao=0;
int contador_notificacao=0;
int som_multiplicador=0;

int dificuldade=2;

void notifica(int tipo,SDL_Rect* rect)
{
	
	if(tipo==1)
	{
		SDL_BlitSurface(mute_on_txt,NULL,janela,rect);
	}
	
	else if(tipo==3)
	{
		SDL_BlitSurface(multi_2x,NULL,janela,rect);
	}
	else if(tipo==4)
	{
		SDL_BlitSurface(multi_4x,NULL,janela,rect);
	}
	else if(tipo==5)
	{
		SDL_BlitSurface(multi_8x,NULL,janela,rect);
	}

	
}

int novojogo(int abatido)
{
	vida=N_VIDA;
	abatido=0;
	escudo=1;
	
	return abatido;
}


float desloca_x(float x,float y)
{
	d_x=(sin((x * M_PI)/180.0))*y;
	return d_x;
}
float desloca_y(float x,float y)
{
	d_y=(cos((x * M_PI)/180.0))*y;
	return d_y;
}


void escreverTexto(int posicao_x, int posicao_y,char* texto, int R, int G, int B,int tamanho_texto){

	//Modo de uso escreverTexto(x,y,"Texto",RED,GREEN,BLUE,tamanhotexto);
	fonte = TTF_OpenFont("src/Futura.ttf", tamanho_texto);
	SDL_Color cor = {R, G, B};
	SDL_Surface* src = TTF_RenderText_Solid(fonte, texto, cor);
	SDL_Rect posicaoTexto = {posicao_x, posicao_y, 0, 0};
	SDL_BlitSurface(src, NULL, janela, &posicaoTexto);
	SDL_FreeSurface(src);
	TTF_CloseFont(fonte);

}

int colisao_nave(float x, float y, SDL_Rect B, SDL_Surface *C)
{
	int leftA = x; // Ponto x da imagem
	int leftB = B.x;
	int rightA = x + C -> w;
	int rightB = B.x + B.w;
	int topA = y;
	int topB = B.y;
	int bottomA = y + C -> h; 
	int bottomB = B.y + B.h;
	
	if( topA >= bottomB)
		return 0;
			
	if(bottomA <= topB)
		return 0;
		
	if(rightA <= leftB)
		return 0;
					
	if(leftA >= rightB)
		return 0;
					
	return 1;	
}

				
int colisao_tiro(SDL_Rect A, SDL_Rect B)
	{

		int leftA = A.x;
		int leftB = B.x;
		int rightA = A.x + A.w;
		int rightB = B.x + B.w;
		int topA = A.y;
		int topB = B.y;
		int bottomA = A.y + A.h;
		int bottomB = B.y + B.h;
			
		if( topA >= bottomB)
			return 0;
		
		if(bottomA <= topB)
			return 0;
					
		if(rightA <= leftB)
			return 0;
				
		if(leftA >= rightB)
			return 0;
			
		atirar=0;
					
	return 1;	
				
}


void travessia(SDL_Rect *quadAsteroid){
	
	if(quadAsteroid -> x >= 800)
		quadAsteroid -> x = 0;

	if(quadAsteroid ->x < 0)
		quadAsteroid ->x = 800 - quadAsteroid->w;
				
	if(quadAsteroid -> y >= 600)
		quadAsteroid -> y = 0;
								
	if(quadAsteroid -> y < 0)
		quadAsteroid -> y = 600 - quadAsteroid->h;
}

void retorna(float *x, float *y, float *vel, int *angle){
	
	*x = 400;
	*y = 300;
	*angle = 0;
	*vel = 0;
}

void animanave(SDL_Rect* imagem){
	
	imagem[0].x=0;
	imagem[0].y=0;
	imagem[0].w=28;
	imagem[0].h=54;
	
	imagem[1].x=27;
	imagem[1].y=0;
	imagem[1].w=28;
	imagem[1].h=54;
	
	imagem[2].x=56;
	imagem[2].y=0;
	imagem[2].w=28;
	imagem[2].h=54;
	
	imagem[3].x=82;
	imagem[3].y=0;
	imagem[3].w=28;
	imagem[3].h=54;
	
	imagem[4].x=109;
	imagem[4].y=0;
	imagem[4].w=28;
	imagem[4].h=54;
	
	imagem[5].x=136;
	imagem[5].y=0;
	imagem[5].w=29;
	imagem[5].h=54;
}


void animatiro(SDL_Rect* imagem){
	
	imagem[0].x=0;
	imagem[0].y=0;
	imagem[0].w=17;
	imagem[0].h=17;
	
	imagem[1].x=18;
	imagem[1].y=0;
	imagem[1].w=17;
	imagem[1].h=17;
	
	imagem[2].x=34;
	imagem[2].y=0;
	imagem[2].w=15;
	imagem[2].h=17;
	
	imagem[3].x=49;
	imagem[3].y=0;
	imagem[3].w=17;
	imagem[3].h=17;
	
	imagem[4].x=66;
	imagem[4].y=0;
	imagem[4].w=17;
	imagem[4].h=17;
	
	imagem[5].x=83;
	imagem[5].y=0;
	imagem[5].w=17;
	imagem[5].h=17;
	
	imagem[6].x=101;
	imagem[6].y=0;
	imagem[6].w=15;
	imagem[6].h=17;
	
	imagem[7].x=116;
	imagem[7].y=0;
	imagem[7].w=17;
	imagem[7].h=17;
	
	
}


void facilita()
{
	int i=0;
	
	for(i=100;i<200;i++)
	{
		printf("imagem[%d].x=%d;\n",i,i);
		printf("imagem[%d].y=%d;\n",i,i);
		printf("imagem[%d].w=800;\n",i);
		printf("imagem[%d].h=600;\n",i);
		
		printf("imagem[%d].x=%d;\n",i+1,i);
		printf("imagem[%d].y=%d;\n",i+1,i);
		printf("imagem[%d].w=800;\n",i+1);
		printf("imagem[%d].h=600;\n",i+1);
	}
}
void setexplosion(SDL_Rect* imagem)
{
	imagem[0].x=0;
	imagem[0].y=0;
	imagem[0].w=85;
	imagem[0].h=90;
	
	imagem[1].x=0;
	imagem[1].y=0;
	imagem[1].w=85;
	imagem[1].h=90;
	
	imagem[2].x=0;
	imagem[2].y=0;
	imagem[2].w=85;
	imagem[2].h=90;
	
	imagem[3].x=110;
	imagem[3].y=0;
	imagem[3].w=85;
	imagem[3].h=90;
	
	imagem[4].x=110;
	imagem[4].y=0;
	imagem[4].w=85;
	imagem[4].h=90;
	
	imagem[5].x=110;
	imagem[5].y=0;
	imagem[5].w=85;
	imagem[5].h=90;
	
	imagem[6].x=210;
	imagem[6].y=0;
	imagem[6].w=85;
	imagem[6].h=90;
	
	imagem[7].x=210;
	imagem[7].y=0;
	imagem[7].w=85;
	imagem[7].h=90;
	
	
	imagem[8].x=210;
	imagem[8].y=0;
	imagem[8].w=85;
	imagem[8].h=90;
	
	imagem[9].x=310;
	imagem[9].y=0;
	imagem[9].w=85;
	imagem[9].h=90;
	
	imagem[10].x=310;
	imagem[10].y=0;
	imagem[10].w=85;
	imagem[10].h=90;
	
	imagem[11].x=310;
	imagem[11].y=0;
	imagem[11].w=85;
	imagem[11].h=90;
	
	imagem[12].x=410;
	imagem[12].y=0;
	imagem[12].w=85;
	imagem[12].h=90;
	
	imagem[13].x=410;
	imagem[13].y=0;
	imagem[13].w=85;
	imagem[13].h=90;
	
	imagem[14].x=410;
	imagem[14].y=0;
	imagem[14].w=85;
	imagem[14].h=90;
	
	

	
}

void setanimation3(SDL_Rect* imagem)
{
	imagem[0].x=0;
	imagem[0].y=0;
	imagem[0].w=70;
	imagem[0].h=35;
	
	imagem[1].x=0;
	imagem[1].y=0;
	imagem[1].w=70;
	imagem[1].h=35;
	
	imagem[2].x=0;
	imagem[2].y=0;
	imagem[2].w=70;
	imagem[2].h=35;
	
	imagem[3].x=0;
	imagem[3].y=0;
	imagem[3].w=70;
	imagem[3].h=35;
	
	
	imagem[4].x=70;
	imagem[4].y=0;
	imagem[4].w=70;
	imagem[4].h=45;
	
	imagem[5].x=70;
	imagem[5].y=0;
	imagem[5].w=70;
	imagem[5].h=45;
	
	imagem[6].x=70;
	imagem[6].y=0;
	imagem[6].w=70;
	imagem[6].h=45;
	
	imagem[7].x=70;
	imagem[7].y=0;
	imagem[7].w=70;
	imagem[7].h=45;

	imagem[8].x=140;
	imagem[8].y=0;
	imagem[8].w=70;
	imagem[8].h=45;
	
	imagem[9].x=140;
	imagem[9].y=0;
	imagem[9].w=70;
	imagem[9].h=45;
	
	imagem[10].x=140;
	imagem[10].y=0;
	imagem[10].w=70;
	imagem[10].h=45;
	
	imagem[11].x=140;
	imagem[11].y=0;
	imagem[11].w=70;
	imagem[11].h=45;
	
	imagem[12].x=210;
	imagem[12].y=0;
	imagem[12].w=70;
	imagem[12].h=45;
	
	imagem[13].x=210;
	imagem[13].y=0;
	imagem[13].w=70;
	imagem[13].h=50;
	
	imagem[14].x=210;
	imagem[14].y=0;
	imagem[14].w=70;
	imagem[14].h=50;
	
	imagem[15].x=210;
	imagem[15].y=0;
	imagem[15].w=70;
	imagem[15].h=50;

}


void setanimation2(SDL_Rect* imagem)
{
	imagem[0].x=0;
	imagem[0].y=0;
	imagem[0].w=90;
	imagem[0].h=68;
	
	imagem[1].x=0;
	imagem[1].y=0;
	imagem[1].w=90;
	imagem[1].h=68;
	
	imagem[2].x=0;
	imagem[2].y=0;
	imagem[2].w=90;
	imagem[2].h=68;
	
	imagem[3].x=0;
	imagem[3].y=0;
	imagem[3].w=90;
	imagem[3].h=68;
	
	imagem[4].x=90;
	imagem[4].y=0;
	imagem[4].w=90;
	imagem[4].h=68;
	
	imagem[5].x=90;
	imagem[5].y=0;
	imagem[5].w=90;
	imagem[5].h=68;
	
	imagem[6].x=90;
	imagem[6].y=0;
	imagem[6].w=90;
	imagem[6].h=68;
	
	imagem[7].x=90;
	imagem[7].y=0;
	imagem[7].w=90;
	imagem[7].h=68;
	
	imagem[8].x=180;
	imagem[8].y=0;
	imagem[8].w=100;
	imagem[8].h=68;
	
	imagem[9].x=180;
	imagem[9].y=0;
	imagem[9].w=100;
	imagem[9].h=68;
	
	imagem[10].x=180;
	imagem[10].y=0;
	imagem[10].w=100;
	imagem[10].h=68;
	
	imagem[11].x=180;
	imagem[11].y=0;
	imagem[11].w=100;
	imagem[11].h=68;
	
	imagem[12].x=280;
	imagem[12].y=0;
	imagem[12].w=90;
	imagem[12].h=68;
	
	imagem[13].x=280;
	imagem[13].y=0;
	imagem[13].w=90;
	imagem[13].h=68;
			
	imagem[14].x=280;
	imagem[14].y=0;
	imagem[14].w=90;
	imagem[14].h=68;
			
	imagem[15].x=280;
	imagem[15].y=0;
	imagem[15].w=90;
	imagem[15].h=68;
}

void setanimation(SDL_Rect* imagem)
{
	imagem[0].x=743;
	imagem[0].y=100;
	imagem[0].w=38;
	imagem[0].h=30;

	imagem[1].x=743;
	imagem[1].y=100;
	imagem[1].w=38;
	imagem[1].h=30;
	
	imagem[2].x=743;
	imagem[2].y=100;
	imagem[2].w=38;
	imagem[2].h=30;
	
	imagem[3].x=743;
	imagem[3].y=100;
	imagem[3].w=38;
	imagem[3].h=30;
	
	imagem[4].x=780;
	imagem[4].y=100;
	imagem[4].w=38;
	imagem[4].h=30;
	
	imagem[5].x=780;
	imagem[5].y=100;
	imagem[5].w=38;
	imagem[5].h=30;
	
	imagem[6].x=780;
	imagem[6].y=100;
	imagem[6].w=38;
	imagem[6].h=30;

	imagem[7].x=780;
	imagem[7].y=100;
	imagem[7].w=38;
	imagem[7].h=30;
	
	imagem[8].x=816;
	imagem[8].y=100;
	imagem[8].w=40;
	imagem[8].h=30;
	
	imagem[9].x=816;
	imagem[9].y=100;
	imagem[9].w=40;
	imagem[9].h=30;
	
	imagem[10].x=816;
	imagem[10].y=100;
	imagem[10].w=40;
	imagem[10].h=30;
	
	imagem[11].x=816;
	imagem[11].y=100;
	imagem[11].w=40;
	imagem[11].h=30;
	
	imagem[12].x=855;
	imagem[12].y=105;
	imagem[12].w=40;
	imagem[12].h=30;
	
	imagem[13].x=855;
	imagem[13].y=105;
	imagem[13].w=40;
	imagem[13].h=30;
	
	imagem[14].x=855;
	imagem[14].y=105;
	imagem[14].w=40;
	imagem[14].h=30;
	
	imagem[15].x=855;
	imagem[15].y=105;
	imagem[15].w=40;
	imagem[15].h=30;
}

int geraAsteroidInicial(ASTEROID asteroides[]){

	int posicao;
	int contador;
	int soma = 0;
	
	for(contador = 0; contador < 3; contador++){
		
		posicao = rand()%4;
		
		if(posicao == 0){
			
			asteroides[contador].quadAsteroid.x = 0;
			asteroides[contador].quadAsteroid.y = 0;
			
			asteroides[contador].anguloAsteroid = rand()%90 + 270;
		}
		if(posicao == 1){
			
			asteroides[contador].quadAsteroid.x = 0;
			asteroides[contador].quadAsteroid.y = 450;
			
			asteroides[contador].anguloAsteroid = rand() % 90;
		}
		if(posicao == 2){
			
			asteroides[contador].quadAsteroid.x = 650;
			asteroides[contador].quadAsteroid.y = 0;
			
			asteroides[contador].anguloAsteroid = rand()%90 + 180;
		}
		if(posicao == 3){
			
			asteroides[contador].quadAsteroid.x = 650;
			asteroides[contador].quadAsteroid.y = 450;
			
			asteroides[contador].anguloAsteroid = rand()%90 + 90;
		}
	
	
		asteroides[contador].tipo = 8;
		soma += asteroides[contador].tipo;
	}
	
	for(contador = 3; contador < 24; contador++){
	
		asteroides[contador].tipo = 0;
		asteroides[contador].destruido = 1;
	}
	
	return soma;
}

int destroiAsteroid(ASTEROID asteroides[], int soma, int contador){

	int tipoDestruido;
	int tipoGerado;
	int posicao_x;
	int posicao_y;
	int posicao;
	int gera;
	
	tipoDestruido = asteroides[contador].tipo;
	
	soma -= tipoDestruido;
	
	asteroides[contador].destruido = 1;
	asteroides[contador].tipo = 0;
	
	posicao_x = asteroides[contador].quadAsteroid.x;
	posicao_y = asteroides[contador].quadAsteroid.y;
	
	tipoGerado = tipoDestruido/2;
	
	if(tipoDestruido != 2){
		
		for(gera = 0; gera < 2; gera++){
		
			contador = achar_vazio(asteroides);
			
			asteroides[contador].destruido = 0;
			
			asteroides[contador].tipo = tipoGerado;
			
			asteroides[contador].quadAsteroid.x = posicao_x;
			
			asteroides[contador].quadAsteroid.y = posicao_y;
			
			asteroides[contador].anguloAsteroid = rand() % 360;
			
			soma += tipoGerado;
		}
	}
	
	if(soma <= 8){
		
		while(soma < 24){

			contador = achar_vazio(asteroides);
			posicao = rand()%4;
		
			if(posicao == 0){
			
				asteroides[contador].quadAsteroid.x = 0;
				asteroides[contador].quadAsteroid.y = 0;
			
				asteroides[contador].anguloAsteroid = rand()%90 + 270;
			}
			if(posicao == 1){
			
				asteroides[contador].quadAsteroid.x = 0;
				asteroides[contador].quadAsteroid.y = 450;
			
				asteroides[contador].anguloAsteroid = rand()%90;
			}
			if(posicao == 2){
			
				asteroides[contador].quadAsteroid.x = 650;
				asteroides[contador].quadAsteroid.y = 0;
				
				asteroides[contador].anguloAsteroid = rand()%90 + 180;
			}
			if(posicao == 3){
			
				asteroides[contador].quadAsteroid.x = 650;
				asteroides[contador].quadAsteroid.y = 450;
			
				asteroides[contador].anguloAsteroid = rand()%90 + 90;
			}
			
			asteroides[contador].destruido = 0;
			asteroides[contador].tipo = 8;
			soma += 8;
		}
	 }
	
	return soma;
}

int achar_vazio(ASTEROID asteroides[]){
	
	int i;	
	
	for(i = 0; i < 24; i++){
		
		if(asteroides[i].destruido == 1)
			return i;
	}
	
	return i;
}

void setbackground(SDL_Rect* imagem)
{	
imagem[0].x=0;
imagem[0].y=0;
imagem[0].w=800;
imagem[0].h=600;
imagem[1].x=1;
imagem[1].y=1;
imagem[1].w=800;
imagem[1].h=600;
imagem[2].x=2;
imagem[2].y=2;
imagem[2].w=800;
imagem[2].h=600;
imagem[3].x=3;
imagem[3].y=3;
imagem[3].w=800;
imagem[3].h=600;
imagem[4].x=4;
imagem[4].y=4;
imagem[4].w=800;
imagem[4].h=600;
imagem[5].x=5;
imagem[5].y=5;
imagem[5].w=800;
imagem[5].h=600;
imagem[6].x=6;
imagem[6].y=6;
imagem[6].w=800;
imagem[6].h=600;
imagem[7].x=7;
imagem[7].y=7;
imagem[7].w=800;
imagem[7].h=600;
imagem[8].x=8;
imagem[8].y=8;
imagem[8].w=800;
imagem[8].h=600;
imagem[9].x=9;
imagem[9].y=9;
imagem[9].w=800;
imagem[9].h=600;
imagem[10].x=10;
imagem[10].y=10;
imagem[10].w=800;
imagem[10].h=600;
imagem[11].x=11;
imagem[11].y=11;
imagem[11].w=800;
imagem[11].h=600;
imagem[12].x=12;
imagem[12].y=12;
imagem[12].w=800;
imagem[12].h=600;
imagem[13].x=13;
imagem[13].y=13;
imagem[13].w=800;
imagem[13].h=600;
imagem[14].x=14;
imagem[14].y=14;
imagem[14].w=800;
imagem[14].h=600;
imagem[15].x=15;
imagem[15].y=15;
imagem[15].w=800;
imagem[15].h=600;
imagem[16].x=16;
imagem[16].y=16;
imagem[16].w=800;
imagem[16].h=600;
imagem[17].x=17;
imagem[17].y=17;
imagem[17].w=800;
imagem[17].h=600;
imagem[18].x=18;
imagem[18].y=18;
imagem[18].w=800;
imagem[18].h=600;
imagem[19].x=19;
imagem[19].y=19;
imagem[19].w=800;
imagem[19].h=600;
imagem[20].x=20;
imagem[20].y=20;
imagem[20].w=800;
imagem[20].h=600;
imagem[21].x=21;
imagem[21].y=21;
imagem[21].w=800;
imagem[21].h=600;
imagem[22].x=22;
imagem[22].y=22;
imagem[22].w=800;
imagem[22].h=600;
imagem[23].x=23;
imagem[23].y=23;
imagem[23].w=800;
imagem[23].h=600;
imagem[24].x=24;
imagem[24].y=24;
imagem[24].w=800;
imagem[24].h=600;
imagem[25].x=25;
imagem[25].y=25;
imagem[25].w=800;
imagem[25].h=600;
imagem[26].x=26;
imagem[26].y=26;
imagem[26].w=800;
imagem[26].h=600;
imagem[27].x=27;
imagem[27].y=27;
imagem[27].w=800;
imagem[27].h=600;
imagem[28].x=28;
imagem[28].y=28;
imagem[28].w=800;
imagem[28].h=600;
imagem[29].x=29;
imagem[29].y=29;
imagem[29].w=800;
imagem[29].h=600;
imagem[30].x=30;
imagem[30].y=30;
imagem[30].w=800;
imagem[30].h=600;
imagem[31].x=31;
imagem[31].y=31;
imagem[31].w=800;
imagem[31].h=600;
imagem[32].x=32;
imagem[32].y=32;
imagem[32].w=800;
imagem[32].h=600;
imagem[33].x=33;
imagem[33].y=33;
imagem[33].w=800;
imagem[33].h=600;
imagem[34].x=34;
imagem[34].y=34;
imagem[34].w=800;
imagem[34].h=600;
imagem[35].x=35;
imagem[35].y=35;
imagem[35].w=800;
imagem[35].h=600;
imagem[36].x=36;
imagem[36].y=36;
imagem[36].w=800;
imagem[36].h=600;
imagem[37].x=37;
imagem[37].y=37;
imagem[37].w=800;
imagem[37].h=600;
imagem[38].x=38;
imagem[38].y=38;
imagem[38].w=800;
imagem[38].h=600;
imagem[39].x=39;
imagem[39].y=39;
imagem[39].w=800;
imagem[39].h=600;
imagem[40].x=40;
imagem[40].y=40;
imagem[40].w=800;
imagem[40].h=600;
imagem[41].x=41;
imagem[41].y=41;
imagem[41].w=800;
imagem[41].h=600;
imagem[42].x=42;
imagem[42].y=42;
imagem[42].w=800;
imagem[42].h=600;
imagem[43].x=43;
imagem[43].y=43;
imagem[43].w=800;
imagem[43].h=600;
imagem[44].x=44;
imagem[44].y=44;
imagem[44].w=800;
imagem[44].h=600;
imagem[45].x=45;
imagem[45].y=45;
imagem[45].w=800;
imagem[45].h=600;
imagem[46].x=46;
imagem[46].y=46;
imagem[46].w=800;
imagem[46].h=600;
imagem[47].x=47;
imagem[47].y=47;
imagem[47].w=800;
imagem[47].h=600;
imagem[48].x=48;
imagem[48].y=48;
imagem[48].w=800;
imagem[48].h=600;
imagem[49].x=49;
imagem[49].y=49;
imagem[49].w=800;
imagem[49].h=600;
imagem[50].x=50;
imagem[50].y=50;
imagem[50].w=800;
imagem[50].h=600;
imagem[51].x=51;
imagem[51].y=51;
imagem[51].w=800;
imagem[51].h=600;
imagem[52].x=52;
imagem[52].y=52;
imagem[52].w=800;
imagem[52].h=600;
imagem[53].x=53;
imagem[53].y=53;
imagem[53].w=800;
imagem[53].h=600;
imagem[54].x=54;
imagem[54].y=54;
imagem[54].w=800;
imagem[54].h=600;
imagem[55].x=55;
imagem[55].y=55;
imagem[55].w=800;
imagem[55].h=600;
imagem[56].x=56;
imagem[56].y=56;
imagem[56].w=800;
imagem[56].h=600;
imagem[57].x=57;
imagem[57].y=57;
imagem[57].w=800;
imagem[57].h=600;
imagem[58].x=58;
imagem[58].y=58;
imagem[58].w=800;
imagem[58].h=600;
imagem[59].x=59;
imagem[59].y=59;
imagem[59].w=800;
imagem[59].h=600;
imagem[60].x=60;
imagem[60].y=60;
imagem[60].w=800;
imagem[60].h=600;
imagem[61].x=61;
imagem[61].y=61;
imagem[61].w=800;
imagem[61].h=600;
imagem[62].x=62;
imagem[62].y=62;
imagem[62].w=800;
imagem[62].h=600;
imagem[63].x=63;
imagem[63].y=63;
imagem[63].w=800;
imagem[63].h=600;
imagem[64].x=64;
imagem[64].y=64;
imagem[64].w=800;
imagem[64].h=600;
imagem[65].x=65;
imagem[65].y=65;
imagem[65].w=800;
imagem[65].h=600;
imagem[66].x=66;
imagem[66].y=66;
imagem[66].w=800;
imagem[66].h=600;
imagem[67].x=67;
imagem[67].y=67;
imagem[67].w=800;
imagem[67].h=600;
imagem[68].x=68;
imagem[68].y=68;
imagem[68].w=800;
imagem[68].h=600;
imagem[69].x=69;
imagem[69].y=69;
imagem[69].w=800;
imagem[69].h=600;
imagem[70].x=70;
imagem[70].y=70;
imagem[70].w=800;
imagem[70].h=600;
imagem[71].x=71;
imagem[71].y=71;
imagem[71].w=800;
imagem[71].h=600;
imagem[72].x=72;
imagem[72].y=72;
imagem[72].w=800;
imagem[72].h=600;
imagem[73].x=73;
imagem[73].y=73;
imagem[73].w=800;
imagem[73].h=600;
imagem[74].x=74;
imagem[74].y=74;
imagem[74].w=800;
imagem[74].h=600;
imagem[75].x=75;
imagem[75].y=75;
imagem[75].w=800;
imagem[75].h=600;
imagem[76].x=76;
imagem[76].y=76;
imagem[76].w=800;
imagem[76].h=600;
imagem[77].x=77;
imagem[77].y=77;
imagem[77].w=800;
imagem[77].h=600;
imagem[78].x=78;
imagem[78].y=78;
imagem[78].w=800;
imagem[78].h=600;
imagem[79].x=79;
imagem[79].y=79;
imagem[79].w=800;
imagem[79].h=600;
imagem[80].x=80;
imagem[80].y=80;
imagem[80].w=800;
imagem[80].h=600;
imagem[81].x=81;
imagem[81].y=81;
imagem[81].w=800;
imagem[81].h=600;
imagem[82].x=82;
imagem[82].y=82;
imagem[82].w=800;
imagem[82].h=600;
imagem[83].x=83;
imagem[83].y=83;
imagem[83].w=800;
imagem[83].h=600;
imagem[84].x=84;
imagem[84].y=84;
imagem[84].w=800;
imagem[84].h=600;
imagem[85].x=85;
imagem[85].y=85;
imagem[85].w=800;
imagem[85].h=600;
imagem[86].x=86;
imagem[86].y=86;
imagem[86].w=800;
imagem[86].h=600;
imagem[87].x=87;
imagem[87].y=87;
imagem[87].w=800;
imagem[87].h=600;
imagem[88].x=88;
imagem[88].y=88;
imagem[88].w=800;
imagem[88].h=600;
imagem[89].x=89;
imagem[89].y=89;
imagem[89].w=800;
imagem[89].h=600;
imagem[90].x=90;
imagem[90].y=90;
imagem[90].w=800;
imagem[90].h=600;
imagem[91].x=91;
imagem[91].y=91;
imagem[91].w=800;
imagem[91].h=600;
imagem[92].x=92;
imagem[92].y=92;
imagem[92].w=800;
imagem[92].h=600;
imagem[93].x=93;
imagem[93].y=93;
imagem[93].w=800;
imagem[93].h=600;
imagem[94].x=94;
imagem[94].y=94;
imagem[94].w=800;
imagem[94].h=600;
imagem[95].x=95;
imagem[95].y=95;
imagem[95].w=800;
imagem[95].h=600;
imagem[96].x=96;
imagem[96].y=96;
imagem[96].w=800;
imagem[96].h=600;
imagem[97].x=97;
imagem[97].y=97;
imagem[97].w=800;
imagem[97].h=600;
imagem[98].x=98;
imagem[98].y=98;
imagem[98].w=800;
imagem[98].h=600;
imagem[99].x=99;
imagem[99].y=99;
imagem[99].w=800;
imagem[99].h=600;
imagem[100].x=100;
imagem[100].y=100;
imagem[100].w=800;
imagem[100].h=600;
imagem[101].x=101;
imagem[101].y=101;
imagem[101].w=800;
imagem[101].h=600;
imagem[102].x=102;
imagem[102].y=102;
imagem[102].w=800;
imagem[102].h=600;
imagem[103].x=103;
imagem[103].y=103;
imagem[103].w=800;
imagem[103].h=600;
imagem[104].x=104;
imagem[104].y=104;
imagem[104].w=800;
imagem[104].h=600;
imagem[105].x=105;
imagem[105].y=105;
imagem[105].w=800;
imagem[105].h=600;
imagem[106].x=106;
imagem[106].y=106;
imagem[106].w=800;
imagem[106].h=600;
imagem[107].x=107;
imagem[107].y=107;
imagem[107].w=800;
imagem[107].h=600;
imagem[108].x=108;
imagem[108].y=108;
imagem[108].w=800;
imagem[108].h=600;
imagem[109].x=109;
imagem[109].y=109;
imagem[109].w=800;
imagem[109].h=600;
imagem[110].x=110;
imagem[110].y=110;
imagem[110].w=800;
imagem[110].h=600;
imagem[111].x=111;
imagem[111].y=111;
imagem[111].w=800;
imagem[111].h=600;
imagem[112].x=112;
imagem[112].y=112;
imagem[112].w=800;
imagem[112].h=600;
imagem[113].x=113;
imagem[113].y=113;
imagem[113].w=800;
imagem[113].h=600;
imagem[114].x=114;
imagem[114].y=114;
imagem[114].w=800;
imagem[114].h=600;
imagem[115].x=115;
imagem[115].y=115;
imagem[115].w=800;
imagem[115].h=600;
imagem[116].x=116;
imagem[116].y=116;
imagem[116].w=800;
imagem[116].h=600;
imagem[117].x=117;
imagem[117].y=117;
imagem[117].w=800;
imagem[117].h=600;
imagem[118].x=118;
imagem[118].y=118;
imagem[118].w=800;
imagem[118].h=600;
imagem[119].x=119;
imagem[119].y=119;
imagem[119].w=800;
imagem[119].h=600;
imagem[120].x=120;
imagem[120].y=120;
imagem[120].w=800;
imagem[120].h=600;
imagem[121].x=121;
imagem[121].y=121;
imagem[121].w=800;
imagem[121].h=600;
imagem[122].x=122;
imagem[122].y=122;
imagem[122].w=800;
imagem[122].h=600;
imagem[123].x=123;
imagem[123].y=123;
imagem[123].w=800;
imagem[123].h=600;
imagem[124].x=124;
imagem[124].y=124;
imagem[124].w=800;
imagem[124].h=600;
imagem[125].x=125;
imagem[125].y=125;
imagem[125].w=800;
imagem[125].h=600;
imagem[126].x=126;
imagem[126].y=126;
imagem[126].w=800;
imagem[126].h=600;
imagem[127].x=127;
imagem[127].y=127;
imagem[127].w=800;
imagem[127].h=600;
imagem[128].x=128;
imagem[128].y=128;
imagem[128].w=800;
imagem[128].h=600;
imagem[129].x=129;
imagem[129].y=129;
imagem[129].w=800;
imagem[129].h=600;
imagem[130].x=130;
imagem[130].y=130;
imagem[130].w=800;
imagem[130].h=600;
imagem[131].x=131;
imagem[131].y=131;
imagem[131].w=800;
imagem[131].h=600;
imagem[132].x=132;
imagem[132].y=132;
imagem[132].w=800;
imagem[132].h=600;
imagem[133].x=133;
imagem[133].y=133;
imagem[133].w=800;
imagem[133].h=600;
imagem[134].x=134;
imagem[134].y=134;
imagem[134].w=800;
imagem[134].h=600;
imagem[135].x=135;
imagem[135].y=135;
imagem[135].w=800;
imagem[135].h=600;
imagem[136].x=136;
imagem[136].y=136;
imagem[136].w=800;
imagem[136].h=600;
imagem[137].x=137;
imagem[137].y=137;
imagem[137].w=800;
imagem[137].h=600;
imagem[138].x=138;
imagem[138].y=138;
imagem[138].w=800;
imagem[138].h=600;
imagem[139].x=139;
imagem[139].y=139;
imagem[139].w=800;
imagem[139].h=600;
imagem[140].x=140;
imagem[140].y=140;
imagem[140].w=800;
imagem[140].h=600;
imagem[141].x=141;
imagem[141].y=141;
imagem[141].w=800;
imagem[141].h=600;
imagem[142].x=142;
imagem[142].y=142;
imagem[142].w=800;
imagem[142].h=600;
imagem[143].x=143;
imagem[143].y=143;
imagem[143].w=800;
imagem[143].h=600;
imagem[144].x=144;
imagem[144].y=144;
imagem[144].w=800;
imagem[144].h=600;
imagem[145].x=145;
imagem[145].y=145;
imagem[145].w=800;
imagem[145].h=600;
imagem[146].x=146;
imagem[146].y=146;
imagem[146].w=800;
imagem[146].h=600;
imagem[147].x=147;
imagem[147].y=147;
imagem[147].w=800;
imagem[147].h=600;
imagem[148].x=148;
imagem[148].y=148;
imagem[148].w=800;
imagem[148].h=600;
imagem[149].x=149;
imagem[149].y=149;
imagem[149].w=800;
imagem[149].h=600;
imagem[150].x=150;
imagem[150].y=150;
imagem[150].w=800;
imagem[150].h=600;
imagem[151].x=151;
imagem[151].y=151;
imagem[151].w=800;
imagem[151].h=600;
imagem[152].x=152;
imagem[152].y=152;
imagem[152].w=800;
imagem[152].h=600;
imagem[153].x=153;
imagem[153].y=153;
imagem[153].w=800;
imagem[153].h=600;
imagem[154].x=154;
imagem[154].y=154;
imagem[154].w=800;
imagem[154].h=600;
imagem[155].x=155;
imagem[155].y=155;
imagem[155].w=800;
imagem[155].h=600;
imagem[156].x=156;
imagem[156].y=156;
imagem[156].w=800;
imagem[156].h=600;
imagem[157].x=157;
imagem[157].y=157;
imagem[157].w=800;
imagem[157].h=600;
imagem[158].x=158;
imagem[158].y=158;
imagem[158].w=800;
imagem[158].h=600;
imagem[159].x=159;
imagem[159].y=159;
imagem[159].w=800;
imagem[159].h=600;
imagem[160].x=160;
imagem[160].y=160;
imagem[160].w=800;
imagem[160].h=600;
imagem[161].x=161;
imagem[161].y=161;
imagem[161].w=800;
imagem[161].h=600;
imagem[162].x=162;
imagem[162].y=162;
imagem[162].w=800;
imagem[162].h=600;
imagem[163].x=163;
imagem[163].y=163;
imagem[163].w=800;
imagem[163].h=600;
imagem[164].x=164;
imagem[164].y=164;
imagem[164].w=800;
imagem[164].h=600;
imagem[165].x=165;
imagem[165].y=165;
imagem[165].w=800;
imagem[165].h=600;
imagem[166].x=166;
imagem[166].y=166;
imagem[166].w=800;
imagem[166].h=600;
imagem[167].x=167;
imagem[167].y=167;
imagem[167].w=800;
imagem[167].h=600;
imagem[168].x=168;
imagem[168].y=168;
imagem[168].w=800;
imagem[168].h=600;
imagem[169].x=169;
imagem[169].y=169;
imagem[169].w=800;
imagem[169].h=600;
imagem[170].x=170;
imagem[170].y=170;
imagem[170].w=800;
imagem[170].h=600;
imagem[171].x=171;
imagem[171].y=171;
imagem[171].w=800;
imagem[171].h=600;
imagem[172].x=172;
imagem[172].y=172;
imagem[172].w=800;
imagem[172].h=600;
imagem[173].x=173;
imagem[173].y=173;
imagem[173].w=800;
imagem[173].h=600;
imagem[174].x=174;
imagem[174].y=174;
imagem[174].w=800;
imagem[174].h=600;
imagem[175].x=175;
imagem[175].y=175;
imagem[175].w=800;
imagem[175].h=600;
imagem[176].x=176;
imagem[176].y=176;
imagem[176].w=800;
imagem[176].h=600;
imagem[177].x=177;
imagem[177].y=177;
imagem[177].w=800;
imagem[177].h=600;
imagem[178].x=178;
imagem[178].y=178;
imagem[178].w=800;
imagem[178].h=600;
imagem[179].x=179;
imagem[179].y=179;
imagem[179].w=800;
imagem[179].h=600;
imagem[180].x=180;
imagem[180].y=180;
imagem[180].w=800;
imagem[180].h=600;
imagem[181].x=181;
imagem[181].y=181;
imagem[181].w=800;
imagem[181].h=600;
imagem[182].x=182;
imagem[182].y=182;
imagem[182].w=800;
imagem[182].h=600;
imagem[183].x=183;
imagem[183].y=183;
imagem[183].w=800;
imagem[183].h=600;
imagem[184].x=184;
imagem[184].y=184;
imagem[184].w=800;
imagem[184].h=600;
imagem[185].x=185;
imagem[185].y=185;
imagem[185].w=800;
imagem[185].h=600;
imagem[186].x=186;
imagem[186].y=186;
imagem[186].w=800;
imagem[186].h=600;
imagem[187].x=187;
imagem[187].y=187;
imagem[187].w=800;
imagem[187].h=600;
imagem[188].x=188;
imagem[188].y=188;
imagem[188].w=800;
imagem[188].h=600;
imagem[189].x=189;
imagem[189].y=189;
imagem[189].w=800;
imagem[189].h=600;
imagem[190].x=190;
imagem[190].y=190;
imagem[190].w=800;
imagem[190].h=600;
imagem[191].x=191;
imagem[191].y=191;
imagem[191].w=800;
imagem[191].h=600;
imagem[192].x=192;
imagem[192].y=192;
imagem[192].w=800;
imagem[192].h=600;
imagem[193].x=193;
imagem[193].y=193;
imagem[193].w=800;
imagem[193].h=600;
imagem[194].x=194;
imagem[194].y=194;
imagem[194].w=800;
imagem[194].h=600;
imagem[195].x=195;
imagem[195].y=195;
imagem[195].w=800;
imagem[195].h=600;
imagem[196].x=196;
imagem[196].y=196;
imagem[196].w=800;
imagem[196].h=600;
imagem[197].x=197;
imagem[197].y=197;
imagem[197].w=800;
imagem[197].h=600;
imagem[198].x=198;
imagem[198].y=198;
imagem[198].w=800;
imagem[198].h=600;
imagem[199].x=199;
imagem[199].y=199;
imagem[199].w=800;
imagem[199].h=600;
}

