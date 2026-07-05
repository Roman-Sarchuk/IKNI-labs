package com.nulp.edu.mobileappsdev.moviesdbviewer.data.repository

import com.nulp.edu.mobileappsdev.moviesdbviewer.data.source.MoviesLocalDataSource
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.source.MoviesRemoteDataSource
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object RepositoryDI {

    @Provides
    @Singleton
    fun provideMoviesRepository(
        moviesRemoteDataSource: MoviesRemoteDataSource,
        moviesLocalDataSource: MoviesLocalDataSource
    ): MoviesRepository {
        return MoviesRepositoryImpl(moviesRemoteDataSource, moviesLocalDataSource)
    }
}