//
// Created by krist on 06.11.2026.
//

#ifndef TMOVIE_H
#define TMOVIE_H


#include <string>
#include "EMovieGenreType.h"
using namespace std;


class TMovie {
private:
    string Title;
    string Director;
    int Year;
    EMovieGenreType Genre;
    float Score;

public:
    TMovie(string Title, string Director, int Year, EMovieGenreType Genre, float Score);
    string GetTitle();
    string GetDirector();
    int GetYear();
    EMovieGenreType GetGenre();
    float GetScore();
};


#endif //TMOVIE_H
