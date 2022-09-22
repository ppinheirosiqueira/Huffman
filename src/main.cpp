#include "arquivo.hpp"
#include <algorithm>    // std::sort


int main(){
	
	// Lendo arquivo de StopWords
	vector<vector<string>> stopwords = LerStopWord();			
	int auxMenu = 0;
	string doc_name;
	unordered_map<string,int> HW;
	unordered_map<string,string> HWH;
	vector<Tree*> VW;

	while (auxMenu != 3){
		cout << "Escolha entre as opções abaixo: \n\n";
		cout << "1 - Compactar arquivo txt.\n";
		cout << "2 - Reler o arquivo de stopwords.\n";
		cout << "3 - Sair\n";
		cin >> auxMenu;
		cout << "\n";


		switch(auxMenu) {
			case 1:
				cout << "Escreva o nome do arquivo TXT que deseja compactar\n";
				cout << "Não precisa digitar o .txt no final\n";
				cin >> doc_name;
				cout << "\n";

				// Lendo o arquivo que será processado
  				
				HW.clear();
				HW = LerArquivo(doc_name+".txt", stopwords); // Hash Word

				if (HW.empty()){
					cout << "Arquivo inválido\n\n";
					break;
				}
				
				// Colocar no vector e Ordenar de ordem decrescente de aparição a lista de palavras

				VW.clear();
				VW = CreateVW(HW); // Vector Word
				
				// Normalizando o valor de RP

				NormalizandoRP(&VW);
				
				// Criar árvore de huffman

				CreateHuffman(&VW);
				
				// Rodar algoritmo para determinar o binário de cada palavra
				// O widthPath modificado só para isso
				// Como iria varrer a árvore para ir colocando ela em outro unordored map, vou fazer isso ao mesmo tempo que vou criando o Huffman Path
  				
				HWH.clear();
				HWH = HuffmanPath(VW[0]); // Hash Word Huffman
				
				/*
				// Para mostrar em tela as palavras e seu código Huffman
				for ( auto local_it = HWH.begin(); local_it != HWH.end(); ++local_it ){
					cout << "Palavra: " << local_it->first << " : " << local_it->second << endl;
				}
				*/

				// Criar um novo arquivo enquanto lê o anterior substituindo as palavras pelo código binário

				CompactarArquivo(doc_name, HWH, stopwords);
				cout << "Arquivo compactado para " << doc_name << ".bin\n\n";
				break;
			case 2:
				stopwords.clear();
				stopwords = LerStopWord();
				cout << "Arquivo lido\n";		
				break;
			default:
				break;
				// code block
		}
	}
}
