
// Função que decide o peso de cada estaçãp e retorna a que tem o menor peso

//-------------------------------------------------------------------------------------------------------------------

LINK menor_peso(LINK est_a, LINK est_b, int estacao_atual, int espera, int origem, int destino, char linha_atual, int velocidade)
{
    int t_espera_a, t_espera_b;
    int a,b;
    float peso_a=0, peso_b=0;

    if(est_a->linha==linha_atual || linha_atual=='z'||origem==11) t_espera_a=0;
    else t_espera_a=espera;
    if(est_b->linha==linha_atual || linha_atual=='z'||origem==11) t_espera_b=0;
    else t_espera_b=espera;

    a=est_a->estacao;
    b=est_b->estacao;

    if(m_dis[destino-1][a-1]>m_dis[destino-1][estacao_atual-1]||a==origem||b==destino) peso_a=99999999;
    if(m_dis[destino-1][b-1]>m_dis[destino-1][estacao_atual-1]||b==origem||a==destino) peso_b=99999999;

    peso_a += (m_dis[destino-1][a-1]*60)/velocidade + t_espera_a;
    peso_b += (m_dis[destino-1][b-1]*60)/velocidade + t_espera_b;

    if(peso_a<peso_b||(peso_a==peso_b && t_espera_a==0)) return est_a;
    else return est_b;
}
