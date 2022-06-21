#include <assert.h>
#include <stdlib.h>

#include "cost.h"
#include "graph.h"
#include "mini_set.h"


cost_t *dijkstra(graph_t graph, vertex_t init) {    
    cost_t *costs = calloc(graph_max_vertexs(graph), sizeof(cost_t));
    set no_visit = set_empty();


    vertex_t c;
    for(vertex_t i=0; i< graph_max_vertexs(graph); ++i) {
        no_visit = set_add(no_visit, i);
        costs[i] = graph_get_cost(graph, init, i);
    }

    while(!set_is_empty(no_visit)) {
        // Seleccionar el nodo
        cost_t min_cost = costs[set_get(no_visit)]; // algun costo de los que no sabemos su costo minimo
        c = set_get(no_visit);
        for(vertex_t i = 0; i<graph_max_vertexs(graph); ++i) {
            if(cost_lt(costs[i], min_cost) && set_member(i, no_visit)) {
                min_cost = costs[i];
                c = i;
            }
        }

        // Actualizar el problema
        no_visit = set_elim(no_visit, c);
        for(vertex_t i=0; i < graph_max_vertexs(graph); ++i) {
            if(cost_lt(cost_sum(costs[c], graph_get_cost(graph, c, i)), costs[i]) && set_member(i, no_visit)) {
                costs[i] = cost_sum(costs[c], graph_get_cost(graph, c, i));
            }
        }
    }

    no_visit = set_destroy(no_visit);


    return costs;
}
