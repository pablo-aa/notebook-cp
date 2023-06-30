#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update> ordered_set;

void Erase(ordered_set& a, int x){
    int r = a.order_of_key(x);
    auto it = a.find_by_order(r);
    a.erase(it);
}

/*
    order_of_key(k) // Number of items strictly smaller than k.
    find_by_order(k) // K-th element in a set (counting from zero).
*/

/* os parametros são, na ordem:
1) int -> tipo do valor que quero inserir(key), pode ser int, double, pii e etc
2) null_type -> é para usar essa árvore como set/multiset. Dá pra usar essa ED como map tmb trocando isso pra um tipo map
3) less<int> -> forma de comparação dos elementos. less<int>, less_equal<int>, greater, greater_equal e etc
4) rb_tree_tag -> tipo de árvore a ser usado, usar a rb para as operações serem O(logN)
5) tree_order_statistics_node__update -> contém várias operações para atualizar "tree-based container", usado pra manter algo como o numero de nodes em alguma subárvore

usar less<equal> em (3) para usar como set e less_equal<TIPO> para usar como multiset (permitir elementos repetidos).
se em (3) colocar greater_equal, entao o order_of_key(k) retorna a quantidade de valores maiores que k (é preferivel usar less_equal e retornar o tamanho do intervalo - order)
*/

/* Como usar
 .find_by_order(k) -> retorna um ITERADOR para o elemento na posição kth (contando do 0, ou seja, k = 0 retorna o menor)
    Usar *(find_by_order(k)) para saber QUAL É o numero na posição.

 .order_of_key(k) -> retorna o numero de valores na árvore que estão ESTRITAMENTE menores que k;
    retorna um inteiro

 Também é possivel usar as funções que o set comum possui, como o .insert().
 Dá pra percorrer os valores inseridos na árvore usando o for(auto p: tree);
 Obs.: O .erase funciona, mas precisa de um iterador para o elemento! Para isso tem a função Erase implementada.
*/