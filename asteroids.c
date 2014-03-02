#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "jogo.h"
#include <math.h>
#include <time.h>
#include "SDL/SDL_mixer.h"
#include <string.h>


int main(int argc,char** argv){

	SDL_Init(SDL_INIT_EVERYTHING);
				
	TTF_Init();
	
	fo=fopen(jogador_txt,"rw+");
	ranking=fopen(recorde_txt,"a+");
	fscanf(fo,"%s \n", nome_jogador);
	posicao_nome=strlen(nome_jogador);

	printf("%s \n",nome_jogador_reserva);
	
	rewind(fo);
		
	SDL_WM_SetCaption(NOME, NULL); //tela
	janela = SDL_SetVideoMode(ALTURA, LARGURA, 32, SDL_HWSURFACE);
	fonte2 = TTF_OpenFont("src/Futura.ttf", 24);
	
		
	nome_ttf = TTF_RenderText_Blended(fonte2, nome_jogador, white);
	
	//SDL_Window *janela;
	//SDL_Renderer *sdlRenderer;
	//SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &janela, &sdlRenderer);



	srand(time(NULL));
	
	Uint32 start;

	SDL_Rect quad = {0,0};
	
	//posição inicial do seletor
	SDL_Rect seletor = {490,295};
	SDL_Rect select_over={250,499};
	SDL_Rect select_pause={217,362};
	
	Mix_Chunk* efeito;
	Mix_Music* musica_menu;
	Mix_Chunk* shot_sound;
	Mix_Chunk* explosao_nave;
	Mix_Music* musica_jogo;
	Mix_Chunk* death_bat;
	Mix_Chunk* multiplicador_sound;
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	
	musica_menu=Mix_LoadMUS("src/sounds/menu-sound.mp3");	
	musica_jogo=Mix_LoadMUS("src/sounds/game-sound.mp3");
	
	efeito=Mix_LoadWAV("src/sounds/menu-select.wav");
	death_bat=Mix_LoadWAV("src/sounds/death_bat.wav");
	multiplicador_sound=Mix_LoadWAV("src/sounds/multiplicador.wav");
	shot_sound=Mix_LoadWAV("src/sounds/shot-sound.wav");
	explosao_nave=Mix_LoadWAV("src/sounds/explosao-nave.wav");
		
	Mix_PlayMusic(musica_menu,-1);	
		
	Mix_VolumeChunk(efeito,16);
	Mix_VolumeChunk(shot_sound,32);
	Mix_VolumeChunk(explosao_nave,16);
	Mix_VolumeChunk(death_bat,32);
	Mix_VolumeChunk(multiplicador_sound,32);
	Mix_VolumeMusic(48);
	

	//Alpha
	SDL_Surface *alpha=SDL_CreateRGBSurface(SDL_SWSURFACE,janela->w,janela->h,32,janela->format->Rmask,janela->format->Gmask,janela->format->Bmask,janela->format->Amask);
	SDL_Surface *alpha2=SDL_CreateRGBSurface(SDL_SWSURFACE,janela->w,janela->h,32,janela->format->Rmask,janela->format->Gmask,janela->format->Bmask,janela->format->Amask);
	SDL_FillRect(alpha,&espacot,SDL_MapRGBA(janela->format,0,0,0,128));
	SDL_FillRect(alpha2,&espacot,SDL_MapRGBA(janela->format,255,255,255,128));
	//SDL_SetAlpha(alpha,SDL_SRCALPHA,36);
	
	transparencia=IMG_Load("transparencia.png");	
		
	//Espaco
	espaco =IMG_Load("src/fundo-jogo.png");
	nuvens =IMG_Load("src/nuvens.png");
	trocadenome_img=IMG_Load("src/troca_nome.png");
	
	//Nave
	nave = IMG_Load("src/nave1.png");
	nave2 = IMG_Load("src/nave2.png");
	nave3 = IMG_Load("src/nave3.png");
	nave4 = IMG_Load("src/nave4.png");
	nave5 = IMG_Load("src/nave5.png");
	nave6 = IMG_Load("src/nave6.png");
	
		
	//Escudo
	img_escudo= IMG_Load("src/escudo.png");
		
	//Tiro da nave
	tiro_animado=IMG_Load("src/tiro-sprite.png");
		
	//Imagem da vida
	vida_img=IMG_Load("src/vida.png");
	
			
	//Asteroide original
	asteroide=IMG_Load("src/asteroid.png");
		
	//Asteroide original
	morcego=IMG_Load("src/morcego.png");
	morcego_medio=IMG_Load("src/morcego_medio.png");
		
	//animaçao morcego
	explosao=IMG_Load("src/explosao.png");
		
	//tela gameover
	gameover_screen=IMG_Load("src/gameover.png");
	
	//tela de pause
	pause_screen=IMG_Load("src/tela-pause.png");
	
	//tela de creditos
	creditos_img=IMG_Load("src/creditos.png");
	
	//barra pontuacao e multiplicadores
	barra_pontuacao=IMG_Load("src/barra-pontuacao.png");
	multi_1x=IMG_Load("src/x1.png");
	multi_2x=IMG_Load("src/x2.png");
	multi_4x=IMG_Load("src/x4.png");
	multi_8x=IMG_Load("src/x8.png");
	
	//mute assets
	mute_img=IMG_Load("src/mute.png");
	mute_off_txt=IMG_Load("src/mute_off.png");
	mute_on_txt=IMG_Load("src/mute_on.png");
	
	SDL_Surface *tela = IMG_Load("src/tela_inicial.png");
	SDL_Surface *jogo = IMG_Load("src/jogo.png");
	SDL_Surface *pagina_recordes = IMG_Load("src/ranking.png");
	SDL_Surface *integrantes = IMG_Load("src/integrantes.png");
	SDL_Surface *instrucoes = IMG_Load("src/instrucoes.png");
	SDL_Surface *escolha = IMG_Load("src/seletor.png");	
	SDL_Surface *fim_de_jogo = IMG_Load("src/fim_de_jogo.png");
	
	//Elementos Visuais
	SDL_Rect rect_pontuacao={0,0,800,78};

	SDL_Rect rect_multiplicador={740,15,43,33};
	
	
	SDL_Rect rect_mute = {760,60,66,35};
	
	SDL_Rect mute_on = {0,0,36,38};
	SDL_Rect mute_off = {36,0,36,38};
	

			
	navet.x = 0; 
	navet.y = 0; 
	navet.h = 46; 
	navet.w = 25;
	
	espacot.x =0; /* Local de Destino X da Nave */
	espacot.y = 0; /* Local de Destino Y da Nave */
	espacot.h = ALTURA; /* Tamanho total possível de deslocamento */
	espacot.w = LARGURA; /* Tamanho total possível de deslocamento */

	SDL_Rect quadTiro={(int)x,(int) y, 20, 20};
	
	int menu=1;
	int record = 0;
	int jogar = 0;
	int gameover=0;
	int pause=0;
	int paginadeinstrucoes = 0;
	int paginadeintegrantes = 0;
	int pagina_record=0;	
	int opcao = 1;
	int opcao_over = 1;
	int opcao_pause =1;
	int troca_nome=0;
	int pagina_creditos=0;

	while(menu != 0){
					
		SDL_BlitSurface(tela, NULL, janela, NULL);
		SDL_BlitSurface(escolha, NULL, janela, &seletor);
		
		sprintf(bemvindo_txt,"Jogando como: %s",nome_jogador);
		escreverTexto(640,565,bemvindo_txt,255,255,255,12);
		escreverTexto(640,580,"(para trocar pressione F7)",239,137,5,10);
		
		SDL_Flip(janela);

		int selecao = 0;
		
		start = SDL_GetTicks();

		
		SDL_Event event;
		
		while(SDL_PollEvent(&event)){
			
			switch(event.type){
				
				case SDL_QUIT:
					menu = 0;
					break;

				case SDL_KEYDOWN:
				
					switch(event.key.keysym.sym){
					
						//esc para sair
						case SDLK_ESCAPE:
							menu = 0;
							jogar=0;
							break;

						//seta para baixo
						case SDLK_DOWN:

							//posicao de instrucoes
							if(seletor.y == 295)
							{
								seletor.y = 340;
								opcao = 4;
								Mix_PlayChannel(-1,efeito,0);
								break;
							}

							//posicao de ranking
							if(seletor.y == 340)
							{
								seletor.y = 390;
								Mix_PlayChannel(-1,efeito,0);
								opcao = 2;
								break;
							}

							//posicao de sair
							if(seletor.y ==390)
							{
								seletor.y = 440;
								Mix_PlayChannel(-1,efeito,0);
								opcao = 6;
								break;
							}

							//posicao de sair
							if(seletor.y == 440)
							{
								seletor.y = 485;
								Mix_PlayChannel(-1,efeito,0);
								opcao = 5;
								break;
							}
							
							if(seletor.y == 485)
							{
								seletor.y = 295;
								Mix_PlayChannel(-1,efeito,0);
								opcao = 1;
								break;
							}




						//seta para cima
						case SDLK_UP:
							if(seletor.y == 295)
							{
								seletor.y = 485;
								opcao = 5;
								Mix_PlayChannel(-1,efeito,0);
								break;
							}
							
							if(seletor.y == 485)
							{
								seletor.y = 440;
								opcao = 6;
								Mix_PlayChannel(-1,efeito,0);
								break;
							}
							
							if(seletor.y == 440)
							{
								seletor.y = 390;
								opcao = 2;
								Mix_PlayChannel(-1,efeito,0);
								break;
							}
							if(seletor.y==390)
							{
								seletor.y = 340;
								opcao = 4;
								Mix_PlayChannel(-1,efeito,0);
								break;
							}
							
								if(seletor.y==340)
							{
								seletor.y = 290;
								opcao = 1;
								Mix_PlayChannel(-1,efeito,0);
								break;
							}
								if(seletor.y==290)
							{
								seletor.y = 485;
								opcao = 5;
								Mix_PlayChannel(-1,efeito,0);
								break;
							}

							


						case SDLK_F7:
							troca_nome=1;
							break;
							
						case SDLK_F8:
							if(mute==0)
							{
								mute=1;
							}
							else if(mute==1)
							{
								mute=0;
							}
						break;	

						//enter
						case SDLK_RETURN:
							selecao = 1;
							break;
							
						default:
							break;
					}
					
					default:
						break;
				}
			}


		//quando apertar enter para escolher a opção			
		if(selecao == 1){
			
			if(opcao == 1)
			{
				jogar = 1;
				gameover=0;			
				Mix_PlayMusic(musica_jogo,-1);	
			}

			else if(opcao == 2)
				paginadeinstrucoes = 1;

			else if(opcao == 3)
				paginadeintegrantes = 1;

			else if(opcao == 4)
				pagina_record = 1;

			else if(opcao == 5)
				menu = 0;	
			else if(opcao == 6)
				pagina_creditos = 1;
				
		}
		if(mute==1)
		{
			Mix_VolumeChunk(death_bat,0);
			Mix_VolumeChunk(efeito,0);
			Mix_VolumeChunk(shot_sound,0);
			Mix_VolumeChunk(explosao_nave,0);
			Mix_VolumeChunk(multiplicador_sound,0);
			Mix_VolumeMusic(0);
		}				
		if(mute==0)				
		{
			Mix_VolumeChunk(death_bat,32);	
			Mix_VolumeChunk(efeito,16);
			Mix_VolumeChunk(shot_sound,32);
			Mix_VolumeChunk(explosao_nave,16);
			Mix_VolumeChunk(multiplicador_sound,32);
			Mix_VolumeMusic(48);
		}
	
	soma = geraAsteroidInicial(asteroides);
		
	for(i=0;i<numero_tiros;i++)
	{
	tiro[i].exists=false;		
	}
	
	int multiplicador=1;
	int abatido=0;
		
	while(jogar==1)	
	{

	start = SDL_GetTicks();		

	//SDL_UpdateRect(janela, 0, 0, 0, 0);
			
	while( SDL_PollEvent( &event ) ){ 	
		
	if(angulo >= 360)
		angulo -= 360;
	if(angulo <= -360)
		angulo += 360;

	
				switch(event.type)
				{
					{
						
						case SDL_QUIT:
						jogar=0;
						break;
					}   
					
					case SDL_MOUSEMOTION:
							mousex=event.motion.x;
							mousey=event.motion.y;
							break;
					
					case SDL_MOUSEBUTTONDOWN:
							mousex=event.button.x;
							mousey=event.button.y;
							
							if(mousex>rect_mute.x && mousex<rect_mute.x+rect_mute.w && mousey>rect_mute.y && mousey<rect_mute.y+rect_mute.h)
							if(mute==0)
							{
								contador_notificacao=0;
								mute=1;
								tipo_notificacao=1;
							}
							else if(mute==1)
							{
								contador_notificacao=0;
								mute=0;
								tipo_notificacao=2;
							}
							
							break;
							
						case SDL_KEYDOWN : 
							switch(event.key.keysym.sym)
							{
								case SDLK_UP:
								move[0]=1;
								break;
								
								case SDLK_LEFT:
								move[1]=1;
								break;
												
								case SDLK_DOWN:
								move[2]=1;
								break;
												
								case SDLK_RIGHT:
								move[3]=1;
								break;
												
								case SDLK_SPACE:
								atirar=1;	
								escudo=0;
								break;
	
								case SDLK_ESCAPE:
								if (pause==0)
								{
									jogar=0;
									pause=1;
									Mix_PauseMusic();
								}
								break;
								
								case SDLK_RETURN:
								break;
								
								case SDLK_F8:
									if(mute==0)
									{
										contador_notificacao=0;
										mute=1;
										tipo_notificacao=1;
									}
									else if(mute==1)
									{
										contador_notificacao=0;
										mute=0;
										tipo_notificacao=2;
									}
								break;	
							}
						break;
										
						case SDL_KEYUP: 
							switch(event.key.keysym.sym)
							{
								case SDLK_UP:
								move[0]=0;
								break;
											
								case SDLK_LEFT:
								move[1]=0;
								break;
										
								case SDLK_DOWN:
								move[2]=0;
								break;
										
								case SDLK_RIGHT:
								move[3]=0;
								break;
								
								case SDLK_SPACE:
								atirar=0;
								break;
							}
						break;			
						}			
				}

			
				//animacoes morcego
			
				setexplosion(rect_explosao);
				
				setbackground(rect_nuvens);	
				
				//Blita o espaço
				SDL_BlitSurface(espaco, NULL, janela, NULL);
								
				//Blita as nuvens
				SDL_BlitSurface(nuvens,&rect_nuvens[frame_nuvens], janela, NULL);
				
				//Blita a barra de pontuacao
				SDL_BlitSurface(barra_pontuacao,NULL, janela, &rect_pontuacao);
				
				//Blita a nave
				if(velocidade==0)
				angulonave = rotozoomSurface(nave,angulo,1.0,1);
				
				if(velocidade>0&&velocidade<=3)
				angulonave = rotozoomSurface(nave2,angulo,1.0,1);
				
				if(velocidade>3&&velocidade<=6)
				angulonave = rotozoomSurface(nave3,angulo,1.0,1);
				
				if(velocidade>6&&velocidade<=9)
				angulonave = rotozoomSurface(nave4,angulo,1.0,1);
				
				if(velocidade>9&&velocidade<=12)
				angulonave = rotozoomSurface(nave5,angulo,1.0,1);
				
				if(velocidade>=12)
				angulonave = rotozoomSurface(nave6,angulo,1.0,1);
								
				SDL_Rect posicaonave={(int) x,(int) y,0,0};	
				posicaonave.x-=angulonave->w/2-nave->w/2;
				posicaonave.y-=angulonave->h/2-nave->h/2;
				
				SDL_Rect posicaoescudo={(int) x,(int) y,0,0};
								
				// Blita e centraliza a Nave 

				if(dead==0)
				{		
					SDL_BlitSurface(angulonave,NULL, janela, &posicaonave);
				}
				
				
				//sprintf(abatido_txt, "Inimigos Abatidos: %d", abatido);
				//escreverTexto(660,15,abatido_txt,255,255,255,14);
				
				sprintf(pontuacao_txt, "%d", pontuacao);
				escreverTexto(620,20,pontuacao_txt,255,255,255,30);
				
				//Blita o mute
				if(mute==1)
				{
					SDL_BlitSurface(mute_img,&mute_on,janela,&rect_mute);
					Mix_VolumeChunk(death_bat,0);
					Mix_VolumeChunk(efeito,0);
					Mix_VolumeChunk(shot_sound,0);
					Mix_VolumeChunk(explosao_nave,0);
					Mix_VolumeChunk(multiplicador_sound,0);
					Mix_VolumeMusic(0);
				}				
				if(mute==0)				
				{
					SDL_BlitSurface(mute_img,&mute_off,janela,&rect_mute);
					Mix_VolumeChunk(death_bat,32);	
					Mix_VolumeChunk(efeito,16);
					Mix_VolumeChunk(shot_sound,32);
					Mix_VolumeChunk(explosao_nave,16);
					Mix_VolumeChunk(multiplicador_sound,32);
					Mix_VolumeMusic(48);
				}			

				if(abatido==25)
					Mix_PlayChannel(-1,multiplicador_sound,0);
				
				if(abatido==50)
					Mix_PlayChannel(-1,multiplicador_sound,0);
					
				if(abatido==100)
					Mix_PlayChannel(-1,multiplicador_sound,0);
				
					
				//Blita multiplicador			
				if(abatido<25)
				{
					SDL_BlitSurface(multi_1x,NULL,janela,&rect_multiplicador);
					multiplicador=1;
				}
									
				if(abatido>=25&&abatido<50)
				{
					SDL_BlitSurface(multi_2x,NULL,janela,&rect_multiplicador);
					multiplicador=2;
				}	
				
				if(abatido>=50&&abatido<100)	
				{
					SDL_BlitSurface(multi_4x,NULL,janela,&rect_multiplicador);
					multiplicador=4;
					tipo_notificacao=4;
				}
				
				if(abatido>=100)
				{
					SDL_BlitSurface(multi_8x,NULL,janela,&rect_multiplicador);
					multiplicador=8;
					tipo_notificacao=5;
				}
				
				if(abatido==25)
				tipo_notificacao=3;
				
				if(abatido==50)
				tipo_notificacao=4;
					
				if(abatido==100)
				tipo_notificacao=5;
					
				//Blita recarga		
				//sprintf(recarga_txt, "%d", recarga);
				//escreverTexto(15,550,recarga_txt,255,255,255,18);

				//animacao morcego
				setanimation(rect_morcego);
				
				setanimation2(rect_morcego2);
				
				setanimation3(rect_morcego3);
				
				setexplosion(rect_explosao);
				
				animanave(rect_naveanimada);
				
				animatiro(rect_tiro);
				
				//Blitando
				for( contador = 0; contador < 24; contador++){
					
					if(asteroides[contador].destruido == 0){
						
						if(asteroides[contador].tipo == 8)
							SDL_BlitSurface( morcego, &rect_morcego2[frame_morcego], janela, &asteroides[contador].quadAsteroid);
						
						if(asteroides[contador].tipo == 4)
							SDL_BlitSurface( morcego_medio, &rect_morcego3[frame_morcego1], janela, &asteroides[contador].quadAsteroid);
						
						if(asteroides[contador].tipo == 2)
							SDL_BlitSurface( morcego,&rect_morcego[frame_morcego2], janela, &asteroides[contador].quadAsteroid);
					}				
				}
				
				
				//Movimentacao
				for(contador = 0; contador < 24; contador++){
			
					if(asteroides[contador].destruido == 0){
						asteroide_x = asteroides[contador].quadAsteroid.x;
						asteroide_y = asteroides[contador].quadAsteroid.y;
								
						asteroide_x -= (sin(asteroides[contador].anguloAsteroid * M_PI/180.0)*dificuldade);
						asteroide_y -= (cos(asteroides[contador].anguloAsteroid * M_PI/180.0)*dificuldade);
								
						asteroides[contador].quadAsteroid.x = (int) asteroide_x;
						asteroides[contador].quadAsteroid.y = (int) asteroide_y;
								
						if(asteroides[contador].quadAsteroid.x >= 800)
							asteroides[contador].quadAsteroid.x = 0;

						if(asteroides[contador].quadAsteroid.x < 0)
							asteroides[contador].quadAsteroid.x = 800 - asteroides[contador].quadAsteroid.w;
						
						if(asteroides[contador].quadAsteroid.y >= 600)
							asteroides[contador].quadAsteroid.y = 0;
										
						if(asteroides[contador].quadAsteroid.y < 0)
							asteroides[contador].quadAsteroid.y = 600 - asteroides[contador].quadAsteroid.h;
							}
				}
				
				//Colisao Asteroide com Nave
				
				for(contador = 0; contador < 24; contador++){
				
				
				if(asteroides[contador].destruido==0 && (colisao_tiro(tiro[0].quadTiro, asteroides[contador].quadAsteroid) == 1)&&(tiro[0].exists)==true)
				{
						if(asteroides[contador].tipo == 8)
							pontuacao += 10*multiplicador+10*dificuldade;
							
						else if(asteroides[contador].tipo == 4)
							pontuacao += 20*multiplicador+20*dificuldade;
						else 
							pontuacao += 30*multiplicador+30*dificuldade;
							
						frame_explosao=0;		
						quadDeath.x=asteroides[contador].quadAsteroid.x;
						quadDeath.y=asteroides[contador].quadAsteroid.y;
						asteroide_destruiu=1;	
							
						abatido+=1;	
						
						Mix_PlayChannel(-1,death_bat,0);	
							
						tiro[0].exists=false;	
						
						soma = destroiAsteroid(asteroides, soma, contador);
				}
				
				if(asteroides[contador].destruido==0 && (colisao_tiro(tiro[1].quadTiro, asteroides[contador].quadAsteroid) == 1)&&(tiro[1].exists==true))
				{
						if(asteroides[contador].tipo == 8)
							pontuacao += 10*multiplicador+10*dificuldade;
							
						else if(asteroides[contador].tipo == 4)
							pontuacao += 20*multiplicador+20*dificuldade;
						else 
							pontuacao += 30*multiplicador+30*dificuldade;
							
					frame_explosao=0;			
					quadDeath.x=asteroides[contador].quadAsteroid.x;
					quadDeath.y=asteroides[contador].quadAsteroid.y;
					asteroide_destruiu=1;		
							
							
					abatido+=1;			
					
					Mix_PlayChannel(-1,death_bat,0);
					
					tiro[1].exists=false;	
						
					soma = destroiAsteroid(asteroides, soma, contador);
				}
				
				if(asteroides[contador].destruido==0 && (colisao_tiro(tiro[2].quadTiro, asteroides[contador].quadAsteroid) == 1)&&(tiro[2].exists==true))
				{
						if(asteroides[contador].tipo == 8)
						pontuacao += 10*multiplicador+10*dificuldade;
							
						else if(asteroides[contador].tipo == 4)
							pontuacao += 20*multiplicador+20*dificuldade;
						else 
							pontuacao += 30*multiplicador+30*dificuldade;
							
						frame_explosao=0;		
						quadDeath.x=asteroides[contador].quadAsteroid.x;
						quadDeath.y=asteroides[contador].quadAsteroid.y;
						asteroide_destruiu=1;	

						abatido+=1;		
						
						Mix_PlayChannel(-1,death_bat,0);
							
						tiro[2].exists=false;	
						
						soma = destroiAsteroid(asteroides, soma, contador);
				}
				
				if(asteroides[contador].destruido==0 && (colisao_tiro(tiro[3].quadTiro, asteroides[contador].quadAsteroid) == 1)&&(tiro[3].exists==true))
				{
						if(asteroides[contador].tipo == 8)
							pontuacao += 10*multiplicador+10*dificuldade;
							
						else if(asteroides[contador].tipo == 4)
							pontuacao += 20*multiplicador+20*dificuldade;
						else 
							pontuacao += 30*multiplicador+30*dificuldade;
							
						frame_explosao=0;		
						quadDeath.x=asteroides[contador].quadAsteroid.x;
						quadDeath.y=asteroides[contador].quadAsteroid.y;
						asteroide_destruiu=1;
							
						abatido+=1;		
						
						Mix_PlayChannel(-1,death_bat,0);
										
						tiro[3].exists=false;	
						
						soma = destroiAsteroid(asteroides, soma, contador);
				}
				if(asteroides[contador].destruido==0 && (colisao_tiro(tiro[4].quadTiro, asteroides[contador].quadAsteroid) == 1)&&(tiro[4].exists==true))
				{
						if(asteroides[contador].tipo == 8)
							pontuacao += 10*multiplicador+10*dificuldade;
							
						else if(asteroides[contador].tipo == 4)
							pontuacao += 20*multiplicador+20*dificuldade;
						else 
							pontuacao += 30*multiplicador+30*dificuldade;
						
						frame_explosao=0;	
						quadDeath.x=asteroides[contador].quadAsteroid.x;
						quadDeath.y=asteroides[contador].quadAsteroid.y;
						asteroide_destruiu=1;	
							
						abatido+=1;		
							
						tiro[4].exists=false;	
						
						soma = destroiAsteroid(asteroides, soma, contador);

				}
					
				if((asteroides[contador].destruido==0) && ((colisao_nave(x, y, asteroides[contador].quadAsteroid, angulonave))==1)&&escudo==0&&dead==0){
					
					soma = destroiAsteroid(asteroides, soma, contador);
					Mix_PlayChannel(-1,explosao_nave,0);
					vida-=1;
					dead=1;
					frame_explosao=0;
					abatido=0;
					multiplicador=1;
					quadExplode.x=posicaonave.x;
					quadExplode.y=posicaonave.y;
					
					quadEscudo.x=posicaonave.x;
					quadEscudo.y=posicaonave.y;
					
					retorna(&x, &y, &velocidade, &angulo);
				}
					
			}

				if(dead==1)
				SDL_BlitSurface(explosao,&rect_explosao[frame_explosao], janela, &quadExplode);
			
				
				if(escudo==1)
					SDL_BlitSurface(img_escudo,NULL,janela, &posicaonave);
						
	
				total_vidas[0].vida.x=15;
				total_vidas[0].vida.y=3;
				total_vidas[0].vida.w=30;
				total_vidas[0].vida.h=49;
				
				total_vidas[1].vida.x=55;
				total_vidas[1].vida.y=3;
				total_vidas[1].vida.w=30;
				total_vidas[1].vida.h=49;
				
				total_vidas[2].vida.x=95;
				total_vidas[2].vida.y=3;
				total_vidas[2].vida.w=30;
				total_vidas[2].vida.h=49;
			
				if(vida>=0)
				{
					for(i=0;i<vida;i++)
					{

					SDL_BlitSurface(vida_img,NULL,janela,&total_vidas[i].vida);
					}
				}
				
				////Lógic		
				

				
				int colisao_tiro(SDL_Rect a, SDL_Rect b)
				{
				 if(b.x + b.w < a.x) //- b.direita < a.esquerda
				    return 0;
				 if(b.x > a.x + a.w) //- b.esquerda > a.direita
				    return 0;
				 if(b.y + b.h < a.y) //- b.baixo < a.cima
				    return 0;
				 if(b.y > a.y + a.h) //- b.cima > a.baixo
				    return 0;
				
				 return 1; //- ret�ngulos se colidem
				}
					
								
		if(atirar == 1&& numero_tiros>0 && dead==0 &&recarga>90){
					
			Mix_PlayChannel(-1,shot_sound,0);
			
			for(i=0;i<numero_tiros;i++)
			{ 
				if(tiro[i].exists == false)
				{ 
					tiro[i].exists = true;
					tiro[i].angulo_tiro = angulo; 
					
					tiro[i].quadTiro.x = posicaonave.x;
					tiro[i].quadTiro.y = posicaonave.y;
				break;
				} 
			}
			recarga=0;
		}
		
		for( i=0;i<numero_tiros;i++)
			{

				if(tiro[i].exists == true) 
				{
				
				SDL_BlitSurface(tiro_animado,&rect_tiro[frame_tiro],janela,&tiro[i].quadTiro);
				
				tiro[i].quadTiro.x -= desloca_x(tiro[i].angulo_tiro,vel_tiro);
				tiro[i].quadTiro.y -= desloca_y(tiro[i].angulo_tiro,vel_tiro);
				}
			}
		
		if(move[0] == 1){
			angulo_nave = angulo;
			
			x -= desloca_x(angulo_nave,velocidade);
			y -= desloca_y(angulo_nave,velocidade);
			escudo=0;
			

			
			if(velocidade < 20)
				velocidade += 1.8;
			
		}
				
		if(move[1] == 1)
		{	
			angulo += 5;
			escudo=0;
		}
		
		if(move[2] == 1)
		{	
			if(velocidade>0)
			velocidade-=1.5;
		}
			
		if(move[3] == 1)
		{
			angulo -= 5;
			escudo=0;
		}
				if(1000/FPS	>(SDL_GetTicks()-start))
					SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
					
					if(x < 0)
						x = 800 - angulonave -> w;	
													
					if(x >= 800)
						x = 0;
						
					if(y < 0)
						y = 600 - angulonave -> h;	
											
					if(y >= 600)
						y = 0;
		
		for(i=0;i<numero_tiros;i++)
		{
			if(tiro[i].quadTiro.x>=800)
				tiro[i].exists=false;
			if(tiro[i].quadTiro.x<=0)
				tiro[i].exists=false;
			if(tiro[i].quadTiro.y>=600)
				tiro[i].exists=false;
			if(tiro[i].quadTiro.y<=0)
				tiro[i].exists=false;
		}
		
		
		if(move[0] == 0){
			if(velocidade > 0)
				velocidade -= 0.5;

			x -= desloca_x(angulo_nave,velocidade);
			y -= desloca_y(angulo_nave,velocidade);
			
		}
		
		if(vida<0)
		{	
			fprintf(ranking,"%s %d \n",nome_jogador,pontuacao);	
			jogar=0;
			gameover=1;

		}
		
		frame_morcego+=1;
		frame_morcego1+=1;
		frame_morcego2+=1;
				
		frame_explosao+=1;	
		
		if(contador_notificacao==100)
		{
			tipo_notificacao=0;
			contador_notificacao=0;
		}
			
		if(tipo_notificacao!=0)
			contador_notificacao+=1;	
		
		if(tipo_notificacao==1&&contador_notificacao<=100)
		{
			SDL_BlitSurface(mute_on_txt,NULL,janela,&notificacao);
		}
		
		if(tipo_notificacao==2&&contador_notificacao<=100)
		{
			SDL_BlitSurface(mute_off_txt,NULL,janela,&notificacao);
		}
		
		if(tipo_notificacao==3&&contador_notificacao<=100)
		{
			SDL_BlitSurface(multi_2x,NULL,janela,&notificacao);
		}
		
		if(tipo_notificacao==4&&contador_notificacao<=100)
		{
			SDL_BlitSurface(multi_4x,NULL,janela,&notificacao);
		}
		
		if(tipo_notificacao==5&&contador_notificacao<=100)
		{
			SDL_BlitSurface(multi_8x,NULL,janela,&notificacao);
		}
			
						
		if(dead==1)
			frame_explosao+=1;
		
		if(frame_explosao>=15&&asteroide_destruiu==1)
		{
			frame_explosao=0;
			dead=0;
			asteroide_destruiu=0;
		}
		
		if(frame_explosao>=15&&dead==1)
		{	
			frame_explosao=0;
			escudo=1;
			dead=0;
		}
	
		escreverTexto(300,2,"dificuldade",255,255,255,14);
		
		if(pontuacao>=0&&pontuacao<5000)
		{
			escreverTexto(300,25,"Regular",255,255,255,20);
			dificuldade=3;
		}
		
		if(pontuacao>=5000&&pontuacao<10000)
		{
			escreverTexto(300,25,"Die Hard",255,255,0,20);
			dificuldade=4;
			
		}
		
		if(pontuacao>=10000&&pontuacao<20000)
		{
			escreverTexto(300,25,"Dominating",255,86,0,20);
			dificuldade=5;
		}
		
		if(pontuacao>=20000&&pontuacao<50000)
		{
			escreverTexto(300,25,"GODLIKE",255,0,0,24);
			dificuldade=6;
		}
		
		if(pontuacao>=50000)
		{
			escreverTexto(300,25,"LEGENDARY",94,23,206,30);
			dificuldade=7;
		}
			
		if(asteroide_destruiu==1)
		{
			SDL_BlitSurface(explosao,&rect_explosao[frame_explosao], janela, &quadDeath);
		}
		
		if(velocidade<0)
			velocidade=0;
		
		if((frame_nuvens>0)&&(dinamico==true))
			frame_nuvens++;
		
		if((frame_nuvens<=195)&&(dinamico==false))
			frame_nuvens--;
			
		if((frame_nuvens==0)&&(dinamico==true))
			frame_nuvens++;
			
		if(frame_nuvens >= 195)
		{
			dinamico=false;
		}
		
		if(frame_nuvens==0)
			dinamico=true;
		
		recarga+=15;
		
		if (recarga>=100)
		{
		recarga=100;
		}
		
		frame_tiro+=1;
		
		if(frame_tiro==8)
			frame_tiro=0;
				
		if(frame_morcego==16)
			frame_morcego=0;
		
		if(frame_morcego1==16)
			frame_morcego1=0;
			
		if(frame_morcego2==16)
			frame_morcego2=0;
			
			
		SDL_Flip(janela);
		}
		
		while(pagina_record == 1){
			
			SDL_BlitSurface(pagina_recordes,NULL,janela,NULL);
			SDL_Event event;
	
			while(SDL_PollEvent(&event)){
			
				switch(event.type){
				
					case SDL_QUIT:
						record = 0;
						menu = 0;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym){
					
							case SDLK_ESCAPE:
								pagina_record = 0;
								break;
							
							default:
								break;
					}
					default:
						break;
				
				}
			}
		
			SDL_Flip(janela);
		
			if(1000/FPS > SDL_GetTicks() - start)
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
		
		
		//instruções
		while(paginadeinstrucoes == 1){
			
			SDL_FillRect(janela,NULL,0);
			
			SDL_BlitSurface(instrucoes, NULL, janela, &quad);	
			
			SDL_Flip(janela);
			
			SDL_Event event;
		
			while(SDL_PollEvent(&event)){
			
				switch(event.type){
				
					case SDL_QUIT:
						menu = 0;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym){
					
							case SDLK_RETURN:
								paginadeinstrucoes = 0;
								break;
							case SDLK_ESCAPE:
								paginadeinstrucoes = 0;
								break;	
								
							
							default:
								break;
					}
					default:
						break;
				}
			}
			if(1000/FPS > SDL_GetTicks() - start)
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
		
		
		
		while(gameover == 1){
			
			int seleciona=0;
			
			SDL_BlitSurface(gameover_screen, NULL, janela, &quad);	
			
			SDL_BlitSurface(escolha,NULL,janela,&select_over);
			
			SDL_Event event;
		
			while(SDL_PollEvent(&event)){
			
				switch(event.type){
				
					case SDL_QUIT:
						menu=0;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym){

							case SDLK_RIGHT:
								Mix_PlayChannel(-1,efeito,0);
								if(select_over.x==250)
								{
								select_over.x=420;
								opcao_over=2;
								}
								else if(select_over.x==420)
								{
								select_over.x=250;
								opcao_over=1;
								}
								break;
								
							case SDLK_LEFT:
								Mix_PlayChannel(-1,efeito,0);
								if(select_over.x==250)
								{
								select_over.x=420;
								opcao_over=2;
								}
								else if(select_over.x==420)
								{
								select_over.x=250;
								opcao_over=1;
								}
								break;	
								
							case SDLK_RETURN:
								seleciona=1;
								break;
								
								
							case SDLK_a:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'a';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_b:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'b';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_c:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'c';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_d:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'd';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_e:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'e';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_f:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'f';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_g:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'g';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_h:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'h';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_i:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'i';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_j:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'j';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_k:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'k';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_l:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'l';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_m:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'm';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_n:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'n';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_o:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'o';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_p:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'p';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_q:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'q';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_r:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'r';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_s:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 's';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_t:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 't';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_u:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'u';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_v:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'v';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_w:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'w';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_x:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'x';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_y:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'y';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_z:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'z';
									posicao_nome++;
								}
								
								break;
							
							case SDLK_BACKSPACE:
								
								if(posicao_nome > 0){
									
									posicao_nome--;
									nome_jogador[posicao_nome] = '\0';
									
								}	
								break;
								
							default:
								break;
					}
					default:
						break;
				}
				
					if(seleciona==1)
					{
								if(opcao_over==1)
								{
								abatido=novojogo(abatido);
								pontuacao=0;
								jogar=1;
								gameover=0;
								velocidade=0;
								}								
								else if(opcao_over==2)
								{
								Mix_PlayMusic(musica_menu,-1);
								gameover=0;
								jogar=0;
								menu=1;
								}
					}
					
			SDL_Flip(janela);	
								
			}
		
			if(1000/FPS > SDL_GetTicks() - start)
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
		
			while(pause == 1){
			SDL_FillRect(janela,NULL,0);
			SDL_BlitSurface(pause_screen,NULL,janela,NULL);
			SDL_BlitSurface(escolha,NULL,janela,&select_pause);
		
			
			SDL_Flip(janela);
			
			SDL_Event event;
			
		
			while(SDL_PollEvent(&event)){
			
				switch(event.type){
				
					case SDL_QUIT:
						menu=0;
						pause=0;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym){
					
							case SDLK_ESCAPE:
								if (pause==1)
								{
									pause=0;
									jogar=1;
									Mix_ResumeMusic();
								}
								break;
					
					
							case SDLK_RETURN:
								Mix_ResumeMusic();
								if(opcao_pause==1)
								{
									pause=0;
									jogar=1;
								}
								else if(opcao_pause==2)
								{
									Mix_PlayMusic(musica_menu,-1);
									pause=0;
									jogar=0;
								}
								else if(opcao_pause==3)
								{
									pause=0;
									jogar=0;
									menu=0;
								}		
									
								break;
								
							
							case SDLK_DOWN:
								if(select_pause.y==362)
								{
									Mix_PlayChannel(-1,efeito,0);
									select_pause.y=413;
									opcao_pause=2;
								}
								
								else if(select_pause.y==413)
								{
									Mix_PlayChannel(-1,efeito,0);
									select_pause.y=464;
									opcao_pause=3;
								}
								
								else if(select_pause.y==464)
								{
									Mix_PlayChannel(-1,efeito,0);
									select_pause.y=362;
									opcao_pause=1;
								}
								
								break;
								
								case SDLK_UP:
								if(select_pause.y==362)
								{
									Mix_PlayChannel(-1,efeito,0);
									select_pause.y=464;
									opcao_pause=3;
								}
								
								else if(select_pause.y==413)
								{
									Mix_PlayChannel(-1,efeito,0);
									select_pause.y=362;
									opcao_pause=1;
								}
								
								else if(select_pause.y==464)
								{
									Mix_PlayChannel(-1,efeito,0);
									select_pause.y=413;
									opcao_pause=2;
								}
								
								break;
								
							
							default:
								break;
					}
					default:
						break;
				}
			}

			SDL_Flip(janela);
		
			if(1000/FPS > SDL_GetTicks() - start)
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
		
		while(troca_nome == 1){
					
			nome_ttf = TTF_RenderText_Blended(fonte2, nome_jogador, gray);
			
			SDL_BlitSurface(trocadenome_img, NULL, janela, &quad);	
			
			SDL_BlitSurface(nome_ttf, NULL, janela, &rect_trocanome);
			
		
			
			//SDL_BlitSurface(escolha,NULL,janela,&select_over);
			
			SDL_Event event;
		
			while(SDL_PollEvent(&event)){
			
				switch(event.type){
				
					case SDL_QUIT:
						menu=0;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym){
								
							case SDLK_RETURN:
								rewind(fo);
								fprintf(fo,"%s \n", nome_jogador);							
								troca_nome=0;
								
								break;
								
								
							case SDLK_a:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'A';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_b:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'B';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_c:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'C';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_d:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'D';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_e:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'E';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_f:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'F';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_g:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'G';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_h:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'H';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_i:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'I';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_j:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'J';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_k:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'K';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_l:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'L';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_m:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'M';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_n:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'N';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_o:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'O';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_p:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'P';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_q:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'Q';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_r:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'R';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_s:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'S';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_t:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'T';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_u:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'U';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_v:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'V';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_w:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'W';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_x:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'X';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_y:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'Y';
									posicao_nome++;
								}
								
								break;
								
							case SDLK_z:
								
								if(posicao_nome < 10){
									
									nome_jogador[posicao_nome] = 'Z';
									posicao_nome++;
								}
								
								break;
							
							case SDLK_BACKSPACE:
								
								if(posicao_nome > 0){
									
									posicao_nome--;
									nome_jogador[posicao_nome] = '\0';
								}	
								break;
								
							default:
								break;
					}
					default:
						break;
				}
				
					
			SDL_Flip(janela);	
								
			}
		
			if(1000/FPS > SDL_GetTicks() - start)
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
		
		
		while(pagina_creditos == 1){
			
			SDL_FillRect(janela,NULL,0);
			
			SDL_BlitSurface(creditos_img, NULL, janela, &quad);	
			
			SDL_Flip(janela);
			
			SDL_Event event;
		
			while(SDL_PollEvent(&event)){
			
				switch(event.type){
				
					case SDL_QUIT:
						menu = 0;
						break;

					case SDL_KEYDOWN:
				
						switch(event.key.keysym.sym){
					
							case SDLK_RETURN:
								pagina_creditos = 0;
								break;
							case SDLK_ESCAPE:
								pagina_creditos = 0;
								break;	
								
							
							default:
								break;
					}
					default:
						break;
				}
			}
			if(1000/FPS > SDL_GetTicks() - start)
				SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
		

	}

	
	Mix_FreeChunk(efeito);
	Mix_FreeChunk(shot_sound);
	Mix_FreeChunk(explosao_nave);
	Mix_FreeChunk(death_bat);
	
	SDL_FreeSurface(nave);
	SDL_FreeSurface(nave2);
	SDL_FreeSurface(nave3);
	SDL_FreeSurface(nave4);
	SDL_FreeSurface(nave5);
	SDL_FreeSurface(nave6);
	SDL_FreeSurface(espaco);
	SDL_FreeSurface(angulonave);
	SDL_FreeSurface(texto);
	SDL_FreeSurface(tiro_nave);
	SDL_FreeSurface(tiro_rotated);
	SDL_FreeSurface(asteroide);
	SDL_FreeSurface(vida_img);
	SDL_FreeSurface(morcego);
	SDL_FreeSurface(morcego_medio);
	SDL_FreeSurface(explosao);
	SDL_FreeSurface(nuvens);
	SDL_FreeSurface(img_escudo);
	SDL_FreeSurface(tiro_animado);
	SDL_FreeSurface(gameover_screen);
	

	
	Mix_FreeMusic(musica_jogo);
	Mix_FreeMusic(musica_menu);
	Mix_CloseAudio();
	
	return 0;
	} 


