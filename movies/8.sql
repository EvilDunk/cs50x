SELECT name FROM ((stars INNER JOIN people ON people.id = person_id) INNER JOIN movies ON movies.id = movie_id) WHERE title = "Toy Story";