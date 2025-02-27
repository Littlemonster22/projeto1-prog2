#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <locale.h>
#include <fstream>
#define TAMANHO 7
using namespace std;

void letreiro();
void limparTela();
void cores();
void exibirRegras();
void exibirOpcao(int &escolha);
void inserirNome(string &nome);
void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO], int &contadorPecas);
void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO]);
void jogadaOrigem(int &linhaOrigem,int &colunaOrigem);
void jogadaDestino(int &linhaDestino,int &colunaDestino);
bool realizarJogada(int linhaOrigem,int colunaOrigem,int linhaDestino,int colunaDestino,
                    char tabuleiro[TAMANHO][TAMANHO]);
void realizarJogada(int linhaOrigem,int colunaOrigem,int linhaDestino,int colunaDestino,
                    char tabuleiro[TAMANHO][TAMANHO], int &contadorPecas);
bool verificarfimdejogo(char tabuleiro[TAMANHO][TAMANHO], int contadorPecas, string nome);
void gravarResultado(string nome,string resultado,int contadorPecas);
void consultarResultado();

int main()
{
    setlocale(LC_ALL, "");
    cores();

    char tabuleiro[TAMANHO][TAMANHO];
    string nome;
    int opcao;
    int lOrigem, lDestino, cOrigem, cDestino;
    int contadorPecas = 0;

    letreiro();

    do {
        exibirOpcao(opcao);

        switch (opcao) {

            case 1:
                inserirNome(nome);
                inicializarTabuleiro(tabuleiro, contadorPecas);
                while (true) {
                    limparTela();
                    imprimirTabuleiro(tabuleiro);
                    jogadaOrigem(lOrigem,cOrigem);
                    jogadaDestino(lDestino,cDestino);
                    if (realizarJogada(lOrigem, cOrigem, lDestino, cDestino, tabuleiro)) {
                        realizarJogada(lOrigem, cOrigem, lDestino, cDestino, tabuleiro, contadorPecas);
                        if (verificarfimdejogo(tabuleiro, contadorPecas, nome)) {
                            imprimirTabuleiro(tabuleiro);
                            cout << "\n\tDIGITE QUALQUER TECLA PARA CONTINUAR...";
                            getch();
                            limparTela();
                            break;
                        }
                    } else {
                        cout << "\tTente novamente!";
                        getch();
                    }
                }
                break;

            case 2:
                exibirRegras();
                break;

            case 3:
                limparTela();
                consultarResultado();
                getch();
                limparTela();
                break;

            case 4: limparTela();
                    cout << "Saindo do jogo...\n\n";
                    break;

            default:
                cout << "\n\tOpção inválida. Tente novamente!";
                getch();
                limparTela();
        }

    } while (opcao != 4);

    return 0;
}

void letreiro()
{
    cout << "\n";
    cout << "\t\t\tRRRRRRRRRRRRRRRRR   EEEEEEEEEEEEEEEEEEEEEE   SSSSSSSSSSSSSSS TTTTTTTTTTTTTTTTTTTTTTT         AAA                      1111111\n";
    cout << "\t\t\tR::::::::::::::::R  E::::::::::::::::::::E SS:::::::::::::::ST:::::::::::::::::::::T        A:::A                    1::::::1\n";
    cout << "\t\t\tR::::::RRRRRR:::::R E::::::::::::::::::::ES:::::SSSSSS::::::ST:::::::::::::::::::::T       A:::::A                  1:::::::1\n";
    cout << "\t\t\tRR:::::R     R:::::REE::::::EEEEEEEEE::::ES:::::S     SSSSSSST:::::TT:::::::TT:::::T      A:::::::A                 111:::::1\n";
    cout << "\t\t\t  R::::R     R:::::R  E:::::E       EEEEEES:::::S            TTTTTT  T:::::T  TTTTTT     A:::::::::A                   1::::1\n";
    cout << "\t\t\t  R::::R     R:::::R  E:::::E             S:::::S                    T:::::T            A:::::A:::::A                  1::::1\n";
    cout << "\t\t\t  R::::RRRRRR:::::R   E::::::EEEEEEEEEE    S::::SSSS                 T:::::T           A:::::A A:::::A                 1::::1\n";
    cout << "\t\t\t  R:::::::::::::RR    E:::::::::::::::E     SS::::::SSSSS            T:::::T          A:::::A   A:::::A                1::::l\n";
    cout << "\t\t\t  R::::RRRRRR:::::R   E:::::::::::::::E       SSS::::::::SS          T:::::T         A:::::A     A:::::A               1::::l\n";
    cout << "\t\t\t  R::::R     R:::::R  E::::::EEEEEEEEEE          SSSSSS::::S         T:::::T        A:::::AAAAAAAAA:::::A              1::::l\n";
    cout << "\t\t\t  R::::R     R:::::R  E:::::E                         S:::::S        T:::::T       A:::::::::::::::::::::A             1::::1\n";
    cout << "\t\t\t  R::::R     R:::::R  E:::::E       EEEEEE            S:::::S        T:::::T      A:::::AAAAAAAAAAAAA:::::A            1::::l\n";
    cout << "\t\t\tRR:::::R     R:::::REE::::::EEEEEEEE:::::ESSSSSSS     S:::::S      TT:::::::TT   A:::::A             A:::::A        111::::::111\n";
    cout << "\t\t\tR::::::R     R:::::RE::::::::::::::::::::ES::::::SSSSSS:::::S      T:::::::::T  A:::::A               A:::::A       1::::::::::1\n";
    cout << "\t\t\tR::::::R     R:::::RE::::::::::::::::::::ES:::::::::::::::SS       T:::::::::T A:::::A                 A:::::A      1::::::::::1\n";
    cout << "\t\t\tRRRRRRRR     RRRRRRREEEEEEEEEEEEEEEEEEEEEE SSSSSSSSSSSSSSS         TTTTTTTTTTTAAAAAAA                   AAAAAAA     111111111111\n";

    cout << "\n\n\t\t\t\t\t\t\t\t   ||BEM-VINDO AO JOGO RESTA UM||\n";
    cout << "\n\n\t\t\t\t\t\t\t\tDIGITE QUALQUER TECLA PARA CONTINUAR...";
    getch();
    limparTela();
}

