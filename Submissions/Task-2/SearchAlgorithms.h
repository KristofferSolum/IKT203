//
// Created by krist on 06.11.2026.
//

#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H

#include "TMovie.h"
#include <algorithm>

inline bool SearchByTitle(TMovie* movie, void* criteria) {
    string title = movie->GetTitle();
    string searchTitle = *static_cast<string*>(criteria);

    transform(title.begin(), title.end(), title.begin(), ::tolower);
    transform(searchTitle.begin(), searchTitle.end(), searchTitle.begin(), ::tolower);

    return title.find(searchTitle) != string::npos;
}

inline bool SearchByDirector(TMovie* movie, void* criteria) {
    string director = movie->GetDirector();
    string searchDirector = *static_cast<string*>(criteria);

    transform(director.begin(), director.end(), director.begin(), ::tolower);
    transform(searchDirector.begin(), searchDirector.end(), searchDirector.begin(), ::tolower);

    return director.find(searchDirector) != string::npos;
}

inline bool SearchByGenre(TMovie* movie, void* criteria) {
    const auto* searchGenre = static_cast<EMovieGenreType*>(criteria);

    return (static_cast<int>(movie->GetGenre()) & static_cast<int>(*searchGenre)) != 0;
}

#endif //SEARCHALGORITHMS_H
