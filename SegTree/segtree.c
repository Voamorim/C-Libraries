#include "segtree.h"

SegTree* segtreeCreate(uint capacity, uint node_size, void* identity, void (*merge)(void*, const void*, const void*), void (*update)(void*, const void*)){
    SegTree *segtree = (SegTree*) malloc (sizeof(SegTree));

    segtree->tree = (void*) malloc (4 * node_size * capacity);
    segtree->node_size = node_size;
    
    segtree->identity = (void*) malloc (node_size);
    memcpy(segtree->identity, identity, node_size);
   
    for(uint i = 0; i < capacity * 4; ++i){
        char* pos = (char*) segtree->tree + (i * node_size);
        memcpy(pos, identity, node_size);
    }

    segtree->merge = merge;
    segtree->update = update;

    return segtree;
}

void segtreeBuild(SegTree* segtree, void* items, uint tl, uint tr, uint node){
    if(!segtree || !segtree->tree){
        perror("[segtree.c][segtreeBuild()] ERROR: Invalid argument. SegTree object or SegTree's tree can't be NULL.\n");
        return;
    }

    if(tl == tr){
        char* dest = (char*) segtree->tree + (node * segtree->node_size);
        char* src = (char*) items + (tl * segtree->node_size);
        memcpy(dest, src, segtree->node_size);
        return;
    }

    uint tmid = (tl + tr) / 2;
    uint lchild = node * 2, rchild = node * 2 + 1;

    segtreeBuild(segtree, items, tl, tmid, lchild);
    segtreeBuild(segtree, items, tmid + 1, tr, rchild);

    char* dest = (char*) segtree->tree + (node * segtree->node_size);
    char* lval = (char*) segtree->tree + (lchild * segtree->node_size);
    char* rval = (char*) segtree->tree + (rchild * segtree->node_size);
   
    segtree->merge(dest, lval, rval);
}

void segtreeUpdate(SegTree* segtree, uint l, uint r, void* value, uint tl, uint tr, uint node){
    if(!segtree || !segtree->tree){
        perror("[segtree.c][segtreeUpdate()] WARNING: Invalid argument. SegTree object or SegTree's tree can't be NULL.\n");
        return;
    }

    if(l > tr || r < tl) return;

    if(tl == tr){
        char *self = (char*) segtree->tree + (node * segtree->node_size);
        segtree->update(self, value);
        return;
    }

    uint tmid = (tl + tr) / 2;
    uint lchild = node * 2, rchild = node * 2 + 1;

    segtreeUpdate(segtree, l, r, value, tl, tmid, lchild);
    segtreeUpdate(segtree, l, r, value, tmid + 1, tr, rchild);

    char* dest = (char*) segtree->tree + (node * segtree->node_size);
    char* lval = (char*) segtree->tree + (lchild * segtree->node_size);
    char* rval = (char*) segtree->tree + (rchild * segtree->node_size);
   
    segtree->merge(dest, lval, rval);
}

void segtreeQuery(const SegTree* segtree, void* output_result, uint l, uint r, uint tl, uint tr, uint node){
    if(!segtree || !segtree->tree){
        perror("[segtree.c][segtreeQuery()] ERROR: Invalid argument. SegTree object or SegTree's tree can't be NULL.\n");
        memcpy(output_result, segtree->identity, segtree->node_size);
        return; 
    }

    if(l > tr || r < tl){
        memcpy(output_result, segtree->identity, segtree->node_size);
        return;
    } 

    if(tl >= l && tr <= r){
        char *self = (char*) segtree->tree +(node * segtree->node_size);
        memcpy(output_result, self, segtree->node_size);
        return;
    } 

    uint tmid = (tl + tr) / 2;
    uint lchild = node * 2, rchild = node * 2 + 1;

    char lquery[segtree->node_size];
    char rquery[segtree->node_size];

    segtreeQuery(segtree, lquery, l, r, tl, tmid, lchild);
    segtreeQuery(segtree, rquery, l, r, tmid + 1, tr, rchild);

    segtree->merge(output_result, lquery, rquery);
}

void segtreeFree(SegTree* segtree){
    if(!segtree){
        perror("[segtree.c][segtreeFree()] WARNING: Can't erase SegTree object. The object doesn't exist.\n");
        return;
    }

    free(segtree->tree);
    free(segtree->identity);
    free(segtree);
}