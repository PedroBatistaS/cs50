# TODO
import sys
from cs50 import get_int


def valid_card(credit_number):
    credit_number = str(credit_number)
    if len(credit_number) < 13 or 16 < len(credit_number):  # Checks the length of the number
        print("INVALID")
        sys.exit(0)

    e = 0
    o = 0
    length = len(credit_number)

    if length % 2 == 0:             # even
        for i in range(length):
            num = int(credit_number[i])
            if i % 2 == 0:
                m = num * 2
                if m >= 10:
                    e += m // 10
                    e += m % 10
                else:
                    e += m
            else:
                o += num            # Multiply
    else:
        for j in range(length):
            num = int(credit_number[j])
            if j % 2 != 0:
                m = num * 2
                if m >= 10:
                    e += m // 10
                    e += m % 10
                else:
                    e += m
            else:
                o += num                # Multiply

    checksum = (e + o) % 10             # The checksum

    if checksum == 0:                   # Validate the type of credit number
        first_digit = int(credit_number[0])
        second_digit = int(credit_number[1])
        if first_digit == 3 and second_digit == 4 or second_digit == 7:
            print("AMEX")
        elif first_digit == 5 and 1 <= second_digit <= 5:
            print("MASTERCARD")
        elif first_digit == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    credit_number = get_int("Number: ")
    valid_card(credit_number)