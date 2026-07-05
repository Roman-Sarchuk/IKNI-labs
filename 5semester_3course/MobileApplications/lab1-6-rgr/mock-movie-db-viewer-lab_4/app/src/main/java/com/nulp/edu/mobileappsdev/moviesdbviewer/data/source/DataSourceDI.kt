package com.nulp.edu.mobileappsdev.moviesdbviewer.data.source

import android.content.Context
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.db.MovieDataDao
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.db.MovieRatingDataDao
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.network.MoviesDbApi
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object DataSourceDI {

    @Provides
    @Singleton
    fun provideRemoteDataSource(
        @ApplicationContext context: Context,
        moviesDbApi: MoviesDbApi
    ): MoviesRemoteDataSource {
        return MoviesDbServerDataSource(context, moviesDbApi)
    }

    @Provides
    @Singleton
    fun provideLocalDataSource(
        @ApplicationContext context: Context,
        movieDataDao: MovieDataDao,
        movieRatingDataDao: MovieRatingDataDao
    ): MoviesLocalDataSource {
        return MoviesLocalDataSourceImpl(
            context = context,
            moviesDataDao = movieDataDao,
            movieRatingDataDao = movieRatingDataDao
        )
    }
}