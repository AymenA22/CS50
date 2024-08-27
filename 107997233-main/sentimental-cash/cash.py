from cs50 import get_float

cents = 0  # Variable for change (in cents)
coin_count = 0  # Variable to count the number of of coins

while cents <= 0:  # If change is less than or equal to 0 then exit otherwise continue
    cents = int(get_float("Change owed: ") * 100)

# While cents is greater than 0, take away largest coin possible  and increment count

# If the change owed in cents is greater than 0 then minus cents from the number
# 67p - 50p = 17p and increment the coin_count by 1
# 17p - 50p does not work so move to elif
# 17p - 20p does not work so move to elif
# 17p - 10p = 7p and increment the coin_count by 1
# 7p - 10p does not work so move to elif
# 7p - 5p = 2p and increment the coin_count by 1
# 2p - 5p does not work so move to elif
# 2p - 2p = 0p and increment the coin_count by 1
# Now at 0p, print the coin_count = 4

while cents > 0:
    if cents >= 25:
        cents = cents - 25
        coin_count = coin_count + 1
    elif cents >= 10:
        cents = cents - 10
        coin_count = coin_count + 1
    elif cents >= 5:
        cents = cents - 5
        coin_count = coin_count + 1
    elif cents >= 1:
        cents = cents - 1
        coin_count = coin_count + 1

print(coin_count)
