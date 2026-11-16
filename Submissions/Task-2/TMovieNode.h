//
// Created by krist on 06.11.2026.
//

#ifndef TMOVIENODE_H
#define TMOVIENODE_H



#include "TMovie.h"

class TMovieNode {
public:
    TMovie* movie;
    TMovieNode* next;
    TMovieNode* prev;
    explicit TMovieNode(TMovie* movie);
    ~TMovieNode();
};




#endif //TMOVIENODE_H
