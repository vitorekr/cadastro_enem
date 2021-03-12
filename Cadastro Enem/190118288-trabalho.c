//De acordo com as políticas de entrega de atividades repassadas pelo professor, certifico que os algoritmos e programas que estou
//entregando são de minha autoria e que não os repassei ou os recebi de qualquer outra pessoa.
//Nome: Vitor Eduardo Kühl Rodrigues;
//Matricula: 19/0118288;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define MAX_PESSOAS 100
#define MAX_ESTADO 100
#define MAX_CURSO 100

//Arquivos
FILE *arq_pessoa;
FILE *arq_estado;
FILE *arq_curso;

//Struct para cadastro de curso;
typedef struct cadastro_curso{
    char curso[50];
    int ativo_curso;
}Curso;

//Struct para cadastro de estado;
typedef struct cadastro_estado{
    char unidade_federacao[10];
    int ativo_estado;//Responsável por ativar/cadastrar um estado;
}Estado;

//Struct de cadastro de pessoas;
typedef struct cadastro{
    char nome[50], sexo[3];
    int idade, dia, mes, ano;
    int ativo;//Responsável por deixar um aluno em estado ativo(Cadastrado);
    Estado estado;
    Curso curso;
}Pessoa;

//Declarações dos tipos e váriaveis das structs;
Pessoa pessoas[MAX_PESSOAS];//Declaração do tipo Pessoa do struct cadastro
Estado estado[MAX_ESTADO];
Curso curso[MAX_CURSO];


//Declaração de procedimentos e funções;
void cadastrar_estado();
void cadastrar_curso();
void cadastrar_pessoa();
void remover_cadastro();
void listar_pessoas_estado();
void listar_pessoas_curso();
void consultar_pessoa_nome();
void relatorio_demografico();
void cadastrar_curso_auxiliar();

int main()
{
    //Declaração de variáveis na função principal;
    int opcao;

    //Menu de opções;
    while(1){
        system("cls || clear");
        menu();
        scanf("%d", &opcao);
        getchar();//buffer
        switch (opcao) {
            case 1:
                cadastrar_estado();
                break;
            case 2:
                cadastrar_curso();
                break;
            case 3:
                cadastrar_pessoa();
                break;
            case 4:
                remover_cadastro();
                break;
            case 5:
                listar_pessoas_estado();
                break;
            case 6:
                listar_pessoas_curso();
                break;
            case 7:
                consultar_pessoa_nome();
                break;
            case 8:
                relatorio_demografico();
                break;
            case 9:
                printf("Tchau!\n");
                exit(1);
            default:
                printf("Entrada invalida!\n");
        }
        getchar();
    }

    return 0;
}

void menu(){
    printf("\t\t        ---------------------------MENU---------------------------------\n");
    printf("\n\t\t        |                  1 - Cadastrar Estado                         |\n");
    printf("\t\t        |                  2 - Cadastrar curso                          |\n");
    printf("\t\t        |                  3 - Cadastrar Pessoa                         |\n");
    printf("\t\t        |                  4 - Remover Cadastro                         |\n");
    printf("\t\t        |                  5 - Listar pessoas por Estado                |\n");
    printf("\t\t        |                  6 - Listar pessoas por Curso Desejado        |\n");
    printf("\t\t        |                  7 - Consultar Pessoa por Nome                |\n");
    printf("\t\t        |                  8 - Gerar relatorio demografico              |\n");
    printf("\t\t        |                  9 - Finalizar Programa                       |\n");
    printf("\t\t        |_______________________________________________________________|\n");
}

//Procedimentos

