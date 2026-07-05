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
import androidx.compose.ui.res.stringResource
import com.nulp.edu.mobileappsdev.moviesdbviewer.R
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.theme.PaddingExtraLarge

@Composable
fun GreetingScreen(onContinue: ()-> Unit, modifier: Modifier = Modifier) {
    Column(
        modifier = modifier,
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Text(
            text = stringResource(R.string.greeting_text),
            style = MaterialTheme.typography.titleLarge
        )
        Button(
            onClick = onContinue,
            modifier = Modifier.padding(PaddingExtraLarge)
        ) {
            Text(
                text = stringResource(R.string.continue_btn_text),
                style = MaterialTheme.typography.bodyMedium
            )
        }
    }
}