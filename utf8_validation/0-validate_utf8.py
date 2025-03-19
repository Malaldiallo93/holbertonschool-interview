#!/usr/bin/python3
"""
    Script to UTF-8 validation
"""


def one_byte_encoding(number: int):
    """
        Checks if the provided number represents a one-byte UTF-8.

        Args:
            number (int): The integer representing the byte.

        Returns:
            bool: True if the byte represents a one-byte character.
        """
    # check if 8th bit is set
    if number & 1 << 7 == 0:
        return True
    return False


def byte_encoding(byte_len, data, i):
    """
       Checks if the sequence of bytes starting from the provided index
       represents a multibyte UTF-8 character.

       Args:
           byte_len (int): The length of the multibyte character.
           data (list[int]): The list of integers representing the UTF-8
           encoded data.
           i (int): The starting index of the sequence.

       Returns:
           bool: True if the sequence represents a valid multibyte
           character, otherwise False.
       """
    n = len(data)
    # out of bound check
    if i + byte_len > n:
        return False

    # first byte should be byte_len 1's followed by 0
    first_byte = data[i]
    for j in range(byte_len):
        if first_byte & 1 << (7 - j) == 0:
            return False

    # check that n+1 bit to be 0
    if first_byte & 1 << 7 - byte_len != 0:
        return False

    # the rest n-1 bytes should be 10xxxxxx
    for j in range(i + 1, i + 1 + (byte_len - 1)):
        # Check if the byte starts with '10'
        if data[j] & 1 << 7 == 0:
            return False
        if data[j] & 1 << 6 != 0:
            return False
    return True


def validUTF8(data):
    """
         method that determines if a given data set represents
         a valid UTF-8.

        :param data: list of integer

        :return: True if data valid UTF-8, else False
    """

    n = len(data)
    i = 0

    while i < n:
        valid_encoding = False
        # Check for one-byte encoding
        if one_byte_encoding(data[i]):
            i += 1
            valid_encoding = True

        # Check for multi-byte encoding (2 to 4 bytes)
        for byte_len in range(2, 4 + 1):
            if byte_encoding(byte_len, data, i):
                i += byte_len
                valid_encoding = True
                break

        if not valid_encoding:
            return False
    return True
