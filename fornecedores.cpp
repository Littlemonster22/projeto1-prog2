#include<iostream>
#include<cstring>
#include<fstream>
#include<locale.h>
#include "gconio.h"
#include "fornecedores.h"
using namespace std;

void opcao(int &op);
void letreiro();
void menu();
void InicializarTabela(TabelaFornecedor &tabela);
void Cadastrar(TabelaFornecedor &tabela,Fornecedor &f);
void ArmazenarDados(TabelaFornecedor &tabela, Fornecedor &f);
void editarFornecedor(TabelaFornecedor &tabela);
void excluirFornecedor(TabelaFornecedor &tabela);
void mostrar(TabelaFornecedor &tabela);
void pesquisar(TabelaFornecedor &tabela);
void carregarFornecedores(TabelaFornecedor &tabela);
void salvarFornecedores(const TabelaFornecedor &tabela);
void LiberarMemoria(TabelaFornecedor &tabela);
bool verificarIdExistente(TabelaFornecedor &tabela, int codigo);
void formataContato(char contato[]);
void confirmarCadastro(Fornecedor &f, TabelaFornecedor &tabela);

int main()
{
    setlocale(LC_ALL,"portuguese");
    Fornecedor f;
    TabelaFornecedor tabela;
    int esc;

    InicializarTabela(tabela);
    carregarFornecedores(tabela);

    letreiro();

    do{
        menu();
        opcao(esc);

        switch (esc){

            case 1: Cadastrar(tabela,f);
                    confirmarCadastro(f,tabela);
                    salvarFornecedores(tabela);
                    break;

            case 2: editarFornecedor(tabela);
                    salvarFornecedores(tabela);
                    break;

            case 3: excluirFornecedor(tabela);
                    salvarFornecedores(tabela);
                    break;

            case 4: mostrar(tabela);
                    break;

            case 5: pesquisar(tabela);
                    break;

            case 0: cout << "Encerrando a sess�o...";
                    break;

            default: cout << "Op��o inv�lida. Tente novamente!" << endl;
                     getch();
                     clrscr();

        }
    }while(esc!=0);

    LiberarMemoria(tabela);

    return 0;
}

void letreiro()
{
    cout << "GEST�O DE FORNECEDORES" << endl;
    cout << "Pressione qualquer tecla para continuar...";
    getch();
    clrscr();
}

void menu()
{
    cout << "1-Cadastrar" << endl;
    cout << "2-Editar" << endl;
    cout << "3-Remover" << endl;
    cout << "4-Mostrar fornecedores cadastrados" << endl;
    cout << "5-Pesquisar fornecedor" << endl;
    cout << "0-Sair" << endl;
}

void opcao(int &op)
{
    cout << "\nEscolha a op��o desejada: ";
    cin >> op;
    clrscr();
}

void InicializarTabela(TabelaFornecedor &tabela) {
    tabela.qtd = 0;
    tabela.dados = nullptr;
}

bool verificarIdExistente(TabelaFornecedor &tabela, int codigo)
{
    for(int i = 0; i < tabela.qtd; i++){
        if(tabela.dados[i].codigo==codigo)
            return true;
    }
    return false;
}

void formataContato(char contato[])
{
    char temp[15];

    sprintf(temp, "(%c%c) %c%c%c%c%c-%c%c%c%c",
        contato[0], contato[1],
        contato[2], contato[3], contato[4], contato[5], contato[6],
        contato[7], contato[8], contato[9], contato[10]
    );

    strcpy(contato, temp);
}

void Cadastrar(TabelaFornecedor &tabela, Fornecedor &f) {

    bool codigoDiferente = false;
    bool contatoValido = false;

    do{
        cout << "Informe o c�digo do fornecedor: ";
        cin >> f.codigo;
        cin.ignore();

        if(verificarIdExistente(tabela,f.codigo)){
            cout << "O c�digo informado j� existe, informe um diferente." << endl;
            getch();
            clrscr();
        }else
            codigoDiferente = true;

    }while(!codigoDiferente);

    cout << "Informe o nome da empresa fornecedora: ";
    cin.getline(f.empresaNome, sizeof(f.empresaNome));

    cout << "Nome do respons�vel pelo fornecimento: ";
    cin.getline(f.responsavel, sizeof(f.responsavel));

    do{
        cout << "Informe o contato (apenas os n�meros juntos): ";
        cin.getline(f.contato, sizeof(f.contato));

        if(strlen(f.contato) != 11){
            cout << "O n�mero n�o cont�m 11 d�gitos, tente novamente!";
            getch();
            clrscr();
        }else{
            formataContato(f.contato);
            contatoValido = true;
        }
    }while(!contatoValido);
    clrscr();
}

