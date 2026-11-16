//
// Created by krist on 06.11.2026.
//

#include "TMovieNode.h"

TMovieNode::TMovieNode(TMovie *movie) {
    this->movie = movie;
    this->next = nullptr;
    this->prev = nullptr;
}

TMovieNode::~TMovieNode() {
    delete movie;
}