void inserirNome(string &nome)
{
    limparTela();
    cin.ignore();
    cout << "\n\tJogador(a), insira o seu nome: ";
    getline(cin,nome);
}

void limparTela()
{
    system("cls");
}

void cores()
{
    system("color 9F"); //fundo azul e texto branco
}

void exibirOpcao(int &escolha)
{
    cout << "\n\t1-Iniciar o jogo.\n";
    cout << "\t2-Exibir as regras do jogo.\n";
    cout << "\t3-Exibir histórico de jogadas.\n";
    cout << "\t4-Sair do jogo.\n";
    cout << "\n\tDigite o número referente à opção do menu para selecionar o que deseja: ";
    cin >> escolha;
}

void exibirRegras() {
    limparTela();
    cout << "\n\t||REGRAS DO JOGO RESTA UM||\n";
    cout << "\n\t- Objetivo:\n";
    cout << "\t   O objetivo é terminar o jogo com apenas uma peça no centro do tabuleiro.\n";
    cout << "\n\t- Movimentos:\n";
    cout << "\t   Um pino pode saltar sobre um pino adjacente (horizontal ou vertical)";
    cout << "para cair em um espaço vazio logo após o pino pulado;\n";
    cout << "\t   O pino sobre o qual foi dado o salto é removido do tabuleiro;\n";
    cout << "\t   Apenas uma peça pode ser pulada por vez.\n";
    cout << "\n\t- Fim do jogo:\n";
    cout << "\t   O jogo termina quando não há mais movimentos possíveis;\n";
    cout << "\t   Se você conseguir deixar apenas uma peça no tabuleiro";
    cout << "(em seu centro), venceu o jogo.";
    getch();
    limparTela();
}

void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO], int &contadorPecas)
{
    contadorPecas = 0;

    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if ((i < 2 || i > 4) && (j < 2 || j > 4)) {
                tabuleiro[i][j] = ' ';
            } else {
                tabuleiro[i][j] = '0';
                contadorPecas++;
            }
        }
    }
    tabuleiro[3][3] = ' ';
    contadorPecas--;
}

void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO])
{
    cout << "\n\t\t\t\t\t\t\t\t    ";
    for (int i = 0; i < TAMANHO; i++) {
        cout << i << "   ";
    }
    cout << "\n\t\t\t\t\t\t\t\t  +";
    for (int i = 0; i < TAMANHO; i++) {
        cout << "---+";
    }
    cout << "\n";
    for (int i = 0; i < TAMANHO; i++) {
        cout << "\t\t\t\t\t\t\t\t" << i << " |";
        for (int j = 0; j < TAMANHO; j++) {
            cout << " " << tabuleiro[i][j] << " |";
        }
        cout << "\n\t\t\t\t\t\t\t\t  +";
        for (int j = 0; j < TAMANHO; j++) {
            cout << "---+";
        }
        cout << "\n";
    }
}

void jogadaOrigem(int &linhaOrigem, int &colunaOrigem)
{
    cout << "\n\n\tInsira a linha e coluna de origem, ex: [5 3]: ";
    cin >> linhaOrigem >> colunaOrigem;
}

void jogadaDestino(int &linhaDestino, int &colunaDestino)
{
    cout << "\n\tAgora a linha e coluna de destino: ";
    cin >> linhaDestino >> colunaDestino;
}

