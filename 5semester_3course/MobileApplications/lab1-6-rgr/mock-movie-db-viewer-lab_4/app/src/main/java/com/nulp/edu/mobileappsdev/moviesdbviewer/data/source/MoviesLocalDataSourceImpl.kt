package com.nulp.edu.mobileappsdev.moviesdbviewer.data.source

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieFullInfo
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MoviesShortInfoHolder
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.db.MovieData
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.db.MovieDataDao
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.db.MovieRatingData
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.db.MovieRatingDataDao
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.db.toMovieFullInfo
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.db.toMovieShortInfo
import java.io.File
import java.io.FileOutputStream

class MoviesLocalDataSourceImpl(
    private val context: Context,
    private val moviesDataDao: MovieDataDao,
    private val movieRatingDataDao: MovieRatingDataDao
) : MoviesLocalDataSource {

    override suspend fun getMovies(): MoviesShortInfoHolder? {
        /**
         * TODO: Лабораторна робота №6
         *
         * Реалізуйте програмний код, який використовуючи
         * методи примірника інтерфейсу MovieDataDao, отримає
         * дані про фільми збережені в локальній базі
         * даних у стислому форматі і поверне їх з даної
         * функції у вигляді примірника класу
         * MoviesShortInfoHolder.
         *
         * Зверніть увагу, для конвертації примірника
         * класу MovieShortDataTuple у примірник класу
         * MovieShortInfo, використовуйте функцію
         * toMovieShortInfo() класу MovieShortDataTuple.
         *
         */
        val moviesTuples = moviesDataDao.getAllMoviesShort()

        if (moviesTuples.isEmpty()) {
            return null
        }

        val moviesShortInfo = moviesTuples.map { it.toMovieShortInfo() }

        return MoviesShortInfoHolder(
            movies = moviesShortInfo
        )
    }

    override suspend fun getPoster(poster: String): Bitmap? {
        /**
         * TODO: Лабораторна робота №6
         *
         * Реалізуйте програмний код, який зчитає
         * збережене зображення плакату фільму з
         * файлової системи пристрою у випадку
         * існування відповідного файлу.
         *
         * В якості назви файлу використовуйте
         * значення параметру poster з розширенням
         * ".jpg".
         *
         */
        val fileName = "$poster.jpg"
        val file = File(context.filesDir, fileName)

        return if (file.exists()) {
            BitmapFactory.decodeFile(file.absolutePath)
        } else {
            null
        }
    }

    override suspend fun getMovieFullInfo(movieId: Int): MovieFullInfo? {
        /**
         * TODO: Лабораторна робота №6
         *
         * Реалізуйте програмний код, який використовуючи
         * методи примірника інтерфейсу MovieDataDao, отримає
         * повні дані про фільми збережені в локальній базі
         * і поверне їх з даної функції у вигляді примірника класу
         * MovieFullInfo.
         *
         * Зверніть увагу:
         *
         * 1. Для конвертації примірника класу
         *    MovieWithRatingsData у примірник класу
         *    MovieFullInfo, використовуйте функцію
         *    toMovieFullInfo() класу MovieWithRatingsData.
         * 2. Параметр movieId містить ідентифікатор фільму,
         *    який повернутий сервером.
         *
         */
        val movieWithRatings = moviesDataDao.getMovieWithRatings(movieId)

        return movieWithRatings?.toMovieFullInfo()
    }

    override suspend fun putMovie(movie: MovieFullInfo) {
        /**
         * TODO: Лабораторна робота №6
         *
         * Реалізуйте програмний код, який використовуючи
         * методи примірників інтерфейсів MovieDataDao
         * і MovieRatingDataDao збереже повні дані про фільм,
         * які представлені в якості примірника класу MovieFullInfo
         * і передаються у вигляді параметра movie у дану функцію.
         *
         */
        // Створюємо MovieData з даних MovieFullInfo
        val movieData = MovieData(
            title = movie.title,
            year = movie.year,
            rated = movie.rated,
            released = movie.released,
            runtime = movie.runtime,
            genre = movie.genre,
            director = movie.director,
            writer = movie.writer,
            actors = movie.actors,
            plot = movie.plot,
            language = movie.language,
            country = movie.country,
            awards = movie.awards,
            poster = movie.poster,
            metaScore = movie.metaScore,
            imdbRating = movie.imdbRating,
            imdbVotes = movie.imdbVotes,
            id = movie.id,
            type = movie.type,
            dvd = movie.dvd,
            boxOffice = movie.boxOffice,
            production = movie.production,
            website = movie.website
        )

        // Перевіряємо чи існує фільм в БД
        val existingDbId = moviesDataDao.getDbIdByServerId(movie.id)

        val movieDbId = if (existingDbId != null) {
            // Оновлюємо існуючий фільм
            moviesDataDao.updateMovie(movieData.copy(dbId = existingDbId))
            existingDbId
        } else {
            // Вставляємо новий фільм і отримуємо його dbId
            moviesDataDao.insertMovie(movieData)
        }

        // Зберігаємо рейтинги
        movie.ratings.forEach { rating ->
            val ratingData = MovieRatingData(
                movieLocalId = movieDbId,
                source = rating.source,
                value = rating.value
            )
            movieRatingDataDao.insertRating(ratingData)
        }
    }

    override suspend fun putPoster(poster: String, bitmap: Bitmap) {
        /**
         * TODO: Лабораторна робота №6
         *
         * Реалізуйте програмний код, який збереже
         * зображення плакату фільму у файлову систему
         * пристрою.
         *
         * В якості назви файлу використовуйте
         * значення параметру poster з розширенням
         * ".jpg".
         *
         * Зображення, яке повинне бути збережене
         * передається у дану функцію за допомогою
         * параметру bitmap.
         *
         */
        val fileName = "$poster.jpg"
        val file = File(context.filesDir, fileName)

        FileOutputStream(file).use { outputStream ->
            bitmap.compress(Bitmap.CompressFormat.JPEG, 90, outputStream)
        }
    }
}