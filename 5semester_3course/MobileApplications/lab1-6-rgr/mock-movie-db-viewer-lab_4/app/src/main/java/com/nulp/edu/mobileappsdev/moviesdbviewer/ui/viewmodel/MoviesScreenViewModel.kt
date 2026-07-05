package com.nulp.edu.mobileappsdev.moviesdbviewer.ui.viewmodel

import android.graphics.Bitmap
import androidx.compose.runtime.mutableStateMapOf
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.C
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MoviesShortInfoHolder
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.repository.MoviesRepository
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class MoviesScreenViewModel @Inject constructor(
    private val moviesRepository: MoviesRepository
): ViewModel() {

    private val _state = MutableStateFlow(MoviesScreenState.INITIAL)

    private val _moviesShortInfoHolder = mutableStateOf<MoviesShortInfoHolder?>(null)
    private val _postersLoading = mutableStateMapOf<String, (Bitmap) -> Unit>()

    val state: StateFlow<MoviesScreenState>
        get() = _state.asStateFlow()
    val moviesShortInfoHolder: MoviesShortInfoHolder?
        get() = _moviesShortInfoHolder.value

    fun getPoster(poster: String, onPosterLoaded: (Bitmap) -> Unit) {
        if (poster != C.DATA_NOT_AVAILABLE_STR) {
            _postersLoading[poster] = onPosterLoaded

            viewModelScope.launch {
                moviesRepository.getPoster(poster)?.let { bitmap ->
                    _postersLoading[poster]?.invoke(bitmap)
                }
                _postersLoading.remove(poster)
            }
        }

    }

    fun getMovies() {
        _state.value = MoviesScreenState.LOADING

        viewModelScope.launch {
            val moviesShortInfoHolder = moviesRepository.getMovies()

            if (null == moviesShortInfoHolder) {
                _state.value = MoviesScreenState.FAILED
            } else {
                _moviesShortInfoHolder.value = moviesShortInfoHolder
                _state.value = MoviesScreenState.SUCCESS
            }
        }
    }
}

enum class MoviesScreenState {
    INITIAL,
    LOADING,
    FAILED,
    SUCCESS
}