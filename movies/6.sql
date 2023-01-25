-- In 6.sql, write a SQL query to determine the average rating of all movies released in 2012.
SELECT avg(rating) FROM ratings
JOIN movies ON movies.id = ratings.movie_id
WHERE movies.year = 2012;