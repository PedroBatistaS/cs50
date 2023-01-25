-- Keep a log of any SQL queries you execute as you solve the mystery.
/*
First of all I start to find wich descriptions mentioned the bakery in the day.
*/

SELECT description
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28
AND street = "Humphrey Street";


SELECT name, transcript
FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28;

/*
Three people (Eugene, Raymon and Ruth) in their transcript went to the bakery at that day, at that hour.
*/

/*
Ruth said: "Sometime within ten minutes of the theft,
I saw the thief get into a car in the bakery parking lot and drive away.
If you have security footage from the bakery parking lot,
you might want to look for cars that left the parking lot in that time frame."

So I found the cars and name of the people that exit the parking between 10:15-10:25
*/

SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.activity = 'exit'
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25
ORDER BY bakery_security_logs.minute;


/*
Now I get a first suspect list:
+---------+------+--------+
|  name   | hour | minute |
+---------+------+--------+
| Vanessa | 10   | 16     |
| Bruce   | 10   | 18     |
| Barry   | 10   | 18     |
| Luca    | 10   | 19     |
| Sofia   | 10   | 20     |
| Iman    | 10   | 21     |
| Diana   | 10   | 23     |
| Kelsey  | 10   | 23     |
+---------+------+--------+

Then I decided to move on to the next clue.
Eugene gave us this new clue: "I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at Emma's bakery,
I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

Select the people who withdraw some money in that street and his names with the number account.
*/

SELECT account_number, amount
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

SELECT name, atm_transactions.amount
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';

/*
This was the result,
+---------+--------+
|  name   | amount |
+---------+--------+
| Bruce   | 50     |
| Diana   | 35     |
| Brooke  | 80     |
| Kenny   | 20     |
| Iman    | 20     |
| Luca    | 48     |
| Taylor  | 60     |
| Benista | 30     |
+---------+--------+

When I compare both results these names were in the both tables: Diana, Luca, Iman y Bruce.

Next I started with the last clue of Raymon: "As the thief was leaving the bakery,
they called someone who talked to them for less than a minute. In the call,
I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket."

So first I decided to found out information about the calls.
*/

SELECT name, phone_calls.duration
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;

SELECT name, phone_calls.duration
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;



/*

The callers:
+---------+----------+
|  name   | duration |
+---------+----------+
| Kelsey  | 36       |
| Carina  | 38       |
| Taylor  | 43       |
| Bruce   | 45       |
| Diana   | 49       |
| Kelsey  | 50       |
| Sofia   | 51       |
| Benista | 54       |
| Kenny   | 55       |
| Kathryn | 60       |
+---------+----------+

The recievers:
+------------+----------+
| Larry      | 36       |
| Jacqueline | 38       |
| James      | 43       |
| Robin      | 45       |
| Philip     | 49       |
| Melissa    | 50       |
| Jack       | 51       |
| Anna       | 54       |
| Doris      | 55       |
| Luca       | 60       |
+------------+----------+

Bruce-Robin, Diana-Philip and Sofia-Jack

I keep going with the flights. So I found the name of the airport and the earliest
flight for the 29th of July.
*/

SELECT abbreviation, full_name, city
FROM airports
WHERE city = 'Fiftyville';

/*
Result:
+--------------+-----------------------------+------------+
| abbreviation |          full_name          |    city    |
+--------------+-----------------------------+------------+
| CSF          | Fiftyville Regional Airport | Fiftyville |
+--------------+-----------------------------+------------+
*/

SELECT flights.id, full_name, city, flights.hour, flights.minute
FROM airports
JOIN flights
ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id =
(SELECT id
FROM airports
WHERE city = 'Fiftyville')
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour, flights.minute;

/*
Result:
+----+-------------------------------------+---------------+------+--------+
| id |              full_name              |     city      | hour | minute |
+----+-------------------------------------+---------------+------+--------+
| 36 | LaGuardia Airport                   | New York City | 8    | 20     |
| 43 | O'Hare International Airport        | Chicago       | 9    | 30     |
| 23 | San Francisco International Airport | San Francisco | 12   | 15     |
| 53 | Tokyo International Airport         | Tokyo         | 15   | 20     |
| 18 | Logan International Airport         | Boston        | 16   | 0      |
+----+-------------------------------------+---------------+------+--------+

When I discovered that the first flight was to NY I started looking for the information about these flight
*/

SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE flights.year = 2021
AND flights.month = 7
AND flights.day = 29
AND flights.hour = 8
AND flights.minute = 20
ORDER BY passengers.passport_number;

/*
The only coincidence in all the three clues was Bruce.
My conclusion is that the thief is Bruce beacuse is the only coincidence.
His partner was Robin, he calls to buy a flight ticket
To NY because is the earlist flight