void cadastrar_estado()
{
    //Arquivo para cadastramento de Estados;
    FILE *arq_estado;
    arq_estado = fopen("cadastro_estado.txt", "a");
    if(arq_estado == NULL){
        printf("Ocorreu um erro ao acessar o arquivo\n");
        return 1;
    }
    //Declarações de variáveis para o cadastro de um estado;
    char unidade_federacao[10];
    int op;//Opção para continuar ou sair do cadastro;
    int i;
    int cont_min; //Contador para transformar caracteres minusculos em maiusculos;
    //Cadastro da pessoa;
    do{
        arq_estado = fopen("cadastro_estado.txt", "a");
        system("cls || clear");
        printf("                          --------------------- CADASTRAR ESTADO ---------------------\n");
        printf("\nInforme o Estado a ser cadastrado:\n");
            fgets(unidade_federacao, 10, stdin);
        for(cont_min=0; cont_min<=strlen(unidade_federacao); cont_min++){ //Transformar Caracteres maiúsculos em minúsculos;
            unidade_federacao[cont_min] = toupper(unidade_federacao[cont_min]);
        }

        //Gravar e fechar arquivo;
            fprintf(arq_estado, "%s", unidade_federacao);
            fclose(arq_estado);

        //Copiar para a struct;
        for (i=0; i<MAX_ESTADO; i++){
            if(estado[i].ativo_estado==0){
                strcpy(pessoas[i].estado.unidade_federacao, unidade_federacao);
                break;
            }
        }
        //Opcão de continuar ou sair
        printf("Estado cadastrado com sucesso!\n");
        printf("1 - Cadastrar outro Estado\n");
        printf("0 - Sair\n");
        scanf("%d", &op);
        getchar();
    }while(op!=0);
}

void cadastrar_curso()
{
    //Arquivo para cadastramento de cursos;
    FILE *arq_curso;
    arq_curso = fopen("cadastro_curso.txt", "a");
    if(arq_curso == NULL){
        printf("Ocorreu um erro ao acessar o arquivo\n");
        return 1;
    }

    //Declarações de variáveis para o cadastro de um curso;
    char curso[50];
    int op;//Opção para continuar ou sair do cadastro;
    int i;
    int cont_min; //Contador para transformar letras minusculas em maiusculas;

    //Cadastro de curso;
    do{
        arq_curso = fopen("cadastro_curso.txt", "a");
        system("cls || clear");
        printf("                          --------------------- CADASTRAR CURSO ---------------------\n");
        printf("Informe o Curso a ser cadastrado:\n");
            fgets(curso, 50, stdin);
            for(cont_min=0; cont_min<=strlen(curso); cont_min++){ //Transformar Caracteres maiúsculos em minúsculos;
                curso[cont_min] = toupper(curso[cont_min]);
            }

        //Gravar e fechar arquivo;
            fprintf(arq_curso, "%s", curso);
            fclose(arq_curso);

       for (i=0; i<MAX_CURSO; i++){ //Copiar para a struct;
            if(pessoas[i].curso.ativo_curso==0){
                strcpy(pessoas[i].curso.curso, curso);
                break;
            }
        }
        //Opcão de continuar ou sair
        printf("Curso cadastrado com sucesso!\n");
        printf("1 - Continuar\n");
        printf("0 - Sair\n");
        scanf("%d", &op);
        getchar();
    }while(op!=0);

}

