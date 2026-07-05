package com.nulp.edu.mobileappsdev.moviesdbviewer.data.db

import androidx.room.Entity
import androidx.room.ForeignKey
import androidx.room.PrimaryKey
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieRating

/**
 * TODO: Лабораторна робота №6
 *
 * Змініть оголошення класу MovieRatingData таким чином,
 * щоб забезпечити можливість збереження і отримування
 * даних про рейтинг фільму з локальної бази даних.
 *
 */
@Entity(
    tableName = "movie_ratings",
    foreignKeys = [
        ForeignKey(
            entity = MovieData::class,
            parentColumns = ["dbId"],
            childColumns = ["movieLocalId"],
            onDelete = ForeignKey.CASCADE
        )
    ]
)
data class MovieRatingData(
    val movieLocalId: Long,
    val source: String,
    val value: String,

    @PrimaryKey(autoGenerate = true)
    val ratingId: Long = 0
)

fun MovieRatingData.toMovieRating(): MovieRating {
    return MovieRating(
        source = source,
        value = value
    )
}