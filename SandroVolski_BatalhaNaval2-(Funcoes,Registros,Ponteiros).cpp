#include <iostream>
#include <string>
#include <ctime>
#define FACIL 10

using namespace std;

//Função com Retorno (1)
//Gera números para linha da matriz de 1 ate 10 aleatoriamente
int aleatoriolinha(){
    int alelinha;
    alelinha = (rand() % FACIL) + 1;
    return (alelinha);
}

//Função com Retorno (1)
//Gera números para a coluna de 1 ate 10 aleatoriamente
int aleatoriocoluna(){
    int alecoluna;
    alecoluna = (rand() % FACIL) + 1;
    return (alecoluna);
}

//Função com parâmetro(s) por valor (2)
// Retorma o Nick/Nome do usuário
string Nome(string *name){
    getline(cin, *name);
    return (*name);
}

//Função com parâmetro(s) por valor (2)
//Retorna a quantidade de erros que teve no jogo.
int Erros(int erro, int errobot){
    return (erro + errobot);
}

//Função com parâmetro(s) por valor (2)
//Realiza a Diferenca entre os pontos do usuário e da máquina, mostrando quantos pontos faltaram para ocorrer um possível empate
int DiferencaPontos (int pmeu, int ppc){
    int diferenca;
    if (pmeu > ppc)
        diferenca = pmeu - ppc;
    else
        diferenca = ppc - pmeu;

    return (diferenca);
}

char poslinha, linchute, sla, MEU[FACIL][FACIL], PC[FACIL][FACIL];
int nivel, quant, quant2, erromeu, erropc, colchute, linchuteale, colchuteale, embar, poscoluna, linha, coluna, alecoluna, alelinha, pontostotal = 0, pontostotalpc = 0, rounds = 0, pontmeu, pontpc;
string denovo, nome, cont, busca;

//Função com passagem de matriz por parâmetro (3)
//Faz as bordas do tabuleiro (antes eu tinha 2 funcoes para isso, mas agora com os parametros consegui colocar em somente uma)
void borda(char JOGADOR[FACIL][FACIL]){
    char y = 65, x = 49;
    for (int linha = 1; linha < FACIL; linha++){
        JOGADOR[linha][0] = y;
        y++;
    } 
    for (int coluna = 0; coluna < FACIL; coluna++){
        if (coluna == 0)
            JOGADOR[0][0] = '#';
        else {
            JOGADOR[0][coluna] = x;
            x++;
        }
    }
}

//Registro (4)
// Lista de variáveis para saber a data que o usuário jogou, para assim armazenar seu jogo no sistema
typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

//Registro (4)
// Lista de variáveis para saber as informacoes do usuário, para armazenar seu jogo
typedef struct{
    int idade;
    string nome;
    Data jogo;
    int PontosTotal;
    int PontosTotalPC;
    int Rounds;
}Player;

//Função com passagem de registro por parâmetro (5)
//Entrada das informacoes que o usuario ira preencher
void Registro(Player *cons){
    cout << "Idade: ";
    cin >> cons->idade;
    cin.ignore();
    cout << "Escreva seu Nickname: " << endl;
    getline(cin, cons->nome);
    cout << "Qual a data de hoje?" << endl;
    cout << "dia: ";
    cin >> cons->jogo.dia;
    cout << "mes: ";
    cin >> cons->jogo.mes;
    cout << "ano: ";
    cin >> cons->jogo.ano;
}

//Função com passagem de registro por parâmetro (5)
//Saida das informacoes cadastradas pelo usuario, desta forma, as informacoes ficam no sistema, e ele consegue ver seu "historico" daquela partida.
void ImprimeRegistro(Player *cons){
    cout << "Nick: " << cons->nome << endl;
    cout << "Idade: " << cons->idade << endl;
    cout << "Data Jogo: " << cons->jogo.dia << "/" << cons->jogo.mes << "/" << cons->jogo.ano << endl;
    cout << "Meus Pontos: " << cons->PontosTotal << endl;
    cout << "Pontos PC: " << cons->PontosTotalPC << endl;
    cout << "Rounds: " << cons->Rounds << endl;
}