void cadastrar_pessoa()
{
    //Arquivo para cadastramento de pessoas;
    FILE *arq_pessoa;
    arq_pessoa = fopen("cadastro_pessoa.txt", "a");
    if(arq_pessoa == NULL){
        printf("Ocorreu um erro ao acessar o arquivo\n");
        return 1;
    }

    //Declarações de variáveis para o cadastro de uma pessoa;
    char nome[50], sexo[3], curso[50], unidade_federacao[10];
    int idade, dia, mes, ano;
    int op;//Opção para continuar ou sair do cadastro;
    int i; //Contador para copiar dados na struct;
    int cont_min; //Contador para tranformar maiusculo em minusculo;
    int cont_pessoa; //Contador para cadastrar a pessoa e passar para a struct;

    //Cadastro da pessoa;
    do{
        system("cls || clear");
        //Nome
        printf("                          --------------------- CADASTRAR PESSOA ---------------------\n");
        printf("Nome:\n");
            fgets(nome, 50, stdin);
            for(cont_min=0; cont_min<=strlen(nome); cont_min++){ //Transformar Caracteres maiúsculos em minúsculos;
                nome[cont_min] = toupper(nome[cont_min]);
            }
        fprintf(arq_pessoa, "\n%s", nome);

        //Idade
        while(1){
            printf("Idade:\n");
                scanf("%d", &idade);

            getchar();
            if(idade>0){
                fprintf(arq_pessoa, "%d\n", idade);
                break;
            }
        }


        //Sexo
        while(1){
            printf("Utilize M para masculino ou F para feminino\n");
            printf("Sexo:\n");
            //getchar();
            fgets(sexo, 3, stdin);
            if(strcmp(sexo, "M\n") == 0 || strcmp(sexo, "F\n")== 0) {
                fprintf(arq_pessoa, "%s", sexo);
                break;
            }
        }

        //Data de nascimento
        while(1){
            printf("A data de nascimento devera ser informado no tipo DIA/MES/ANO(DD/MM/AAAA)\n");
            printf("Data de nascimento:\n");
                scanf("%d/%d/%d", &dia, &mes, &ano);
                getchar();
            fprintf(arq_pessoa, "%d/%d/%d\n", dia, mes, ano);
            if(mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12){
                if(dia>0 && dia<=31){
                    printf("Sua data de nascimento e: %d/%d/%d\n", dia, mes, ano);
                    break;
                }else{
                    printf("Informe uma data de nascimento valida!\n");
                }
            }
            if(mes==4 || mes==6 || mes==9 || mes==11){
                if(dia>0 && dia<=30){
                    printf("Sua data de nascimento e: %d/%d/%d\n", dia, mes, ano);
                    break;
                }else{
                    printf("Informe uma data de nascimento valida!\n");
                }
            }
            if(mes==2){
                if(ano%4==0 && ano%100!=0){
                    if(dia>0 && dia<=29){
                        printf("Sua data de nascimento e: %d/%d/%d\n", dia, mes, ano);
                        break;
                    }else{
                        printf("Informe uma data de nascimento valida!\n");
                    }
                }
            }
            if(mes==2){
                if(ano%4!=0 && ano%400!=0){
                    if(dia>0 && dia<=28){
                        printf("Sua data de nascimento e: %d/%d/%d\n", dia, mes, ano);
                        break;
                    }else{
                        printf("Informe uma data de nascimento valida!\n");
                    }
                }
            }

            if(mes>0 && mes<=12){
                break;
                }else{
                printf("Informe um mes valido!\n");
            }
    }

        //Opcão de curso

    do{
        arq_curso = fopen("cadastro_curso.txt", "rt");
        printf("Opcao de Curso:\n");
            scanf(" %[^\n]s", curso);
            getchar();
        for(cont_min=0; cont_min<=strlen(curso); cont_min++){ //Transformar Caracteres maiúsculos em minúsculos;
            curso[cont_min] = toupper(curso[cont_min]);
        }

       if(arq_curso != NULL){

       while (!feof(arq_curso)){//Pegar dados com base no curso;
                   fscanf(arq_curso, " %[^\n]s", pessoas[1].curso.curso);
           if(strcmp(pessoas[1].curso.curso, curso) == 0){
                fprintf(arq_pessoa, "%s\n", curso);
                break;
           }
       }
       }
    }while(strstr(pessoas[1].curso.curso, curso) == NULL);
        fclose(arq_curso);


        //Unidade de Federação
        do{
        arq_estado = fopen("cadastro_estado.txt", "rt");
        printf("Unidade de Federacao:\n");
            scanf(" %[^\n]s", unidade_federacao);
            getchar();
        for(cont_min=0; cont_min<=strlen(unidade_federacao); cont_min++){ //Transformar Caracteres maiúsculos em minúsculos;
            unidade_federacao[cont_min] = toupper(unidade_federacao[cont_min]);
        }

       if(arq_estado != NULL){

       while (!feof(arq_estado)){//Pegar dados com base no curso;
                   fscanf(arq_estado, " %[^\n]s", pessoas[1].estado.unidade_federacao);
           if(strstr(pessoas[1].estado.unidade_federacao, unidade_federacao) != NULL){
                fprintf(arq_pessoa, "%s", unidade_federacao);
                break;
           }
       }
       }
    }while(strstr(pessoas[1].estado.unidade_federacao, unidade_federacao) == NULL);
            fclose(arq_estado);
        //Fechar arquivo responsável pelo cadastro de uma pessoa;
        fclose(arq_pessoa);

        //Cadastrar e mandar para a struct;
        for (i=0; i<cont_pessoa; i++){
            if(pessoas[i].ativo==0){
                strcpy(pessoas[i].nome, nome);
                pessoas[i].idade = idade;
                strcpy(pessoas[i].sexo, sexo);
                pessoas[i].dia = dia;
                pessoas[i].mes = mes;
                pessoas[i].ano = ano;
                strcpy(pessoas[i].curso.curso, curso);
                strcpy(pessoas[i].estado.unidade_federacao, unidade_federacao);
                break;
            }
        }

        //Opcão para voltar ao menu;
        printf("Cadastro realizado com sucesso!\n");
        printf("Aperte 0 para voltar ao menu\n");
        scanf("%d", &op);
    }while(op!=0);
}

