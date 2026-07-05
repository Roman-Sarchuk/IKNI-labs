package com.nulp.edu.mobileappsdev.moviesdbviewer.data.repository

import android.graphics.Bitmap
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieFullInfo
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MoviesShortInfoHolder

interface MoviesRepository{
    suspend fun getMovies(): MoviesShortInfoHolder?
    suspend fun getPoster(poster: String): Bitmap?
    suspend fun getMovieFullInfo(movieId: Int): MovieFullInfo?
}