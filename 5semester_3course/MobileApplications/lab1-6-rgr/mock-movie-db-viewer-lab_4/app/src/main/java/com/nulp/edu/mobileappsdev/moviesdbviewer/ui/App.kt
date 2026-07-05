package com.nulp.edu.mobileappsdev.moviesdbviewer.ui

import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.navigation.NavController
import androidx.navigation.NavHost
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import kotlinx.serialization.Serializable

/*
App screens declaration.
 */
@Serializable
object Greeting
@Serializable
object Movies

/**
 * TODO #1: Оголошення ідентифікатора екрану (маршруту) для MovieDetailsScreen
 * з параметром movieId
 */
@Serializable
data class MovieDetails(val movieId: Int)


@Composable
fun App(
    navController: NavHostController = rememberNavController()
) {
    Scaffold { innerPadding ->
        NavHost(
            navController = navController,
            startDestination = Greeting,
            modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding)
        ) {
            composable<Greeting> {
                GreetingScreen(
                    onContinue = {
                        navController.navigate(
                            route = Movies
                        )
                    }
                )
            }
            composable<Movies> {
                MoviesScreen(
                    moviesScreenViewModel = hiltViewModel(),
                    onOpenMovieDetails = { movieId ->
                        /**
                         * TODO #2: Реалізація навігації до екрану деталей фільму
                         */
                        navController.navigate(
                            route = MovieDetails(movieId = movieId)
                        )
                    }
                )
            }
            /**
             * TODO #3: Оголошення вершини графу навігації для екрану деталей фільму
             */
            composable<MovieDetails> {
                MovieDetailsScreen(
                    movieDetailsViewModel = hiltViewModel()
                )
            }
        }
    }
}