package com.nulp.edu.mobileappsdev.moviesdbviewer.data.db

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.Update

/**
 * TODO: Лабораторна робота №6
 *
 * Змініть оголошення інтерфейсу MovieRatingDataDao
 * таким чином, щоб він міг бути використаний
 * як DAO (Data Access Object) для роботи з
 * локальною базою даних про фільми.
 *
 */
@Dao
interface MovieRatingDataDao {
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
     * 1. Додати новий запис про рейтинг фільму до
     *    бази даних.
     * 2. Оновити запис про рейтинг фільму в
     *    базі даних.
     * 3. Видалити запис про рейтинг фільму з
     *    бази даних.
     *
     * Для кожного з наведених вище пунктів оголосіть окрему
     * сигнатуру функції.
     *
     * Зверніть увагу що всі оголошення сигнатур функцій
     * в даному інтерфейсі повинні використовувати ключове
     * слово suspend.
     *
     */

    @Insert
    suspend fun insertRating(rating: MovieRatingData)

    @Update
    suspend fun updateRating(rating: MovieRatingData)

    @Delete
    suspend fun deleteRating(rating: MovieRatingData)
}