#include <iostream>
#include <iostream>
#include "TMovie.h"
#include "TMovieList.h"
#include "SearchAlgorithms.h"
using namespace std;

void DisplayMovie(TMovie* movie) {
  if (movie == nullptr) {
    cout << "No movie found.\n";
    return;
  }

  cout << "Title: " << movie->GetTitle() << endl;
  cout << "Director: " << movie->GetDirector() << endl;
  cout << "Year: " << movie->GetYear() << endl;
  cout << "Genre: " << GenreToString(movie->GetGenre()) << endl;
  cout << "Score: " << movie->GetScore() << endl;
}


void DisplayMovies(TMovieList& movies) {
  TMovieNode* current = movies.head->next;
  int index = 0;

  cout << "\n========== MOVIE LIST ==========\n";

  if (current == nullptr) {
    cout << "No movies found.\n";
    return;
  }

  while (current != nullptr) {
    cout << "\n[" << index << "]\n";
    DisplayMovie(current->movie);

    current = current->next;
    index++;
  }

  cout << "\n================================\n";
}


void DisplayMenu() {
  cout << "\n========== MOVIE DATABASE ==========\n";
  cout << "1. Show all movies\n";
  cout << "2. Search by title\n";
  cout << "3. Search by director\n";
  cout << "4. Search by genre\n";
  cout << "5. Get movie at index\n";
  cout << "6. Append movie\n";
  cout << "7. Prepend movie\n";
  cout << "8. Remove movie\n";
  cout << "9. Reverse list\n";
  cout << "0. Exit\n";
  cout << "====================================\n";
  cout << "Choose an option: ";
}

TMovie* CreateMovie() {
  string title, director;
  int year, genre;
  float score;

  cout << "Enter movie title: ";
  getline(cin >> ws, title);

  cout << "Enter director: ";
  getline(cin, director);

  cout << "Enter release year: ";
  cin >> year;

  cout << "\nAvailable genres:\n";
  cout << "1. Action\n";
  cout << "2. Comedy\n";
  cout << "4. Sci-Fi\n";
  cout << "8. Horror\n";
  cout << "16. Drama\n";

  cout << "Enter genre value: ";
  cin >> genre;

  cout << "Enter score: ";
  cin >> score;

  return new TMovie(
      title,
      director,
      year,
      static_cast<EMovieGenreType>(genre),
      score
  );
}


int main() {
  TMovieList movies;

  // Append movies
  movies.Append(new TMovie("The Dark Knight", "Christopher Nolan", 2008, ACTION | DRAMA, 9.0));
  movies.Append(new TMovie("Inception", "Christopher Nolan", 2010, ACTION | SCIFI, 8.8));
  movies.Append(new TMovie("Interstellar", "Christopher Nolan", 2014, SCIFI | DRAMA, 8.7));
  movies.Append(new TMovie("The Matrix", "Lana Wachowski", 1999, ACTION | SCIFI, 8.7));
  movies.Append(new TMovie("Gladiator", "Ridley Scott", 2000, ACTION | DRAMA, 8.5));
  movies.Append(new TMovie("Titanic", "James Cameron", 1997, DRAMA, 7.9));
  movies.Append(new TMovie("Avatar", "James Cameron", 2009, ACTION | SCIFI, 7.9));
  movies.Append(new TMovie("The Conjuring", "James Wan", 2013, HORROR, 7.5));

  // Prepend movies
  movies.Prepend(new TMovie("Joker", "Todd Phillips", 2019, DRAMA, 8.4));
  movies.Prepend(new TMovie("The Hangover", "Todd Phillips", 2009, COMEDY, 7.7));
  movies.Prepend(new TMovie("Superbad", "Greg Mottola", 2007, COMEDY, 7.6));
  movies.Prepend(new TMovie("Get Out", "Jordan Peele", 2017, HORROR | DRAMA, 7.8));
  movies.Prepend(new TMovie("Scream", "Wes Craven", 1996, HORROR, 7.4));
  movies.Prepend(new TMovie("The Avengers", "Joss Whedon", 2012, ACTION | SCIFI, 8.0));
  movies.Prepend(new TMovie("Shutter Island", "Martin Scorsese", 2010, DRAMA, 8.2));

  int choice;

  do {
    DisplayMenu();
    cin >> choice;

    switch (choice) {
      case 1:
        DisplayMovies(movies);
        break;

      case 2: {
        string searchTitle;

        cout << "Enter movie title: ";
        cin >> ws;
        getline(cin, searchTitle);

        TMovie* result = movies.SearchFor(SearchByTitle, &searchTitle);

        DisplayMovie(result);

        break;
      }

      case 3: {
        string searchDirector;

        cout << "Enter director name: ";
        cin >> ws;
        getline(cin, searchDirector);

        TMovie* result = movies.SearchFor(SearchByDirector, &searchDirector);

        DisplayMovie(result);

        break;
      }

      case 4: {
        int choice;

        cout << "\n========== GENRES ==========\n";
        cout << "1. Action\n";
        cout << "2. Comedy\n";
        cout << "3. Sci-Fi\n";
        cout << "4. Horror\n";
        cout << "5. Drama\n";
        cout << "============================\n";
        cout << "Choose a genre: ";
        cin >> choice;

        EMovieGenreType searchGenre;

        switch (choice) {
          case 1: searchGenre = ACTION; break;
          case 2: searchGenre = COMEDY; break;
          case 3: searchGenre = SCIFI; break;
          case 4: searchGenre = HORROR; break;
          case 5: searchGenre = DRAMA; break;
          default:
            cout << "Invalid genre!\n";
            break;
        }

        if (choice < 1 || choice > 5) {
          break;
        }

        TMovie* result = movies.SearchFor(SearchByGenre, &searchGenre);

        DisplayMovie(result);

        break;
      }

      case 5: {
        int index;

        cout << "Enter movie index: ";
        cin >> index;

        TMovie* result = movies.GetAtIndex(index);

        DisplayMovie(result);

        break;
      }

      case 6: {
        TMovie* movie = CreateMovie();

        movies.Append(movie);

        cout << "\nMovie successfully appended!\n";
        DisplayMovie(movie);

        break;
      }

      case 7: {
        TMovie* movie = CreateMovie();

        movies.Prepend(movie);

        cout << "\nMovie successfully prepended!\n";
        DisplayMovie(movie);

        break;
      }

      case 8: {
        DisplayMovies(movies);

        int index;
        cout << "\nEnter index of movie to remove: ";
        cin >> index;

        TMovie* movie = movies.GetAtIndex(index);

        if (movie == nullptr) {
          cout << "\nInvalid index! No movie removed.\n";
          break;
        }

        string title = movie->GetTitle();

        movies.Remove(index);

        cout << "\nMovie '" << title << "' successfully removed!\n";

        break;
      }

      case 9: {
        movies.Reverse();

        cout << "\nMovie list successfully reversed!\n";
        DisplayMovies(movies);

        break;
      }

      case 0:
        cout << "Exiting program...\n";
        break;

      default:
        cout << "Invalid option!\n";
    }

  } while (choice != 0);

  return 0;
}