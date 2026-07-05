package com.nulp.edu.mobileappsdev.moviesdbviewer.data

/*
{
  "title": "string",
  "year": "string",
  "rated": "string",
  "released": "string",
  "runtime": "string",
  "genre": "string",
  "director": "string",
  "writer": "string",
  "actors": "string",
  "plot": "string",
  "language": "string",
  "country": "string",
  "awards": "string",
  "poster": "string",
  "ratings": [
    {
      "source": "string",
      "value": "string"
    }
  ],
  "metaScore": "string",
  "imdbRating": "string",
  "imdbVotes": "string",
  "id": 0,
  "type": "string",
  "dvd": "string",
  "boxOffice": "string",
  "production": "string",
  "website": "string"
}
 */
data class MovieFullInfo(
    val title: String,
    val year: String,
    val rated: String,
    val released: String,
    val runtime: String,
    val genre: String,
    val director: String,
    val writer: String,
    val actors: String,
    val plot: String,
    val language: String,
    val country: String,
    val awards: String,
    val poster: String,
    val ratings: List<MovieRating>,
    val metaScore: String,
    val imdbRating: String,
    val imdbVotes: String,
    val id: Int,
    val type: String,
    val dvd: String,
    val boxOffice: String,
    val production: String,
    val website: String
)

fun MovieFullInfo.isFullyLoaded(): Boolean {
    return C.DATA_NOT_LOADED_STR != rated
}