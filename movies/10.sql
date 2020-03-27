SELECT DISTINCT name FROM (((directors INNER JOIN people ON people.id = person_id) INNER JOIN movies ON movies.id = directors.movie_id) INNER JOIN ratings ON movies.id = ratings.movie_id) WHERE rating >= 9.0;