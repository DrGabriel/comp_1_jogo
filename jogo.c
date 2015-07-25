///UFRRJ
///COMPUTACAO 1 2015
///GABRIEL SANTOS, LUCAS MATTOS, RODRIGO QUEIROZ,JOEL LEMOS.
///Jogo baseado em donkey kong
/// versao do SDL: 1.2.15

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include<string.h>

/* Desfinicoes da configuracao do Video */
#define LARGURA 800 /* Numero total de colunas*largura_da_parede */
#define ALTURA  600 /* Numero total de linhas*altura_da_parede */
#define BPP       0 /* A Flag SDL_ANYFORMAT se encaregara da resolucao */
#define FPS 20
#define TILE_SIZE_W 34
#define TILE_SIZE_H 18
#define LADDER_SIZE_W 34
#define LADDER_SIZE_H 18
#define MAX_MAP_Y 33
#define MAX_MAP_X 22
#define MAX_FALL_SPEED 10.0
#define BLANK_TILE 0






//variaveis globais
SDL_Event event;

Mix_Music *musica=NULL;
Mix_Chunk *som_pulo=NULL;
Mix_Chunk *batida=NULL;
Mix_Chunk *espada_barril;

SDL_Surface *tela=NULL;
SDL_Surface *rato=NULL;
SDL_Surface *fundo=NULL;
SDL_Surface *piso=NULL;
SDL_Surface *escada=NULL;
SDL_Surface *queijo=NULL;
SDL_Surface *rata=NULL;
SDL_Surface *lorde_cheddar=NULL;
SDL_Surface *espada=NULL;
SDL_Surface *tela_game_over=NULL;
SDL_Surface *tela_1=NULL;
SDL_Surface *tela_2=NULL;
SDL_Surface *tela_3=NULL;
SDL_Surface *tela_4=NULL;
SDL_Surface *tela_5=NULL;
SDL_Surface *tela_instrucoes=NULL;
SDL_Surface *tela_creditos=NULL;
SDL_Surface *tela_ranking=NULL;
SDL_Surface *tela_recordes=NULL;

SDL_Rect plataformapos[MAX_MAP_Y][MAX_MAP_X];
SDL_Rect player_pos;
SDL_Surface *texto_nome_do_jogador=NULL;
SDL_Surface *texto_pontuacao=NULL;
SDL_Surface *texto1=NULL;
SDL_Surface *texto2=NULL;
SDL_Surface *texto3=NULL;
SDL_Surface *texto4=NULL;
SDL_Surface *texto_nome=NULL;
SDL_Surface *texto_nome_1=NULL;
SDL_Surface *texto_nome_2=NULL;
SDL_Surface *texto_nome_3=NULL;
SDL_Surface *texto_pontos=NULL;
SDL_Surface *texto_pontos_1=NULL;
SDL_Surface *texto_pontos_2=NULL;
SDL_Surface *texto_pontos_3=NULL;
SDL_Surface *texto_vida=NULL;
SDL_Surface *texto_vidas=NULL;
SDL_Surface *texto_nome_personagem=NULL;
SDL_Surface *texto_bonus=NULL;
SDL_Surface *texto_bonus_1=NULL;
SDL_Surface *texto_sua_pontuacao=NULL;
SDL_Surface *texto_sua_pontuacao_1=NULL;
SDL_Surface *texto_maior_pontuacao=NULL;
SDL_Surface *texto_pular=NULL;

TTF_Font *fonteTeste=NULL;
char *IMG_GetError();
int pontos[20];
int muda_img_lorde=0;
int n, left,right,jogo=1,pulo=0,up=0,down=0,ground=1,i=10,vel_muda=40,plataform_h=34,plataform_w=18,platx=34,e_escada=0,subindo=0,e_chao=1,pontucao=0,taca_outro=80;
float force,gravity=0.5,posicaoatualy=0,posicaoatualx=0;
float gravidade = 0.5;
int b[4]= {0,0,0,0};
int side;
int xx;
int yy;
int deuruim=0;
int pulou=0;
int barril_1_img=10;
int barril_2_img=10;
int barril_3_img=10;
int barril_4_img=10;
int barril_5_img=10;
int tamanho;
int jogar=0;
int muda_tela=0;
int n_enter=0;
int limpa;
int pontos_1[3];
int pontuacao_1,pontuacao_2,pontuacao_3;
char nome_1[20];
char nome_2[20];
char nome_3[20];
char nome_1_ler[20];
char nome_2_ler[20];
char nome_3_ler[20];
char nome_total[3][20];
FILE *arq_1, *arq_2;
    int fecha;
float vel_barril_x=6.0;
int historia=0;
int troca_frame=0;
char nome_jogador[20],nome_digitado[20];
int digita_recorde=0;
int prox_linha=0;
int pontos_ler[20];
int pontos_2[20];
int pontos_3[20];
int escreve=0;
int player_vida=3;
int tem_espada=0;
int e_esquerda=0;
int e_direita=0;
int z_pressionado=0;
int remove_espada=400;
int mostra_ranking=0;
int vidas[4];
int bonus=4000;
int bonus_total[10];
int diminui_bonus=100;
int fecha_tela=20;
int acabou=0;

Uint32 tempo;
Uint32 tempo_2;



typedef struct PLAYER Player;
struct PLAYER
{
     float sx, sy, dx, dy, velx, vely;
     int largura, altura, pulo;
     int thinkTime;
     int onGround;
};

Player player;



typedef struct BARRIL Barril;
struct BARRIL
{
    float sx_1[6],sy_1[6],dx_1[6],dy_1[6],velx_1[6],vely_1[6];
    int largura_1, altura_1;
};

Barril barril;

typedef struct BARRIL_1 Barril_1;
struct BARRIL_1
{
    float sx_10,sy_10,dx_10,dy_10,velx_10,vely_10;
    int largura_10, altura_10;
};

Barril_1 barril_1;

typedef struct BARRIL_2 Barril_2;
struct BARRIL_2
{
    float sx_100,sy_100,dx_100,dy_100,velx_100,vely_100;
    int largura_100, altura_100;
};

Barril_2 barril_2;

typedef struct BARRIL_3 Barril_3;
struct BARRIL_3
{
    float sx_1000,sy_1000,dx_1000,dy_1000,velx_1000,vely_1000;
    int largura_1000, altura_1000;
};

Barril_3 barril_3;




typedef struct PLATAFORMA Plataforma;
struct PLATAFORMA
{
    float sx_2,sy_2,dx_2,dy_2,velx_2,vely_2;
    int largura_2, altura_2, pulo_2;
};

Plataforma plataforma;

typedef struct LORDE Lorde;
struct LORDE
{
    float sx_3,sy_3,dx_3,dy_3,velx_3,vely_3;
    int largura_3, altura_3;
};

Lorde lorde;


typedef struct MAP Map;
struct MAP
{
    int tile[MAX_MAP_Y][MAX_MAP_X];
    int startX, startY;
    int maxX, maxY;
} ;
Map map;

int collision(SDL_Rect *a, SDL_Rect *b)
{
    if(a->y >= b->y + b->h)
        return 0;
    if(a->x >= b->x + b->w)
        return 0;
    if(a->y + a->h <= b->y)
        return 0;
    if(a->x + a->w <= b->x)
        return 0;
    return 1;
}



