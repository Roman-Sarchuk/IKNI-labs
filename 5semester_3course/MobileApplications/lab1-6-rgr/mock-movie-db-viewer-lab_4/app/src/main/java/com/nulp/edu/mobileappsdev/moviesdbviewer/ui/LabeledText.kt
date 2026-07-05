package com.nulp.edu.mobileappsdev.moviesdbviewer.ui

import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.theme.PaddingMedium

@Composable
fun LabeledText(
    label: String,
    text: String,
    modifier: Modifier = Modifier
) {
    Row(modifier = modifier) {
        Text(
            text = label,
            modifier = Modifier.padding(end = PaddingMedium),
            style = MaterialTheme.typography.labelLarge
        )
        Text(
            text = text,
            style = MaterialTheme.typography.bodyMedium
        )
    }
}