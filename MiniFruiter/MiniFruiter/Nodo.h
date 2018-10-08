#pragma once
template <class T>
struct Nodo {

	T dado;
	int prior = 0;
	struct Nodo<T> *proximo;
	struct Nodo<T> *anterior;

};
