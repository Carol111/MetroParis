
// Processo de mensagens

//------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Dados do bloco opções

    char s_vel[6],s_esp[6];
    char s_dado[300],s_trajeto_0[2000],s_trajeto_1[30],branco;

    // Dados do caminho

    int horas,minutos,t;
    char linha;

    // Mapa

    PAINTSTRUCT ps;

    // Zerando os valores do tempo

    for(t=0;t<6;t++)
    {
        s_vel[t]="0";
        s_esp[t]="0";
    }

    // Processo de mensagens

    switch (message)
    {
    case WM_CREATE:
        {
            // Criando interior da janela principal -----------------------------------------------------------------------

            // Opções
            DesenharBlocos(hwnd,message,wParam,lParam);

            //Mapa
            completo=1;
            mapa = (HBITMAP)LoadImage(NULL,"imagens\\mapa_c.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
            GetObject(mapa,sizeof(BITMAP),&bm);
            bxWidth = bm.bmWidth;
            bxHeight = bm.bmHeight;
            rect.left = 305;
            rect.top = 1;
            rect.right = 704;
            rect.bottom = 396;
            InvalidateRect(hwnd,&rect,1);
        }
        break;
    case WM_COMMAND:
    {
        // Selecionando estação na combobox ------------------------------------------------------------------------------

        if(HIWORD(wParam) == CBN_SELCHANGE)
        {
            switch(LOWORD(wParam))
            {
            case ID_ORIGEM: // COMBOBOX Estação de origem
                {
                    item_origem = SendMessage((HWND)lParam,(UINT)CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);
                    SendMessage((HWND)lParam,(UINT)CB_GETLBTEXT,(WPARAM)item_origem,(LPARAM)&s_origem);
                    for(i=1;i<3;i++)
                        e_o[i-1]=s_origem[i];
                    e_o[3]='\0';
                    origem=atoi(e_o);
                }
            break;
            case ID_DESTINO: // COMBOBOX Estação de destino
                {
                    item_destino = SendMessage((HWND)lParam,(UINT)CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);
                    SendMessage((HWND)lParam,(UINT)CB_GETLBTEXT,(WPARAM)item_destino,(LPARAM)&s_destino);
                    for(i=1;i<3;i++)
                        e_d[i-1]=s_destino[i];
                    e_d[3]='\0';
                    destino=atoi(e_d);
                }
            break;
            }
        }
        if ((HIWORD(wParam) == BN_CLICKED))
        {

            // Recebendo valores sobre velocidade e tempo de espera

            SendMessage((HWND)VelMetro,(UINT) EM_GETLINE,(WPARAM) 1,(LPARAM)&s_vel);
            velocidade = atoi(s_vel);
            SendMessage((HWND)TemBaldeacao,(UINT)EM_GETLINE,(WPARAM)1,(LPARAM)&s_esp);
            espera = atoi(s_esp);

            switch (LOWORD(wParam))
            {
                case ID_CALCULA:    //  Botão CALCULANDO O CAMINHO ---------------------------------------------------------
                    {
                        completo=0;
                        branco='\0';
                        s_trajeto_0[0]='\0';

                        item_origem = SendMessage((HWND)lParam,(UINT)CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);
                        SendMessage((HWND)lParam,(UINT)CB_GETLBTEXT,(WPARAM)item_origem,(LPARAM)&s_origem);
                        for(i=1;i<3;i++)
                            e_o[i-1]=s_origem[i];
                        e_o[3]='\0';
                        origem=atoi(e_o);

                        item_destino = SendMessage((HWND)lParam,(UINT)CB_GETCURSEL,(WPARAM) 0, (LPARAM) 0);
                        SendMessage((HWND)lParam,(UINT)CB_GETLBTEXT,(WPARAM)item_destino,(LPARAM)&s_destino);
                        for(i=1;i<3;i++)
                            e_d[i-1]=s_destino[i];
                        e_d[3]='\0';
                        destino=atoi(e_d);

                        if(origem==destino)
                        {
                            completo=1;
                            SendMessage((HWND)Caixa1,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)&branco);
                            sprintf(s_trajeto_0,"Voce já se encontra na estação E%d.",origem);
                            SendMessage((HWND)Caixa2,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)&s_trajeto_0);
                            mapa = (HBITMAP)LoadImage(NULL,"imagens\\mapa_null.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(mapa,sizeof(BITMAP),&bm);
                            bxWidth = bm.bmWidth;
                            bxHeight = bm.bmHeight;
                            rect.left = 305;
                            rect.top = 1;
                            rect.right = 704;
                            rect.bottom = 396;
                            InvalidateRect(hwnd,&rect,1);
                            break;
                        }
                        if(origem!=11)
                        {
                            if(destino!=11){
                            troca=destino;
                            if(origem>destino){destino=origem;origem=troca;}}
                            else{destino=origem;origem=11;}
                        }

                        caminho = dijkstra(origem,destino,velocidade,espera); // DIJKSTRA -------------------------------------

                        minutos=(int)caminho.tempo;
                        horas=minutos/60;
                        minutos%=60;
                        sprintf(s_dado,"Menor distância pelo algoritmo de Dijkstra: %.1f km             Tempo estimado do trajeto: %d hora(s) %d minutos(s)",caminho.distancia,horas,minutos);

                        #include "imprime.h"    // imprime o caminho no bloco Trajeto

                        SendMessage((HWND)Caixa1,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)&s_dado);
                        SendMessage((HWND)Caixa2,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)&s_trajeto_0);

                        mapa = (HBITMAP)LoadImage(NULL,"imagens\\mapa_null.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                        GetObject(mapa,sizeof(BITMAP),&bm);
                        bxWidth = bm.bmWidth;
                        bxHeight = bm.bmHeight;
                        rect.left = 305;
                        rect.top = 1;
                        rect.right = 704;
                        rect.bottom = 396;
                        InvalidateRect(hwnd,&rect,1);   // Força repintura da tela para mostrar o caminho no mapa

                    }
                break;
                case ID_RESET: // Botão RESET ------------------------------------------------------------------------------
                    {
                        completo=1;
                        branco='\0';
                        SendMessage((HWND)Caixa1,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)&branco);
                        SendMessage((HWND)Caixa2,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)&branco);

                        mapa = (HBITMAP)LoadImage(NULL,"imagens\\mapa_c.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                        GetObject(mapa,sizeof(BITMAP),&bm);
                        bxWidth = bm.bmWidth;
                        bxHeight = bm.bmHeight;
                        rect.left = 305;
                        rect.top = 1;
                        rect.right = 704;
                        rect.bottom = 396;
                        InvalidateRect(hwnd,&rect,1);
                    }
                break;
            }
        }

        // Menu ------------------------------------------------------------------------------------------------

        switch(LOWORD(wParam))
        {
            case ID_ARQUIVO_SAIR:
                PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
            case ID_AJUDA:
            {
                int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AJUDA), hwnd, AboutDlgProc);
                if(ret == -1)
                MessageBox(hwnd, "Falha na caixa de diálogo", "Error",MB_OK | MB_ICONINFORMATION);
            }
            break;
            case ID_SOBRE:
            {
                int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SOBRE), hwnd, AboutDlgProc);
                if(ret == -1)
                    MessageBox(hwnd, "Falha na caixa de diálogo", "Error",MB_OK | MB_ICONINFORMATION);
            }
            break;
        }
    }
    break;

    // Desenhando o mapa ----------------------------------------------------------------------------------------------------

    case WM_PAINT:
    {
        HDC hdc = BeginPaint(hwnd,&ps);
        hdcMem = CreateCompatibleDC(hdc);

        if(completo)    // Mapa completo
        {
            SelectObject(hdcMem, mapa);
            StretchBlt(hdc, 305, 1, bxWidth, bxHeight, hdcMem, 0, 0,bxWidth,bxHeight, SRCCOPY);
        }
        else    // trajeto
        {
            SelectObject(hdcMem, mapa);
            StretchBlt(hdc, 305, 1, bxWidth, bxHeight, hdcMem, 0, 0,bxWidth,bxHeight, SRCCOPY);

            caminho.tail->prox=(LINK)malloc(sizeof(celula));
            caminho.tail=caminho.tail->prox;
            caminho.tail->prox=NULL;

            e_atual=caminho.vert;
            p=caminho.head;
            p=p->prox;
            e_prox=p->estacao;
            if(e_atual>e_prox)
            {
                aux=e_atual;
                e_atual=e_prox;
                e_prox=aux;
            }
            while(p->prox!=NULL){
            if(e_atual==1)//1-2
                {
                traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_1_2.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                GetObject(traj,sizeof(BITMAP),&tr);
                SelectObject(hdcMem, traj);
                StretchBlt(hdc, 323, 129, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                }
                else{
                    if(e_atual==2)
                    {
                        if(e_prox==3)//2-3
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_2_3.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 406, 182, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                        if(e_prox==9)//2-9
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_2_9.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 405, 129, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                        if(e_prox==10)//2-10
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_2_10.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 338, 183, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                    }
                    else
                    {
                    if(e_atual==3)
                    {
                        if(e_prox==4)//3-4
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_3_4.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 472, 202, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                        if(e_prox==9)//3-9
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_3_9.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 467, 133, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                        if(e_prox==13)//3-13
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_3_13.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 464, 208, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                    }
                    else
                    {
                    if(e_atual==4)
                    {
                        if(e_prox==5)//4-5
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_4_5.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 522, 219, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                        if(e_prox==8)//4-8
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_4_8.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 521, 121, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                        if(e_prox==13)//4-13
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_4_13.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 502, 222, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                    }
                    else
                    {
                    if(e_atual==5)
                    {
                        if(e_prox==6)//5-6
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_5_6.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 611, 262, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                        if(e_prox==7)//5-7
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_5_7.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 587, 260, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                        if(e_prox==8)//5-8
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_5_8.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 535, 116, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                    }
                    else
                    {
                    if(e_atual==8)
                    {
                        if(e_prox==9)//8-9
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_8_9.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 471, 112, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                        if(e_prox==12)//8-12
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_8_12.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 514, 40, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                    }
                    else
                    {
                    if(e_atual==9)
                    {
                        if(e_prox==11)//9-11
                        {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_9_11.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 387, 40, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                        }
                    }
                    else
                    {
                    if(e_atual==13)//13-14
                    {
                            traj = (HBITMAP)LoadImage(NULL,"imagens\\mapa_13_14.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
                            GetObject(traj,sizeof(BITMAP),&tr);
                            SelectObject(hdcMem, traj);
                            StretchBlt(hdc, 482, 304, tr.bmWidth, tr.bmHeight, hdcMem, 0, 0,tr.bmWidth,tr.bmHeight, SRCCOPY);
                    }
            }}}}}}}
            if(e_atual!=p->estacao)
                e_atual=e_prox;
            p=p->prox;
            e_prox=p->estacao;
            if(e_atual>e_prox)
            {
                aux=e_atual;
                e_atual=e_prox;
                e_prox=aux;
            }
        }
        }
        DeleteDC(hdcMem);
        EndPaint(hwnd,&ps);
    }
    break;

    // Encerrando --------------------------------------------------------------------------------------------------

    case WM_CLOSE:
    {
        DeleteObject(mapa);
        DestroyWindow(hwnd);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage (0);
    break;
    default:
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
