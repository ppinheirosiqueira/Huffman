# Trabalho sobre o Código de Huffman

[![Linguagem C++](https://img.shields.io/badge/Linguagem-C%2B%2B-green.svg)](https://github.com/PedroLouback/Exercicio3-ListaAEDs)
[![requirement](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-informational)](https://code.visualstudio.com/docs/?dv=linux64_deb)
![ISO](https://img.shields.io/badge/ISO-Linux-blueviolet)

---
 
## Problema

<p align="justify">Elabore uma árvore binária que utilize o código de Huffman para comprimir arquivos. Para tanto:

1. Contabilizar a recorrência de cada palavra (RP) no arquivo; 
2. Normalizar a contabilização entre 0 e 1 utilizando a formula -> RP / (max(RP) - min(RP));
3. Montar a árvore com as regras apresentadas por Huffman; 
4. Troque as palavras pela codificação binária (utilizar booleano para representar 0 e 1); 
5. Salve o arquivo em formato binário e observe qual foi o ganho de espaço obtido.</p>

---

## Lógica

### Executar o Programa
<p align="justify">Ao executar o programa, a primeira coisa feita é a leitura do arquivo "stopwords.txt", que lerá este arquivo e salvará as palavras dele em uma estrutura que permitirá seu fácil acesso no futuro ao realizar a leitura dos arquivos que compactará. Todas as stopwords serão ignoradas na compactação.</p>

### Menu
<p align="justify">Para obedecer o enunciado foram realizados alguns passos e o aluno achou mais interessante de mantê-los como opção para o usuário que fará uso do programa. Com isso, existe um Menu que oferece as opções: </p>

1. Compactar arquivo .txt;
2. Atualizar as stopwords;
3. Sair

### Primeira Opção
<p align="justify">Ao escolher a primeira opção, ocorrerá uma sequência de etapas.</p>

1. Será requisitado o nome do arquivo txt, onde não é necessário colocar a extensão, somente o nome do arquivo;
2. A função LerArquivo é chamada;
3. É checado se essa função retornou algo, ou se o arquivo colocado era inválido;
4. A função CreateVW é chamada;
5. A função NormalizandoRP é chamada;
6. A função CreateHuffman é chamada;
7. A função HuffmanPath é chamada;
8. A função compactarArquivo é chamada;

### Segunda Opção
<p align="justify">Opção caso a pessoa decida modificar o arquivo stopwords sem precisar parar e rodar o programa de novo.</p>

### LerArquivo
<p align="justify">A função LerArquivo recebe como argumento o nome do documento que o usuário quer compactar e o vetor de stopwords realizado de forma automática sempre que o programa é inicializado. Esta função lerá palavra por palavra do documento txt e irá adicionar esta palavra em um unordered map, onde a chave é justamente a palavra e o segundo elemento é um contador que é iniciado em 1. Caso a palavra já exista no unordered map, será adicionado 1 em seu contador. Palavras que sejam stopwords serão ignoradas e por causa disso não apareceram no arquivo compactado. Assim, ao final teremos o unordered map com todas as palavras já coletadas e com seu contador completo.
</p>

### CreateVW
<p align="justify">O unordered map criado na LerArquivo é enviado para a função CreateVW. VW é a sigla para Vector Word, ou seja, esta função retornará um Vector das palavras dessa Hash, este vector já estará ordenado de forma decrescente pelo contador de cada palavra. Apesar do nome, este vector é um vector de ponteiros de nós de árvore. Esta árvore possui três elementos, que são:

* O ponteiro para o filho esquerdo;
* O ponteiro para o filho direito;
* Um Record, que é uma estrutura. Esta estrutura possui 3 elementos:
    * Uma string chamada Palavra, que será onde a Palavra será armazenada;
    * Uma string chamada Huffman, que será onde o código Huffman será armazenado;
    * Um float chamado RP, que será armazenado inicialmente o contador de cada palavra.
</p>

### NormalizandoRP
<p align="justify">Após a criação do vector, este é enviado para o NormalizandoRP, que simplesmente pegará o maior e menor valor dos contadores e irá normalizá-los com a conta mostrada na descrição do problema.
</p>

### CreateHuffman
<p align="justify">O vetor já ordenado de forma decrescente é enviado para a função CreateHuffman. Esta função irá realizar o algoritmo de Huffman, onde aproveitando que o vector está ordenado, pegará seus dois últimos valores e os colocará em um novo nó, cada um como filho esquerdo e direito a depender de qual possuir RP maior e menor. Depois disso, esses dois nós de árvores são excluidos do vector e o novo nó com seus dois filhos é adicionado. O vector é então reordenado e este processo é repetido até que o vector possua um único nó que será a raiz da árvore Huffman.
</p>

### HuffmanPath
<p align="justify">Este nó é enviado para a função HuffmanPath. Nela, é realizada uma leitura em largura na árvore. Nesta leitura, o "pai" da vez é adicionado em um unordered map, onde a chave é a palavra e o outro item é o código Huffman desta palavra. Além disso, a cada nível que será lido, é adicionado na string Huffmnan do nó filho '0' se este filho for da esquerda e '1' se este filho for da direita. Desta forma, ao terminar de realizar a leitura em largura, a árvore de Huffman já foi completamente preenchida e todos os seus valores já foram salvos no unordered map com seu código Huffman.
</p>

### compactarArquivo
<p align="justify">Este novo unordered map é enviado para a função compactarArquivo. Que simplesmente lerá o arquivo inicial novamente e ao mesmo tempo irá o "traduzir" para o código Huffman usando o unordered map criado. Colocando tudo em um arquivo de mesmo nome só que .bin, como requisitado pelo enunciado do problema.
</p>

## Resultado
-----
<p align="justify">Foram realizados duas baterias de testes. O primeiro com o arquivo stopwords contendo somente as cinco vogais. O resultado deste é possível de ser nos arquivos que possuem "_5_vogais" em seus nomes. Todos, apesar de serem "compactados", possuem uma extensão muito maior do que a inicial. Isso se deve principalmente por palavras usadas que se repetem, mas não o suficiente para terem um código binário tão pequeno que seja equivalente ao próprio tamanho da palavra. Como exemplo, colocarei alguns códigos gerados no arquivo "globalizacao":</p>

* Palavra: ao : 01011011
* Palavra: nos : 11101111
* Palavra: no : 1110000
* Palavra: processo : 11101001
* Palavra: entre : 11101101
* Palavra: às : 11101110

<p align="justify">Com exceção da palavra processo, todas as outras acabam ocupando mais espaço em sua versão "compacta". Por isso, o que se vê neste caso é que a compactação simplesmente não serviu para muita coisa. Os resultados foram:</p>

| Nome | Arquivo Original | Arquivo Compacto | Aumento (%) |
| -----| ---------------- | ---------------- | ----------- |
| teste | 176 bytes | 196 bytes| 11.36 |
| ti | 307 kB | 423 kB | 37.78 |
| ti2 | 307 kB | 423 kB| 37.78 |
| globalizacao | 300 kB | 399 kB | 33 |
| politica | 304 kB | 409 kB | 34.53 |
| filosofia | 377 kB | 562 kB | 49.07 |
| filosofia2 | 377 kB | 563 kB| 49.33 |

<p align="justify">Algo acaba ficando claro, apesar de não poder ser afirmado com toda a certeza, de que quanto maior o arquivo, maior será o aumento dele. Provavelmente porque em arquivos maiores existem mais palavras e com isso a árvore de Huffman acaba ainda maior, tornando seu código ainda mais extenso.</p>

<p align="justify">A segunda bateria de testes foi realizada com o arquivo stopwords completo para a língua portuguesa. E os resultados dessa segunda bateria estão apresentados abaixo:</p>

| Nome | Arquivo Original | Arquivo Compacto | Diminuição (%) |
| -----| ---------------- | ---------------- | ----------- |
| teste | 176 bytes | 106 bytes| 40 |
| ti | 307 kB | 286 kB | 6.84 |
| ti2 | 307 kB | 286 kB| 6.84 |
| globalizacao | 300 kB | 275 kB | 8.33 |
| politica | 304 kB | 279 kB | 8.22 |
| filosofia | 377 kB | 402 kB | -6.63 |
| filosofia2 | 377 kB | 402 kB| -6.63 |

<p align="justify">Mesmo com todas as stopwords, os arquivos de Filosofia ainda possuiram um aumento. Claramente existem palavras, itens, ou outras coisas, que possuem um tamanho infimo em seus arquivos e que possuem um código Huffman bem extenso.</p>

<p align="justify">Independente disso, é perceptível que o código de Huffman por si só não é adequado para compactar o arquivo por completo. Várias palavras foram simplesmente desprezadas para que o arquivo fosse minimamente compactado e seu retorno a partir do .bin gerado no momento é impossível.</p>

---

## Compilação e Execução

<p align="justify">O exercício disponibilizado possui um arquivo Makefile cedido pelo professor que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:</p>


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

<p align="justify">É recomendado fazer um <code>make clean</code> antes de um <code>make</code>.</p>