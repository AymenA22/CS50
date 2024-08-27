-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Run .tables and .schema to get familiar with the db
.tables;
.schema;
-- Open the crime_scene_report to the day of the crime
SELECT * FROM crime_scene_report WHERE month = '7' AND day = '28';
-- Theft took place at 10:15am at the bakery.
-- Three witnesses - their INTERVIEW TRANSCRIPTS MENTION THE BAKERY
-- Open the transcripts to find the witnesses statements
SELECT * FROM interviews WHERE month = '7' AND day = '28';
-- Read statements to identify names of witnesses
-- Ruth - Thief got in a car, check security footage for cars leaving around 10:15am
-- Eugene - Recognised the theif at LEGGETT STREET ATM EARLIER THAT DAY
-- Check ATM records for EUGENE and other people
-- Raymond - Thief planning to get the EARLIEST FLIGHT ON THE 29th
-- Accomplice booked the ticket for the thief, phone call for less than 1 minute

-- Look into Ruth's statement
SELECT COUNT(*) FROM bakery_security_logs;
-- 468 Records, check the headings to narrow the search
SELECT * FROM bakery_security_logs LIMIT 1;
-- Use the month day and hour
SELECT * FROM bakery_security_logs WHERE month = '7' AND day = '28' and hour = '10';
-- Not useful information , check people table
SELECT * FROM people LIMIT 2;

-- Who got in a car around 10:15am at the bakery
-- AND was at the LEGGETT STREET ATM earlier
-- AND who made a phone call that lasted less than 60 seconds
-- AND who was leaving the bakery
SELECT distinct name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN phone_calls ON phone_calls.caller = people.phone_number
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE atm_location = 'Leggett Street'
AND atm_transactions.month = '7'
AND atm_transactions.day = '28'
AND bakery_security_logs.minute BETWEEN 15 AND 30
AND duration < 60
AND caller IS NOT NULL
AND activity = "exit";

-- This leaves:
+---------+
|  name   |
+---------+
| Bruce   |
| Diana   |
+---------+

-- Which Airport is in Fiftyville?
SELECT * FROM airports;

-- This leaves:
+----+--------------+-----------------------------------------+---------------+
| id | abbreviation |                full_name                |     city      |
+----+--------------+-----------------------------------------+---------------+
| 8  | CSF          | Fiftyville Regional Airport             | Fiftyville    |
+----+--------------+-----------------------------------------+---------------+

-- Where was the first flight the next day going?
SELECT full_name
FROM airports
JOIN flights ON destination_airport_id = airports.id
WHERE origin_airport_id = 8
AND year = '2023'
AND month = '7'
AND day = '29'
ORDER BY hour
LIMIT 1;

-- This leaves:
+-------------------------------------+
|              full_name              |
+-------------------------------------+
| LaGuardia Airport                   |
+-------------------------------------+

-- Who got a flight the next morning to LaGuardia Airport?
SELECT name FROM flights
JOIN airports ON airports.id = flights.destination_airport_id
JOIN passengers ON passengers.flight_id = flights.id
JOIN people ON people.passport_number = passengers.passport_number
WHERE month = '7'
AND day = '29'
AND hour < 12
AND airports.id = 4;

-- This leaves:
+--------+
|  name  |
+--------+
| Doris  |
| Sofia  |
| Bruce  |
| Edward |
| Kelsey |
| Taylor |
| Kenny  |
| Luca   |
+--------+

-- Compare for cross overs
SELECT name FROM (
    SELECT distinct name FROM people
    JOIN bank_accounts ON bank_accounts.person_id = people.id
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    JOIN phone_calls ON phone_calls.caller = people.phone_number
    JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
    WHERE atm_location = 'Leggett Street'
    AND atm_transactions.month = '7'
    AND atm_transactions.day = '28'
    AND bakery_security_logs.minute BETWEEN 15 AND 30
    AND duration < 60
    AND caller IS NOT NULL
    AND activity = "exit"
)
INTERSECT
SELECT name FROM (
    SELECT name FROM flights
    JOIN airports ON airports.id = flights.destination_airport_id
    JOIN passengers ON passengers.flight_id = flights.id
    JOIN people ON people.passport_number = passengers.passport_number
    WHERE month = '7'
    AND day = '29'
    AND hour < 12
    AND airports.id = 4
);

-- This leaves:
+--------+
|  name  |
+--------+
| Bruce  |
+--------+

-- Who was Bruce calling when he left the bakery?
SELECT distinct name FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE caller = "(367) 555-5533"
AND phone_calls.year = '2023'
AND phone_calls.month = '7'
AND phone_calls.day = '28'
AND duration < 60;

-- This leaves:
+-------+
| name  |
+-------+
| Robin |
+-------+