void confirmarCadastro(Fornecedor &f, TabelaFornecedor &tabela) {
    char opcao;

        cout << "Confirma��o dos dados" << endl << endl;
        cout << "C�digo: " << f.codigo << endl;
        cout << "Nome da empresa: " << f.empresaNome << endl;
        cout << "Respons�vel: " << f.responsavel << endl;
        cout << "Contato: " << f.contato << endl << endl;
        cout << "O cadastro est� correto? (s/n): ";
        cin >> opcao;
        clrscr();
        cin.ignore();

        if (opcao == 's' || opcao == 'S'){ //caso base da fun��o recursiva
            cout << "Fornecedor cadastrado com sucesso!" << endl;
            getch();
            clrscr();

            ArmazenarDados(tabela, f);
        }else{
            Cadastrar(tabela,f);
            confirmarCadastro(f,tabela); //chama ela mesma
        }
}

void ArmazenarDados(TabelaFornecedor &tabela, Fornecedor &f) {
    Fornecedor *novo_dados = new Fornecedor[tabela.qtd+1];

    if(novo_dados == nullptr){
        cout << "N�o foi poss�vel cadastrar outro fornecedor." << endl;
        return;
    }

    for (int i = 0; i < tabela.qtd; i++)
        novo_dados[i] = tabela.dados[i];

    novo_dados[tabela.qtd] = f;
    delete[] tabela.dados;
    tabela.dados = novo_dados;
    tabela.qtd++;
}

void LiberarMemoria(TabelaFornecedor &tabela)
{
    delete[] tabela.dados;
    tabela.dados = nullptr;
}

void editarFornecedor(TabelaFornecedor &tabela)
{
    int codigoBusca;
    bool achou = false,contatoValido = false;
    char empresaNomeNovo[NOME1_TAM+1];
    char responsavelNomeNovo[NOME2_TAM+1];
    char novoContato[CONTATO_TAM+1];

    cout << "Informe o c�digo de identifica��o do fornecedor: ";
    cin >> codigoBusca;
    cin.ignore();
    clrscr();

    if(tabela.qtd > 0){
        for(int i=0; i<tabela.qtd; i++){
            if(codigoBusca==tabela.dados[i].codigo){

                cout << "Fornecedor " << tabela.dados[i].responsavel << " encontrado" << endl << endl;

                cout << "Caso n�o queira mudar os dados, basta clicar Enter.";
                getch();
                clrscr();

                cout << "Digite o novo nome para a empresa: ";
                cin.getline(empresaNomeNovo,NOME1_TAM);

                if(strlen(empresaNomeNovo) > 0) // caso n�o seja digitado nada, o dado � mantido
                    strcpy(tabela.dados[i].empresaNome,empresaNomeNovo);

                cout << "Novo nome para o respons�vel: ";
                cin.getline(responsavelNomeNovo,NOME2_TAM);

                if(strlen(responsavelNomeNovo) > 0)
                    strcpy(tabela.dados[i].responsavel,responsavelNomeNovo);

                do{
                    cout << "Novo contato (apenas n�meros): ";
                    cin.getline(novoContato,CONTATO_TAM);

                    if(strlen(novoContato) == 0) // mant�m o mesmo n�mero
                        contatoValido = true;
                    else{
                        if(strlen(novoContato) > 0){
                            if(strlen(novoContato) != 11){ //� pedido para digitar um novo contato
                                cout << "Contato com o formato inv�lido, tente de novo!" << endl;
                                getch();
                                clrscr();
                            }else{ //caso o contato seja ok, novo contato � salvo
                                formataContato(novoContato);
                                strcpy(tabela.dados[i].contato,novoContato);
                                contatoValido = true;
                                break;
                            }
                        }
                    }
                }while(!contatoValido);

                achou = true;
                clrscr();

                cout << "Dados atualizados com sucesso!" << endl;
                getch();
                clrscr();
                break;
            }
        }
    }else{
        cout << "Nenhum fornecedor cadastrado no sistema." << endl;
        getch();
        clrscr();
    }

    if(!achou){
        cout << "O fornecedor n�o foi localizado!" << endl;
        getch();
        clrscr();
    }
}

