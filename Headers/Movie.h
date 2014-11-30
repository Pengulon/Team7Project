// Anthony Liu, 2014
// Header for Movie class object
// Team 1 Project

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
    void setTitle(string title){this->title = title;}				//This function sets the Title
    void setGenre(string genre){this->genre = genre;}				//This function sets the Genre
    void setYear(int year){this->year = year;}						//This function sets the Year
    void setRating(double rating){this->rating = rating;}			//This function sets the Rating

    //accessors
    string getTitle(){return title;}								//This function returns the title
    string getGenre(){return genre;}								//This function returns the genre
    int getYear(){return year;}										//This function returns the year
    double getRating(){return rating;}								//This function returns the rating
};
#endif // MOVIE_H_INCLUDED
