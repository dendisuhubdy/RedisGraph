#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"
#include "node_block.h"
#include "node_iterator.h"
#include "GraphBLAS.h"
#include "../util/triemap/triemap.h"

#define GRAPH_DEFAULT_NODE_CAP 16384    // Default number of nodes a graph can hold before resizing.
#define GRAPH_DEFAULT_RELATION_CAP 16   // Default number of different relationships a graph can hold before resizing.
#define GRAPH_DEFAULT_LABEL_CAP 16      // Default number of different labels a graph can hold before resizing.
#define GRAPH_NO_LABEL -1               // Labels are numbered [0-N], -1 represents no label.
#define GRAPH_NO_RELATION -1            // Relations are numbered [0-N], -1 represents no relation.
typedef struct {
    NodeBlock **nodes_blocks;       // Graph nodes arranged in blocks.
    size_t block_count;             // Number of node blocks.
    size_t node_cap;                // Number of nodes graph can hold.
    size_t node_count;              // Number of nodes stored.
    GrB_Matrix adjacency_matrix;    // Adjacency matrix, holds all graph connections.
    GrB_Matrix *relations;          // Relation matrices.
    size_t relation_cap;            // Number of relations graph can hold.
    size_t relation_count;          // Number of relation matrices.
    GrB_Vector *labels;             // Label vectors.
    size_t label_cap;               // Number of labels graph can hold.
    size_t label_count;             // Nunber of label vectors.
} Graph;

// Create a new graph.
Graph *Graph_New (
    size_t n    // Initial number of nodes in the graph.
);

// Creates N new nodes.
// Returns node iterator.
NodeIterator *Graph_CreateNodes (
    Graph* g,               // Graph for which nodes will be added.
    size_t n,               // Number of nodes to create.
    int* labels             // Lables Node i with label i.
);

// Connects src[i] to dest[i] with edge of type relation[i].
void Graph_ConnectNodes (
        Graph *g,                   // Graph in which connections are formed. 
        size_t n,                   // Number of src,dest pairs.
        int *connections            // Triplets (src_id, dest_id, relation).
);

// Retrieves node with given node_id from graph,
// Returns NULL if node_id wasn't found.
Node *Graph_GetNode (
    const Graph *g,
    int node_id
);

// Retrieves a node iterator which can be used to access
// every node in the graph.
NodeIterator *Graph_ScanNodes (
    const Graph *g
);

// Retrieves a label vector, incase the vector does not exists
// it is created. Vector is resized if its size doesn't match the 
// number of nodes in the graph.
GrB_Vector Graph_GetLabelVector (
    Graph *g,           // Graph from which to get adjacency matrix.
    int label           // Label described by vector.
);

// Creates a new label vector, returns id given to label.
int Graph_AddLabelVector (
    Graph *g
);

// Retrieves a typed adjacency matrix, incase the matrix does not exists
// it is created.
// Matrix is resized if its size doesn't match graph's main adjacency matrix.
GrB_Matrix Graph_GetRelationMatrix (
    const Graph *g,     // Graph from which to get adjacency matrix.
    int relation        // Relation described by matrix.
);

// Creates a new relation matrix, returns id given to relation.
int Graph_AddRelationMatrix (
    Graph *g
);

// Free graph.
void Graph_Free (
    Graph *g
);

#endif