void remover_cadastro()
{
    char nome[50];
    int op;
    int cont_min;

    FILE *remover; //Arquivo auxiliar para remover o cadastro de uma pessoa;

    arq_pessoa = fopen("cadastro_pessoa.txt", "rt");
    remover = fopen("remover.txt", "a+");
    do{
        system("cls || clear");
        printf("                          --------------------- EXCLUIR CADASTRO ---------------------\n");
        printf("\nNome Completo:\n");
            scanf(" %[^\n]s", nome);
        for(cont_min=0; cont_min<=strlen(nome); cont_min++){ //Transformar Caracteres maiúsculos em minúsculos;
            nome[cont_min] = toupper(nome[cont_min]);
            }

        while(!feof(arq_pessoa)){
            fscanf(arq_pessoa, " %[^\n]s", pessoas[1].nome);
            fscanf(arq_pessoa, "%d", &pessoas[1].idade);
            fscanf(arq_pessoa, "%s", pessoas[1].sexo);
            fscanf(arq_pessoa, "%d/%d/%d", &pessoas[1].dia, &pessoas[1].mes, &pessoas[1].ano);
            fscanf(arq_pessoa, "%s", pessoas[1].curso.curso);
            fscanf(arq_pessoa, "%s", pessoas[1].estado.unidade_federacao);
            if(strcmp(pessoas[1].nome, nome) != 0){
                fprintf(remover, "\n%s\n", pessoas[1].nome);
                fprintf(remover, "%d\n", pessoas[1].idade);
                fprintf(remover, "%s\n", pessoas[1].sexo);
                fprintf(remover, "%d/%d/%d\n", pessoas[1].dia, pessoas[1].mes, pessoas[1].ano);
                fprintf(remover, "%s\n", pessoas[1].curso.curso);
                fprintf(remover, "%s", pessoas[1].estado.unidade_federacao);

            }
        }

    printf("Deseja realmente excluir o cadastro?\n");
    printf("1 - SIM\n");
    printf("2 - NAO\n");
        scanf("%d", &op);
        if(op == 1){
            printf("Cadastro excluido com sucesso\n");
            getchar();
            printf("Pressione qualquer tecla para retornar ao menu\n");
        }
    }while(op != 1);
        fclose(arq_pessoa);
        fclose(remover);

        remove("cadastro_pessoa.txt"); //Remover arquivo de cadastro de pessoas;
        rename("remover.txt", "cadastro_pessoa.txt"); //Renomear arquivo auxiliar igual ao do arquivo excluido de cadastro de pessoas;

}

void listar_pessoas_estado()
{
    char estado[50];
    int i, op;
    int cont_min;

   do{
   system("cls || clear");
   printf("                          --------------------- PESQUISA POR ESTADO ---------------------\n");
   printf("\nEstado: ");
        scanf("%s", &estado);
        fflush(stdin); //Limpar buffer do teclado;
        for(cont_min=0; cont_min<=strlen(estado); cont_min++){ //Transformar Caracteres maiúsculos em minúsculos;
            estado[cont_min] = toupper(estado[cont_min]);
        }

        arq_pessoa = fopen("cadastro_pessoa.txt", "rt");


       if(arq_pessoa != NULL){
       while (!feof(arq_pessoa)){//Pegar dados com base no curso;
            fscanf(arq_pessoa, " %[^\n]s", pessoas[1].nome);
            fscanf(arq_pessoa, "%d", &pessoas[1].idade);
            fscanf(arq_pessoa, "%s", pessoas[1].sexo);
            fscanf(arq_pessoa, "%d/%d/%d", &pessoas[1].dia, &pessoas[1].mes, &pessoas[1].ano);
            fscanf(arq_pessoa, "%s", pessoas[1].curso.curso);
            fscanf(arq_pessoa, "%s", pessoas[1].estado.unidade_federacao);
           if(strstr(pessoas[1].estado.unidade_federacao, estado) != NULL){
                printf("Nome: %s\n", pessoas[1].nome);
                printf("Idade: %d\n", pessoas[1].idade);
                printf("Sexo: %s\n", pessoas[1].sexo);
                printf("Data de Nascimento: %d/%d/%d\n", pessoas[1].dia, pessoas[1].mes, pessoas[1].ano);
                printf("Opcao de Curso: %s\n", pessoas[1].curso.curso);
                printf("Unidade de Federacao: %s\n", pessoas[1].estado.unidade_federacao);
                printf("-----------------------------------------------------------------------------\n");

            }
       }
    }
   printf("Aperte 1 para realizar nova pesquisa ou 0 para voltar ao menu\n");
        scanf("%d", &op);
   }while(op!=0);

   printf("\n");
fclose(arq_pessoa);
}


