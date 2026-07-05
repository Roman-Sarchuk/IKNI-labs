package com.nulp.edu.mobileappsdev.moviesdbviewer.ui

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.asImageBitmap
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import com.nulp.edu.mobileappsdev.moviesdbviewer.R
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.viewmodel.MovieDetailsScreenState
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.viewmodel.MovieDetailsScreenViewModel

@Composable
fun MovieDetailsScreen(
    movieDetailsViewModel: MovieDetailsScreenViewModel,
    modifier: Modifier = Modifier
) {

    val screenState by movieDetailsViewModel.state.collectAsState()

    when(screenState) {
        MovieDetailsScreenState.INITIAL -> {
            movieDetailsViewModel.getMovieFullInfo()
        }
        MovieDetailsScreenState.LOADING -> {
            LoadingScreen(modifier)
        }
        MovieDetailsScreenState.FAILED -> {
            ErrorScreen(
                modifier = modifier,
                errorText = stringResource(R.string.failed_to_load_movie_full_info_err_msg),
                actionBtnText = stringResource(R.string.retry_btn_text),
                onAction = {
                    movieDetailsViewModel.getMovieFullInfo()
                }
            )
        }
        MovieDetailsScreenState.SUCCESS -> {
            movieDetailsViewModel.movieFullInfo?.let { movie ->
                /**
                 * TODO: Лабораторна робота №5
                 * Реалізація користувацького інтерфейсу
                 */
                var posterBitmap by remember { mutableStateOf<android.graphics.Bitmap?>(null) }

                movieDetailsViewModel.getPoster(movie.poster) { bitmap ->
                    posterBitmap = bitmap
                }

                Box(modifier = modifier.fillMaxSize()) {
                    // Контент що прогортується
                    Column(
                        modifier = Modifier
                            .fillMaxSize()
                            .verticalScroll(state = rememberScrollState())
                            .padding(16.dp)
                            .padding(top = 196.dp) // Відступ для sticky header (180dp висота + 16dp відступ)
                    ) {
                        // Контейнер: Ratings
                        Card(
                            modifier = Modifier.fillMaxWidth(),
                            shape = MaterialTheme.shapes.medium,
                            elevation = CardDefaults.cardElevation(defaultElevation = 4.dp)
                        ) {
                            Column(modifier = Modifier.padding(16.dp)) {
                                Text(
                                    text = "Ratings:",
                                    style = MaterialTheme.typography.titleMedium,
                                    fontWeight = FontWeight.Bold,
                                    modifier = Modifier.padding(bottom = 8.dp)
                                )

                                if (movie.ratings.isNotEmpty()) {
                                    movie.ratings.forEach { rating ->
                                        LabeledText(label = rating.source, text = rating.value)
                                    }
                                }
                                LabeledText(label = "Metacritic", text = movie.metaScore)
                                LabeledText(label = "Meta Score", text = movie.metaScore)
                                LabeledText(label = "Imdb Rating", text = movie.imdbRating)
                                LabeledText(label = "Imdb Votes", text = movie.imdbVotes)
                            }
                        }

                        Spacer(modifier = Modifier.height(16.dp))

                        // Контейнер: General Info
                        Card(
                            modifier = Modifier.fillMaxWidth(),
                            shape = MaterialTheme.shapes.medium,
                            elevation = CardDefaults.cardElevation(defaultElevation = 4.dp)
                        ) {
                            Column(modifier = Modifier.padding(16.dp)) {
                                Text(
                                    text = "General Info:",
                                    style = MaterialTheme.typography.titleMedium,
                                    fontWeight = FontWeight.Bold,
                                    modifier = Modifier.padding(bottom = 8.dp)
                                )

                                LabeledText(label = "Rated", text = movie.rated)
                                LabeledText(label = "Released", text = movie.released)
                                LabeledText(label = "Runtime", text = movie.runtime)
                                LabeledText(label = "Language", text = movie.language)
                                LabeledText(label = "Country", text = movie.country)
                                LabeledText(label = "Awards", text = movie.awards)
                                LabeledText(label = "DVD", text = movie.dvd)
                                LabeledText(label = "Box Office", text = movie.boxOffice)
                                LabeledText(label = "Production", text = movie.production)
                                LabeledText(label = "Web Site", text = movie.website)
                                LabeledText(label = "Director", text = movie.director)
                                LabeledText(label = "Genre", text = movie.genre)
                                LabeledText(label = "Writer", text = movie.writer)
                                LabeledText(label = "Actors", text = movie.actors)
                            }
                        }

                        Spacer(modifier = Modifier.height(16.dp))

                        // Контейнер: Plot
                        Card(
                            modifier = Modifier.fillMaxWidth(),
                            shape = MaterialTheme.shapes.medium,
                            elevation = CardDefaults.cardElevation(defaultElevation = 4.dp)
                        ) {
                            Column(modifier = Modifier.padding(16.dp)) {
                                Text(
                                    text = "Plot:",
                                    style = MaterialTheme.typography.titleMedium,
                                    fontWeight = FontWeight.Bold,
                                    modifier = Modifier.padding(bottom = 8.dp)
                                )

                                Text(
                                    text = movie.plot,
                                    style = MaterialTheme.typography.bodyMedium
                                )
                            }
                        }
                    }

                    // Sticky Header: Постер + Базова інформація
                    Card(
                        modifier = Modifier
                            .fillMaxWidth()
                            .align(Alignment.TopCenter)
                            .padding(16.dp),
                        shape = MaterialTheme.shapes.medium,
                        elevation = CardDefaults.cardElevation(defaultElevation = 8.dp)
                    ) {
                        Row(
                            modifier = Modifier.fillMaxWidth(),
                            verticalAlignment = Alignment.Top
                        ) {
                            // Постер без padding
                            posterBitmap?.let { bitmap ->
                                Image(
                                    bitmap = bitmap.asImageBitmap(),
                                    contentDescription = movie.title,
                                    contentScale = ContentScale.Crop,
                                    modifier = Modifier
                                        .width(120.dp)
                                        .height(180.dp)
                                )
                            }

                            Spacer(modifier = Modifier.width(16.dp))

                            // Базова інформація з padding
                            Column(
                                modifier = Modifier
                                    .weight(1f)
                                    .padding(top = 16.dp, end = 16.dp, bottom = 16.dp)
                            ) {
                                LabeledText(label = "Title", text = movie.title)
                                LabeledText(label = "Type", text = movie.type)
                                LabeledText(label = "Year", text = movie.year)
                            }
                        }
                    }
                }
            }
        }
    }
}