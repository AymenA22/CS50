SELECT name FROM people
JOIN stars on stars.person_id = people.id
JOIN movies on movies.id = stars.movie_id
WHERE movies.id IN (
SELECT movies.id FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE name = 'Kevin Bacon' AND birth = '1958')
AND name != 'Kevin Bacon';
