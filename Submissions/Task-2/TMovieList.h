//
// Created by krist on 06.11.2026.
//

#ifndef TMOVIELIST_H
#define TMOVIELIST_H


#include "TMovieNode.h"
#include "TMovie.h"

using FCheckMovie = bool(*)(TMovie*, void*);

class TMovieList {
public:
    TMovieNode* head;
    TMovieNode* tail;
    TMovieList();
    ~TMovieList();
    void Append(TMovie* movie);
    void Prepend(TMovie* movie);
    TMovie* GetAtIndex(int index);
    void Remove(int index);
    void Reverse();
    TMovie* SearchFor(FCheckMovie callback, void* criteria);
};



#endif //TMOVIELIST_H
