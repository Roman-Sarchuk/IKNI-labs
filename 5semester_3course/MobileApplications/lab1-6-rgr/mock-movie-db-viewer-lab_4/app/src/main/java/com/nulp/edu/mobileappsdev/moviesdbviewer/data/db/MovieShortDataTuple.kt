package com.nulp.edu.mobileappsdev.moviesdbviewer.data.db

import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieShortInfo

data class MovieShortDataTuple(
    val dbId: Long,
    val title: String,
    val year: String,
    val id: Int,
    val type: String,
    val poster: String
)

fun MovieShortDataTuple.toMovieShortInfo(): MovieShortInfo {
    return MovieShortInfo(
        title = title,
        year = year,
        id = id,
        type = type,
        poster = poster
    )
}