void tela_menu()
{
    int a,b,c,d;



       if(digita_recorde==0 && acabou==0)
       {

           switch(event.type)
            {
            case SDL_QUIT:
                jogo = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
            case SDLK_RETURN:
                if(muda_tela==1)
                {

                    historia=1;
                }
                else
                if(muda_tela==2)
                {
                    tela_1= IMG_Load("img/Jogo/Telas/tela_instrucoes.png");
                    n_enter=1;
                }
                else
                if(muda_tela==3)
                {
                    tela_1= IMG_Load("img/Jogo/Telas/tela_ranking.png");
                    n_enter=1;


                      mostra_ranking=1;


                }
                else
                if(muda_tela==4)
                {
                    tela_1= IMG_Load("img/Jogo/Telas/tela_sobre.png");
                    n_enter=1;
                }



                break;
            case SDLK_ESCAPE:
                    jogo=0;
                    break;


                case SDLK_LEFT:
                    if(!n_enter)
                    {
                        muda_tela--;
                    }
                    mostra_ranking=0;
                    n_enter=0;
                    break;


                case SDLK_RIGHT:
                    muda_tela++;
                    break;


                }
                break;

        }

    if(muda_tela==0)
    {
        tela_1= IMG_Load("img/Jogo/Telas/tela_inicio_1.png");
    }
    if(muda_tela==1 && historia==0)
    {
        tela_1= IMG_Load("img/Jogo/Telas/tela_inicio_2.png");
    }
    if(muda_tela==2 && n_enter==0)
    {
        tela_1= IMG_Load("img/Jogo/Telas/tela_inicio_3.png");
    }
    if(muda_tela==3 && n_enter==0)
    {
        tela_1= IMG_Load("img/Jogo/Telas/tela_inicio_4.png");
    }
    if(muda_tela==4 && n_enter==0)
    {
        tela_1= IMG_Load("img/Jogo/Telas/tela_inicio_5.png");
    }


    if(muda_tela==3 && n_enter==1)
    {

    }

    if(muda_tela>4)
    {
        muda_tela=0;
    }
    if(muda_tela<0)
    {
        muda_tela=4;
    }
    SDL_BlitSurface(tela_1,NULL,tela,NULL);
    if(mostra_ranking)
    {
        arq_2=fopen("arquivos/recordes_pontos.txt","r");
            fscanf(arq_2,"%d",&pontuacao_1);
            fscanf(arq_2,"%d",&pontuacao_2);
            fscanf(arq_2,"%d",&pontuacao_3);
            fclose(arq_2);
            arq_1=fopen("arquivos/recordes.txt","r");
            fscanf(arq_1,"%s",&nome_1);
            fscanf(arq_1,"%s",&nome_2);
            fscanf(arq_1,"%s",&nome_3);
            fclose(arq_1);

            fonteTeste=TTF_OpenFont("teste.ttf",50);
 SDL_Color fonteCor={0,0,0};

texto_nome=TTF_RenderText_Solid(fonteTeste,"-NOMES-",fonteCor);
texto_nome_1=TTF_RenderText_Solid(fonteTeste,nome_1,fonteCor);
texto_nome_2=TTF_RenderText_Solid(fonteTeste,nome_2,fonteCor);
texto_nome_3=TTF_RenderText_Solid(fonteTeste,nome_3,fonteCor);
sprintf(pontos_ler,"%d",pontuacao_1);
sprintf(pontos_2,"%d",pontuacao_2);
sprintf(pontos_3,"%d",pontuacao_3);
texto_pontos=TTF_RenderText_Solid(fonteTeste,"-PONTOS-",fonteCor);
texto_pontos_1=TTF_RenderText_Solid(fonteTeste,pontos_ler,fonteCor);
texto_pontos_2=TTF_RenderText_Solid(fonteTeste,pontos_2,fonteCor);
texto_pontos_3=TTF_RenderText_Solid(fonteTeste,pontos_3,fonteCor);

SDL_Rect texto_nomePos;
texto_nomePos.x=0;
texto_nomePos.y=140;
        SDL_BlitSurface(texto_nome,NULL,tela,&texto_nomePos);

SDL_Rect texto_nome_1Pos;
texto_nome_1Pos.x=0;
texto_nome_1Pos.y=240;
        SDL_BlitSurface(texto_nome_1,NULL,tela,&texto_nome_1Pos);

SDL_Rect texto_nome_2Pos;
texto_nome_2Pos.x=0;
texto_nome_2Pos.y=340;
        SDL_BlitSurface(texto_nome_2,NULL,tela,&texto_nome_2Pos);

SDL_Rect texto_nome_3Pos;
texto_nome_3Pos.x=0;
texto_nome_3Pos.y=440;
        SDL_BlitSurface(texto_nome_3,NULL,tela,&texto_nome_3Pos);

SDL_Rect texto_pontosPos;
texto_pontosPos.x=400;
texto_pontosPos.y=140;
        SDL_BlitSurface(texto_pontos,NULL,tela,&texto_pontosPos);

SDL_Rect texto_pontos_1Pos;
texto_pontos_1Pos.x=400;
texto_pontos_1Pos.y=240;
        SDL_BlitSurface(texto_pontos_1,NULL,tela,&texto_pontos_1Pos);

SDL_Rect texto_pontos_2Pos;
texto_pontos_2Pos.x=400;
texto_pontos_2Pos.y=340;
        SDL_BlitSurface(texto_pontos_2,NULL,tela,&texto_pontos_2Pos);

SDL_Rect texto_pontos_3Pos;
texto_pontos_3Pos.x=400;
texto_pontos_3Pos.y=440;
        SDL_BlitSurface(texto_pontos_3,NULL,tela,&texto_pontos_3Pos);
    }


       }

       if(digita_recorde==1)
       {
            arq_2=fopen("arquivos/recordes_pontos.txt","r");
            fscanf(arq_2,"%d",&pontuacao_1);
            fscanf(arq_2,"%d",&pontuacao_2);
            fscanf(arq_2,"%d",&pontuacao_3);
            fclose(arq_2);
            arq_1=fopen("arquivos/recordes.txt","r");
            fscanf(arq_1,"%s",&nome_1);
            fscanf(arq_1,"%s",&nome_2);
            fscanf(arq_1,"%s",&nome_3);
            fclose(arq_1);

            if(pontucao>=pontuacao_1)
            {
                tela_1= IMG_Load("img/Jogo/Telas/novo_recorde.png");
                pontuacao_1=pontucao;
                strcpy(nome_1,nome_jogador);

            }
            else
            if(pontucao<pontuacao_1 && pontucao>=pontuacao_2 && pontucao>pontuacao_3)
            {
                 tela_1= IMG_Load("img/Jogo/Telas/recorde.png");
                 pontuacao_2=pontucao;
                 strcpy(nome_2,nome_jogador);
            }
            else
            {
                tela_1= IMG_Load("img/Jogo/Telas/recorde.png");
                 pontuacao_3=pontucao;
                 strcpy(nome_3,nome_jogador);
            }




SDL_BlitSurface(tela_1,NULL,tela,NULL);


    switch(event.type)
            {
            case SDL_QUIT:
                jogo = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {


                break;
            case SDLK_ESCAPE:
                    jogo=0;
                    break;

                case SDLK_a:
                    nome_jogador[prox_linha]='A';
                    prox_linha++;
                    break;
                case SDLK_b:
                    nome_jogador[prox_linha]='B';
                    prox_linha++;
                    break;
                case SDLK_c:
                    nome_jogador[prox_linha]='C';
                   prox_linha++;
                    break;
                    case SDLK_d:
                    nome_jogador[prox_linha]='D';
                    prox_linha++;
                    break;
                    case SDLK_e:
                    nome_jogador[prox_linha]='E';
                    prox_linha++;
                    break;
                    case SDLK_f:
                    nome_jogador[prox_linha]='F';
                    prox_linha++;
                    break;
                    case SDLK_g:
                    nome_jogador[prox_linha]='G';
                    prox_linha++;
                    break;
                    case SDLK_h:
                    nome_jogador[prox_linha]='H';
                    prox_linha++;
                    break;
                    case SDLK_i:
                    nome_jogador[prox_linha]='I';
                    prox_linha++;
                    break;
                    case SDLK_j:
                    nome_jogador[prox_linha]='J';
                    prox_linha++;
                    break;
                    case SDLK_l:
                    nome_jogador[prox_linha]='L';
                    prox_linha++;
                    break;
                    case SDLK_k:
                    nome_jogador[prox_linha]='K';
                    prox_linha++;
                    break;
                    case SDLK_m:
                    nome_jogador[prox_linha]='M';
                    prox_linha++;
                    break;
                    case SDLK_n:
                    nome_jogador[prox_linha]='N';
                    prox_linha++;
                    break;
                    case SDLK_o:
                    nome_jogador[prox_linha]='O';
                    prox_linha++;
                    break;
                    case SDLK_p:
                    nome_jogador[prox_linha]='P';
                    prox_linha++;
                    break;
                    case SDLK_q:
                    nome_jogador[prox_linha]='Q';
                    prox_linha++;
                    break;
                    case SDLK_r:
                    nome_jogador[prox_linha]='R';
                    prox_linha++;
                    break;
                    case SDLK_s:
                    nome_jogador[prox_linha]='S';
                    prox_linha++;
                    break;
                    case SDLK_t:
                    nome_jogador[prox_linha]='T';
                    prox_linha++;
                    break;
                    case SDLK_u:
                    nome_jogador[prox_linha]='U';
                    prox_linha++;
                    break;
                    case SDLK_v:
                    nome_jogador[prox_linha]='V';
                    prox_linha++;
                    break;
                    case SDLK_x:
                    nome_jogador[prox_linha]='X';
                    prox_linha++;
                    break;
                    case SDLK_y:
                    nome_jogador[prox_linha]='Y';
                    prox_linha++;
                    break;
                    case SDLK_w:
                    nome_jogador[prox_linha]='W';
                    prox_linha++;
                    break;
                    case SDLK_z:
                    nome_jogador[prox_linha]='Z';
                    prox_linha++;
                    break;
                    case SDLK_BACKSPACE:
                    nome_jogador[prox_linha-1]=' ';
                    prox_linha--;

                    break;
                    case SDLK_RETURN:
                        digita_recorde=0;
                        prox_linha=0;

                        break;


                }
                break;

        }
        if(prox_linha<0)
        {
            prox_linha=0;
        }

        fonteTeste=TTF_OpenFont("teste.ttf",50);
 SDL_Color fonteCor={0,0,0};

//sprintf(pontos,"%d",pontucao);
texto_nome_do_jogador=TTF_RenderText_Solid(fonteTeste,nome_jogador,fonteCor);

SDL_Rect texto_nome_do_jogadorPos;
texto_nome_do_jogadorPos.x=360;
texto_nome_do_jogadorPos.y=200;


        SDL_BlitSurface(texto_nome_do_jogador,NULL,tela,&texto_nome_do_jogadorPos);


        arq_1= fopen("arquivos/recordes.txt","w");
        fprintf(arq_1,"%s\n",nome_1);
        fprintf(arq_1,"%s\n",nome_2);
        fprintf(arq_1,"%s\n",nome_3);
        fclose(arq_1);
        arq_2= fopen("arquivos/recordes_pontos.txt","w");
        fprintf(arq_2,"%d\n",pontuacao_1);
        fprintf(arq_2,"%d\n",pontuacao_2);
        fprintf(arq_2,"%d\n",pontuacao_3);
        fclose(arq_2);

       }


