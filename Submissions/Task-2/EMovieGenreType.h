//
// Created by krist on 06.11.2026.
//

#ifndef EMOVIEGENRETYPE_H
#define EMOVIEGENRETYPE_H
#include <string>

enum EMovieGenreType {
    ACTION = 1,
    COMEDY = 2,
    SCIFI = 4,
    HORROR = 8,
    DRAMA = 16
};

inline EMovieGenreType operator|(EMovieGenreType a, EMovieGenreType b) {
    return static_cast<EMovieGenreType>(static_cast<int>(a) | static_cast<int>(b));
}

inline std::string GenreToString(EMovieGenreType genre) {
    std::string result;

    if (genre & ACTION)
        result += "ACTION ";

    if (genre & COMEDY)
        result += "COMEDY ";

    if (genre & SCIFI)
        result += "SCIFI ";

    if (genre & HORROR)
        result += "HORROR ";

    if (genre & DRAMA)
        result += "DRAMA ";

    return result;
}

#endif //EMOVIEGENRETYPE_H
