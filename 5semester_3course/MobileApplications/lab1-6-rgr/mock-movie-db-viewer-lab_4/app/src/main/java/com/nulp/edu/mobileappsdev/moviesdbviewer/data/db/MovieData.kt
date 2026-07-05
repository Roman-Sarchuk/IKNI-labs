package com.nulp.edu.mobileappsdev.moviesdbviewer.data.db

import androidx.room.Entity
import androidx.room.PrimaryKey

/**
 * TODO: Лабораторна робота №6
 *
 * Змініть оголошення класу MovieData таким чином,
 * щоб він міг бути використаний для представлення
 * даних про фільм при роботі з локальною базою даних.
 *
 * Зверніть увагу, що ідентифікатор фільму (поле id),
 * який отриманий з сервера не може бути використаний для
 * представлення запису про фільм у локальній базі даних.
 *
 */
@Entity(tableName = "movies")
data class MovieData(
    val title: String,
    val year: String,
    val rated: String,
    val released: String,
    val runtime: String,
    val genre: String,
    val director: String,
    val writer: String,
    val actors: String,
    val plot: String,
    val language: String,
    val country: String,
    val awards: String,
    val poster: String,
    val metaScore: String,
    val imdbRating: String,
    val imdbVotes: String,
    val id: Int,
    val type: String,
    val dvd: String,
    val boxOffice: String,
    val production: String,
    val website: String,

    @PrimaryKey(autoGenerate = true)
    val dbId: Long = 0
)