/*       if(escreve)
       {
         escreve_recorde();
       }*/






}

void historia_do_jogo()
{


 switch(event.type)
            {
            case SDL_QUIT:
                jogo = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
            case SDLK_RETURN:

                    //jogar=1;

                break;
            case SDLK_ESCAPE:
                    jogo=0;
                    break;

                case SDLK_LEFT:

                        troca_frame--;

                    break;


                case SDLK_RIGHT:
                    troca_frame++;
                    break;


                }
                break;

        }
        SDL_BlitSurface(tela_1,NULL,tela,NULL);

    if(troca_frame==0)
    {
        tela_1= IMG_Load("img/Jogo/Telas/0.jpg");


    }
    if(troca_frame==1)
    {
        tela_1= IMG_Load("img/Jogo/Telas/1.jpg");
    }
    if(troca_frame==2)
    {
        tela_1= IMG_Load("img/Jogo/Telas/2.jpg");
    }
    if(troca_frame==3)
    {
        tela_1= IMG_Load("img/Jogo/Telas/3.jpg");
    }
    if(troca_frame==4)
    {
        tela_1= IMG_Load("img/Jogo/Telas/4.jpg");
    }
    if(troca_frame==5)
    {
        tela_1= IMG_Load("img/Jogo/Telas/5.jpg");
    }
    if(troca_frame==6)
    {
        tela_1= IMG_Load("img/Jogo/Telas/6.jpg");
    }
    if(troca_frame==7)
    {
        tela_1= IMG_Load("img/Jogo/Telas/7.jpg");
    }
    if(troca_frame==8)
    {
        tela_1= IMG_Load("img/Jogo/Telas/8.jpg");
    }

    if(troca_frame==9)
    {
        jogar=1;
        historia=0;
        troca_frame=0;
    }
    if(troca_frame==-1)
    {
        jogar=1;
        historia=0;
        troca_frame=0;
    }



}

void playerInfo()
{
    player.largura = 56, player.altura = 66, player.pulo = 0,player.thinkTime=0;
	player.sx =0, player.sy = 0, player.dx =0, player.dy = 514, player.velx = 5.5, player.vely =0.0;
}

void barrilInfo()
{
    barril.largura_1 = 32, barril.altura_1 = 30;
	barril.sx_1[0] =0, barril.sy_1[0] = 0, barril.dx_1[0] =530, barril.dy_1[0] = 118, barril.velx_1[0] = vel_barril_x, barril.vely_1[0] =2.0;
}
void barrilInfo1()
{
    barril.largura_1 = 32, barril.altura_1 = 30;
	barril.sx_1[1] =0, barril.sy_1[1] = 0, barril.dx_1[1] =530, barril.dy_1[1] = 118, barril.velx_1[1] = vel_barril_x, barril.vely_1[1] =2.0;
}
void barrilInfo2()
{
    barril.largura_1 = 32, barril.altura_1 = 30;
	barril.sx_1[2] =0, barril.sy_1[2] = 0, barril.dx_1[2] =530, barril.dy_1[2] = 118, barril.velx_1[2] = vel_barril_x, barril.vely_1[2] =2.0;
}
void barrilInfo3()
{
    barril.largura_1 = 32, barril.altura_1 = 30;
	barril.sx_1[3] =0, barril.sy_1[3] = 0, barril.dx_1[3] =530, barril.dy_1[3] = 118, barril.velx_1[3] = vel_barril_x, barril.vely_1[3] =2.0;
}
void barrilInfo4()
{
    barril.largura_1 = 32, barril.altura_1 = 30;
	barril.sx_1[4] =0, barril.sy_1[4] = 0, barril.dx_1[4] =530, barril.dy_1[4] = 118, barril.velx_1[4] = vel_barril_x, barril.vely_1[4] =2.0;
}

void barrilInfo5()
{
    barril.largura_1 = 32, barril.altura_1 = 30;
	barril.sx_1[5] =0, barril.sy_1[5] = 0, barril.dx_1[5] =530, barril.dy_1[5] = 118, barril.velx_1[5] = vel_barril_x, barril.vely_1[5] =2.0;
}


void plataformainfo(SDL_Rect plataformapos)
{
    plataforma.largura_2=34, plataforma.altura_2=18;
    plataforma.dx_2=plataformapos.x, plataforma.dy_2=plataformapos.y;
}

void lordeInfo()
{
    lorde.largura_3=135, lorde.altura_3=90;
    lorde.sx_3=0, lorde.sy_3=0, lorde.dx_3=560, lorde.dy_3=60;
}

///vai desenhando o player conforme ele se movimenta
void draw_player(float srcX, float srcY, float dstX, float dstY, int width, int height, SDL_Surface* source, SDL_Surface* destination)
{
   SDL_Rect sourc, destino;
   sourc.x = srcX;
   sourc.y = srcY;
   sourc.w = width;
   sourc.h = height;

   destino.x = dstX;
   destino.y = dstY;
   destino.w = width;
   destino.h = height;

   SDL_BlitSurface(source, &sourc, destination, &destino);
}

/// vai desenhando o barril conforme ele se movimenta
void draw_barril(float srcX_1, float srcY_1, float dstX_1, float dstY_1, int width_1, int height_1, SDL_Surface* origin, SDL_Surface* destina)
{
   SDL_Rect origem, destin;
   origem.x = srcX_1;
   origem.y = srcY_1;
   origem.w = width_1;
   origem.h = height_1;

   destin.x = dstX_1;
   destin.y = dstY_1;
   destin.w = width_1;
   destin.h = height_1;

   SDL_BlitSurface(origin, &origem, destina, &destin);
}

void draw_lorde(float srcX_1, float srcY_1, float dstX_1, float dstY_1, int width_1, int height_1, SDL_Surface* origin, SDL_Surface* destina)
{
   SDL_Rect origem, destin;
   origem.x = srcX_1;
   origem.y = srcY_1;
   origem.w = width_1;
   origem.h = height_1;

   destin.x = dstX_1;
   destin.y = dstY_1;
   destin.w = width_1;
   destin.h = height_1;

   SDL_BlitSurface(origin, &origem, destina, &destin);
}

