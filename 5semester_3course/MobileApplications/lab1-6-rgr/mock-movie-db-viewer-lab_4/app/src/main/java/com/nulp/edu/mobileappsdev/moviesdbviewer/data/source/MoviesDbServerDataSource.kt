package com.nulp.edu.mobileappsdev.moviesdbviewer.data.source

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieFullInfo
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MoviesShortInfoHolder
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.network.MoviesDbApi

class MoviesDbServerDataSource(
    private val context: Context,
    private val moviesDbApi: MoviesDbApi
) : MoviesRemoteDataSource {

    /**
     * TODO: Лабораторна робота №4
     *
     * 1. Видаліть оголошення змінних moviesCount і movies,
     *    які оголошені нижче.
     * 2. Видаліть блок програмного коду init {},
     *    який оголошений нижче.
     *
     */

    override suspend fun getMovies(): MoviesShortInfoHolder? {
        /**
         * TODO: Лабораторна робота №4
         *
         * Використовуючи примірник класу MoviesDbApi,
         * який оголошений у вигляді поля цього класу
         * moviesDbApi: MoviesDbApi вище, завантажте колекцію
         * даних про фільми у стислому форматі і поверніть отриманий
         * примірник класу MoviesShortInfoHolder з цієї функції.
         *
         */
        var moviesShortInfoHolder: MoviesShortInfoHolder? = null

        val response = moviesDbApi.getMovies()

        if (response.isSuccessful) {
            moviesShortInfoHolder = response.body()
        }

        return moviesShortInfoHolder
    }

    override suspend fun getPoster(poster: String): Bitmap? {
        /**
         * TODO: Лабораторна робота №4
         *
         * Використовуючи примірник класу MoviesDbApi,
         * який оголошений у вигляді поля цього класу
         * moviesDbApi: MoviesDbApi вище, напишіть програмний код
         * для завантаження зображення плакату фільму з навчального
         * сервера і повернення зображення з даної функції у вигляді
         * примірника класу Bitmap.
         *
         * Ідентифікатор зображеня плакату фільму передається
         * за домогою параметра poster.
         *
         */
        var bitmap: Bitmap? = null

        val response = moviesDbApi.getPoster(posterFileName = poster)

        if (response.isSuccessful) {
            response.body()?.let { responseBody ->
                bitmap = BitmapFactory.decodeStream(
                    responseBody.byteStream()
                )
            }
        }

        return bitmap
    }

    override suspend fun getMovieFullInfo(movieId: Int): MovieFullInfo? {
        /**
         * TODO: Лабораторна робота №5
         *
         * Використовуючи примірник класу MoviesDbApi,
         * який оголошений у вигляді поля цього класу
         * moviesDbApi: MoviesDbApi вище, напишіть програмний код
         * для завантаження повних даних про фільм з навчального
         * сервера і повернення цих даних з даної функції у вигляді
         * примірника класу MovieFullInfo.
         *
         * Ідентифікатор фільму передається за допомгою
         * параметра movieId.
         *
         */
        var movieFullInfo: MovieFullInfo? = null

        val response = moviesDbApi.getMovieFullInfo(movieId = movieId)

        if (response.isSuccessful) {
            movieFullInfo = response.body()
        }

        return movieFullInfo
    }
}