void listar_pessoas_curso()
{
    char curso[50];
    int i, op;
    int cont_min;

   do{
   system("cls || clear");
   printf("                          --------------------- PESQUISA POR CURSO ---------------------\n");
   printf("\nCurso: ");
        scanf("%s", &curso);
        fflush(stdin);
        for(cont_min=0; cont_min<=strlen(curso); cont_min++){ //Transformar Caracteres maiúsculos em minúsculos;
                curso[cont_min] = toupper(curso[cont_min]);
        }

        arq_pessoa = fopen("cadastro_pessoa.txt", "rt");


       if(arq_pessoa != NULL){ //Verificar se o arquivo existe;
       while (!feof(arq_pessoa)){//Pegar dados com base no curso;
            fscanf(arq_pessoa, " %[^\n]s", pessoas[1].nome);
            fscanf(arq_pessoa, "%d", &pessoas[1].idade);
            fscanf(arq_pessoa, "%s", pessoas[1].sexo);
            fscanf(arq_pessoa, "%d/%d/%d", &pessoas[1].dia, &pessoas[1].mes, &pessoas[1].ano);
            fscanf(arq_pessoa, "%s", pessoas[1].curso.curso);
            fscanf(arq_pessoa, "%s", pessoas[1].estado.unidade_federacao);
           if(strstr(pessoas[1].curso.curso, curso) != NULL){
                printf("Nome: %s\n", pessoas[1].nome);
                printf("Idade: %d\n", pessoas[1].idade);
                printf("Sexo: %s\n", pessoas[1].sexo);
                printf("Data de Nascimento: %d/%d/%d\n", pessoas[1].dia, pessoas[1].mes, pessoas[1].ano);
                printf("Opcao de Curso: %s\n", pessoas[1].curso.curso);
                printf("Unidade de Federacao: %s\n", pessoas[1].estado.unidade_federacao);
                printf("-----------------------------------------------------------------------------\n");

            }
       }
    }
   printf("Aperte 1 para realizar nova pesquisa ou 0 para voltar ao menu\n");
        scanf("%d", &op);
   }while(op!=0);

   printf("\n");
fclose(arq_pessoa);
}

void consultar_pessoa_nome()
{
    char nome[50];
    int i, op, cont_min;

   do{
   system("cls || clear");
   printf("                          --------------------- PESQUISA POR NOME ---------------------\n");

   printf("\nNome: ");
        scanf("%s", &nome);
        fflush(stdin);
        for(cont_min=0; cont_min<=strlen(nome); cont_min++){ //Transformar caracteres maiusculos em minusculos;
                nome[cont_min] = toupper(nome[cont_min]);
        }

        arq_pessoa = fopen("cadastro_pessoa.txt", "rt");


       if(arq_pessoa != NULL){
       while (!feof(arq_pessoa)){//Pegar dados com base no curso;
            fscanf(arq_pessoa, " %[^\n]s", pessoas[1].nome);
            fscanf(arq_pessoa, "%d", &pessoas[1].idade);
            fscanf(arq_pessoa, "%s", pessoas[1].sexo);
            fscanf(arq_pessoa, "%d/%d/%d", &pessoas[1].dia, &pessoas[1].mes, &pessoas[1].ano);
            fscanf(arq_pessoa, "%s", pessoas[1].curso.curso);
            fscanf(arq_pessoa, "%s", pessoas[1].estado.unidade_federacao);
           if(strstr(pessoas[1].nome, nome) != NULL){
                printf("Nome: %s\n", pessoas[1].nome);
                printf("Idade: %d\n", pessoas[1].idade);
                printf("Sexo: %s\n", pessoas[1].sexo);
                printf("Data de Nascimento: %d/%d/%d\n", pessoas[1].dia, pessoas[1].mes, pessoas[1].ano);
                printf("Opcao de Curso: %s\n", pessoas[1].curso.curso);
                printf("Unidade de Federacao: %s\n", pessoas[1].estado.unidade_federacao);
                printf("-----------------------------------------------------------------------------\n");

            }
       }
    }
   printf("Aperte 1 para realizar nova pesquisa ou 0 para voltar ao menu\n");
        scanf("%d", &op);
   }while(op!=0);

fclose(arq_pessoa);

}

