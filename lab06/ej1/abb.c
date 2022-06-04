#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool invrep(abb tree) {
    return tree == NULL ||
           // El arbol a la izquierda es valido
           ((tree->left == NULL || (tree->elem > abb_max(tree->left) && invrep(tree->left))) &&
           // El arbol a la derecha es valido
           (tree->right == NULL || (tree->elem < abb_min(tree->right) && invrep(tree->right))))
           ;
}

abb abb_empty(void) {
    return NULL;
}

static struct _s_abb *leaf_node(abb_elem e) {
  struct _s_abb *node = malloc(sizeof(struct _s_abb));
  node->elem = e;
  node->left = NULL;
  node->right = NULL;
  return node;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if(tree == NULL) {
      tree = leaf_node(e);
    }
    else if(e < tree->elem) {
      tree->left = abb_add(tree->left, e);
    } 
    else if(e > tree->elem) {
      tree->right = abb_add(tree->right, e);
    }

    assert(invrep(tree));
    assert(abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    struct _s_abb *curr = tree;
    while(!exists && curr != NULL) {
        if(e < curr->elem) {
            curr = curr->left;
        } else if(e < curr->elem) {
            curr = curr->right;
        } else {
            exists = true;
        }
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if(tree != NULL) {
      length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

static struct _s_abb *node_destroy(struct _s_abb *node) {
      if(node != NULL) {
        free(node);
        node = NULL;
      }
      return node;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    // Referencia al puntero que enlaza al nodo a borrar
    struct _s_abb **ref = NULL;
    // Referencia al puntero que enlaza al nodo que reemplazara al borrado
    struct _s_abb **refrepl;
    // Variable auxiliar para las busquedas
    struct _s_abb *curr;
    bool keepLooking = true;
    
    if(tree != NULL) {
      curr = tree;
      /* Busco el elemento a borrar y una referencia al puntero que lo enlaza */
      while(keepLooking) {
        if(e < curr->elem) {
          ref = &curr->left;
          curr = curr->left; 
        }
        else if(e > curr->elem) {
          ref = &curr->right;
          curr = curr->right; 
        } else {
          keepLooking = false;
        }
      }
      if(ref == NULL) {
        ref = &tree;
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
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    while(tree->right != NULL) {
      tree = tree->right;
    }
    max_e = tree->elem;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    while(tree->left != NULL) {
      tree = tree->left;
    }
    min_e = tree->elem;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(tree != NULL) {
      abb_destroy(tree->left);
      abb_destroy(tree->right);
      free(tree);
      tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