bool realizarJogada(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino,
                    char tabuleiro[TAMANHO][TAMANHO])
{
    if (linhaOrigem < 0 || linhaOrigem >= TAMANHO || colunaOrigem < 0 || colunaOrigem >= TAMANHO) {
        cout << "\n\tInsira uma coordenada de origem válida!\n";
        return false;
    }

    if (linhaDestino < 0 || linhaDestino >= TAMANHO || colunaDestino < 0 || colunaDestino >= TAMANHO) {
        cout << "\n\tA coordenada de destino não foi válida!\n";
        return false;
    }

     if ((linhaDestino < 2 || linhaDestino > 4) && (colunaDestino < 2 || colunaDestino > 4)) {
        cout << "\n\tEssa posição não existe!\n";
        return false;
    }

    if (tabuleiro[linhaOrigem][colunaOrigem] != '0') {
        cout << "\n\tA posição de origem não contém uma peça.\n";
        return false;
    }

    if (tabuleiro[linhaDestino][colunaDestino] != ' ') {
        cout << "\n\tA posição de destino está ocupada.\n";
        return false;
    }

    if (linhaOrigem == linhaDestino) {
        if (abs(colunaOrigem - colunaDestino) != 2) {
            cout << "\n\tA jogada horizontal não foi feita com um pulo de duas casas.\n";
            return false;
        }

    } else if (colunaOrigem == colunaDestino) {
        if (abs(linhaOrigem - linhaDestino) != 2) {
            cout << "\n\tA jogada vertical não foi feita com um pulo de duas casas.\n";
            return false;
        }

    } else {
        cout << "\n\tNão é permitido movimento na diagonal.\n";
        return false;
    }

    int linhaMeio = (linhaOrigem + linhaDestino) / 2;
    int colunaMeio = (colunaOrigem + colunaDestino) / 2;
    if (tabuleiro[linhaMeio][colunaMeio] != '0') {
        cout << "\n\tNão há peça no meio para ser removida.\n";
        return false;
    }

    return true;
}

void realizarJogada(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino,
                    char tabuleiro[TAMANHO][TAMANHO], int &contadorPecas)
{
    tabuleiro[linhaOrigem][colunaOrigem] = ' ';
    tabuleiro[linhaDestino][colunaDestino] = '0';

    int linhaMeio = (linhaOrigem + linhaDestino) / 2;
    int colunaMeio = (colunaOrigem + colunaDestino) / 2;
    tabuleiro[linhaMeio][colunaMeio] = ' ';

    contadorPecas--;
}

bool verificarfimdejogo(char tabuleiro[TAMANHO][TAMANHO], int contadorPecas, string nome)
{
    if (contadorPecas > 1) {
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                if (tabuleiro[i][j] == '0') {
                    if (i > 1 && tabuleiro[i - 1][j] == '0' && tabuleiro[i - 2][j] == ' ') {
                        return false;
                    }
                    if (i < TAMANHO - 2 && tabuleiro[i + 1][j] == '0' && tabuleiro[i + 2][j] == ' ') {
                        return false;
                    }
                    if (j > 1 && tabuleiro[i][j - 1] == '0' && tabuleiro[i][j - 2] == ' ') {
                        return false;
                    }
                    if (j < TAMANHO - 2 && tabuleiro[i][j + 1] == '0' && tabuleiro[i][j + 2] == ' ') {
                        return false;
                    }
                }
            }
        }
        limparTela();
        cout << "\n\tFim de jogo! Não há mais movimentos possíveis.";
        cout << "\n\t" << nome << "\tfinalizou o jogo com " << contadorPecas << " peças.";

        gravarResultado(nome,"Perdeu",contadorPecas);
        return true;
    }
    else if (contadorPecas == 1) {
        if (tabuleiro[3][3] == '0') {
            limparTela();
            cout << "\n\tParabéns, " << nome << ", você venceu o jogo! \n\tA peça restante está no centro.";
            gravarResultado(nome,"Venceu",contadorPecas);

        } else {
            limparTela();
            cout << "\n\t" << nome << ", você deixou apenas uma peça, \n\tmas ela não está no centro. Tente novamente!";

            gravarResultado(nome,"Perdeu (peça restante não estava no centro)",contadorPecas);
        }
        return true;
    }
    return false;
}

void gravarResultado(string nome,string resultado,int contadorPecas)
{
    ofstream arquivo;
    arquivo.open("resultado.txt",ios::out|ios::app);

    if(arquivo.is_open()){
        arquivo << "\t\tJogador(a): " << nome << "\n";
        arquivo << "\t\tResultado: " << resultado << "\n";
        arquivo << "\t\tPeças restantes: " << contadorPecas << "\n\n";
    }else{
        cout << "Erro ao abrir o arquivo";
    }
    arquivo.close();
}

void consultarResultado()
{
    ifstream arquivo;
    string linha;
    arquivo.open("resultado.txt",ios::in);

    if(!arquivo){
        cout << "Erro ao ler o resultado ou não há resultados salvos no momento.";
        return;
    }
    cout << "\t\t\t\t\t\t\t\t\t--------------------\n";
    cout << "\t\t\t\t\t\t\t\t\tHISTÓRICO DE JOGADAS\n";
    cout << "\t\t\t\t\t\t\t\t\t--------------------\n";
    while(getline(arquivo,linha)){
        cout << linha << "\n";
    }
    arquivo.close();
}
