#include "arquivo.hpp"

vector<vector<string>> LerStopWord(){

	string myText, auxWord;
	ifstream StopFile;
	int textLen;
	vector<vector<string>> auxVector;

	// Open the file
	StopFile.open("stopwords.txt");

	while (getline(StopFile, myText)){
		textLen = myText.length();
		while (textLen > int(auxVector.size())){
			vector<string> auxSize;
			auxVector.push_back(auxSize);
		}
		auxWord = myText.substr(0, textLen);
		auxVector[textLen - 1].push_back(auxWord);
	}

	// Close the file
	StopFile.close();

	return auxVector;
}

unordered_map<string, int> LerArquivo(string doc_name, vector<vector<string>> stopwords){
	unordered_map<string, int> HW;
	ifstream myfile;
	string palavra, linha, delimiter = " ";
	size_t pos = 0;

	// Abrir Arquivo
	doc_name = doc_name;
	myfile.open(doc_name);

	if (myfile.is_open()){
		while (!myfile.eof()){
			getline(myfile, linha); // Pegando a linha
			while ((pos = linha.find(delimiter)) != std::string::npos){
				palavra = (linha.substr(0, pos));		// Palavra auxiliar pega do começo da linha até o primeiro delimitador
				linha.erase(0, pos + delimiter.size()); // Apago a linha até o delimitador para o próximo ciclo
				palavra = string_treatment(palavra);
				if(palavra.size()>0 && !palavra.empty()){
					if (palavra.size() <= stopwords.size()){
						if (!check_if_stopword(stopwords[palavra.size() - 1], palavra)){
							HInsert(&HW, palavra);
						}
					}
					else{
						HInsert(&HW, palavra);
					}
				}
			}
		}
	}

	myfile.close();
	return HW;
}

bool check_if_stopword(vector<string> listaPalavras, string palavra){

	for (int i = 0; i <= int(listaPalavras.size()); i++){
		if (listaPalavras[i] == palavra) return true;
	}
	return false;
}

string string_treatment(string s){
	int size = s.size();
	string aux;

	for (int i = 0; i < size; i++){
		if (s[i] != '.' && s[i] != ',' && s[i] != ':' && s[i] != ';' && s[i] != '?' && s[i] != '!' && s[i] != '(' && s[i] != ')' && s[i] != '[' && s[i] != ']' && s[i] != '{' && s[i] != '}' && s[i] != '+' && s[i] != '=' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '%' && !isdigit(s[i])){
			s[i] = tolower(s[i]);
			aux += s[i];
		}
	}

	return aux;
}

void HInsert(unordered_map<string, int> *Map, string palavra){
	unordered_map<string, int>::const_iterator got = (*Map).find(palavra);

	if (got == (*Map).end())(*Map).insert(pair<string, int>(palavra, 1));
	else (*Map).at(palavra)++;
}

void CompactarArquivo(string doc_name, unordered_map<string, string> HWH, vector<vector<string>> stopwords){
	ifstream ReadFile;
	string linha, palavra, delimiter = " ";
	size_t pos = 0;
	char aux_delimiter[2] = " ";
	char aux_line[2] = "\n";

	// Abrir Arquivo
	string doc_aux = doc_name + ".txt";
	ReadFile.open(doc_aux);
	// Criar Arquivo compactado
	string doc_comp = doc_name + ".bin";
  	ofstream CreateFile(doc_comp, ios::binary);

	if (ReadFile.is_open()){
		while (!ReadFile.eof()){
			getline(ReadFile, linha); // Pegando a linha
			while ((pos = linha.find(delimiter)) != std::string::npos){
				palavra = (linha.substr(0, pos));		// Palavra auxiliar pega do começo da linha até o primeiro delimitador
				linha.erase(0, pos + delimiter.size()); // Apago a linha até o delimitador para o próximo ciclo
				palavra = string_treatment(palavra);
				
				if(palavra.size()>0 && !palavra.empty()){
					if (palavra.size() <= stopwords.size()){
						if (!check_if_stopword(stopwords[palavra.size() - 1], palavra)){
							char* aux_bin = new char[HWH.at(palavra).length() + 1];
							strcpy(aux_bin, HWH.at(palavra).c_str()); 
							CreateFile.write(aux_bin, HWH.at(palavra).length() + 1);
							CreateFile.write(aux_delimiter, 2);
						}
					}
					else{
						char* aux_bin = new char[HWH.at(palavra).length() + 1];
						strcpy(aux_bin, HWH.at(palavra).c_str()); 
						CreateFile.write(aux_bin, HWH.at(palavra).length() + 1);
						CreateFile.write(aux_delimiter, 2);	
					}
				}
			}
			CreateFile.write(aux_line, 2);
		}
	}
	else{
		cout << "Arquivo Inválido\n";
	}
	ReadFile.close();
	CreateFile.close();
}