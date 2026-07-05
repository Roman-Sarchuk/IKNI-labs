package com.nulp.edu.mobileappsdev.moviesdbviewer.ui

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import com.nulp.edu.mobileappsdev.moviesdbviewer.R
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.theme.PaddingMedium

@Composable
fun LoadingScreen(modifier: Modifier = Modifier) {
    Column (
        modifier = modifier,
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(
            text = stringResource(R.string.loading_dialog_message),
            style = MaterialTheme.typography.titleMedium,
            modifier = Modifier.padding(PaddingMedium)
        )
        CircularProgressIndicator()
    }
}