///cria um texto na tela
void texto()
{
     /*Cria uma fonte para texto  */

 fonteTeste=TTF_OpenFont("teste.ttf",20);
 SDL_Color fonteCor={255,50,0};

                /*cria um texto usando o SDL_ttf */
texto_nome_personagem=TTF_RenderText_Solid(fonteTeste,"Gon ",fonteCor);
sprintf(bonus_total,"%d",bonus);

texto_bonus=TTF_RenderText_Solid(fonteTeste,bonus_total,fonteCor);
texto_bonus_1=TTF_RenderText_Solid(fonteTeste,"Bonus: ",fonteCor);
sprintf(vidas,"%d",player_vida);

texto_vidas=TTF_RenderText_Solid(fonteTeste,"Vidas: ",fonteCor);

texto_vida=TTF_RenderText_Solid(fonteTeste,vidas,fonteCor);


sprintf(pontos,"%d",pontucao);
texto1=TTF_RenderText_Solid(fonteTeste,pontos,fonteCor);
texto_pontuacao=TTF_RenderText_Solid(fonteTeste,"Pontuacao: ",fonteCor);

                /* posicao do texto  */

SDL_Rect texto_bonusPosition;
texto_bonusPosition.x=130;//(tela->w - texto1->w);
texto_bonusPosition.y=0;//(tela->h - texto1->h);

SDL_Rect texto_bonus1Position;
texto_bonus1Position.x=70;//(tela->w - texto1->w);
texto_bonus1Position.y=0;//(tela->h - texto1->h);

SDL_Rect texto_vidaPosition;
texto_vidaPosition.x=260;//(tela->w - texto1->w);
texto_vidaPosition.y=0;//(tela->h - texto1->h);

SDL_Rect texto_nome_personagemPosition;
texto_nome_personagemPosition.x=0;//(tela->w - texto1->w);
texto_nome_personagemPosition.y=0;//(tela->h - texto1->h);

SDL_Rect texto_vidasPosition;
texto_vidasPosition.x=200;//(tela->w - texto1->w);
texto_vidasPosition.y=0;//(tela->h - texto1->h);

SDL_Rect texto1Position;
texto1Position.x=400;//(tela->w - texto1->w);
texto1Position.y=0;//(tela->h - texto1->h);


SDL_Rect texto_pontuacaoPosition;
texto_pontuacaoPosition.x=300;//(tela->w - texto1->w);
texto_pontuacaoPosition.y=0;//(tela->h - texto1->h);

// blita o texto na tela
        SDL_BlitSurface(texto_bonus_1,NULL,tela,&texto_bonus1Position);
        SDL_BlitSurface(texto_bonus,NULL,tela,&texto_bonusPosition);
        SDL_BlitSurface(texto_nome_personagem,NULL,tela,&texto_nome_personagemPosition);
        SDL_BlitSurface(texto_vidas,NULL,tela,&texto_vidasPosition);
        SDL_BlitSurface(texto_vida,NULL,tela,&texto_vidaPosition);
        SDL_BlitSurface(texto1,NULL,tela,&texto1Position);
        SDL_BlitSurface(texto_pontuacao,NULL,tela,&texto_pontuacaoPosition);

         /*atualiza a tela*/

}
///caminho do barril ate entao esta sendo feito por ifs
void caminho_barril_1()
{
    tamanho=0;
    SDL_Surface *aux = queijo;
    queijo = IMG_Load("img/queijo.png");
    SDL_FreeSurface(aux);
    if(barril.sx_1[tamanho] > 63)
    {
        barril.sx_1[tamanho] = 0;
    }
    ///primeira plataforma

    if(barril.dx_1[tamanho]<=530 && barril.dx_1[tamanho]>=38 && barril.dy_1[tamanho]==118)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 &&barril.dy_1[tamanho]>=118 && barril.dy_1[tamanho]<=190)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }

    if(barril.dy_1[tamanho]==190 && barril.dx_1[tamanho]<=680)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]==680 && barril.dy_1[tamanho]>=190 && barril.dy_1[tamanho]<=262)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==262)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 && barril.dy_1[tamanho]>=262 && barril.dy_1[tamanho]<=334)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==334)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=334 && barril.dy_1[tamanho]<=406 && barril.dx_1[tamanho]>=440)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==406)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=406 && barril.dy_1[tamanho]<=478 &&  barril.dx_1[tamanho]<=140)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==478)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
     if(barril.dy_1[tamanho]>=478 && barril.dy_1[tamanho]<=550 &&  barril.dx_1[tamanho]>=575)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
     if(barril.dy_1[tamanho]==550)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }


    if(barril.dy_1[tamanho]==550 && barril.dx_1[tamanho]<-2)
    {
        barril.dy_1[tamanho]=118;
             barril.dx_1[tamanho]=530;
    }



    atualizaFrame();
    i--;

}
void caminho_barril_2()
{
    tamanho=1;
    SDL_Surface *aux = queijo;
    queijo = IMG_Load("img/queijo.png");
    SDL_FreeSurface(aux);
    if(barril.sx_1[tamanho] > 63)
    {
        barril.sx_1[tamanho] = 0;
    }
    ///primeira plataforma

    if(barril.dx_1[tamanho]<=530 && barril.dx_1[tamanho]>=38 && barril.dy_1[tamanho]==118)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 &&barril.dy_1[tamanho]>=118 && barril.dy_1[tamanho]<=190)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }

    if(barril.dy_1[tamanho]==190 && barril.dx_1[tamanho]<=680)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]==680 && barril.dy_1[tamanho]>=190 && barril.dy_1[tamanho]<=262)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==262)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 && barril.dy_1[tamanho]>=262 && barril.dy_1[tamanho]<=334)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==334)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=334 && barril.dy_1[tamanho]<=406 && barril.dx_1[tamanho]>=440)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==406)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=406 && barril.dy_1[tamanho]<=478 &&  barril.dx_1[tamanho]<=140)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==478)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
     if(barril.dy_1[tamanho]>=478 && barril.dy_1[tamanho]<=550 &&  barril.dx_1[tamanho]>=575)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
     if(barril.dy_1[tamanho]==550)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }


    if(barril.dy_1[tamanho]==550 && barril.dx_1[tamanho]<-2)
    {
        barril.dy_1[tamanho]=118;
             barril.dx_1[tamanho]=530;
    }


    if (barril_1_img==0)
    {
        barril.sx_1[tamanho] += barril.largura_1;
        barril_1_img=10;
    }
    barril_1_img--;

}

void caminho_barril_3()
{
    tamanho=2;
    SDL_Surface *aux = queijo;
    queijo = IMG_Load("img/queijo.png");
    SDL_FreeSurface(aux);
    if(barril.sx_1[tamanho] > 63)
    {
        barril.sx_1[tamanho] = 0;
    }
    ///primeira plataforma

    if(barril.dx_1[tamanho]<=530 && barril.dx_1[tamanho]>=38 && barril.dy_1[tamanho]==118)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 &&barril.dy_1[tamanho]>=118 && barril.dy_1[tamanho]<=190)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }

    if(barril.dy_1[tamanho]==190 && barril.dx_1[tamanho]<=680)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]==680 && barril.dy_1[tamanho]>=190 && barril.dy_1[tamanho]<=262)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==262)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 && barril.dy_1[tamanho]>=262 && barril.dy_1[tamanho]<=334)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==334)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=334 && barril.dy_1[tamanho]<=406 && barril.dx_1[tamanho]>=440)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==406)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=406 && barril.dy_1[tamanho]<=478 &&  barril.dx_1[tamanho]<=140)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==478)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
     if(barril.dy_1[tamanho]>=478 && barril.dy_1[tamanho]<=550 &&  barril.dx_1[tamanho]>=575)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
     if(barril.dy_1[tamanho]==550)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }


    if(barril.dy_1[tamanho]==550 && barril.dx_1[tamanho]<-2)
    {
        barril.dy_1[tamanho]=118;
             barril.dx_1[tamanho]=530;
    }


    if (barril_2_img==0)
    {
       barril.sx_1[tamanho] += barril.largura_1;
        barril_2_img=10;
    }
    barril_2_img--;

}

void caminho_barril_4()
{
    tamanho=3;
    SDL_Surface *aux = queijo;
    queijo = IMG_Load("img/queijo.png");
    SDL_FreeSurface(aux);
    if(barril.sx_1[tamanho] > 63)
    {
        barril.sx_1[tamanho] = 0;
    }
    ///primeira plataforma

    if(barril.dx_1[tamanho]<=530 && barril.dx_1[tamanho]>=38 && barril.dy_1[tamanho]==118)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 &&barril.dy_1[tamanho]>=118 && barril.dy_1[tamanho]<=190)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }

    if(barril.dy_1[tamanho]==190 && barril.dx_1[tamanho]<=680)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]==680 && barril.dy_1[tamanho]>=190 && barril.dy_1[tamanho]<=262)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==262)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 && barril.dy_1[tamanho]>=262 && barril.dy_1[tamanho]<=334)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==334)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=334 && barril.dy_1[tamanho]<=406 && barril.dx_1[tamanho]>=440)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==406)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=406 && barril.dy_1[tamanho]<=478 &&  barril.dx_1[tamanho]<=140)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==478)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
     if(barril.dy_1[tamanho]>=478 && barril.dy_1[tamanho]<=550 &&  barril.dx_1[tamanho]>=575)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
     if(barril.dy_1[tamanho]==550)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }


    if(barril.dy_1[tamanho]==550 && barril.dx_1[tamanho]<-2)
    {
        barril.dy_1[tamanho]=118;
             barril.dx_1[tamanho]=530;
    }


    if (barril_3_img==0)
    {
        barril.sx_1[tamanho] += barril.largura_1;
        barril_3_img=10;
    }
    barril_3_img--;

}