void relatorio_demografico(){
    float porcentagem_15_20, porcentagem_21_25, porcentagem_26_30, porcentagem_30, porcentagem_M, porcentagem_F;
    float cont = 0; //Contar quantas pessoas foram cadastradas;
    float cont_15_20 = 0; //Contar quantas pessoas foram cadastradas tem entre 15 e 20 anos;
    float cont_21_25 = 0; //Contar quantas pessoas foram cadastradas tem entre 21 e 25 anos;
    float cont_26_30 = 0; //Contar quantas pessoas foram cadastradas tem entre 26 e 30 anos;
    float cont_30 = 0; //Contar quantas pessoas foram cadastradas tem mais de 30 anos;
    float cont_M = 0; //Contar quantas pessoas foram cadastradas são do sexo masculino;
    float cont_F = 0; //Contar quantas pessoas foram cadastradas são do sexo feminino;
    int op;

    arq_pessoa = fopen("cadastro_pessoa.txt", "rt");

    do{
       system("cls || clear");
       printf("                          --------------------- RELATORIO DEMOGRAFICO ---------------------\n");
       if(arq_pessoa != NULL){
       while (!feof(arq_pessoa)){//Pegar dados com base no curso;
            fscanf(arq_pessoa, " %[^\n]s", pessoas[1].nome);
            fscanf(arq_pessoa, "%d", &pessoas[1].idade);
            fscanf(arq_pessoa, "%s", pessoas[1].sexo);
            fscanf(arq_pessoa, "%d/%d/%d", &pessoas[1].dia, &pessoas[1].mes, &pessoas[1].ano);
            fscanf(arq_pessoa, "%s", pessoas[1].curso.curso);
            fscanf(arq_pessoa, "%s", pessoas[1].estado.unidade_federacao);
            cont++;
            if(pessoas[1].idade>=15 && pessoas[1].idade<=20){
                cont_15_20++;
            }
            if(pessoas[1].idade>=21 && pessoas[1].idade<=25){
                cont_21_25++;
            }
            if(pessoas[1].idade>=26 && pessoas[1].idade<=30){
                cont_26_30++;
            }
            if(pessoas[1].idade>30){
                cont_30++;
            }
            if(strcmp(pessoas[1].sexo, "M") == 0){
                cont_M++;
            }
            if(strcmp(pessoas[1].sexo, "F") == 0){
                cont_F++;
            }
       }
        porcentagem_15_20 = (cont_15_20/cont)*100;
        printf("\nA porcentagem de pessoas entre 15 e 20 anos e: %.1f %%\n", porcentagem_15_20);

        porcentagem_21_25 = (cont_21_25/cont)*100;
        printf("\nA porcentagem de pessoas entre 21 e 25 anos e: %.1f %%\n", porcentagem_21_25);

        porcentagem_26_30 = (cont_26_30/cont)*100;
        printf("\nA porcentagem de pessoas entre 26 e 30 anos e: %.1f %%\n", porcentagem_26_30);

        porcentagem_30 = (cont_30/cont)*100;
        printf("\nA porcentagem de pessoas maiores de 30 anos e: %.1f %%\n", porcentagem_30);

        porcentagem_M = (cont_M/cont)*100;
        printf("\nA porcentagem de pessoas do sexo masculino e: %.1f %%\n", porcentagem_M);

        porcentagem_F = (cont_F/cont)*100;
        printf("\nA porcentagem de pessoas do sexo feminino e: %.1f %%\n", porcentagem_F);

        fclose(arq_pessoa);
       }
        printf("\n\nAperte 0 para voltar ao menu\n");
            scanf("%d", &op);
    }while(op!=0);
}
