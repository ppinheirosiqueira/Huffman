#ifndef TREE_HPP
#define TREE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h> 
using namespace std;

typedef struct Record Record;
typedef struct Tree Tree;

struct Record{
	string key; // Palavra 
	string HuffmanCode; // Código binário dessa palavra
	float RP; // Recorrência de cada Palavra
};

struct Tree{
	Record reg;
	Tree *esq, *dir;
};

Tree* CreateTree();
bool TVazia(Tree **t);
void insertTree(Tree **t, Record r);
void pesquisa(Tree **t, Tree **aux, Record r);
int isInTree(Tree *t, Record r);

void removeTree(Tree **t, Record r);
void antecessor(Tree **t, Tree *aux);

void widthPath(Tree *t);
unordered_map<string,string> HuffmanPath(Tree *t);

vector<Tree*> CreateVW(unordered_map<string,int> HW);
void CreateHuffman(vector<Tree*> *VW);
void NormalizandoRP(vector<Tree*> *VW);

#endif