void caminho_barril_5()
{
    tamanho=4;
    SDL_Surface *aux = queijo;
    queijo = IMG_Load("img/queijo.png");
    SDL_FreeSurface(aux);
    if(barril.sx_1[tamanho] > 63)
    {
        barril.sx_1[tamanho] = 0;
    }
    ///primeira plataforma

    if(barril.dx_1[tamanho]<=530 && barril.dx_1[tamanho]>=38 && barril.dy_1[tamanho]==118)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 &&barril.dy_1[tamanho]>=118 && barril.dy_1[tamanho]<=190)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }

    if(barril.dy_1[tamanho]==190 && barril.dx_1[tamanho]<=680)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]==680 && barril.dy_1[tamanho]>=190 && barril.dy_1[tamanho]<=262)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==262)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 && barril.dy_1[tamanho]>=262 && barril.dy_1[tamanho]<=334)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==334)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=334 && barril.dy_1[tamanho]<=406 && barril.dx_1[tamanho]>=440)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==406)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=406 && barril.dy_1[tamanho]<=478 &&  barril.dx_1[tamanho]<=140)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==478)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
     if(barril.dy_1[tamanho]>=478 && barril.dy_1[tamanho]<=550 &&  barril.dx_1[tamanho]>=575)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
     if(barril.dy_1[tamanho]==550)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }


    if(barril.dy_1[tamanho]==550 && barril.dx_1[tamanho]<-2)
    {
        barril.dy_1[tamanho]=118;
             barril.dx_1[tamanho]=530;
    }


    if (barril_4_img==0)
    {
        barril.sx_1[tamanho] += barril.largura_1;
        barril_4_img=10;
    }
    barril_4_img--;

}

void caminho_barril_6()
{
    tamanho=5;
    SDL_Surface *aux = queijo;
    queijo = IMG_Load("img/queijo.png");
    SDL_FreeSurface(aux);
    if(barril.sx_1[tamanho] > 63)
    {
        barril.sx_1[tamanho] = 0;
    }
    ///primeira plataforma

    if(barril.dx_1[tamanho]<=530 && barril.dx_1[tamanho]>=38 && barril.dy_1[tamanho]==118)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 &&barril.dy_1[tamanho]>=118 && barril.dy_1[tamanho]<=190)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }

    if(barril.dy_1[tamanho]==190 && barril.dx_1[tamanho]<=680)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]==680 && barril.dy_1[tamanho]>=190 && barril.dy_1[tamanho]<=262)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==262)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }

    if(barril.dx_1[tamanho]<=38 && barril.dy_1[tamanho]>=262 && barril.dy_1[tamanho]<=334)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==334)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=334 && barril.dy_1[tamanho]<=406 && barril.dx_1[tamanho]>=440)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==406)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }
    if(barril.dy_1[tamanho]>=406 && barril.dy_1[tamanho]<=478 &&  barril.dx_1[tamanho]<=140)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
    if(barril.dy_1[tamanho]==478)
    {
        barril.dx_1[tamanho]+=barril.velx_1[tamanho];
    }
     if(barril.dy_1[tamanho]>=478 && barril.dy_1[tamanho]<=550 &&  barril.dx_1[tamanho]>=575)
    {
        barril.dy_1[tamanho]+=barril.vely_1[tamanho];
    }
     if(barril.dy_1[tamanho]==550)
    {
        barril.dx_1[tamanho]-=barril.velx_1[tamanho];
    }


    if(barril.dy_1[tamanho]==550 && barril.dx_1[tamanho]<-2)
    {
        barril.dy_1[tamanho]=118;
             barril.dx_1[tamanho]=530;
    }


    if (barril_5_img==0)
    {
        barril.sx_1[tamanho] += barril.largura_1;
        barril_5_img=10;
    }
    barril_5_img--;

}

void lorde_cheddar_movimento()
{
    SDL_Surface *aux = lorde_cheddar;

    if(muda_img_lorde>-420 && muda_img_lorde<=0)
    {
        lorde_cheddar = IMG_Load("img/Jogo/LordCheddar/lorde.png");
    }


    SDL_FreeSurface(aux);
    if(muda_img_lorde>-420 && muda_img_lorde<=0)
    {
        if(lorde.sx_3 > 256)
    {
        lorde.sx_3 = 0;
    }
    if (vel_muda==0)
    {
        lorde.sx_3 += lorde.largura_3;
        vel_muda=40;
    }
    vel_muda--;
    }



}

///atualiza os frames do barril
void atualizaFrame()
{
    if (i==0)
    {
        barril.sx_1[0] += barril.largura_1;
        i=10;
    }

}

void carrega_sons ()
{
     musica= Mix_LoadMUS("music/The_Elder_Scrolls_III_Morrowind_theme.mp3");
     som_pulo= Mix_LoadWAV("music/126416__cabeeno-rossley__jump.wav");
     batida= Mix_LoadWAV("music/Crash_Large-Sound.wav");
     espada_barril= Mix_LoadWAV("music/sword_sound.wav");
}



///funcao que le o arquivo .dat com a matriz e vai desenhando o mapa
void loadMap(char *name)
{
    int x, y;
    FILE *fp;

    fp = fopen(name, "rb");

    /* Se nao for possivel abrir o mapa o SDL quita */

    if (fp == NULL)
    {
        printf("Nao foi possivel carregar o mapa %s\n", name);

        exit(1);
    }

    /* Le os dados do mapa*/

    for (y=0;y<MAX_MAP_Y;y++)
    {
        for (x=0;x<MAX_MAP_X;x++)
        {
            fscanf(fp, "%d", &map.tile[y][x]);
        }
    }

    /*Coordenadas de inicio */

    map.startX = map.startY = 0;

    map.maxX = MAX_MAP_X * TILE_SIZE_W;
    map.maxY = MAX_MAP_Y * TILE_SIZE_H;


    /* Fecha o arquivo que tem os dados do mapa */

    fclose(fp);
}
/// desenha as imagens do mapa na tela

void drawImage(SDL_Surface *image, int x, int y)
{
	SDL_Rect dest;

	/* Set the blitting rectangle to the size of the src image */

	dest.x = x;
	dest.y = y;
	dest.w = image->w;
	dest.h = image->h;

	/* Blit the entire image onto the screen at coordinates x and y */

	SDL_BlitSurface(image, NULL, tela, &dest);
}
///desenha o mapa
void drawMap()
{
    int x, y;


    /* Desenha o mapa */

    for (y=0;y<MAX_MAP_Y;y++)
    {
        for (x=0;x<MAX_MAP_X;x++)
        {

            if (map.tile[y][x] == 1)
            {
                drawImage(piso, x * TILE_SIZE_W, y * TILE_SIZE_H);
            }
             if (map.tile[y][x] == 2)
            {
                drawImage(escada,x* LADDER_SIZE_W,y* LADDER_SIZE_H);

            }

            if(map.tile[y][x] == 3)
            {
                drawImage(piso, x * TILE_SIZE_W, y * TILE_SIZE_H);
                drawImage(escada,x* LADDER_SIZE_W,y* LADDER_SIZE_H);

            }
            if(map.tile[y][x] == 4)
            {
                drawImage(rata,x* LADDER_SIZE_W,(y* LADDER_SIZE_H)+6);
            }

            if(map.tile[y][x] == 6)
            {
                if(!tem_espada)
                drawImage(espada,x* LADDER_SIZE_W,(y* LADDER_SIZE_H)+16);
            }
        }
    }
}


///carrega todas as imagens possiveis do jogo
void load_img()
{

    loadMap("arquivos/map01.dat");
    /* Configura o Video */
tela = SDL_SetVideoMode(LARGURA, ALTURA, BPP, SDL_SWSURFACE | SDL_ANYFORMAT);
if(tela == NULL)
{
printf("Erro: %s\n", SDL_GetError());
return 1; /* encerra o programa */
}
 ///fundo

fundo = IMG_Load("img/estalagmites.png");
if(fundo == NULL)
{
  printf("Erro ao carregar a imagem: %s\n", IMG_GetError());
  exit(0);
}
            /*blita o fundo, mas e preciso atualizar a tela*/
SDL_BlitSurface( fundo, NULL, tela, NULL);

///queijo barril
queijo = IMG_Load("img/queijo.png");
if(queijo == NULL)
{
  printf("Erro ao carregar a imagem: %s\n", IMG_GetError());
  exit(0);
}


///plataforma

piso = IMG_Load("img/plataforma.png");
if(piso == NULL)
{
  printf("Erro ao carregar a imagem: %s\n", IMG_GetError());
  exit(0);
}

///escada

escada= IMG_Load("img/escada.png");
if(escada == NULL)
{
  printf("Erro ao carregar a imagem: %s\n", IMG_GetError());
  exit(0);
}

///sprite do personagem principal
rato = IMG_Load("img/Jogo/Rato/ratoright1.png");
if(rato == NULL)
{
  printf("Erro ao carregar a imagem: %s\n", IMG_GetError());
  exit(0);
}
///sprite da princesa
rata = IMG_Load("img/Jogo/Rato/rata.png");
if(rata == NULL)
{
  printf("Erro ao carregar a imagem: %s\n", IMG_GetError());
  exit(0);
}



espada= IMG_Load("img/espadenha.png");

   if(espada == NULL)
{
  printf("Erro ao carregar a imagem: %s\n", IMG_GetError());
  exit(0);
}

///telas



}

