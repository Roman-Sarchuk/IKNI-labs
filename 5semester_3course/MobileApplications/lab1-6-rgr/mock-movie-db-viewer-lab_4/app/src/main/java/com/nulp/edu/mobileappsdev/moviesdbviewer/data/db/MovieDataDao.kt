package com.nulp.edu.mobileappsdev.moviesdbviewer.data.db

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.Query
import androidx.room.Transaction
import androidx.room.Update

/**
 * TODO: Лабораторна робота №6
 *
 * Змініть оголошення інтерфейсу MovieDataDao
 * таким чином, щоб він міг бути використаний
 * як DAO (Data Access Object) для роботи з
 * локальною базою даних про фільми.
 *
 */
@Dao
interface MovieDataDao {
    /**
     * TODO: Лабораторна робота №6
     *
     * Оголосіть сигнатури функцій для роботи
     * з локальною базою даних про фільми, які
     * були завантажені з сервера.
     *
     * Оголошені функції повинні дозволяти виконати
     * наступні дії:
     *
     * 1. Додати новий запис з даними про фільм до
     *    бази даних.
     * 2. Оновити існуючий запис з даними про фільм
     *    у базі даних.
     * 3. Видалити існуючий запис з даними про фільм
     *    з бази даних.
     * 4. Отримати повні дані про фільм, включно з даними
     *    про рейтинги фільму з використанням класу
     *    MovieWithRatingsData. Для пошуку відповідного запису
     *    про фільм у базі даних використайте ідентифікатор
     *    фільму, який був отриманий з сервера.
     * 5. Отримати всі збережені у базі даних записи про фільми
     *    у стислому форматі у вигляді колекції примірників
     *    MovieShortDataTuple.
     * 6. Отримати з бази даних ідентифікатор запису про фільм
     *    за допомогою ідентифікатора фільму, який був
     *    повернутий з сервера.
     *
     * Для кожного з наведених вище пунктів оголосіть окрему
     * сигнатуру функції.
     *
     * Зверніть увагу що всі оголошення сигнатур функцій
     * в даному інтерфейсі повинні використовувати ключове
     * слово suspend.
     *
     */

    // 1. Додати новий запис з даними про фільм
    @Insert
    suspend fun insertMovie(movie: MovieData): Long

    // 2. Оновити існуючий запис з даними про фільм
    @Update
    suspend fun updateMovie(movie: MovieData)

    // 3. Видалити існуючий запис з даними про фільм
    @Delete
    suspend fun deleteMovie(movie: MovieData)

    // 4. Отримати повні дані про фільм з рейтингами за id з сервера
    @Transaction
    @Query("SELECT * FROM movies WHERE id = :serverId")
    suspend fun getMovieWithRatings(serverId: Int): MovieWithRatingsData?

    // 5. Отримати всі фільми у стислому форматі
    @Query("SELECT dbId, title, year, id, type, poster FROM movies")
    suspend fun getAllMoviesShort(): List<MovieShortDataTuple>

    // 6. Отримати dbId за id з сервера
    @Query("SELECT dbId FROM movies WHERE id = :serverId")
    suspend fun getDbIdByServerId(serverId: Int): Long?
}