package com.nulp.edu.mobileappsdev.moviesdbviewer.ui

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.theme.PaddingLarge

@Composable
fun ErrorScreen(
    modifier: Modifier = Modifier,
    errorText: String,
    actionBtnText: String,
    onAction: () -> Unit
) {
    Column(
        modifier = modifier,
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(
            text = errorText,
            style = MaterialTheme.typography.titleMedium
        )
        Button(
            modifier = Modifier.padding(PaddingLarge),
            onClick = onAction
        ) {
            Text(
                text = actionBtnText,
                style = MaterialTheme.typography.bodyMedium
            )
        }
    }
}