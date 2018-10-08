#pragma once
#include "Nodo.h"
#include <iostream>


template <class T>
class Lista {

public:


	// construtor
	Lista<T>::Lista() {
		primeiro = NULL;
		ultimo = NULL;
		pos = NULL;
		tam = 0;
		cont = 0;

	}

	// destrutor
	Lista<T>::~Lista() {
	}


	// limpar a lista
	void Lista<T>::clear() {
		primeiro = NULL;
		ultimo = NULL;
		tam = 0;
	}

	// adiciona no inicio
	void Lista<T>::push_front(const T &dado1) {
		Nodo<T> *addIni = new Nodo<T>;
		addIni->dado = dado1; // atribui o dado

							  // se a lista estiver vazia
		if (tam == 0) {
			addIni->proximo = NULL;
			addIni->anterior = NULL;
			primeiro = addIni;
			ultimo = addIni;
			pos = primeiro;
		}

		// inserir na frente da lista
		else {
			addIni->anterior = NULL; // anterior do primeiro é vazio
			primeiro->anterior = addIni; // o anterior do antigo "primeiro" é o novo adicionado
			addIni->proximo = primeiro; // o próximo do adicionado é o antigo primeiro
			primeiro = addIni; // o primeiro agora é o adicionado na frente
		}

		// aumenta o contador do tamanho da lista
		tam++;
	}

	// adiciona no final
	void Lista<T>::push_back(const T &dado1) {
		Nodo<T> *addFim = new Nodo<T>;
		addFim->dado = dado1;

		// se a lista estiver vazia
		if (tam == 0) {
			addFim->anterior = NULL;
			addFim->proximo = NULL;
			primeiro = addFim;
			ultimo = addFim;
			pos = primeiro;
		}

		// inserir no fim da lista
		else {
			addFim->proximo = NULL; // o próximo do último é vazio
			ultimo->proximo = addFim; // o próximo do antigo último é o novo adicionado
			addFim->anterior = ultimo; // o anterior do novo é o antigo último
			ultimo = addFim; // agora o último é o novo
		}

		// aumenta tamanho da lista
		tam++;
	}


	// imprimir
	void Lista<T>::imprime_lista() {
		imprimir(primeiro);

	}

	// imprimir recursivo
	void Lista<T>::imprimir(Nodo<T> *nodo) { // mandar o primeiro como parâmetro
		if (nodo != NULL) {
			cout << nodo->dado << endl;
			imprimir(nodo->proximo);
		}

	}


	// remover o item da posição atual (pos)
	void Lista<T>::remover_item() {

		// só um item na lista
		if (pos->anterior == NULL && pos->proximo == NULL) {
			pos = NULL;
			primeiro = NULL;
			ultimo = NULL;
			tam--;
		}

		// incio da lista
		else if (pos->anterior == NULL) {
			pos->proximo->anterior = NULL;
			pos = pos->proximo;
			primeiro = pos;
			tam--;
		}

		// fim da lista
		else if (pos->proximo == NULL) {
			pos->anterior->proximo = NULL;
			pos = pos->anterior;
			ultimo = pos;
			tam--;
		}

		// meio da lista
		else {
			pos->anterior->proximo = pos->proximo;
			pos->proximo->anterior = pos->anterior;
			pos = pos->proximo;
			tam--;

		}

	}


	// selecionar o proximo da lista
	void Lista<T>::andar_frente() {
		if (pos->proximo != NULL)
			pos = pos->proximo; // a posição atual recebe a próxima posição se não for o último da lista
		else {
			// se for o último, aponta de volta para o primeiro
			pos = primeiro;
		}

	}

	// selecionar o item anterior da lista
	void Lista<T>::andar_tras() {
		if (pos->anterior != NULL)
			pos = pos->anterior;
		else {
			pos = ultimo;
		}
	}


	// busca recursiva
	int Lista<T>::buscar_r(const T &dado1, Nodo<T> *nodo) {
		if (cont == tam) {
			return 0;
		}

		if (nodo != NULL && cont != tam) {
			cont++; // aumenta o contador de ciclos de busca

			pos = nodo; // seleciona o nodo do parâmetro
			if (nodo->dado == dado1) {
				cont = 0; // zera contador para próximas buscas
				return 1;
			}
			else {
				return buscar_r(dado1, nodo->proximo); // vai selecionar o próximo nodo
			}
		}
	}

	// buscar e deletar
	void Lista<T>::remover(const T dado) {
		if (buscar_r(dado, primeiro) == 1) {

			remover_item();

			pos = primeiro;

		}
		else {

			pos = primeiro;

		}
	}


	// trocar dado
	void Lista<T>::trocar(Nodo<T> *x, Nodo<T> *y) {
		T temp = x->dado;
		x->dado = y->dado;
		y->dado = temp;
	}

	// nodo do final
	struct Nodo<T> *nodoFinal(Nodo<T> *nodo) {
		while (nodo && nodo->proximo) {
			nodo = nodo->proximo;
		}
		return nodo;
	}

	// nodos primeiro e último como referência
	Nodo<T> *dividir(Nodo<T> *a, Nodo<T> *b) {
		T x = b->dado;

		Nodo<T> *i = a->anterior;

		for (Nodo<T> *j = a; j != b; j = j->proximo) {
			if (j->dado <= x) {
				if (i == NULL) {
					i = a;
				}
				else {
					i = i->proximo;
				}

				trocar(i, j);
			}
		}

		if (i == NULL) {
			i = a;
		}
		else {
			i = i->proximo;
		}

		trocar(i, b);
		return i;
	}

	// organizar recursivamente
	void sort_asc(Nodo<T> *a, Nodo<T> *b) {
		if (b != NULL && a != b && a != b->proximo) {
			Nodo<T> *p = dividir(a, b);
			sort_asc(a, p->anterior);
			sort_asc(p->proximo, b);
		}
	}

	// chamar a organização
	void organizar() {
		Nodo<T> *n = nodoFinal(primeiro);
		sort_asc(primeiro, n);
	}

	// selecionar item específico
	void Lista<T>::selecionar(const T dado) {
		buscar_r(dado, primeiro);

	}

	// retornar dado
	T Lista<T>::retornar() {

		return pos->dado;
	}

	int Lista<T>::size() {
		return tam;
	}
	// selecionar o primeiro
	void Lista<T>::resetPos() {
		pos = primeiro;
	}


private:
	Nodo<T> *primeiro; // ponteiro que sempre aponta para o primeiro item da lista
	Nodo<T> *ultimo; // ponteiro que sempre aponta para o ultimo item da lista
	Nodo<T> *pos; // ponteiro da posição atual que estou percorrendo na lista (sempre posiciono no inicio da lista)
	Nodo<T> *temp; // ponteiro temporário
	int tam, cont; // tamanho da lista e contador de busca


};
