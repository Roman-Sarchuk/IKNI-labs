package com.nulp.edu.mobileappsdev.moviesdbviewer.data.source

import android.graphics.Bitmap
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieFullInfo
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MoviesShortInfoHolder

interface MoviesLocalDataSource {
    suspend fun getMovies(): MoviesShortInfoHolder?
    suspend fun getPoster(poster: String): Bitmap?
    suspend fun getMovieFullInfo(movieId: Int): MovieFullInfo?

    suspend fun putMovie(movie: MovieFullInfo)
    suspend fun putPoster(poster: String, bitmap: Bitmap)
}