void tabuleiros2(){
    cout << "Capitao W.L.                     " << nome << endl; 
    for (linha = 0; linha < FACIL; linha++){ 
        for (coluna = 0; coluna < FACIL; coluna++){
            if (PC[linha][coluna] == 'z')// PC[linha][coluna] == 'S' || PC[linha][coluna] == 'K')
                cout << '~' << " ";
            else
                cout << PC[linha][coluna] << " ";
        }
        cout << "             ";
        for (coluna = 0; coluna < FACIL; coluna++){
            if (MEU[linha][coluna] == 'z')
                cout << '~' << " ";
            else
                cout << MEU[linha][coluna] << " ";
        }
        cout << endl;
    }
}

void posicsub_facil(){
    system("cls");
    cout << "               SUBMARINO                        " << endl;
    cout << "       V                                           " << endl;
    cout << "                V               V                " << endl;
    cout << "                  __.                         V" << endl;
    cout << "~.~.~.~.~.~.~.~.~.|.~.~.~.~.~~.~.~.~.~.~.~." << endl;
    cout << "~.~.~.~.~.~.~.____|___~.~.~.~.~.~.~.~~.~.~." << endl;
    cout << "~.~.~.~.~.~.~ L______/~...~...~...~...~...~" << endl;
    cout << "~...~...~...~...~~~    ~~~~    ~...~...~   " << endl << endl << endl;

    quant = 2;
    while (quant != 0){
        borda(MEU);
        for (linha = 0; linha < FACIL; linha++){ 
            for (coluna = 0; coluna < FACIL; coluna++){
                if (MEU[linha][coluna] == 'z')
                    cout << '~' << " ";
                else
                    cout << MEU[linha][coluna] << " ";
            }
            cout << endl;
        }   
        cout << endl << "Submarinos restantes: " << quant << endl;
        cout << "Digite qual posicao adicionar o submarino (LETRA/NUMERO): " << endl;
        cin >> poslinha >> poscoluna;

        if (MEU[poslinha-64][poscoluna] == '~' && MEU[poslinha][poscoluna] != 'z'){

            MEU[poslinha-64][poscoluna+1] = 'z';  
            MEU[poslinha-64][poscoluna-1] = 'z'; 
            MEU[poslinha-65][poscoluna] = 'z'; 
            MEU[poslinha-63][poscoluna] = 'z'; 
            MEU[poslinha-65][poscoluna-1] = 'z'; 
            MEU[poslinha-65][poscoluna+1] = 'z'; 
            MEU[poslinha-63][poscoluna-1] = 'z'; 
            MEU[poslinha-63][poscoluna+1] = 'z';

            MEU[poslinha-64][poscoluna] = 'S';

            quant --;
        }
        else {
            cout << "Posicao Invalida !" << endl;
        }
    }
}

void posichidro_facil(){
    system("cls");
    cout << "         HIDROAVIAO " << endl;
    cout <<"          ___/   L_" << endl;
    cout <<"          ==/   L==`" << endl;
    cout <<"  _________/   L_______" << endl;
    cout <<"  /____________________\"" << endl;
    cout <<" _||__||__/.--.L||__||_" << endl;
    cout <<"  /_|__|__(.><.)__|__|_\"" << endl;
    cout <<"        _ /`--`L _" << endl;
    cout <<"       ( /------L )" << endl << endl << endl;

    quant = 2;
    while (quant > 0){
        borda(MEU);
        for (linha = 0; linha < FACIL; linha++){ 
            for (coluna = 0; coluna < FACIL; coluna++){
                if (MEU[linha][coluna] == 'z')
                    cout << '~' << " ";
                else
                    cout << MEU[linha][coluna] << " ";
            }
            cout << endl;
        }

        cout << endl << "Hidroavioes restantes: " << quant << endl;
        cout << "Digite qual a posicao central para adicionar o hidroaviao (LETRA/NUMERO):" << endl;
        cin >> poslinha >> poscoluna;
        cout << endl;

        if (MEU[poslinha-64][poscoluna] == '~' && MEU[poslinha-64][poscoluna] != 'z' && 
            MEU[poslinha-64][poscoluna+1] == '~' && MEU[poslinha-64][poscoluna+1] != 'z' &&
            MEU[poslinha-64][poscoluna-1] == '~' && MEU[poslinha-64][poscoluna-1] != 'z' &&
            MEU[poslinha-63][poscoluna] == '~' && MEU[poslinha-63][poscoluna] != 'z'){  

            MEU[poslinha-64][poscoluna+2] = 'z'; 
            MEU[poslinha-64][poscoluna-2] = 'z';
            MEU[poslinha-63][poscoluna+1] = 'z';
            MEU[poslinha-63][poscoluna-1] = 'z';
            MEU[poslinha-63][poscoluna+2] = 'z';
            MEU[poslinha-63][poscoluna-2] = 'z';
            MEU[poslinha-62][poscoluna] = 'z';
            MEU[poslinha-62][poscoluna+1] = 'z'; 
            MEU[poslinha-62][poscoluna-1] = 'z';
            MEU[poslinha-65][poscoluna] = 'z';
            MEU[poslinha-65][poscoluna+1] = 'z'; 
            MEU[poslinha-65][poscoluna+2] = 'z';
            MEU[poslinha-65][poscoluna-1] = 'z';
            MEU[poslinha-65][poscoluna-2] = 'z';
            MEU[poslinha-65][poscoluna-2] = 'z';

            MEU[poslinha-64][poscoluna] = 'H';
            MEU[poslinha-64][poscoluna+1] = 'H';
            MEU[poslinha-64][poscoluna-1] = 'H';
            MEU[poslinha-63][poscoluna] = 'H';

            quant --;
        } 
        else {
            cout << "Posicao Invalida !" << endl;
        }
        borda(MEU);
    }
}

