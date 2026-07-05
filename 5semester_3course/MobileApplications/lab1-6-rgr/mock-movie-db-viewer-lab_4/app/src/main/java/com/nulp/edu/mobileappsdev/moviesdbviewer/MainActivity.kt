package com.nulp.edu.mobileappsdev.moviesdbviewer

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.App
import com.nulp.edu.mobileappsdev.moviesdbviewer.ui.theme.MoviesDbViewerTheme
import dagger.hilt.android.AndroidEntryPoint

@AndroidEntryPoint
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            MoviesDbViewerTheme {
                App()
            }
        }
    }
}




