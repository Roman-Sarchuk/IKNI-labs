package com.nulp.edu.mobileappsdev.moviesdbviewer.data.network

import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import okhttp3.OkHttpClient
import okhttp3.logging.HttpLoggingInterceptor
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import java.util.concurrent.TimeUnit
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object NetworkDI {

    /**
     * TODO: Лабораторна робота №4
     *
     * Змініть значення константи BASE_URL таким чином,
     * щоб URL - адреса вказувала на навчальний сервер
     * mock-movies-db-server запущений на локальному ПК.
     *
     * Зверніть увагу, що для коректної роботи додатку на віртуальному
     * пристрої, адреса хоста повинна бути представлена
     * у вигляді IP-адреси.
     *
     * Також зверніть увагу, що навчальний сервер використовує порт 8080.
     */
    private const val BASE_URL = "http://192.168.0.102:8080/"

    @Provides
    @Singleton
    fun provideRetrofit(): Retrofit {
        /**
         * TODO: Лабораторна робота №4
         *
         * Здійсніть конфігурацію примірника класу Retrofit,
         * таким чином, щоб:
         *
         * 1. Забезпечити переведення даних з формату JSON у модель
         *    даних додатку.
         * 2. Забезпечити стабільну комунікацію з сервером: визначте час
         *    очікування на з'єднання з сервером, час очікування при
         *    отримуванні і надсиланні даних.
         * 3. Забезпечити додавання повідомлень в журнал додатку про
         *    комунікацію з сервером.
         */

        // Налаштування логування
        val interceptor = HttpLoggingInterceptor().apply {
            level = HttpLoggingInterceptor.Level.BODY
        }

        // Налаштування клієнта з таймаутами
        val client = OkHttpClient.Builder()
            .connectTimeout(30, TimeUnit.SECONDS)
            .readTimeout(20, TimeUnit.SECONDS)
            .writeTimeout(25, TimeUnit.SECONDS)
            .addInterceptor(interceptor)
            .build()

        return Retrofit.Builder()
            .baseUrl(BASE_URL)
            .client(client)
            .addConverterFactory(GsonConverterFactory.create())
            .build()
    }

    @Provides
    @Singleton
    fun provideMoviesDbApi(retrofit: Retrofit): MoviesDbApi {
        return retrofit.create(MoviesDbApi::class.java)
    }
}