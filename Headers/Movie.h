//Brandon Chai, 2014
//Header for Movie class

#ifndef MOVIE_H_INCLUDED
#define MOVIE_H_INCLUDED

#include <string>

using namespace std;

class Movie
{
private:
    string title;
    string genre;
    int year;
    double rating;
public:
    //constructors
    Movie(){title = ""; genre = ""; year = -1;
            rating = -1;}
    Movie(string title, int year, string genre, double rating)
         {this->title = title; this->year = year;
         this->genre = genre;this->rating = rating;}

    //mutators
    void setTitle(string title){this->title = title;}
    void setGenre(string genre){this->genre = genre;}
    void setYear(int year){this->year = year;}
    void setRating(double rating){this->rating = rating;}

    //accessors
    string getTitle(){return title;}
    string getGenre(){return genre;}
    int getYear(){return year;}
    double getRating(){return rating;}
};
#endif // MOVIE_H_INCLUDED
