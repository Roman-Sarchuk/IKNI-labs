package com.nulp.edu.mobileappsdev.moviesdbviewer.ui

import android.content.res.Configuration
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalConfiguration
import androidx.compose.ui.res.stringResource
import com.nulp.edu.mobileappsdev.moviesdbviewer.R
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.viewmodel.MoviesScreenState
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.viewmodel.MoviesScreenViewModel

@Composable
fun MoviesScreen(
    onOpenMovieDetails: (Int) -> Unit,
    moviesScreenViewModel: MoviesScreenViewModel,
    modifier: Modifier = Modifier
) {

    val screenState by moviesScreenViewModel.state.collectAsState()

    when(screenState) {
        MoviesScreenState.INITIAL -> {
            moviesScreenViewModel.getMovies()
        }
        MoviesScreenState.LOADING -> {
            LoadingScreen(modifier)
        }
        MoviesScreenState.FAILED -> {
            ErrorScreen(
                modifier,
                errorText = stringResource(R.string.failed_to_load_movies_err_msg),
                actionBtnText = stringResource(R.string.retry_btn_text),
                onAction = {
                    moviesScreenViewModel.getMovies()
                }
            )
        }
        MoviesScreenState.SUCCESS -> {
            moviesScreenViewModel.moviesShortInfoHolder?.let { moviesShortInfoHolder ->
                val deviceOrientation = LocalConfiguration.current.orientation
                if (deviceOrientation == Configuration.ORIENTATION_PORTRAIT) {
                    MoviesList(
                        moviesShortInfoHolder =  moviesShortInfoHolder,
                        retrieveMoviePoster = { poster, onPosterLoaded ->
                            moviesScreenViewModel.getPoster(
                                poster = poster,
                                onPosterLoaded = onPosterLoaded
                            )
                        },
                        onItemClick = { movie ->
                            onOpenMovieDetails.invoke(movie.id)
                        },
                        modifier = modifier.fillMaxSize()
                    )
                }
                else if (deviceOrientation == Configuration.ORIENTATION_LANDSCAPE) {
                    MoviesGrid(
                        moviesShortInfoHolder =  moviesShortInfoHolder,
                        retrieveMoviePoster = { poster, onPosterLoaded ->
                            moviesScreenViewModel.getPoster(
                                poster = poster,
                                onPosterLoaded = onPosterLoaded
                            )
                        },
                        onItemClick = { movie ->
                            onOpenMovieDetails.invoke(movie.id)
                        },
                        modifier = modifier.fillMaxSize()
                    )
                }
            }
        }
    }
}