package com.nulp.edu.mobileappsdev.moviesdbviewer.ui.viewmodel

import android.graphics.Bitmap
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.navigation.toRoute
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.C
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieFullInfo
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.repository.MoviesRepository
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.MovieDetails
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class MovieDetailsScreenViewModel @Inject constructor(
    private val moviesRepository: MoviesRepository,
    private val savedStateHandle: SavedStateHandle
): ViewModel() {

    private val _state = MutableStateFlow(MovieDetailsScreenState.INITIAL)

    private val _movieFullInfo = mutableStateOf<MovieFullInfo?>(null)
    private val _onPosterLoaded = mutableStateOf<(Bitmap) -> Unit>({})

    val state: StateFlow<MovieDetailsScreenState>
        get() = _state.asStateFlow()
    val movieFullInfo: MovieFullInfo?
        get() = _movieFullInfo.value

    fun getPoster(poster: String, onPosterLoaded: (Bitmap) -> Unit) {
        if (poster != C.DATA_NOT_AVAILABLE_STR) {
            _onPosterLoaded.value = onPosterLoaded

            /**
             * TODO #1: Реалізація завантаження постера
             */
            viewModelScope.launch {
                val posterBitmap = moviesRepository.getPoster(poster)
                if (posterBitmap != null) {
                    _onPosterLoaded.value.invoke(posterBitmap)
                    _onPosterLoaded.value = {}
                }
            }
        }
    }

    fun getMovieFullInfo() {
        _state.value = MovieDetailsScreenState.LOADING
        /**
         * TODO #2: Реалізація завантаження повних даних про фільм
         */
        viewModelScope.launch {
            val movieDetails = savedStateHandle.toRoute<MovieDetails>()
            val fullInfo = moviesRepository.getMovieFullInfo(movieDetails.movieId)

            if (fullInfo != null) {
                _movieFullInfo.value = fullInfo
                _state.value = MovieDetailsScreenState.SUCCESS
            } else {
                _state.value = MovieDetailsScreenState.FAILED
            }
        }
    }
}

enum class MovieDetailsScreenState {
    /**
     * Початковий стан екрану.
     */
    INITIAL,

    /**
     * Завантаження даних.
     */
    LOADING,

    /**
     * Завантаження даних не було успішним.
     */
    FAILED,

    /**
     * Дані завантажені успішно.
     */
    SUCCESS
}