void excluirFornecedor(TabelaFornecedor &tabela)
{
    int codigoBusca;
    bool achou = false;

    cout << "Informe o c�digo do fornecedor a ser exclu�do: ";
    cin >> codigoBusca;
    cin.ignore();

    if(tabela.qtd > 0){
        for(int i=0; i<tabela.qtd; i++){
            if(codigoBusca==tabela.dados[i].codigo){
                for (int j = i; j < tabela.qtd - 1; j++)
                    tabela.dados[j] = tabela.dados[j + 1];

                tabela.qtd--;
                achou = true;
                cout << "Fornecedor exclu�do com sucesso!" << endl;
                getch();
                clrscr();
                break;
            }
        }
    }else{
        cout << "Nenhum fornecedor cadastrado no sistema." << endl;
        getch();
        clrscr();
    }

    if(!achou){
        cout << "O fornecedor n�o foi localizado." << endl;
        getch();
        clrscr();
    }
}

void mostrar(TabelaFornecedor &tabela)
{
    if(tabela.qtd > 0){
        cout << "Fornecedores cadastrados:" << endl << endl;
        for (int i = 0; i < tabela.qtd; i++) {
            cout << "C�digo: " << tabela.dados[i].codigo;
            cout << " | Empresa: " << tabela.dados[i].empresaNome;
            cout << " | Respons�vel: " << tabela.dados[i].responsavel;
            cout << " | Contato: " << tabela.dados[i].contato << endl;
        }
        getch();
        clrscr();

    }else{
        cout << "Nenhum fornecedor cadastrado no sistema." << endl;
        getch();
        clrscr();
    }
}

void pesquisar(TabelaFornecedor &tabela)
{
    char fornecedorPesquisa[NOME1_TAM];
    bool achou = false;

    if(tabela.qtd > 0){
        cin.ignore();
        cout << "Nome do fornecedor pesquisado: ";
        cin.getline(fornecedorPesquisa,NOME1_TAM);
        clrscr();

        cout << "Resultado da pesquisa: " << endl << endl;
        for(int i = 0; i < tabela.qtd; i++){
            if(strstr(tabela.dados[i].empresaNome,
                  fornecedorPesquisa) != 0){ /* strstr() permite que o usu�rio
									 n�o necessite digitar o nome completo*/
                cout << "C�digo: " << tabela.dados[i].codigo << endl;
                cout << "Empresa: " << tabela.dados[i].empresaNome << endl;
                cout << "Respons�vel: " << tabela.dados[i].responsavel << endl;
                cout << "Contato: " << tabela.dados[i].contato << endl << endl;

                achou = true;
            }
        }

        if(!achou)
            cout << "Fornecedor n�o encontrado." << endl;

        getch();
        clrscr();

    }else{
        cout << "Nenhum fornecedor cadastrado no sistema." << endl;
        getch();
        clrscr();
    }
}

void carregarFornecedores(TabelaFornecedor &tabela) {
    ifstream fornecedoresIn("fornecedores.dat", ios::binary);

    if (fornecedoresIn.fail()){
        tabela.qtd = 0;
        tabela.dados = nullptr;
        return;
    }

    fornecedoresIn.read((char*)&tabela.qtd,sizeof(int));
    tabela.dados = new Fornecedor[tabela.qtd];

    for(int i = 0; i < tabela.qtd; i++)
        fornecedoresIn.read((char*) &tabela.dados[i], sizeof(tabela.dados[i]));

    fornecedoresIn.close();
}

void salvarFornecedores(const TabelaFornecedor &tabela) {
    ofstream fornecedoresOut("fornecedores.dat", ios::binary);

    if (fornecedoresOut.fail()){
        cout << "Erro ao abrir o arquivo de fornecedores para escrita." << endl;
        return;
    }

    fornecedoresOut.write((char*)&tabela.qtd,sizeof(int));

    for(int i = 0; i < tabela.qtd; i++)
        fornecedoresOut.write((const char*) &tabela.dados[i], sizeof(tabela.dados[i]));

    fornecedoresOut.close();
}
