package com.nulp.edu.mobileappsdev.moviesdbviewer.ui

import android.graphics.Bitmap
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.staggeredgrid.LazyHorizontalStaggeredGrid
import androidx.compose.foundation.lazy.staggeredgrid.StaggeredGridCells
import androidx.compose.foundation.lazy.staggeredgrid.items
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.asImageBitmap
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MovieShortInfo
import com.nulp.edu.mobileappsdev.moviesdbviewer.data.MoviesShortInfoHolder

@Composable
fun MoviesGrid(
    moviesShortInfoHolder: MoviesShortInfoHolder,
    retrieveMoviePoster: (String, (Bitmap?) -> Unit) -> Unit,
    onItemClick: (MovieShortInfo) -> Unit,
    modifier: Modifier = Modifier
) {
    LazyHorizontalStaggeredGrid(
        rows = StaggeredGridCells.Fixed(2),
        modifier = modifier,
        contentPadding = PaddingValues(16.dp),
        horizontalItemSpacing = 12.dp,
        verticalArrangement = Arrangement.spacedBy(12.dp)
    ) {
        items(moviesShortInfoHolder.movies) { movie ->
            MovieGridItem(
                movie = movie,
                retrieveMoviePoster = retrieveMoviePoster,
                onItemClick = { onItemClick(movie) }
            )
        }
    }
}

@Composable
private fun MovieGridItem(
    movie: MovieShortInfo,
    retrieveMoviePoster: (String, (Bitmap?) -> Unit) -> Unit,
    onItemClick: () -> Unit
) {
    var posterBitmap by remember { mutableStateOf<Bitmap?>(null) }

    LaunchedEffect(movie.poster) {
        retrieveMoviePoster(movie.poster) { bitmap ->
            posterBitmap = bitmap
        }
    }

    Card(
        modifier = Modifier
            .width(220.dp)
            .clickable { onItemClick() },
        elevation = CardDefaults.cardElevation(defaultElevation = 4.dp)
    ) {
        Row(
            modifier = Modifier.fillMaxWidth()
        ) {
            // Постер фільму або placeholder (без padding!)
            if (posterBitmap != null) {
                Image(
                    bitmap = posterBitmap!!.asImageBitmap(),
                    contentDescription = movie.title,
                    modifier = Modifier
                        .width(100.dp)
                        .fillMaxHeight(),
                    contentScale = ContentScale.Crop
                )
            } else {
                Box(
                    modifier = Modifier
                        .width(100.dp)
                        .fillMaxHeight()
                        .background(MaterialTheme.colorScheme.surfaceVariant),
                    contentAlignment = Alignment.Center
                ) {
                    Text(
                        text = "N/A",
                        style = MaterialTheme.typography.titleLarge,
                        color = MaterialTheme.colorScheme.onSurfaceVariant,
                        textAlign = TextAlign.Center
                    )
                }
            }

            // Інформація про фільм
            Column(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(12.dp),
                verticalArrangement = Arrangement.Center
            ) {
                Text(
                    text = movie.title,
                    style = MaterialTheme.typography.titleSmall,
                    maxLines = 2,
                    overflow = TextOverflow.Ellipsis
                )

                Spacer(modifier = Modifier.height(8.dp))

                Text(
                    text = "${movie.type} ${movie.year}",
                    style = MaterialTheme.typography.bodySmall,
                    color = MaterialTheme.colorScheme.onSurfaceVariant,
                    maxLines = 1
                )
            }
        }
    }
}