package com.nulp.edu.mobileappsdev.moviesdbviewer.data

/*
{
    "title": "string",
    "year": "string",
    "id": 0,
    "type": "string",
    "poster": "string"
}
 */
data class MovieShortInfo(
    val title: String,
    val year: String,
    val id: Int,
    val type: String,
    val poster: String
)

fun MovieShortInfo.toMovieFullInfo(): MovieFullInfo {
    return MovieFullInfo(
        title = title,
        year = year,
        rated = C.DATA_NOT_LOADED_STR,
        released = C.DATA_NOT_LOADED_STR,
        runtime = C.DATA_NOT_LOADED_STR,
        genre = C.DATA_NOT_LOADED_STR,
        director = C.DATA_NOT_LOADED_STR,
        writer = C.DATA_NOT_LOADED_STR,
        actors = C.DATA_NOT_LOADED_STR,
        plot = C.DATA_NOT_LOADED_STR,
        language = C.DATA_NOT_LOADED_STR,
        country = C.DATA_NOT_LOADED_STR,
        awards = C.DATA_NOT_LOADED_STR,
        poster = poster,
        ratings = emptyList(),
        metaScore = C.DATA_NOT_LOADED_STR,
        imdbRating = C.DATA_NOT_LOADED_STR,
        imdbVotes = C.DATA_NOT_LOADED_STR,
        id = id,
        type = type,
        dvd = C.DATA_NOT_LOADED_STR,
        boxOffice = C.DATA_NOT_LOADED_STR,
        production = C.DATA_NOT_LOADED_STR,
        website = C.DATA_NOT_LOADED_STR
    )
}