///inicia o SDL e algumas outras coisas
void start()
{
    /*inicializando a SDL e verificando possiveis erros */
if(SDL_Init(SDL_INIT_VIDEO) != 0)
{
printf("Erro: %s\n", SDL_GetError());
exit(-1);
}
                    /* inicia o TTF e verifica se ha algum erro */
if(TTF_Init() !=0){
    printf("Erro: %s\n",SDL_GetError());
    exit(-1);
}

 //Initialize SDL_mixer
  Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );


     //Set the window caption
    SDL_WM_SetCaption( "The Tale of a Tail", NULL );

load_img();
carrega_sons();
texto();
playerInfo();
barrilInfo();
barrilInfo1();
barrilInfo2();
barrilInfo3();
barrilInfo4();
barrilInfo5();
lordeInfo();
}

void escreve_recorde()
{
   arq_1= fopen("arquivos/recordes.txt","r");
    tela_recordes=IMG_Load("img/Telas/Jogo/recorde.png");

    fgets(nome_1,10,stdin);
    fgets(nome_2,10,stdin);
    fgets(nome_3,10,stdin);
    fclose(arq_1);
    arq_2= fopen("arquivos/recordes_pontos.txt","r");
    fscanf(arq_2,"%d",&pontuacao_1);
    fscanf(arq_2,"%d",&pontuacao_2);
    fscanf(arq_2,"%d",&pontuacao_3);
    fonteTeste=TTF_OpenFont("teste.ttf",90);
 SDL_Color fonteCor={255,50,0};

//sprintf(pontos,"%d",pontucao);
texto_nome_do_jogador=TTF_RenderText_Solid(fonteTeste,nome_1,fonteCor);

SDL_Rect texto_nome_do_jogadorPos;
texto_nome_do_jogadorPos.x=100;
texto_nome_do_jogadorPos.y=200;
    SDL_BlitSurface(texto_nome_do_jogador,NULL,tela,&texto_nome_do_jogadorPos);
}

void andar()
{
    switch(event.type)
            {
            case SDL_QUIT:
                jogo = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
            case SDLK_SPACE:
                if(!tem_espada)
                    {
                    pulo=1;
                    pulou=1;
                    Mix_PlayChannel( -1, som_pulo, 0 );
                }

                    break;
            case SDLK_ESCAPE:
                    jogo=0;
                    break;
                case SDLK_UP:
                    if(!tem_espada)
                    {
                       b[0]=1;
                    e_escada=1;
                    }

                    break;

                case SDLK_LEFT:
                    b[1]=1;
                    break;

                case SDLK_DOWN:
                    if(!tem_espada)
                    {
                        b[2]=1;
                    }

                    break;

                case SDLK_RIGHT:
                    b[3]=1;
                    break;

                case SDLK_z:
                    if(tem_espada && e_esquerda )
                    {
                        player.sx=56;
                    }
                    if(tem_espada && e_direita)
                    {
                        player.sx=112;
                    }
                    z_pressionado=1;
                    break;


                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                    pulo=0;
                    break;
                case SDLK_UP:
                    b[0]=0;
                    break;

                case SDLK_LEFT:
                    b[1]=0;
                    player.sx=0;
                    break;

                case SDLK_DOWN:
                    b[2]=0;
                    break;

                case SDLK_RIGHT:
                    b[3]=0;
                    player.sx=0;
                    break;

                case SDLK_z:
                    if(tem_espada && e_esquerda )
                    {
                        player.sx=166;
                    }
                    if(tem_espada && e_direita)
                    {
                        player.sx=0;
                    }
                    z_pressionado=0;
                    break;
                }
                break;
            }
}

void movimentacao()
{
    if(player.dy>514 && player.dy<519)
    {
        player.dy=514;
        //player.dx=0;
    }
    else
     if(player.dy>441 && player.dy<444)
        {
            player.dy=442;
        }
        else
        if(player.dy>369 && player.dy<372)
        {
            player.dy=370;
        }
         else
            if(player.dy>297 && player.dy<300)
        {
            player.dy=298;
        }
        else
            if(player.dy>225 && player.dy<228)
        {
            player.dy=226;
        }
         else
            if(player.dy>153 && player.dy<155)
        {
            player.dy=154;
        }
        else
            if(player.dy>81 && player.dy<84)
        {
            player.dy=82;
        }

    if(player.dy==514 && player.dx<750)
    {
        e_chao=1;
    }
    else
    if(player.dy==442 && player.dx<750)
    {
        e_chao=1;
    }
    else
     if(player.dy==370 && player.dx<750)
    {
        e_chao=1;
    }
    else
          if(player.dy==298 && player.dx>-10 && player.dx<440)
    {
        e_chao=1;
    }
    else
        if(player.dy==298 && player.dx>=555 && player.dx<700)
        {
        e_chao=1;
        }
    else
        if(player.dy==226 && player.dx>=-10 && player.dx<700)
        {
        e_chao=1;
        }
    else
        if(player.dy==154 && player.dx>=-10 &&player.dx<710)
        {
        e_chao=1;
        }
    else
        if(player.dy==82 && player.dx>=-10)
    {
        e_chao=1;
    }

    /*else
        if(player.dy==154 && player.dx>510 && player.dx<550)
    {
        e_chao=1;
    }*/
    else
        if(!e_escada)
        {
            e_chao=0;
        }


    if(player.dx<=0)
    {
        player.dx=0;
    }
    if(player.dx>=700-player.largura)
    {
        player.dx=player.dx;
    }

    if(e_chao){
        player.vely = 0;
        if(pulo)
            player.vely = -7.0;

        }
    else
        player.vely += gravidade;
    player.dy += player.vely;



            if (player.dx>320 && player.dx<370 && player.dy<=514 && player.dy>=442
                ||player.dy<=514 && player.dy>=442 && player.dx>560 && player.dx<594
                ||player.dy<=442 && player.dy>=370 && player.dx>136 && player.dx<156
                ||player.dy<=370 && player.dy>=298 && player.dx>420 && player.dx<440
                ||player.dy<=298 && player.dy>=226 && player.dx>20 && player.dx<50
                ||player.dy<=226 && player.dy>=154 && player.dx>600 && player.dx<700
                ||player.dy<=154 && player.dy>=82  && player.dx>10 && player.dx<40)
    {
        e_escada=1;

        if (b[0])
        {
    ///troca de sprite aqui
     rato = IMG_Load("img/Jogo/Rato/ratoup.png");
                player.largura=50;
                player.sx += player.largura;
                if(player.sx>86)
                {
                    player.sx=0;
                }
    player.dy-=2;

    }
        }
        else
        {
            e_escada=0;
        }

            if(player.dy<=514 && player.dy>440 && player.dx>320 && player.dx<370
               ||player.dy<=514 && player.dy>=442 && player.dx>560 && player.dx<594
               ||player.dy<=442 && player.dy>=370 && player.dx>136 && player.dx<156
               ||player.dy<=370 && player.dy>=298 && player.dx>420 && player.dx<440
               ||player.dy<=298 && player.dy>=226 && player.dx>20 && player.dx<50
               ||player.dy<=226 && player.dy>=154 && player.dx>600 && player.dx<700
               ||player.dy<=154 && player.dy>=82  && player.dx>10 && player.dx<40)

            {
                e_escada=1;
                if(b[2])
                {
                    ///troca de sprite aqui
                rato = IMG_Load("img/Jogo/Rato/ratoup.png");
                player.largura=50;
                player.sx += player.largura;
                if(player.sx>88)
                {
                    player.sx=0;
                }
                player.dy+=2;
                }
        }
        else
        {
            e_escada=0;
        }

	 if(b[3])
    {
        e_direita=1;
            e_esquerda=0;
    	SDL_Surface *aux = rato;
    	if(!tem_espada)
        {
            rato = IMG_Load("img/Jogo/Rato/ratoright1.png");

            player.largura=56;
            player.altura=66;

        }
        if(tem_espada==1)
        {
            rato = IMG_Load("img/Jogo/Rato/ratosword1.png");
            player.largura=56;
            player.altura=59;
        }


    	SDL_FreeSurface(aux);
        player.sx += player.largura;
        player.dx += player.velx;
    }


     if(b[1])
    {
        e_direita=0;
            e_esquerda=1;
    	SDL_Surface *aux = rato;
    	if(!tem_espada)
        {
            rato = IMG_Load("img/Jogo/Rato/ratoleft1.png");
            player.largura=56;
            player.altura=66;

        }
        if(tem_espada==1)
        {
            rato = IMG_Load("img/Jogo/Rato/ratosword.png");
            player.largura=56;
            player.altura=59;

        }


    	SDL_FreeSurface(aux);
        player.sx -= player.largura;
        player.dx -= player.velx;
    }

    if(b[3])
    {

            if(player.sx > 223)
        player.sx = 0;

    if(player.sx < 0)
        player.sx = 224;





    }
    if(b[1])
    {

            if(player.sx > 223)
        player.sx = 0;

    if(player.sx < 0)
        player.sx = 224;


    }

}

