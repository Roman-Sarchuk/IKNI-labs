package com.nulp.edu.mobileappsdev.moviesdbviewer.data.db

import androidx.room.Embedded
import androidx.room.Relation
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieFullInfo
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieRating
import okhttp3.internal.toImmutableList

data class MovieWithRatingsData(
    /**
     * TODO: Лабораторна робота №6
     *
     * Змініть оголошення полів класу
     * MovieWithRatingsData таким чином щоб:
     *
     * 1. Забезпечити автоматичне зчитування запису
     *    з повними даними про фільму для поля movieData
     *    у вигляді примірника класу MovieData.
     * 2. Забезпечити автоматичне зчитування всіх записів
     *    про наявні рейтинги фільму у поле ratingData у
     *    вигляді колекції примірників класу MovieRatingData
     *    за рахунок оголошення звʼязку один до багатьох між
     *    записами про фільм і записами про рейтинг фільму
     *    у базі даних.
     *
     */
    @Embedded
    val movieData: MovieData,

    @Relation(
        parentColumn = "dbId",
        entityColumn = "movieLocalId"
    )
    val ratingData: List<MovieRatingData>
)

fun MovieWithRatingsData.toMovieFullInfo(): MovieFullInfo {
    val movieRatingsList = mutableListOf<MovieRating>()

    ratingData.forEach { ratingData ->
        movieRatingsList.add(ratingData.toMovieRating())
    }

    return MovieFullInfo(
        title = movieData.title,
        year = movieData.year,
        rated = movieData.rated,
        released = movieData.released,
        runtime = movieData.runtime,
        genre = movieData.genre,
        director = movieData.director,
        writer = movieData.writer,
        actors = movieData.actors,
        plot = movieData.plot,
        language = movieData.language,
        country = movieData.country,
        awards = movieData.awards,
        poster = movieData.poster,
        ratings = movieRatingsList.toImmutableList(),
        metaScore = movieData.metaScore,
        imdbRating = movieData.imdbRating,
        imdbVotes = movieData.imdbVotes,
        id = movieData.id,
        type = movieData.type,
        dvd = movieData.dvd,
        boxOffice = movieData.boxOffice,
        production = movieData.production,
        website = movieData.website
    )
}