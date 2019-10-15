//Carrega as insformacoes referentes ao metro

int inserir_arquivo()
{
    char str_est[16],str_lin[16],str_real[25],str_dis[70];   //usados para receberem dados do arquivo
    char vertx[5],adj_est[5],adj_lin,adj_real[5],adj_dis[5]; //usados para vertices adjacentes
    int n,x,y,i,j,k;                                        //indices
    int vertice,adjac_est;                                  //usados para inserir elementos na lista
    float adjac_real;
    FILE *a_est, *a_lin, *a_real, *a_dis;                    //arquivos
//  LINK p;                                                 //usado na impressao

    //Construindo a lista

    // Inicializando os vertices

    for(i=0;i<LIM;i++)
          vazia(&listadj[i]);

    // Carregando os arquivos

    if ((a_est = fopen("arquivos\\estacao.txt","r")) == NULL) {
	    MessageBox(NULL, "Não foi possível carregar o arquivo estacao.txt", "Erro", MB_OK | MB_ICONERROR);
	    exit(1);
    }

     if ((a_lin = fopen("arquivos\\linha.txt","r")) == NULL) {
	    MessageBox(NULL, "Não foi possível carregar o arquivo linha.txt", "Erro", MB_OK | MB_ICONERROR);
	    exit(1);
    }

    if ((a_real = fopen("arquivos\\d_real.txt","r")) == NULL) {
	    MessageBox(NULL, "Não foi possível carregar o arquivo d_real.txt", "Erro", MB_OK | MB_ICONERROR);
	    exit(1);
    }

    n=0;
    while(!feof(a_est)) {

	//Carregando caracteres dos arquivos

    fgets(str_est,15,a_est);
    fgets(str_lin,15,a_lin);
    fgets(str_real,24,a_real);

	//Colocando vetores na lista

        for(i=0;str_est[i]!='-';i++)
           	vertx[i]=str_est[i];

        vertx[i]='\0';
        vertice=atoi(vertx);
        listadj[n].vert=vertice;

    //Inserindo vertices adjacentes na lista

        j=k=i;

	    do {
		    x=0;
		    y=0;

 	//Recuperando valores da cadeia de caracteres

        //Numero da estacao

        for(k = k+1;str_est[k]!=',' && str_est[k]!='\n' && str_est[k]!=';';k++){
                adj_est[y]=str_est[k];
                y++;
		    }
		    adj_est[y]='\0';
		    adjac_est=atoi(adj_est);

        //Linha que liga as estacoes

        for(j = j+1;str_lin[j]!=',' && str_lin[j]!='\n' && str_lin[j]!=';';j++){
                adj_lin=str_lin[j];
		    }

        //Distancia real entre estacoes

		for(i = i+1;str_real[i]!=',' && str_real[i]!='\n' && str_real[i]!=';';i++) {
            adj_real[x]=str_real[i];
            x++;}
            adj_real[x]='\0';
		    adjac_real=atof(adj_real);

    //Inserindo os valores na lista

		    insere(&adjac_est,&adj_lin,&adjac_real,&listadj[n]);

	    }while(str_real[i]!='\n' && str_real[i]!=';');
	      n++;
	 };
	 fclose(a_est);
	 fclose(a_lin);
	 fclose(a_real);

    //Criando a matriz de distancias diretas entre as estacoes

    //Carregando arquivo

    if ((a_dis = fopen("arquivos\\d_direta.txt","r")) == NULL) {
	    MessageBox(NULL, "Não foi possível carregar o arquivo d_direta.txt", "Erro", MB_OK | MB_ICONERROR);
	    exit(1);
        }

        i=0;
    while(!feof(a_dis)){

        fgets(str_dis,69,a_dis);

        j=0;
        k=-1;
        for(j=j+i;j<LIM;j++){
            x=0;
            for(k=k+1;str_dis[k]!='-' && str_dis[k]!='\n' && str_dis[k]!=';';k++){
                adj_dis[x]=str_dis[k];
                x++;
            }
            adj_dis[x]='\0';
            m_dis[i][j]=atof(adj_dis);
            m_dis[j][i]=atof(adj_dis);
        }
        i++;
    }
    fclose(a_dis);

    // Imprimindo a lista

/*    for(i=0;i<n;i++) {

	 printf("\n%d -", listadj[i].vert);

	 p=listadj[i].head;
	 p=p->prox;
	 while(p!=NULL){
	      printf(" %d (%c) [%.1f km]", p->estacao, p->linha, p->d_real);
	      p=p->prox;
    }
    }
*/
    // Imprimindo matriz de distancias
/*
    printf("\n\n");
    for(i=0;i<LIM;i++) {

	 printf("\n%d ", i+1);

	 for(j=0;j<LIM;j++){
        printf("-%.1f",m_dis[i][j]);
	 }
	 printf("\n");
    }
*/
    return 0;
}