void game_over(int deuruim)
{
    if(deuruim==1 && acabou==0)
    {

    tela_game_over = IMG_Load("img/Jogo/Telas/Game_over.png");
    SDL_BlitSurface(tela_game_over,NULL,tela,NULL);


Mix_PauseMusic();


    }
    if(deuruim==1 && acabou==1)
    {
         tela_game_over = IMG_Load("img/Jogo/Telas/acabou.png");
    SDL_BlitSurface(tela_game_over,NULL,tela,NULL);


Mix_PauseMusic();
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv)
{

    atexit (SDL_Quit);

    start();



            Mix_PlayMusic(musica,-1);



    int x1,x2,y1,y2,x3,x4,y3,y4;
    int x3_1,x4_1,y3_1,y4_1;
    int x3_2,x4_2,y3_2,y4_2;
    int x3_3,x4_3,y3_3,y4_3;
    int x3_4,x4_4,y3_4,y4_4;
    int x3_5,x4_5,y3_5,y4_5;


                //Loop principal onde ocorrem os eventos, a base do programa
        while(jogo){
                ///variaveis para a colisao barril-player que ainda esta um pouco bugada
                    x1=player.dx;
                    x2=player.dx+player.largura;
                    y1=player.dy;
                    y2=player.dy +player.altura;
                    x3=barril.dx_1[0];
                    x4=barril.dx_1[0] +barril.largura_1;
                    y3=barril.dy_1[0];
                    y4=barril.dy_1[0] + barril.altura_1;

                    x3_1=barril.dx_1[1];
                    x4_1=barril.dx_1[1] +barril.largura_1;
                    y3_1=barril.dy_1[1];
                    y4_1=barril.dy_1[1] + barril.altura_1;

                    x3_2=barril.dx_1[2];
                    x4_2=barril.dx_1[2] +barril.largura_1;
                    y3_2=barril.dy_1[2];
                    y4_2=barril.dy_1[2] + barril.altura_1;

                    x3_3=barril.dx_1[3];
                    x4_3=barril.dx_1[3] +barril.largura_1;
                    y3_3=barril.dy_1[3];
                    y4_3=barril.dy_1[3] + barril.altura_1;

                    x3_4=barril.dx_1[4];
                    x4_4=barril.dx_1[4] +barril.largura_1;
                    y3_4=barril.dy_1[4];
                    y4_4=barril.dy_1[4] + barril.altura_1;

                    x3_5=barril.dx_1[5];
                    x4_5=barril.dx_1[5] +barril.largura_1;
                    y3_5=barril.dy_1[5];
                    y4_5=barril.dy_1[5] + barril.altura_1;


                    player_pos.x=player.dx;
                    player_pos.y=player.dy;
                //SDL_WaitEvent(&event);
                /* Para a funcao controla_fps */
tempo = SDL_GetTicks();
tempo_2 =SDL_GetTicks();
    while(SDL_PollEvent(&event))
    {
        if(jogar==0 && historia==0)
        {
            tela_menu();
        }
        if(historia==1 && jogar==0 && digita_recorde==0)
{
    historia_do_jogo();

}

        if(jogar==1 && digita_recorde==0)
        {
           andar();

        }

        if(deuruim==1)
        {
            switch(event.type)
            {
            case SDL_QUIT:
                jogo = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {

            case SDLK_ESCAPE:
                    jogo=0;
                    break;

            case SDLK_s:
                    deuruim=0;
                    player_vida=3;
                    Mix_ResumeMusic();
                    break;
            case SDLK_n:
                    jogar=0;
                    digita_recorde=1;
                     deuruim=0;
                     pontucao+=bonus;
                     Mix_ResumeMusic();
                     break;
            case SDLK_RETURN:
                    if(acabou)
                    {
                        jogar=0;
                    digita_recorde=1;
                    acabou=0;
                    player.dx=0;
                    player.dy=514;
                    }

                    break;
                    //jogar=0;

                   // tela_recorde();
                    break;
                }

                break;


            }
        }


    }

    ///MOVIMENTACAO PERSONAGEM
if(jogar==1 && digita_recorde==0)
{
  movimentacao();



      if(z_pressionado && tem_espada)
      {
          if(( x1 < x3 && x3 < x2) || ( x1 < x4 && x4 < x2))
      {
         if(( y1 < y3 && y3 < y2) || ( y2 < y3 && y4 < y2))
         {
            ///Colidiu

             Mix_PlayChannel( -1, espada_barril, 0 );
             pontucao+=200;
             barril.dx_1[0]=530;
             barril.dy_1[0]=118;

         }
      }

      if(( x1 < x3_1 && x3_1 < x2) || ( x1 < x4_1 && x4_1 < x2))
      {
         if(( y1 < y3_1 && y3_1< y2) || ( y2 < y3_1 && y4_1 < y2))
         {
            ///Colidiu

              Mix_PlayChannel( -1, espada_barril, 0 );


             pontucao+=200;
             barril.dx_1[1]=530;
             barril.dy_1[1]=118;


         }
      }
      if(( x1 < x3_2 && x3_2 < x2) || ( x1 < x4_2 && x4_2 < x2))
      {
         if(( y1 < y3_2 && y3_2 < y2) || ( y2 < y3_2 && y4_2 < y2))
         {
            ///Colidiu

              Mix_PlayChannel( -1, espada_barril, 0 );


             pontucao+=200;
             barril.dx_1[2]=530;
             barril.dy_1[2]=118;


         }
      }
      if(( x1 < x3_3 && x3_3 < x2) || ( x1 < x4_3 && x4_3 < x2))
      {
         if(( y1 < y3_3 && y3_3 < y2) || ( y2 < y3_3 && y4_3 < y2))
         {
            ///Colidiu

              Mix_PlayChannel( -1, espada_barril, 0 );

             pontucao+=200;
             barril.dx_1[3]=530;
             barril.dy_1[3]=118;

         }
      }
      if(( x1 < x3_4 && x3_4 < x2) || ( x1 < x4_4 && x4_4 < x2))
      {
         if(( y1 < y3_4 && y3_4 < y2) || ( y2 < y3_4 && y4_4 < y2))
         {
            ///Colidiu

              Mix_PlayChannel( -1, espada_barril, 0 );

             pontucao+=200;
             barril.dx_1[4]=530;
             barril.dy_1[4]=118;

         }
      }
      if(( x1 < x3_5 && x3_5 < x2) || ( x1 < x4_5 && x4_5 < x2))
      {
         if(( y1 < y3_5 && y3_5 < y2) || ( y2 < y3_5 && y4_5 < y2))
         {
            ///Colidiu

             Mix_PlayChannel( -1, espada_barril, 0 );


             pontucao+=200;
             barril.dx_1[5]=530;
             barril.dy_1[5]=118;


         }
      }

      }
      else
      {
       ///colisao barril-rato
       if(( x1 < x3 && x3 < x2) || ( x1 < x4 && x4 < x2))
      {
         if(( y1 < y3 && y3 < y2) || ( y2 < y3 && y4 < y2))
         {
            ///Colidiu
             player.dx=0;
             player.dy=514;
             Mix_PlayChannel( -1, batida, 0 );
             player_vida--;
             player.dx=0;
             taca_outro=80;
             barril.dx_1[0]=530;
             barril.dy_1[0]=118;

             barril.dx_1[1]=530;
             barril.dy_1[1]=118;

             barril.dx_1[2]=530;
             barril.dy_1[2]=118;

             barril.dx_1[3]=530;
             barril.dy_1[3]=118;

             barril.dx_1[4]=530;
             barril.dy_1[4]=118;

             barril.dx_1[5]=530;
             barril.dy_1[5]=118;

         }
      }

      if(( x1 < x3_1 && x3_1 < x2) || ( x1 < x4_1 && x4_1 < x2))
      {
         if(( y1 < y3_1 && y3_1< y2) || ( y2 < y3_1 && y4_1 < y2))
         {
            ///Colidiu
             player.dx=0;
             player.dy=514;
             Mix_PlayChannel( -1, batida, 0 );
             player_vida--;
             player.dx=0;
             taca_outro=80;
             barril.dx_1[0]=530;
             barril.dy_1[0]=118;

             barril.dx_1[1]=530;
             barril.dy_1[1]=118;

             barril.dx_1[2]=530;
             barril.dy_1[2]=118;

             barril.dx_1[3]=530;
             barril.dy_1[3]=118;

             barril.dx_1[4]=530;
             barril.dy_1[4]=118;

             barril.dx_1[5]=530;
             barril.dy_1[5]=118;

         }
      }
      if(( x1 < x3_2 && x3_2 < x2) || ( x1 < x4_2 && x4_2 < x2))
      {
         if(( y1 < y3_2 && y3_2 < y2) || ( y2 < y3_2 && y4_2 < y2))
         {
            ///Colidiu
             player.dx=0;
             player.dy=514;
             Mix_PlayChannel( -1, batida, 0 );
             player_vida--;
             player.dx=0;
             taca_outro=80;
             barril.dx_1[0]=530;
             barril.dy_1[0]=118;

             barril.dx_1[1]=530;
             barril.dy_1[1]=118;

             barril.dx_1[2]=530;
             barril.dy_1[2]=118;

             barril.dx_1[3]=530;
             barril.dy_1[3]=118;

             barril.dx_1[4]=530;
             barril.dy_1[4]=118;

             barril.dx_1[5]=530;
             barril.dy_1[5]=118;

         }
      }
      if(( x1 < x3_3 && x3_3 < x2) || ( x1 < x4_3 && x4_3 < x2))
      {
         if(( y1 < y3_3 && y3_3 < y2) || ( y2 < y3_3 && y4_3 < y2))
         {
            ///Colidiu
             player.dx=0;
             player.dy=514;
             Mix_PlayChannel( -1, batida, 0 );
             player_vida--;
             player.dx=0;
             taca_outro=80;
             barril.dx_1[0]=530;
             barril.dy_1[0]=118;

             barril.dx_1[1]=530;
             barril.dy_1[1]=118;

             barril.dx_1[2]=530;
             barril.dy_1[2]=118;

             barril.dx_1[3]=530;
             barril.dy_1[3]=118;

             barril.dx_1[4]=530;
             barril.dy_1[4]=118;

             barril.dx_1[5]=530;
             barril.dy_1[5]=118;

         }
      }
      if(( x1 < x3_4 && x3_4 < x2) || ( x1 < x4_4 && x4_4 < x2))
      {
         if(( y1 < y3_4 && y3_4 < y2) || ( y2 < y3_4 && y4_4 < y2))
         {
            ///Colidiu
             player.dx=0;
             player.dy=514;
             Mix_PlayChannel( -1, batida, 0 );
             player_vida--;
             player.dx=0;
             taca_outro=80;
             barril.dx_1[0]=530;
             barril.dy_1[0]=118;

             barril.dx_1[1]=530;
             barril.dy_1[1]=118;

             barril.dx_1[2]=530;
             barril.dy_1[2]=118;

             barril.dx_1[3]=530;
             barril.dy_1[3]=118;

             barril.dx_1[4]=530;
             barril.dy_1[4]=118;

             barril.dx_1[5]=530;
             barril.dy_1[5]=118;

         }
      }
      if(( x1 < x3_5 && x3_5 < x2) || ( x1 < x4_5 && x4_5 < x2))
      {
         if(( y1 < y3_5 && y3_5 < y2) || ( y2 < y3_5 && y4_5 < y2))
         {
            ///Colidiu
             player.dx=0;
             player.dy=514;
             Mix_PlayChannel( -1, batida, 0 );
             player_vida--;
             player.dx=0;
             taca_outro=80;
             barril.dx_1[0]=530;
             barril.dy_1[0]=118;

             barril.dx_1[1]=530;
             barril.dy_1[1]=118;

             barril.dx_1[2]=530;
             barril.dy_1[2]=118;

             barril.dx_1[3]=530;
             barril.dy_1[3]=118;

             barril.dx_1[4]=530;
             barril.dy_1[4]=118;

             barril.dx_1[5]=530;
             barril.dy_1[5]=118;

         }
      }

      }

         if(( x1 < x3 && x3 < x2) || ( x1 < x4 && x4 < x2))
      {
         if(y2<y3 && y3<y2+35)
         {
              pontucao+=100;

         }
      }
      if(( x1 < x3_1 && x3_1 < x2) || ( x1 < x4_1 && x4_1 < x2))
      {
         if(y2<y3_1 && y3_1<y2+35)
         {
              pontucao+=100;

         }
      }
       if(( x1 < x3_2 && x3_2 < x2) || ( x1 < x4_2 && x4_2 < x2))
      {
         if(y2<y3_2 && y3_2<y2+35)
         {
              pontucao+=100;

         }
      }
       if(( x1 < x3_3 && x3_3 < x2) || ( x1 < x4_3 && x4_3 < x2))
      {
         if(y2<y3_3 && y3_3<y2+35)
         {
              pontucao+=100;

         }
      }
       if(( x1 < x3_4 && x3_4 < x2) || ( x1 < x4_4 && x4_4 < x2))
      {
         if(y2<y3_4 && y3_4<y2+35)
         {
              pontucao+=100;

         }
      }
       if(( x1 < x3_5 && x3_5 < x2) || ( x1 < x4_5 && x4_5 < x2))
      {
         if(y2<y3_5 && y3_5<y2+35)
         {
              pontucao+=100;

         }
      }

}



      ////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if(player.dx>=600 && player.dy==298)
{
    tem_espada=1;

}
if(tem_espada)
{
    remove_espada--;
    if(remove_espada==0)
    {
        tem_espada=0;
        remove_espada=400;
    }
}

if(deuruim==0 && jogar==1 && digita_recorde==0){

            //fundo=IMG_Load("img/estalagmites.png");
               SDL_BlitSurface( fundo, NULL, tela, NULL);
     texto();
     drawMap();

    if(taca_outro<=80)
    {
        caminho_barril_1();
        draw_barril(barril.sx_1[0], barril.sy_1[0], barril.dx_1[0], barril.dy_1[0], barril.largura_1, barril.altura_1, queijo, tela);
    }

     if(taca_outro<=0)
     {
         caminho_barril_2();
         draw_barril(barril.sx_1[1], barril.sy_1[1], barril.dx_1[1], barril.dy_1[1], barril.largura_1, barril.altura_1, queijo, tela);
     }
     if(taca_outro<=-80)
     {
         caminho_barril_3();
         draw_barril(barril.sx_1[2], barril.sy_1[2], barril.dx_1[2], barril.dy_1[2], barril.largura_1, barril.altura_1, queijo, tela);
     }

     if(taca_outro<=-160)
     {
         caminho_barril_4();
         draw_barril(barril.sx_1[3], barril.sy_1[3], barril.dx_1[3], barril.dy_1[3], barril.largura_1, barril.altura_1, queijo, tela);
     }
     if(taca_outro<=-240)
     {
         caminho_barril_5();
         draw_barril(barril.sx_1[4], barril.sy_1[4], barril.dx_1[4], barril.dy_1[4], barril.largura_1, barril.altura_1, queijo, tela);
     }
     if(taca_outro<=-320)
     {
         caminho_barril_6();
         draw_barril(barril.sx_1[5], barril.sy_1[5], barril.dx_1[5], barril.dy_1[5], barril.largura_1, barril.altura_1, queijo, tela);
     }
     taca_outro--;


     lorde_cheddar_movimento();
     draw_lorde(lorde.sx_3, lorde.sy_3,lorde.dx_3,lorde.dy_3,lorde.largura_3,lorde.altura_3,lorde_cheddar,tela);


     draw_player(player.sx, player.sy, player.dx, player.dy, player.largura, player.altura, rato, tela);
}
                             // controla o FPS
if(diminui_bonus==0)
{
    bonus--;
    diminui_bonus=100;
}
diminui_bonus--;
if(player.dx>=350 && player.dy==82)
{
                    acabou=1;
                    deuruim=1;

}


                        if(player_vida==0)
                        {
                            deuruim=1;
                            player_vida=3;
                        }
                        game_over(deuruim);

                             if(1000/FPS >(SDL_GetTicks()-tempo))
          SDL_Delay(1000/FPS-(SDL_GetTicks()-tempo));
       SDL_Flip( tela);

           if(SDL_Flip(tela) == -1)
          {
           return 1;
          }
        }

        /* libera memoria*/

SDL_FreeSurface( rato );
SDL_FreeSurface(queijo);
SDL_FreeSurface( piso );
SDL_FreeSurface( escada );
SDL_FreeSurface( tela );
SDL_FreeSurface( piso );
SDL_FreeSurface( lorde_cheddar );
SDL_FreeSurface( espada );
SDL_FreeSurface( tela_1);
SDL_FreeSurface( tela_game_over);
SDL_FreeSurface(tela_instrucoes );
SDL_FreeSurface( tela_creditos);
Mix_FreeMusic( musica );
Mix_CloseAudio();
TTF_Quit();
SDL_Quit();
return 0;

}
