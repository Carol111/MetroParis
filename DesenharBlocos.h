
// Cria o Bloco de Opções

//----------------------------------------------------------------------------------------------------------

// Variáveis utilizadas para criação do bloco de Opções

HWND Opcao, EstOrigem, EstDestino, VelMetro, TemBaldeacao, Calcula, Reset;  // Itens do bloco Opções
HWND Dados,Caixa1,Trajeto,Caixa2;
HWND lb0,lb1,lb2,lb30,lb31,lb40,lb41;   // Labels
// Conteúdo da combobox
char est_cbox[14][4]={{"E01"},{"E02"},{"E03"},{"E04"},{"E05"},{"E06"},{"E07"},{"E08"},{"E09"},{"E10"},{"E11"},{"E12"},{"E13"},{"E14"}}, add_cbox[4];
int i,j;    // Índices para a combobox

//----------------------------------------------------------------------------------------------------------

// Função que cria o bloco de Opções

void DesenharBlocos(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //Título do bloco Opções
    Opcao = CreateWindowEx(0,"STATIC","",WS_VISIBLE|WS_CHILD|WS_BORDER,2,1,300,396,hwnd,NULL,NULL,0);
    SendMessage((HWND)Opcao,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);
    lb0 = CreateWindowEx(0,"STATIC","Opções",WS_VISIBLE|WS_CHILD,9,7,150,60,hwnd,NULL,0,0);
    SendMessage((HWND)lb0,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

    // Item Estação de Origem
    lb1 = CreateWindowEx(0,"STATIC","Estação de Origem:",WS_VISIBLE|WS_CHILD,20,38,120,60,hwnd,NULL,NULL,0);
    SendMessage((HWND)lb1,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);
    EstOrigem = CreateWindowEx(0,"COMBOBOX","",WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_HASSTRINGS,35,56,60,250,hwnd,(HMENU)ID_ORIGEM,NULL,0);
    SendMessage((HWND)EstOrigem,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

    //Item Estação de Destino
    lb2 = CreateWindowEx(0,"STATIC","Estação de Destino:",WS_VISIBLE|WS_CHILD,170,38,120,60,hwnd,NULL,NULL,0);
    SendMessage((HWND)lb2,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);
    EstDestino = CreateWindowEx(0,"COMBOBOX","Estação de Destino",WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST,186,56,60,250,hwnd,(HMENU)ID_DESTINO,NULL,0);
    SendMessage((HWND)EstDestino,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

    //Item Velocidade do Metrô
    lb30 = CreateWindowEx(0,"STATIC","Velocidade do Metrô:",WS_VISIBLE|WS_CHILD,20,100,120,40,hwnd,NULL,NULL,0);
    SendMessage((HWND)lb30,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);
    VelMetro = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","30",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER,35,118,35,20,hwnd,NULL,NULL,0);
    SendMessage((HWND)VelMetro,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);
    lb31 = CreateWindowEx(0,"STATIC","km/h",WS_VISIBLE|WS_CHILD,74,122,35,20,hwnd,NULL,NULL,0);
    SendMessage((HWND)lb31,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

    //Item Tempo de Baldeação
    lb40 = CreateWindowEx(0,"STATIC","Tempo de Baldeação:",WS_VISIBLE|WS_CHILD,170,100,120,40,hwnd,NULL,NULL,0);
    SendMessage((HWND)lb40,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);
    TemBaldeacao = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","4",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_NUMBER,186,118,35,20,hwnd,NULL,NULL,0);
    SendMessage((HWND)TemBaldeacao,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);
    lb41 = CreateWindowEx(0,"STATIC","minutos",WS_VISIBLE|WS_CHILD,225,121,35,20,hwnd,NULL,NULL,0);
    SendMessage((HWND)lb41,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

    //Item Calcular o melhor trajeto
    Calcula = CreateWindowEx(0,"BUTTON","Calcular o melhor trajeto",WS_CHILD|WS_VISIBLE,15,160,140,25,hwnd,(HMENU)ID_CALCULA,NULL,0);
    SendMessage((HWND)Calcula,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

    //Item Reset
    Reset = CreateWindowEx(0,"BUTTON","Reset",WS_CHILD|WS_VISIBLE,185,160,80,25,hwnd,(HMENU)ID_RESET,NULL,0);
    SendMessage((HWND)Reset,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

    //Bloco Dados
    Dados = CreateWindowEx(0,"STATIC","Dados:",WS_VISIBLE|WS_CHILD,9,200,40,20,hwnd,NULL,NULL,0);
    SendMessage((HWND)Dados,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

    //Bloco Caixa1
    Caixa1 = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","",WS_VISIBLE|WS_CHILD|ES_MULTILINE,7,216,290,50,hwnd,NULL,NULL,0);
    SendMessage((HWND)Caixa1,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

    //Bloco Trajeto
    Trajeto = CreateWindowEx(0,"STATIC","Trajeto:",WS_VISIBLE|WS_CHILD,9,268,40,20,hwnd,NULL,NULL,0);
    SendMessage((HWND)Trajeto,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

    //Bloco Caixa2
    Caixa2 = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","",WS_VISIBLE|WS_CHILD|ES_MULTILINE,7,284,290,108,hwnd,NULL,NULL,0);
    SendMessage((HWND)Caixa2,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),(LPARAM) lParam);

//-------------------------------------------------------------------------------------------------------------------------

// Inserindo Itens na combobox

    for(i=0;i<14;i++)
    {
        for(j=0;j<3;j++)
        {
            add_cbox[j]=est_cbox[i][j];
        }
        add_cbox[4]='\0';
        SendMessage((HWND)EstOrigem,(UINT)CB_ADDSTRING,(WPARAM)0,(LPARAM)&add_cbox);
        SendMessage((HWND)EstDestino,(UINT)CB_ADDSTRING,(WPARAM)0,(LPARAM)&add_cbox);
    }

// Definindo Item incial da combobox

    SendMessage (EstOrigem, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
    SendMessage (EstDestino, CB_SETCURSEL, (WPARAM) 1, (LPARAM) 0);
    SendMessage((HWND)EstOrigem,(UINT)CB_GETLBTEXT,(WPARAM)0,(LPARAM)&s_origem);
    for(i=1;i<3;i++)
        e_o[i-1]=s_origem[i];
    e_o[i]='\0';
    origem=atoi(e_o);
    SendMessage((HWND)EstDestino,(UINT)CB_GETLBTEXT,(WPARAM)1,(LPARAM)&s_destino);
    for(i=1;i<3;i++)
        e_d[i-1]=s_destino[i];
    e_d[i]='\0';
    destino=atoi(e_d);
}
