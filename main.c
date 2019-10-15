//////////////////////////////////////////////////////////////////////////////////////////////////////
//                     Universidade Federal do Vale do São Francisco - UNIVASF                      //
//                                                                                                  //
// Disciplina: Algoritmos e Estrutura de Dados II                                                   //
// Projeto: Algoritmo de Dijkstra aplicado ao problema do Metrô de Paris                            //
//                                                                                                  //
// Docente: Ana Emília de Melo Queiroz                                                              //
//                                                                                                  //
// Discentes: Allisson Pierre Lino Gomes                                                            //
//            Caroline Carvalho Machado                                                             //
//            Esron Dtamar da Silva                                                                 //
//            Pedro Henrique Duarte Santana                                                         //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "resource.h"

//---------------------------------------------------------------------------------------------------

// Definindo a lista

typedef struct celula_str *LINK;

typedef struct celula_str {
	int estacao;
	char linha;
	float d_real;
	LINK prox;
}celula;

typedef struct {
	LINK head;
	LINK tail;
	int vert;
	float tempo;
	float distancia;
}TipoLista;

TipoLista listadj[LIM];
float m_dis[LIM][LIM];    //Matriz de distancias diretas entre as estacoes

//--------------------------------------------------------------------------------------------

// Núcleo do programa

#include "funcoes_lista.h"
#include "inserir_arquivo.h"
#include "menor_peso.h"
#include "dijkstra.h"

//--------------------------------------------------------------------------------------------

// Construindo a janela principal

const char g_szClassName[] = "MetroParis";

// Caixa de diálogos

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:

        return TRUE;
        case WM_COMMAND:
            EndDialog(hwnd, IDCANCEL);
        break;
        default:
            return FALSE;
    }
    return TRUE;
}

// Processo de mensagens

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

// Main

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

    // Definindo a janela principal

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon (GetModuleHandle (NULL), MAKEINTRESOURCE (IDI_MICON));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(HOLLOW_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE (IDR_MMENU);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = (HICON) LoadImage (GetModuleHandle (NULL), MAKEINTRESOURCE (IDI_MICON), IMAGE_ICON, 16, 16, 0);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Falha ao registrar janela", "Erro",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

    // Criando janela principal

	hwnd = CreateWindowEx(0,g_szClassName,"Metrô de Paris - Dijkstra",WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX,CW_USEDEFAULT, CW_USEDEFAULT, 712, 447,HWND_DESKTOP, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		MessageBox(NULL, "Falha ao criar janela", "Erro",MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

    // Carregando os arquivos de texto

	inserir_arquivo();

    // Loop de mensagens

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

//------------------------------------------------------------------------------------------------------

// Variáveis do processo

TipoLista caminho;
int item_origem, item_destino;
TCHAR s_origem[256], s_destino[256];
char e_o[3],e_d[3];
int origem,destino,velocidade,espera;
int completo=1,e_atual,e_prox,aux,troca;
LINK p=NULL;

// Variáveis do mapa

RECT rect;
HBITMAP mapa,traj;
BITMAP bm,tr;
int bxWidth, bxHeight;
HDC hdc,hdcMem;
int cxpage = 0;
int cypage = 0;

#include "DesenharBlocos.h"
#include "Processo.h"
