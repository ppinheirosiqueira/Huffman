#include "tree.hpp"
#include "fila.hpp"

bool mySortFunction (Tree* i, Tree* j) { return ((*i).reg.RP > (*j).reg.RP); } // Para ordenar de forma decrescente a lista

Tree* CreateTree(){
	return nullptr;
}

bool TVazia(Tree **t){
  return *t == nullptr;
}

void insertTree(Tree **t, Record r){
  if(TVazia(t)){
    *t = new(Tree);
    (*t)->esq = nullptr; 
    (*t)->dir = nullptr; 
    (*t)->reg = r; 
  
  } else {
    
    if(r.key < (*t)->reg.key){
      insertTree(&(*t)->esq, r);
    }
    
    if(r.key > (*t)->reg.key){
      insertTree(&(*t)->dir, r);
    }
  
  }

}

void pesquisa(Tree **t, Tree **aux, Record r){

  if(*t == nullptr){
    cout << "[ERROR]: Node not found!" << endl;
    return;
  }

  if((*t)->reg.key > r.key){ pesquisa(&(*t)->esq, aux, r); return;}
  if((*t)->reg.key < r.key){ pesquisa(&(*t)->dir, aux, r); return;}

  *aux = *t;
}


int isInTree(Tree *t, Record r) {
  
  if(t == NULL){ 
    return 0;
  }
  
  return t->reg.key == r.key || isInTree(t->esq, r) || isInTree(t->dir, r);
}


void antecessor(Tree **t, Tree *aux){ 

	if ((*t)->dir != nullptr){ 
		antecessor(&(*t)->dir, aux);
		return;
  }
  	
  aux->reg = (*t)->reg;
  aux = *t; 
  *t = (*t)->esq;
  free(aux);
} 


void removeTree(Tree **t, Record r){
	Tree *aux;
  	
  	if (*t == nullptr){ 
  		cout << "[ERROR]: Record not found!!!\n";
    	return;
  	}

  	if (r.key < (*t)->reg.key){ removeTree(&(*t)->esq, r); return; }
  	if (r.key > (*t)->reg.key){ removeTree(&(*t)->dir, r); return; }

  	if ((*t)->dir == nullptr){ 
  		aux = *t;  
  		*t = (*t)->esq;
    	free(aux);
    	return;
  	}

  	if ((*t)->esq != nullptr){ antecessor(&(*t)->esq, *t); return; }

  	aux = *t;  
  	*t = (*t)->dir;
  	free(aux);
}

void widthPath(Tree *t){
  Fila q;
  Item no, filho;
  
  FFVazia(&q);
  no.p = t;
  Enfileira(&q, no);

  while (!isVazia(&q)){
    Desenfileira(&q, &no);
    cout << "RP: " << no.p->reg.RP << "\n";
    cout << "Huffman: " << no.p->reg.HuffmanCode << "\n";

    if(no.p->esq != nullptr){
      filho.p = no.p->esq;
      Enfileira(&q, filho);
    }

    if(no.p->dir != nullptr){
      filho.p = no.p->dir;
      Enfileira(&q, filho);
    }

  }
}

unordered_map<string,string> HuffmanPath(Tree *t){
  Fila q;
  Item no, filho;
	unordered_map<string,string> HWH;
  
  FFVazia(&q);
  no.p = t;
  Enfileira(&q, no);

  while (!isVazia(&q)){
    Desenfileira(&q, &no);
		HWH.insert(pair<string,string>(no.p->reg.key,no.p->reg.HuffmanCode));

    if(no.p->esq != nullptr){
      filho.p = no.p->esq;
      no.p->esq->reg.HuffmanCode = no.p->reg.HuffmanCode + "0";
      Enfileira(&q, filho);
    }

    if(no.p->dir != nullptr){
      filho.p = no.p->dir;
      no.p->dir->reg.HuffmanCode = no.p->reg.HuffmanCode + "1";
      Enfileira(&q, filho);
    }

  }

  return HWH;
}

void CreateHuffman(vector<Tree*> *VW){
	while((*VW).size()>1){
		Tree *AuxFolha = CreateTree();
		Tree *AuxEsquerdo = CreateTree(); 
		Tree *AuxDireito = CreateTree();

		// Recolhendo os dados dos nós menores
		insertTree(&AuxEsquerdo,(*(*VW)[(*VW).size()-1]).reg);
		AuxEsquerdo->esq = (*(*VW)[(*VW).size()-1]).esq; 
		AuxEsquerdo->dir = (*(*VW)[(*VW).size()-1]).dir;
		insertTree(&AuxDireito,(*(*VW)[(*VW).size()-2]).reg);
		AuxDireito->esq = (*(*VW)[(*VW).size()-2]).esq; 
		AuxDireito->dir = (*(*VW)[(*VW).size()-2]).dir;

		// Criando o novo nó
		Record AuxReg;
		AuxReg.RP = AuxEsquerdo->reg.RP + AuxDireito->reg.RP;
		insertTree(&AuxFolha,AuxReg);
		// O novo nó precisa apontar para seus filhos
		AuxFolha->esq = AuxEsquerdo; 
		AuxFolha->dir = AuxDireito;

		// Retirando os dois nós menores
		(*VW).pop_back();
		(*VW).pop_back();

		// Adicionando o novo nó
		(*VW).push_back(AuxFolha);

		// Ordenando o vetor
		sort((*VW).begin(), (*VW).end(), mySortFunction);
	}
}

void NormalizandoRP(vector<Tree*> *VW){


	int Max = (*(*VW)[0]).reg.RP;	
	int Min = (*(*VW)[(*VW).size()-1]).reg.RP;
	int Dif = Max - Min;
	for (int i = 0; i < int((*VW).size()); i++){
		(*(*VW)[i]).reg.RP = (*(*VW)[i]).reg.RP/Dif;
	}
}

vector<Tree*> CreateVW(unordered_map<string,int> HW){
  vector<Tree*> VW; // Vector Word

	for ( auto local_it = HW.begin(); local_it != HW.end(); ++local_it ){
		Tree *AuxFolha = CreateTree();
		Record AuxReg;
		AuxReg.key = local_it->first;
		AuxReg.RP = local_it->second;
		insertTree(&AuxFolha,AuxReg);
		VW.push_back(AuxFolha);
	}

  sort(VW.begin(), VW.end(), mySortFunction);

  return VW;
}