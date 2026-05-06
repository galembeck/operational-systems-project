# Mapa do Código - Toytrace

### 1. Onde o programa começa?

O programa, assim como a grande maioria dos projetos e código em .C, começa no arquivo **`src/main.c`**, especificamente na função **`int main(int argc, char **argv)`**, ou seja, quando o programa roda, inicialmente, a primeira função que é executada é justamente essa, a "main".

### 2. Onde o processo alvo é criado?

O processo alvo é criado dentro do arquivo **`src/trace_runtime.c`**, dentro da função **`static pid_t launch_tracee(char *const argv[])`**.

Essa função, por sua vez, é responsável por iniciar o ciclo de vida do programa, o qual será monitorado.

### 3. Onde o runtime chama o callback?

O runtime chama o callback dentro do código do arquivo **`src/trace_runtime.c`**, na qual o runtime chama o callback (a função **`observer`**) dentro do loop principal da função **`trace_program`**.

### 4. Quais arquivos o grupo deve modificar?

O grupo deverá modificar, principalmente e de forma geral, os arquivos localizados dentro da pasta **`src/student`**, bem como no arquivo principal do runtime, conforme detalhado previamente na descrição/documento do projeto.

De forma detalhada, os arquivos que deverão ser modificados são:
- [ ] **`src/trace_runtime.c`**
- [ ] **`src/student/pairer.c`**
- [ ] **`src/student/formatter.c`**

### 5. Qual TODO aparece primeiro ao executar o scaffold?

Ao executar o scaffold (código base - sem nenhuma modificação), o primeiro erro de TODO que encontramos é:

- **`erro: TODO Semana 2: implementar launch_tracee()`**

Esse erro ocorre porque a função **``trace_program``** no arquivo **``src/trace_runtime.c``** tenta chamar **`launch_tracee`**, a qual ainda não foi implementada e contém apenas um fprintf seguido de um retorno de erro, e a execução é interrompida imediatamente.

### 6. Qual é a principal dúvida técnica do grupo neste momento?

Uma dúvida técnica do grupo neste momento é uma relacionada à de linha de comando (CLI): "Como o programa consegue distinguir o que são opções do toytrace e o que são argumentos do programa que eu quero monitorar?"

Após breve análise e pesquisa, conseguimos entender um pouco melhor essa distinção, a qual está principalmente relacionada ao uso do separador especial "--".  

A função **``find_separator``** no arquivo **``src/cli.c``** varre os argumentos para encontrar exatamente onde está esse marcador.

Tudo o que vem antes do -- (como --raw-events) é processado como configuração do rastreador. Tudo o que vem depois do -- é coletado e guardado para ser passado integralmente ao programa alvo lá no runtime.