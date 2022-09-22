#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include "tree.hpp"
using namespace std;

vector<vector<string>> LerStopWord();
unordered_map<string,int> LerArquivo(string doc_name, vector<vector<string>> stopword);
string string_treatment(string s);
bool check_if_stopword(vector<string> listaPalavras, string palavra);
void HInsert(unordered_map<string,int> *Map, string palavra);
void CompactarArquivo(string doc_name, unordered_map<string,string> HWH, vector<vector<string>> stopwords);

#endif