int main (){ 
    system("cls");
    system("color B");  
    cout << "             |)           |_" << endl;
    cout << "            /|) ========= |)"<< endl;
    cout << "           / |)  BATALHA  |)"<< endl;
    cout << "          /  |)   NAVAL   |)"<< endl;
    cout << "         /   |) ========= |)"<< endl;
    cout << "   _    /    |)           |)      "<< endl;
    cout << "    |__/_____|____________|______"<< endl;
    cout << " ~~~|      .       .      .     /~~~~~ ~~~ ~"<< endl;
    cout << "~~~ ~~|________________________/~~~ ~~~~ ~~~~~"<< endl;
    cout << "~ ~~~~~~ ~~~~~~~~~~~~ ~~~ ~~~~ ~~~~ ~~~ ~~~"<< endl;

    cout << "Escreva seu Nickname: " << endl;
    Nome(&nome);
    
    do{
        do{
            if (rounds == 1)
                cout << "ROUND 1" << endl << endl;
            if (rounds == 2)
                cout << "ROUND 2" << endl << endl;
            if (rounds == 3)
                cout << "ROUND 3" << endl << endl;
            if (rounds == 4)
                break;

            //tabuleiro
            for (linha = 0; linha < FACIL; linha++){ 
                for (coluna = 0; coluna < FACIL; coluna++){
                    MEU[linha][coluna] = '~';
                    PC[linha][coluna] = '~';
                }
            }
            borda(MEU);
            borda(PC);
            cout << endl;
            for (linha = 0; linha < FACIL; linha++){ 
                for (coluna = 0; coluna < FACIL; coluna++){
                    cout << MEU[linha][coluna] << " ";
                }
                cout << endl;
            }
            
            cout << endl << "Adicione suas embarcacoes" << endl;
            cout << "Qual embarcacao deseja adicionar ?" << endl << "1. Submarino" << endl << "2. Hidroaviao" << endl;
            cin >> embar;

            //SUBMARINO E HIDROAVIAO
            if (embar == 1){
                posicsub_facil();
                posichidro_facil();
            }
            else {
                posichidro_facil();
                posicsub_facil();
            } 
            
            //PC
            quant = 2;
            srand(time(NULL));
            while (quant > 0){
                alelinha = aleatoriolinha();
                alecoluna = aleatoriocoluna();
                if  ((PC[alelinha][alecoluna] == '~' && PC[alelinha][alecoluna] != 'z') &&
                    (alelinha >= 0) && (alelinha <= FACIL-1) && (alecoluna >= 0) && (alecoluna <= FACIL-1)){

                    PC[alelinha][alecoluna+1] = 'z';  
                    PC[alelinha][alecoluna-1] = 'z'; 
                    PC[alelinha-1][alecoluna] = 'z'; 
                    PC[alelinha+1][alecoluna] = 'z'; 
                    PC[alelinha-1][alecoluna-1] = 'z'; 
                    PC[alelinha-1][alecoluna+1] = 'z'; 
                    PC[alelinha+1][alecoluna-1] = 'z'; 
                    PC[alelinha+1][alecoluna+1] = 'z';
                
                    PC[alelinha][alecoluna] = 'S';
                    quant --;
                }
            }
            quant2 = 2;
            while (quant2 > 0){
                alelinha = aleatoriolinha();
                alecoluna = aleatoriocoluna();
                
                if (PC[alelinha][alecoluna] == '~' && PC[alelinha][poscoluna] != 'z' && 
                    PC[alelinha][alecoluna+1] == '~' && PC[alelinha][poscoluna+1] != 'z' &&
                    PC[alelinha][alecoluna-1] == '~' && PC[alelinha][poscoluna-1] != 'z' &&
                    PC[alelinha+1][alecoluna] == '~' && PC[alelinha+1][poscoluna] != 'z'){  
                        
                    PC[alelinha][alecoluna+2] = 'z'; 
                    PC[alelinha][alecoluna-2] = 'z';
                    PC[alelinha+1][alecoluna+1] = 'z';
                    PC[alelinha+1][alecoluna-1] = 'z';
                    PC[alelinha+1][alecoluna+2] = 'z';
                    PC[alelinha+1][alecoluna-2] = 'z';
                    PC[alelinha+2][alecoluna] = 'z';
                    PC[alelinha+2][alecoluna+1] = 'z'; 
                    PC[alelinha+2][alecoluna-1] = 'z';
                    PC[alelinha-1][alecoluna] = 'z';
                    PC[alelinha-1][alecoluna+1] = 'z'; 
                    PC[alelinha-1][alecoluna+2] = 'z';
                    PC[alelinha-1][alecoluna-1] = 'z';
                    PC[alelinha-1][alecoluna-2] = 'z';
                    PC[alelinha-1][alecoluna-2] = 'z';

                    PC[alelinha][alecoluna] = 'K';
                    PC[alelinha][alecoluna+1] = 'K';
                    PC[alelinha][alecoluna-1] = 'K';
                    PC[alelinha+1][alecoluna] = 'K';
                    if (quant2 == 1)
                        break;
                    quant2 --;
                } 
            }
            cout << endl;
            //MOSTRAR POSICAO ESCOLHIDA
            borda(PC);
            tabuleiros2();

            //CHUTES
            cout << endl << "Pontos: 0" <<"                        Pontos: 0"<< endl;
            cout << endl << "Tente acertar a embarcacao inimiga" << endl;
            cout << endl << "Qual cordenada voce acha que esta a embarcacao inimiga?" << endl;
            int quant = 10, pontmeu = 0, pontpc = 0, jogadas=0;
            erromeu = 0;
            erropc = 0;
            while (pontmeu < quant || pontpc < quant){
                do {
                    cout << "Sua vez..." << endl;
                    cin >> linchute >> colchute;
                    system("cls");

                    if (PC[linchute-64][colchute] == '-' || PC[linchute-64][colchute] == 'X'){
                        cout << "Voce ja tentou este local, tente novamente!" << endl;
                        //TABULEIROS
                        tabuleiros2();
                        cout << endl << "Pontos: " << pontpc <<"                        Pontos: "<< pontmeu << endl; 
                    }
                    if (PC[linchute-64][colchute] == 'S' || PC[linchute-64][colchute] == 'K'){
                        cout << "Voce acertou" << endl;
                        PC[linchute-64][colchute] = 'X';
                        pontmeu++;
                        tabuleiros2();
                        cout << endl << "Pontos: " << pontpc <<"                        Pontos: "<< pontmeu << endl; 
                    }
                    if (pontmeu == quant || pontpc == quant)
                        break;
                }while (PC[linchute-64][colchute] == 'X' || PC[linchute-64][colchute] == '-');
                if (pontmeu == quant || pontpc == quant)
                    break;
                if (PC[linchute-64][colchute] != 'S' || PC[linchute-64][colchute] != 'K'){
                    cout << "Que pena, voce errou !" << endl;
                    PC[linchute-64][colchute] = '-';
                    erromeu ++;
                } 
                borda(MEU);
                
                do {
                    linchuteale = (rand()% FACIL-1) + 1;
                    colchuteale = (rand()% FACIL-1) + 1;
                    if (MEU[linchuteale][colchuteale] == 'S' || MEU[linchuteale][colchuteale] == 'H'){
                        cout << "O Capitao Wooden Leg acertou !" << endl;
                        MEU[linchuteale][colchuteale] = 'X';
                        pontpc++;
                        
                    }   
                    if (pontmeu == quant || pontpc == quant)
                        break;
                }while (MEU[linchuteale][colchuteale] == 'X' || MEU[linchuteale][colchuteale] == '-');
                if (pontmeu == quant || pontpc == quant)
                    break;
                if (MEU[linchuteale][colchuteale] != 'S' || MEU[linchuteale][colchuteale] != 'H'){
                    cout << endl << "O Capitao Wooden Leg errou !" << endl << endl;
                    MEU[linchuteale][colchuteale] = '-';
                    erropc ++;
                }
                borda(MEU);
                tabuleiros2();
                cout << endl << "Pontos: " << pontpc <<"                        Pontos: "<< pontmeu<< endl; 
            }
            if (rounds == 0){
                if (pontmeu > pontpc){
                    cout << "O Capitao Wooden Leg esta bravo e quer um torneio com voce!" << endl;
                    cout << "Voce aceita?" << endl;
                    cin >> denovo;
                }
                else{
                    cout << "Que pena, nao foi desta vez!" << endl << "Voce quer participar de um torneio contra o Capitao Wooden Leg?" << endl;
                    cin >> denovo;
                }
            }
            if (rounds < 3 && rounds != 0)
                denovo = "SIM";
            pontostotal += pontmeu;
            pontostotalpc += pontpc;
            rounds ++;
            system("cls");
        
        }while (denovo == "SIM" || denovo == "Sim" || denovo == "sim");
        cout << "================" << endl << "SCORE DA PARTIDA" << endl << "================" << endl;
        cout << "Em: " << rounds << " rounds" << endl;
        cout << nome << ": " << pontostotal << " pontos" << endl;
        cout << "Capitao Wooden Leg: " << pontostotalpc << " pontos" << endl;
        cout << "Total de erros no jogo: " << Erros(erromeu, erropc) << endl << "sendo eles: " << endl;
        cout << "Erros " << nome << ": " << erromeu << endl << "Erros Capitao: " << erropc << endl;
        cout << "Diferenca entre pontos: " << DiferencaPontos(pontostotal, pontostotalpc) << endl;

        if (pontostotal > pontostotalpc){
            cout << "    "<<nome << endl; 
            cout << "    CAMPEAO" << endl;        
            cout << "  ___________" << endl;
            cout << " '._==_==_=_.'"<< endl;
            cout << " .-|:       /-."<< endl;
            cout << "| (|:.      |) |"<< endl;
            cout <<  "'-|:.       |-'"<< endl;
            cout << "   |::.    /"<< endl;
            cout << "    '::. .'"<< endl;
            cout << "      ) ("<< endl;
            cout << "    _.' '._"<< endl;
            cout << "   |_______|"<< endl;
        }
        else{
            cout << nome << ", nao foi desta vez! O Capitao Wooden Leg venceu! " << endl;
            cout << "Tente novamente!" << endl;

            cout << "                 ____"<< endl;
            cout << "                |   /"<< endl;
            cout << "                |   |"<< endl;
            cout << "   .__.         |   |_____________________________________________"<< endl;
            cout << "   |  |_________|   |   ...........Tente novamente..........       ! "<< endl;
            cout << "   |  |         |   |________________________________________________! "<< endl;
            cout << "   |  |_________|   |                                                /"<< endl;
            cout << "   |__|         |   |_____________________________________________ /"<< endl;
            cout << "                |   |"<< endl;
            cout << "                |   |"<< endl;
            cout << "                |___/" << endl;
        }

        int pessoas = 1;
        Player NovaPessoa[1000];
        Data NovaData;
        int k = 0;
        cout << "Voce deseja armazenar este score ? (Nao/Sim)" << endl;
        cin >> cont;
        if (cont != "Nao" && cont != "nao"){
            Registro(&NovaPessoa[k]);
            NovaPessoa[k].PontosTotal = pontostotal;
            NovaPessoa[k].PontosTotalPC = pontostotalpc;
            NovaPessoa[k].Rounds = rounds;
            ImprimeRegistro(&NovaPessoa[k]);
            pessoas++;
        }
        pessoas = pessoas - 1;
        cout << "Voce deseja buscar algum score ? (S/N)" << endl;
        cin >> sla;
        if (sla == 'S'){
            do{
                cout << "Buscando Nick: ";
                cin.ignore();
                getline(cin, busca);
                for (int i = 0; i < pessoas; i++){
                    if(busca == NovaPessoa[i].nome)
                        ImprimeRegistro(&NovaPessoa[i]);
                }
                cout << "Gostaria de fazer outra busca (S/N): ";
                cin >> sla;
            }while(sla != 'N');
        }
        k++;
        pontostotal = 0;
        pontostotalpc = 0;
        rounds = 0;
        cout << "Deseja jogar novamente? " << endl;
    }while(cin >> cont && cont == "Sim" || cont == "Sim");
}