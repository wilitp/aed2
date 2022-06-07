#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_ty key;
    value_t value;
};

static bool key_more(key_ty a, key_ty b) {
  // "No es menor o igual"
  return !(key_less(a,b) || key_eq(a, b) );
}

static key_ty key_max(key_ty k1, key_ty k2) {
  return key_more(k1, k2) ? k1 : k2;
}

static key_ty key_min(key_ty k1, key_ty k2) {
  return key_more(k1, k2) ? k1 : k2;
}

static key_ty dict_max_key(dict_t dict) {
  assert(dict != NULL);
  key_ty max;
  max = dict->key;
  if(dict->left != NULL) {
    max = key_max(max, dict_max_key(dict->left));
  }
  if(dict->right != NULL) {
    max = key_max(max, dict_max_key(dict->right));
  }
  
  return max;
}

static key_ty dict_min_key(dict_t dict) {
  assert(dict != NULL);
  key_ty min;
  min = dict->key;
  if(dict->left != NULL) {
    min = key_min(min, dict_min_key(dict->left));
  }
  if(dict->right != NULL) {
    min = key_min(min, dict_min_key(dict->right));
  }
  
  return min;
}

static bool invrep(dict_t dict) {
    return dict == NULL ||
           // El arbol a la izquierda es valido
           ((dict->left == NULL || (key_more(dict->key, dict_max_key(dict->left)) && invrep(dict->left))) &&
           // El arbol a la derecha es valido
           (dict->right == NULL || (key_less(dict->key, dict_min_key(dict->right)) && invrep(dict->right))))
           ;
}

static struct _node_t *leaf_node(key_ty key, value_t value) {
  struct _node_t *node = malloc(sizeof(struct _node_t));
  node->key = key;
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    return dict;
}

dict_t dict_add(dict_t dict, key_ty word, value_t def) {
    assert(invrep(dict));
    if(dict == NULL) {
      dict = leaf_node(key_clone(word), value_clone(def));
    }
    else if(key_less(word, dict->key)) {
      dict->left = dict_add(dict->left, word, def);
    } 
    else if(key_less(dict->key, word)){
      dict->right = dict_add(dict->right, word,def);
    } else {
      value_t tmp;
      tmp = dict->value;
      dict->value=value_clone(def);
      key_destroy(tmp);
    }

    assert(invrep(dict));
    assert(dict_exists(dict, word));
    return dict;
}

value_t dict_search(dict_t dict, key_ty word) {
    value_t def = NULL;
    while(dict != NULL && !key_eq(word, dict->key)) {
      if(key_less(word, dict->key)) {
        dict = dict->left;
      } else {
        dict = dict->right;
      }
    }
    if(dict != NULL){
      def = value_clone(dict->value);
    }
    return def;
}

bool dict_exists(dict_t dict, key_ty word) {
    bool exists = false;
    while(!exists && dict != NULL) {
      if(key_less(word, dict->key)) {
        dict = dict->left;
      } else if(!key_eq(word, dict->key)) {
        dict = dict->right;
      } else {
        exists = true;
      }
    }
    return exists;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    unsigned int length=0;
    if(dict != NULL) {
      length = 1 + dict_length(dict->left) + dict_length(dict->right);
    }
    assert(invrep(dict) && (dict == NULL || length > 0));
    return length;
}

static struct _node_t *node_destroy(struct _node_t *node) {
      if(node != NULL) {
        key_destroy(node->key);
        key_destroy(node->value);
        free(node);
        node = NULL;
      }
      return node;
}

dict_t dict_remove(dict_t dict, key_ty word) {
    assert(invrep(dict));
    struct _node_t *aux;

    // Dict vacio
    if(dict != NULL) {
      // La key a borrar es menor
      if(key_less(word, dict->key)){
        // Borrar del arbol izquierdo
        dict->left = dict_remove(dict->left, word);
      }
      // La key a borrar es mayor
      else if(key_more(word, dict->key)){
        // Borrar del arbol derecho
        dict->right = dict_remove(dict->right, word);
      } 
      // Estamos en la key a borrar, y el sub derecho es nulo
      else if(dict->right == NULL) {
        // Reemplazar por el sub izquierdo
        aux = dict;
        dict = dict->left;
        node_destroy(aux);
      }
      // Estamos en la key a borrar, y el sub izquierdo es nulo
      else if(dict->left == NULL) {
        // Reemplazar por el sub derecho
        aux = dict;
        dict = dict->right;
        node_destroy(aux);
      }
      else {
        /* Dict apunta al nodo a borrar */
        struct _node_t **refrepl; // Lugar donde esta el reemplazo

        // Busco el reemplazo,
        // elijiendo el minimo del subarbol de la derecha
        refrepl = &dict->right;
        while((*refrepl)->left != NULL) {
          refrepl = &((*refrepl)->left);
        }
        
        aux = (*refrepl)->right; // Guardo el arbol derecho de mi reemplazo
        /* Asigno los subarboles del nodo por borrar al reemplazo */
        (*refrepl)->left = (dict)->left;
        (*refrepl)->right = (dict)->right;
        node_destroy(dict); // Destruyo el nodo a borrar
        dict = *refrepl; // Ubico el reemplazo

        // Quitamos el reemplazo del lugar en el que esta
        *refrepl = aux;
      }
    }

    assert(invrep(dict));
    assert(!dict_exists(dict, word));
    return dict;
}


dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL) {
      dict_remove_all(dict->left);
      dict_remove_all(dict->right);
      key_destroy(dict->key);
      key_destroy(dict->value);
      free(dict);
      dict = NULL;
    }
    assert(dict == NULL);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    if (dict != NULL) {
        // Dump in-order
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        fprintf(file, ": ");
        key_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    return dict_remove_all(dict);
}

