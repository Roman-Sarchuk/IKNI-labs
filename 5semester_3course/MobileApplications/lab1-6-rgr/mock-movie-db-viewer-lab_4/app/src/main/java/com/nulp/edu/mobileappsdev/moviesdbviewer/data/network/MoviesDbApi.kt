package com.nulp.edu.mobileappsdev.moviesdbviewer.data.network

import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieFullInfo
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MoviesShortInfoHolder
import okhttp3.ResponseBody
import retrofit2.Response
import retrofit2.http.GET
import retrofit2.http.Query

interface MoviesDbApi {
    /**
     * TODO: Лабораторна робота №4
     *
     * Використовуючи анотації @GET і @Query оголосіть функції
     * для завантаження колекції даних про фільми у стислому форматі,
     * а також для завантаження зображення для плакату фільму
     * використовуючи REST API навчального серверу.
     *
     * Зверніть увагу, що для зберігання колекції даних про фільми
     * у стислому форматі, додаток використовує клас
     * MoviesShortInfoHolder.
     *
     */

    @GET("movies")
    suspend fun getMovies(): Response<MoviesShortInfoHolder>

    @GET("poster")
    suspend fun getPoster(//http://10.43.10.10:8080/poster?p=fdf
        @Query("p") posterFileName: String
    ): Response<ResponseBody>

    /**
     * TODO: Лабораторна робота №5
     *
     * Використовуючи анатоції @GET і @Query оголосіть функцію
     * для завантаження повних даних про фільм.
     *
     * Зверніть увагу, що для представлення повних даних про фільм
     * додаток використовує клас MovieFullInfo.
     *
     */

    @GET("movie")
    suspend fun getMovieFullInfo(
        @Query("id") movieId: Int
    ): Response<MovieFullInfo>
}