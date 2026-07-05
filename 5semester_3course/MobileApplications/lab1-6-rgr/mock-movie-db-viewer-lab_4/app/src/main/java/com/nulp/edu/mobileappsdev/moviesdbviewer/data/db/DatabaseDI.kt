package com.nulp.edu.mobileappsdev.moviesdbviewer.data.db

import android.content.Context
import androidx.room.Room
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object DatabaseDI {

    @Provides
    @Singleton
    fun provideMoviesDatabase(@ApplicationContext context: Context): MoviesDatabase {
        /**
         * TODO: Лабораторна робота №6
         *
         * Змініть програмний код, який розташований
         * нижче цього коментаря таким чином, щоб
         * створити примірник класу MoviesDatabase, який
         * дозволить зберігати і отримувати дані про
         * фільми з бази даних Room.
         *
         */
        return Room.databaseBuilder(
            context,
            MoviesDatabase::class.java,
            "movies_database"
        ).build()
    }

    @Provides
    @Singleton
    fun provideMovieDataDao(moviesDatabase: MoviesDatabase): MovieDataDao {
        return moviesDatabase.movieDataDao()
    }

    @Provides
    @Singleton
    fun provideMovieRatingDataDao(moviesDatabase: MoviesDatabase): MovieRatingDataDao {
        return moviesDatabase.movieRatingDataDao()
    }
}