package com.nulp.edu.mobileappsdev.moviesdbviewer.data.repository

import android.graphics.Bitmap
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieFullInfo
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MoviesShortInfoHolder
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.isFullyLoaded
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.source.MoviesLocalDataSource
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.source.MoviesRemoteDataSource
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.toMovieFullInfo
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext

class MoviesRepositoryImpl (
    private val moviesRemoteDataSource: MoviesRemoteDataSource,
    private val moviesLocalDataSource: MoviesLocalDataSource
): MoviesRepository {

    override suspend fun getMovies(): MoviesShortInfoHolder? {
        var moviesShortInfoHolder: MoviesShortInfoHolder? = null

        withContext(Dispatchers.IO) {
            moviesShortInfoHolder = moviesLocalDataSource.getMovies()

            if (null == moviesShortInfoHolder) {
                moviesShortInfoHolder = moviesRemoteDataSource.getMovies()
                moviesShortInfoHolder?.let { holder ->
                    holder.movies.forEach { movieShortInfo ->
                        moviesLocalDataSource.putMovie(
                            movieShortInfo.toMovieFullInfo()
                        )
                    }
                }
            }
        }

        return moviesShortInfoHolder
    }

    override suspend fun getPoster(poster: String): Bitmap? {
        var posterBitmap: Bitmap? = null

        withContext(Dispatchers.IO) {
            posterBitmap = moviesLocalDataSource.getPoster(poster)

            if (null == posterBitmap) {
                posterBitmap = moviesRemoteDataSource.getPoster(poster)
                posterBitmap?.let { notNullBitmap ->
                    moviesLocalDataSource.putPoster(poster, notNullBitmap)
                }
            }
        }

        return posterBitmap
    }

    override suspend fun getMovieFullInfo(movieId: Int): MovieFullInfo? {
        var movieFullInfo: MovieFullInfo? = null

        withContext(Dispatchers.IO) {
            movieFullInfo = moviesLocalDataSource.getMovieFullInfo(movieId)

            if (null == movieFullInfo || !movieFullInfo.isFullyLoaded()) {
                movieFullInfo = moviesRemoteDataSource.getMovieFullInfo(movieId)
                movieFullInfo?.let { notNullMovieFullInfo ->
                    moviesLocalDataSource.putMovie(notNullMovieFullInfo)
                }
            }
        }

        return movieFullInfo
    }

}