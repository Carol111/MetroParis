
// Imprime caminho na caixa Trajeto

//----------------------------------------------------------------------------------------------------------

sprintf(s_trajeto_0,"Partindo da estação E%d, pegue a linha ",caminho.vert);
p=caminho.head;
p=p->prox;
linha=p->linha;
switch(linha)
{
    case 'r': {strcat(s_trajeto_0,"vermelha."); break;}
    case 'y': {strcat(s_trajeto_0,"amarela."); break;}
    case 'g': {strcat(s_trajeto_0,"verde."); break;}
    case 'b': {strcat(s_trajeto_0,"azul."); break;}
}
if(p->estacao==troca)
{
    strcat(s_trajeto_0," Você chegará no destino E");
    sprintf(s_trajeto_1,"%d.",p->estacao);
    strcat(s_trajeto_0,s_trajeto_1);
}
else
{
    strcat(s_trajeto_0," Você chegará na estação E");
    sprintf(s_trajeto_1,"%d.",p->estacao);
    strcat(s_trajeto_0,s_trajeto_1);
}
while(p->prox!=NULL)
{
    p=p->prox;
    if(linha!=p->linha)
    {
        strcat(s_trajeto_0," Troque para a linha ");
        linha=p->linha;
        switch(linha)
        {
            case 'r': {strcat(s_trajeto_0,"vermelha"); break;}
            case 'y': {strcat(s_trajeto_0,"amarela"); break;}
            case 'g': {strcat(s_trajeto_0,"verde"); break;}
            case 'b': {strcat(s_trajeto_0,"azul"); break;}
        }
        if(p->estacao==troca)
        {
            strcat(s_trajeto_0," e siga até o destino E");
            sprintf(s_trajeto_1,"%d.",p->estacao);
            strcat(s_trajeto_0,s_trajeto_1);
        }
        else
        {
            strcat(s_trajeto_0," e siga até  a estação E");
            sprintf(s_trajeto_1,"%d.",p->estacao);
            strcat(s_trajeto_0,s_trajeto_1);
        }
    }
    else
    {
        if(p->estacao==troca)
        {
            strcat(s_trajeto_0," Na mesma linha, siga até o destino E");
            sprintf(s_trajeto_1,"%d.",p->estacao);
            strcat(s_trajeto_0,s_trajeto_1);
        }
        else
        {
            strcat(s_trajeto_0," Na mesma linha, siga até a estação E");
            sprintf(s_trajeto_1,"%d.",p->estacao);
            strcat(s_trajeto_0,s_trajeto_1);
        }
        linha=p->linha;
    }
}
