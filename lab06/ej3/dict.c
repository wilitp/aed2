#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "string.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_ty key;
    value_t value;
};

static bool invrep(dict_t d) {
    return d == NULL ||
           // El elemento a la izquierda es valido
           ((d->left == NULL || string_less(d->left->key, d->key)) &&
           // El elemento a la derecha es valido
           (d->right == NULL || string_less(d->key, d->right->key) || string_eq(d->key, d->right->key) ) &&
           // El arbol de la izquierda es valido
           invrep(d->left) &&
           // El arbol de la derecha es valido
           invrep(d->right))
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
      dict = leaf_node(string_clone(word), string_clone(def));
    }
    else if(string_less(word, dict->key)) {
      dict->left = dict_add(dict->left, word, def);
    } 
    else if(string_less(dict->key, word)){
      dict->right = dict_add(dict->right, word,def);
    } else {
      string tmp;
      tmp = dict->value;
      dict->value=string_clone(def);
      string_destroy(tmp);
    }

    assert(invrep(dict));
    assert(dict_exists(dict, word));
    return dict;
}

value_t dict_search(dict_t dict, key_ty word) {
    value_t def = NULL;
    while(dict != NULL && !string_eq(word, dict->key)) {
      if(string_less(word, dict->key)) {
        dict = dict->left;
      } else {
        dict = dict->right;
      }
    }
    if(dict != NULL){
      def = string_clone(dict->value);
    }
    return def;
}

bool dict_exists(dict_t dict, key_ty word) {
    bool exists = false;
    while(!exists && dict != NULL) {
      if(string_less(word, dict->key)) {
        dict = dict->left;
      } else if(!string_eq(word, dict->key)) {
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
        string_destroy(node->key);
        string_destroy(node->value);
        free(node);
        node = NULL;
      }
      return node;
}

// TODO: Hacer esto mas lindo usando recursion para buscar el nodo a borrar
dict_t dict_remove(dict_t dict, key_ty word) {
    assert(invrep(dict));
    // Referencia al puntero que enlaza al nodo a borrar
    struct _node_t **ref = NULL;
    // Referencia al puntero que enlaza al nodo que reemplazara al borrado
    struct _node_t **refrepl;
    // Variable auxiliar para las busquedas
    struct _node_t *curr;
    bool keepLooking = true;
    
    if(dict != NULL) {
      curr = dict;
      /* Busco el elemento a borrar y una referencia al puntero que lo enlaza */
      while(keepLooking) {
        if(string_less(word, curr->key)) {
          ref = &curr->left;
          curr = curr->left; 
        } 
        else if(!string_eq(word, curr->key)) {
          ref = &curr->right;
          curr = curr->right; 
        } else {
          keepLooking = false;
        }
      }
      if(ref == NULL) {
        ref = &dict;
      }

      /* PRE: 
       * curr = elemento a borrar && 
       * ref  = referencia al puntero que apunta al lugar del elemento borrado
       */

      /* Busco el minimo nodo del arbol de la derecha */
      refrepl = &curr->right;
      curr = curr->right;
      if(curr != NULL) {

        while(curr->left != NULL) {
          refrepl = &curr->left;
          curr = curr->left;
        }
        // Quitamos el reemplazo del lugar en el que esta
        *refrepl = curr->right;
      }
      /* PRE
       * curr = minimo nodo del arbol de la derecha 
       * */
      
      /* Ubico el reemplazo en el lugar del nodo borrado
       * y libero la memoria del nodo a borrar usando la ref 
       */
      if(curr != NULL) {
        curr->left = (*ref)->left;
        curr->right = (*ref)->right;
      } 
      else {
        /* Si el right es nulo, entonces solo tenemos que poner el 
         * izquierdo en el lugar del borrado.
         * */
        curr = (*ref)->left;
      }
      node_destroy(*ref);
      *ref = curr;
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}


dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL) {
      dict_remove_all(dict->left);
      dict_remove_all(dict->right);
      string_destroy(dict->key);
      string_destroy(dict->value);
      free(dict);
      dict = NULL;
    }
    assert(dict == NULL);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    if (dict != NULL) {
        dict_dump(dict->left, file);
        fprintf(file, "%s: %s\n", string_ref(dict->key), string_ref(dict->value));
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    return dict_remove_all(dict);
}

