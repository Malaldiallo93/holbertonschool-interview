#!/usr/bin/python3

"""
Module for Prime Game.

This module contains functions to determine the winner of a game
where players take turns picking prime numbers and removing them
and their multiples from a set of consecutive integers.
"""

def sieve(n):
    """
    Compute all prime numbers up to n using the Sieve of Eratosthenes.

    Args:
        n (int): The upper bound up to which primes need to be computed.

    Returns:
        list: A boolean list where the index i is True if i is prime,
              False otherwise.
    """
    primes = [True] * (n + 1)
    primes[0] = primes[1] = False  # 0 and 1 are not prime numbers

    for i in range(2, int(n ** 0.5) + 1):
        if primes[i]:  # If i is prime
            for j in range(i * i, n + 1, i):
                primes[j] = False  # Mark multiples of i as non-prime

    return primes


def count_primes_up_to(n, prime_sieve):
    """
    Count the number of prime numbers up to n using a precomputed sieve.

    Args:
        n (int): The number up to which prime numbers need to be counted.
        prime_sieve (list): The precomputed sieve marking prime numbers.

    Returns:
        int: The count of prime numbers less than or equal to n.
    """
    return sum(prime_sieve[:n + 1])  # Sum the primes up to n


def isWinner(x, nums):
    """
    Determine the winner of a prime game played between Maria and Ben.

    The game follows these rules:
    - Maria always plays first.
    - Players take turns picking a prime number and removing it along 
      with its multiples from the set {1, ..., n}.
    - The player who cannot make a move loses.
    - The game is played for x rounds with different values of n.

    Args:
        x (int): The number of rounds played.
        nums (list of int): List of values for n in each round.

    Returns:
        str or None: The name of the player who wins the most rounds, 
                     or None if there's a tie.
    """

    if not nums or x < 1:
        return None  # If input is invalid, return None

    max_n = max(nums)  # Find the largest number in the rounds
    prime_sieve = sieve(max_n)  # Precompute primes up to max_n

    maria_wins = 0  # Maria's win count
    ben_wins = 0    # Ben's win count

    for n in nums:
        prime_count = count_primes_up_to(n, prime_sieve)
        if prime_count % 2 == 1:  # Odd prime count → Maria wins
            maria_wins += 1
        else:  # Even prime count → Ben wins
            ben_wins += 1

    if maria_wins > ben_wins:
        return "Maria"
    elif ben_wins > maria_wins:
        return "Ben"
    return None  # Return None in case of a tie
