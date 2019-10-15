
// Algoritmo de Dijkstra adaptado ao problema do Metrô de Paris

//-------------------------------------------------------------------------------------------------------------

TipoLista dijkstra(int origem,int destino,int velocidade,int espera)
{
    int i;
    int estacao_atual;
    char linha_atual='z';
    float d_percorrida=0,tempo=0;
	LINK e_compara,e_adiciona;
	TipoLista caminho;

    vazia(&caminho);

    caminho.vert=origem;    // colocar origem no inicio do caminho
    estacao_atual=origem;

    while(estacao_atual!=destino)
    {
        for(i=0;listadj[i].vert!=estacao_atual;i++){} // encontra a fronteira para determinada estacao

        e_adiciona=listadj[i].head->prox;
        e_compara=e_adiciona->prox;

        while(e_compara!=NULL)         // Extrair estacao da fronteira que estah mais proxima do destino
        {
            e_adiciona=menor_peso(e_adiciona, e_compara, estacao_atual, espera, origem, destino, linha_atual, velocidade);
            e_compara=e_compara->prox;
        };
        if(linha_atual!=e_adiciona->linha && linha_atual!='z'){   //Verificar baldeacao
            tempo+=espera;}

        insere(&e_adiciona->estacao,&e_adiciona->linha,&e_adiciona->d_real,&caminho); // insere estacao no caminho

        d_percorrida+=e_adiciona->d_real;
        linha_atual=e_adiciona->linha;
        estacao_atual=e_adiciona->estacao;

    }

    tempo=tempo + d_percorrida*60/velocidade;

    caminho.tempo=tempo;
    caminho.distancia=d_percorrida;

    return caminho;

}
