package com.nulp.edu.mobileappsdev.moviesdbviewer.data.db

import androidx.room.Database
import androidx.room.RoomDatabase

/**
 * TODO: Лабораторна робота №6
 *
 * Змініть оголошення класу таким чином,
 * щоб оголосити базу даних Room для збереження
 * даних про фільми.
 *
 */
@Database(
    entities = [
        MovieData::class,
        MovieRatingData::class
    ],
    version = 1,
    exportSchema = false
)
abstract class MoviesDatabase : RoomDatabase() {
    abstract fun movieDataDao(): MovieDataDao
    abstract fun movieRatingDataDao(): MovieRatingDataDao
}